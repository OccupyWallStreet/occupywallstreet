<?php

/**
 * @file
 * Taxonomy integration for Workbench Access.
 */

/**
 * Implements hook_workbench_access_info().
 *
 * Defines the default handler for access controls.
 */
function taxonomy_workbench_access_info() {
  return array(
    'taxonomy' => array(
      'access_scheme' => 'taxonomy',
      'name' => t('Taxonomy'),
      'access_type' => 'taxonomy',
      'access_type_id' => array_filter(variable_get('workbench_access_taxonomy', array())),
      'description' => t('Uses taxonomy vocabularies for assigning hierarchical access control.'),
      'configuration' => 'taxonomy_workbench_access_configuration',
      'query_field' => 'access_id',
      'field_table' => 'workbench_access_node',
      'adjust_join' => array(
        'taxonomy_term_data' => array(
          'original_table' => 'taxonomy_index',
          'original_field' => 'tid',
          'new_table' => 'workbench_access_node',
          'new_field' => 'access_id',
        ),
      ),
      'sort' => array(
        array(
          'table' => 'taxonomy_term_hierarchy',
          'field' => 'parent',
        ),
        array(
          'table' => 'taxonomy_term_data',
          'field' => 'weight',
          'order' => 'ASC',
        ),
        array(
          'table' => 'taxonomy_term_data',
          'field' => 'name',
          'order' => 'ASC',
        ),
      ),
    ),
  );
}

/**
 * Defines configuration options for the default access scheme.
 *
 * @see workbench_access_workbench_access_info()
 */
function taxonomy_workbench_access_configuration(&$form, &$form_state) {
  $options = array();
  $vocabularies = taxonomy_get_vocabularies();
  foreach ($vocabularies as $vid => $vocabulary) {
    $options[$vocabulary->machine_name] = $vocabulary->name;
  }
  $form['taxonomy_workbench_access_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Taxonomy scheme settings'),
    '#states' => array(
      'visible' => array(
        ':input[name=workbench_access]' => array('value' => 'taxonomy'),
      ),
    ),
  );
  $form['taxonomy_workbench_access_info']['workbench_access_taxonomy'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Editorial vocabulary'),
    '#description' => t('Select the vocabularies to be used for access control.'),
    '#options' => $options,
    '#default_value' => variable_get('workbench_access_taxonomy', array()),
    '#states' => array(
      'visible' => array(
        ':input[name=workbench_access]' => array('value' => 'taxonomy'),
      ),
    ),
  );
}

/**
 * Implements hook_workbench_access_FORM_ID_alter().
 */
function taxonomy_workbench_access_field_form_alter(&$form, &$form_state, $active) {
  _workbench_access_taxonomy_remove_option($form);
}

/**
 * Implements hook_workbench_access_FORM_ID_alter().
 */
function taxonomy_workbench_access_field_ui_field_settings_form_alter(&$form, &$form_state, $active) {
  _workbench_access_taxonomy_remove_option($form);
}

/**
 * Helper function to remove the option from Field UI forms.
 */
function _workbench_access_taxonomy_remove_option(&$form) {
  // The element we want is nested very deeply in the form.
  if (!isset($form['field']['settings']['allowed_values'])) {
    return;
  }
  // Cannot trust positional arrays to find the options.
  foreach ($form['field']['settings']['allowed_values'] as $key => $value) {
    if (is_array($value) && isset($value['vocabulary']) && isset($form['field']['settings']['allowed_values'][$key]['vocabulary']['#options']['workbench_access'])) {
      unset($form['field']['settings']['allowed_values'][$key]['vocabulary']['#options']['workbench_access']);
    }
  }
}

/**
 * Implements hook_workbench_access_tree().
 *
 * Get the access tree for a taxonomy term.
 *
 * @param $info
 *   An array defining the access scheme.
 * @param $keys
 *   Boolean value to return only array keys, or all data.
 *
 * @return
 *   An array of access_ids or a data array.
 */
