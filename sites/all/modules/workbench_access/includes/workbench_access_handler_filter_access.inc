<?php

/**
 * @file
 * Views integration for Workbench.
 *
 * Provides a filter to display nodes by assigned section.
 */

class workbench_access_handler_filter_access extends views_handler_filter_many_to_one {
  function option_definition() {
    $options = parent::option_definition();
    $options['access_id'] = array('default' => NULL);
    $options['size'] = array('default' => 5);
    return $options;
  }

  function operator_options($which = 'title') {
    return array(
      'or' => t('Is one of'),
    );
  }

  function value_form(&$form, &$form_state) {
    $active = workbench_access_get_active_tree();
    $tree = $active['tree'];
    workbench_access_build_tree($tree, array_keys($active['active']));
    $options = workbench_access_options($tree, $active['active']);
    $form['access_id'] = array(
      '#type' => 'select',
      '#title' => t('Sections'),
      '#multiple' => TRUE,
      '#options' => $options,
      '#default_value' => $this->options['access_id'],
      '#size' => $this->options['size'],
    );
    $form['size'] = array(
      '#type' => 'select',
      '#title' => t('Size'),
      '#options' => drupal_map_assoc(array(1, 5, 10, 20, 50)),
      '#default_value' => $this->options['size'],
    );
  }

  function exposed_form(&$form, &$form_state) {
    // Prevent parent form errors by using a value.
    $form['value'] = array('#type' => 'value', '#value' => '');
    parent::exposed_form($form, $form_state);
    // Build our form element.
    $active = workbench_access_get_active_tree();
    $tree = workbench_access_get_user_tree();
    $options = workbench_access_options($tree, $active['active']);
    $form['access_id'] = array(
      '#type' => 'select',
      '#multiple' => TRUE,
      '#options' => $options,
      '#default_value' => $this->options['access_id'],
      '#size' => $this->options['size'],
    );
    unset($form['size']);
  }

  function exposed_submit(&$form, &$form_state) {
    if (empty($form_state['values']['access_id'])) {
      $form_state['values']['access_id'] = -5;
    }
  }

  function query() {
    global $user;
    static $node_types;

    // If not configured, do nothing.
    $active = workbench_access_get_active_tree();
    $tree = $active['tree'];
    if (empty($tree)) {
      return;
    }

    // Check the user's access.
    $account = $user; // Not a clone, but that's ok, since we need this data on $user.
    if (!isset($account->workbench_access)) {
      workbench_access_user_load_data($account);
    }
    // If empty, return nothing by forcing a null return.
    if (empty($account->workbench_access)) {
      $table = $this->view->base_table;
      $this->query->add_where($this->options['group'], "$table.nid", -1, '=');
      return;
    }

    // No selection? Use the user's tree.
    if (empty($this->value) || $this->value[0] == -5) {
      workbench_access_build_tree($tree, array_keys($account->workbench_access));
    }
    // Build the selection tree.
    else {
      workbench_access_build_tree($tree, array_keys($this->value[0]));
    }

    // Build the query. Since we allow multi-select, this has to be a subquery.
    $ids = array_keys($tree);
    $table = $active['access_scheme']['field_table'];
    $subquery = db_select($table, $table);
    $subquery->addField($table, 'nid');
    $subquery->distinct();
    $subquery->condition($table . '.' . $active['access_scheme']['query_field'], $ids, 'IN');
    $subquery->condition($table . '.access_scheme', $active['access_scheme']['access_scheme']);

    // Filter out node types not governed by this module.
    // See http://drupal.org/node/1082220.
    if (!isset($node_types)) {
      $node_types = array();
      foreach (node_type_get_names() as $type => $name) {
        $node_types[$type] = variable_get('workbench_access_node_type_' . $type, 1);
      }
      if ($node_types == array_filter($node_types)) {
        // If there were no node types that are not allowed, set the static
        // variable to FALSE to indicate no restriction by node type.
        $node_types = FALSE;
      }
    }
    // If not all node types are allowed, filter out those not used.
    // This has to go in the subquery, not the Views query.
    if ($node_types !== FALSE) {
      $alias = $subquery->join('node', 'n', "$table.nid = n.nid");
      $subquery->condition("$alias.type", array_keys($node_types), 'IN');
    }

    // Now alter the query, which must have an nid in the base table.
    $this->query->add_where($this->options['group'], $this->query->base_table . '.nid', $subquery, 'IN');

  }
}
