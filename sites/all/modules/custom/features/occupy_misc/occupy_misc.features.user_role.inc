<?php
/**
 * @file
 * occupy_misc.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function occupy_misc_user_default_roles() {
  $roles = array();

  // Exported role: Author
  $roles['Author'] = array(
    'name' => 'Author',
    'weight' => '2',
  );

  // Exported role: Content Editor
  $roles['Content Editor'] = array(
    'name' => 'Content Editor',
    'weight' => '4',
  );

  // Exported role: Content Manager
  $roles['Content Manager'] = array(
    'name' => 'Content Manager',
    'weight' => '5',
  );

  // Exported role: Curator
  $roles['Curator'] = array(
    'name' => 'Curator',
    'weight' => '3',
  );

  // Exported role: administrator
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => '6',
  );

  return $roles;
}