function taxonomy_workbench_access_tree($info, $keys) {
  $tree = array();
  $items = array();
  if (isset($info['access_id'])) {
    if ($info['access_type_id'] != $info['access_id']) {
      $items[$info['access_type_id']] = $info['access_id'];
    }
    else {
      $items[$info['access_type_id']] = 0;
    }
  }
  else {
    foreach (array_filter($info['access_type_id']) as $vid) {
      $items[$vid] = 0;
    }
  }
  foreach ($items as $vid => $tid) {
    $vocabulary = taxonomy_vocabulary_machine_name_load($vid);
    if ($tid == 0) {
      $tree[$vocabulary->machine_name] = array(
        'access_id' => $vocabulary->machine_name,
        'access_type_id' => $vocabulary->machine_name,
        'name' => $vocabulary->name,
        'description' => $vocabulary->description,
        'weight' => 0,
        'depth' => 0,
        'parent' => $vocabulary->machine_name,
      );
    }
    $children = taxonomy_get_tree($vocabulary->vid, $tid);
    foreach ($children as $child) {
      $tree[$child->tid] = array(
        'access_id' => $child->tid,
        'access_type_id' => $vocabulary->machine_name,
        'name' => $child->name,
        'description' => $child->description,
        'weight' => $child->weight,
        'depth' => $child->depth+1,
        'parent' => !empty($child->parents[0]) ? $child->parents[0] : $vocabulary->machine_name,
      );
    }
  }
  if ($keys) {
    return array_keys($tree);
  }
  return $tree;
}

/**
 * Implements hook_workbench_access_load().
 *
 * Load data for a taxonomy term.
 */
function taxonomy_workbench_access_load($scheme) {
  if ($vocabulary = taxonomy_vocabulary_machine_name_load($scheme['access_id'])) {
    $data = array(
      'name' => $vocabulary->name,
      'description' => $vocabulary->description,
      'access_id' => $vocabulary->machine_name,
    );
  }
  else {
    $term = taxonomy_term_load($scheme['access_id']);
    $data = array(
      'name' => $term->name,
      'description' => $term->description,
      'access_id' => $term->tid,
    );
  }
  return $data;
}

/**
 * Implements hook_taxonomy_term_insert().
 *
 * If an new term is added, check to see if we need to create a section.
 */
function workbench_access_taxonomy_term_insert($term) {
  if (variable_get('workbench_access', 'taxonomy') != 'taxonomy' || !variable_get('workbench_access_auto_assign', 1)) {
    return;
  }
  $active = array_filter(variable_get('workbench_access_taxonomy', array()));
  if (in_array($term->vocabulary_machine_name, $active)) {
    $section = array(
      'access_id' => $term->tid,
      'access_type' => 'taxonomy',
      'access_scheme' => 'taxonomy',
      'access_type_id' => $term->vocabulary_machine_name,
    );
    workbench_access_section_save($section);
  }
}

/**
 * Implements hook_taxonomy_term_delete().
 *
 * If an active term is deleted, cascade the change through our system.
 */
function workbench_access_taxonomy_term_delete($term) {
  $access_scheme = db_query("SELECT * FROM {workbench_access} WHERE access_type = :access_type AND access_id = :access_id", array(':access_type' => 'taxonomy', ':access_id' => $term->tid))->fetchAssoc();
  if (!empty($access_scheme)) {
    workbench_access_section_delete($access_scheme);
  }
}

/**
 * Implements hook_taxonomy_vocabulary_delete().
 *
 * If an active vocabulary is deleted, cascade the change through our system.
 */
function workbench_access_taxonomy_vocabulary_delete($vocabulary) {
  $access_scheme = db_query("SELECT * FROM {workbench_access} WHERE access_type = :access_type AND access_id = :access_id", array(':access_type' => 'taxonomy', ':access_id' => $vocabulary->machine_name))->fetchAssoc();
  if (!empty($access_scheme)) {
    workbench_access_section_delete($access_scheme);
  }
}
