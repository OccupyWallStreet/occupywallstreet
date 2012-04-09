<?php

/**
 * @file
 * Menu integration for Workbench Access.
 */

/**
 * Implements hook_workbench_access_info().
 *
 * Defines the default handler for access controls.
 */
function menu_workbench_access_info() {
  return array(
    'menu' => array(
      'access_scheme' => 'menu',
      'name' => t('Menu'),
      'access_type' => 'menu',
      'access_type_id' => array_filter(variable_get('workbench_access_menu', array('main-menu'))),
      'description' => t('Uses the menu system for assigning hierarchical access control.'),
      'configuration' => 'menu_workbench_access_configuration',
      'node_table' => 'workbench_access_node',
      'query_field' => 'access_id',
      'field_table' => 'workbench_access_node',
      'adjust_join' => array(
        'menu_links' => array(
          'original_table' => 'menu_links',
          'original_field' => 'mlid',
          'new_table' => 'workbench_access_node',
          'new_field' => 'access_id',
        ),
      ),
      'sort' => array(
        array(
          'table' => 'menu_links',
          'field' => 'plid',
        ),
        array(
          'table' => 'menu_links',
          'field' => 'weight',
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
function menu_workbench_access_configuration(&$form, &$form_state) {
  $options = array();
  $menus = menu_get_menus();
  foreach ($menus as $name => $menu) {
    $options[$name] = $menu;
  }
  $form['menu_workbench_access_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Menu scheme settings'),
    '#states' => array(
      'visible' => array(
        ':input[name=workbench_access]' => array('value' => 'menu'),
      ),
    ),
  );
  $form['menu_workbench_access_info']['workbench_access_menu'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Editorial menus'),
    '#description' => t('Select the menus to be used for access control.'),
    '#options' => $options,
    '#default_value' => variable_get('workbench_access_menu', array('main_menu')),
    '#states' => array(
      'visible' => array(
        ':input[name=workbench_access]' => array('value' => 'menu'),
      ),
    ),
  );
}

/**
 * Implements hook_workbench_access_tree().
 *
 * Get the access tree for a menu item.
 *
 * @param $info
 *   An array defining the access scheme.
 * @param $keys
 *   Boolean value to return only array keys, or all data.
 *
 * @return
 *   An array of access_ids or a data array.
 */
function menu_workbench_access_tree($info, $keys) {
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
    foreach (array_filter($info['access_type_id']) as $key) {
      $items[$key] = 0;
    }
  }
  foreach ($items as $name => $mlid) {
    $data = menu_load($name);
    $tree[$name] = array(
      'access_id' => $data['menu_name'],
      'access_type_id' => $data['menu_name'],
      'name' => $data['title'],
      'description' => $data['description'],
      'weight' => 0,
      'depth' => 0,
      'parent' => 0,
    );
    $menu = menu_tree_all_data($name);
    foreach ($menu as $link) {
      // Ensure that we start at the top of the current request.
      if ($mlid > 0 && $link['link']['mlid'] == $mlid) {
        $tree = array();
        _workbench_access_menu_build_tree($tree, $link);
      }
      elseif ($mlid == 0) {
        _workbench_access_menu_build_tree($tree, $link);
      }
    }
  }
  if ($keys) {
    return array_keys($tree);
  }
  return $tree;
}

/**
 * Recursive helper function to build menus.
 *
 * @param &$tree
 *   The workbench access tree being built.
 * @param $link
 *   The menu link being inspected.
 */
function _workbench_access_menu_build_tree(&$tree, $link) {
  $item = (object) $link['link'];
  $tree[$item->mlid] = array(
    'access_id' => $item->mlid,
    'access_type_id' => $item->menu_name,
    'name' => $item->link_title,
    'description' => isset($item->options['attributes']['title']) ? $item->options['attributes']['title'] : '',
    'weight' => $item->weight,
    'depth' => $item->depth,
    'parent' => ($item->plid == 0) ? $item->menu_name : $item->plid,
  );
  if (!empty($link['below'])) {
    foreach ($link['below'] as $below) {
      _workbench_access_menu_build_tree($tree, $below);
    }
  }
}

/**
 * Implements hook_workbench_access_load().
 *
 * Load data for a menu.
 */
function menu_workbench_access_load($scheme) {
  // This might be a menu or a single menu item.
  if ($menu = menu_load($scheme['access_id'])) {
    $menu = (object) $menu;
    $data = array(
      'access_id' => $menu->menu_name,
      'name' => $menu->title,
      'description' => $menu->description,
    );
  }
  else {
    $item = (object) menu_link_load($scheme['access_id']);
    $data = array(
      'access_id' => $item->mlid,
      'name' => $item->link_title,
      'description' => isset($item->options['attribute']['description']) ? $item->options['attribute']['description'] : '',
    );
  }
  return $data;
}

/**
 * Implements hook_menu_delete().
 *
 * If an active menu is deleted, cascade the change through our system.
 */
function workbench_access_menu_delete($menu) {
  $access_scheme = db_query("SELECT * FROM {workbench_access} WHERE access_type = :access_type AND access_id = :access_id", array(':access_type' => 'menu', ':access_id' => $menu['menu_name']))->fetchAssoc();
  if (!empty($access_scheme)) {
    workbench_access_section_delete($access_scheme);
  }
}

/**
 * Implements hook_menu_link_insert().
 *
 * If an new link is added, check to see if we need to create a section.
 */
function workbench_access_menu_link_insert($link) {
  if (variable_get('workbench_access', 'taxonomy') != 'menu' || !variable_get('workbench_access_auto_assign', 1)) {
    return;
  }
  $active = array_filter(variable_get('workbench_access_menu', array()));
  if (in_array($link['menu_name'], $active)) {
    $section = array(
      'access_id' => $link['mlid'],
      'access_type' => 'menu',
      'access_scheme' => 'menu',
      'access_type_id' => $link['menu_name'],
    );
    workbench_access_section_save($section);
  }
}

/**
 * Implements hook_menu_link_delete().
 *
 * If an active menu link is deleted, cascade the change through our system.
 */
function workbench_access_menu_link_delete($link) {
  $access_scheme = db_query("SELECT * FROM {workbench_access} WHERE access_type = :access_type AND access_id = :access_id", array(':access_type' => 'menu', ':access_id' => $link['mlid']))->fetchAssoc();
  if (!empty($access_scheme)) {
    workbench_access_section_delete($access_scheme);
  }
}
