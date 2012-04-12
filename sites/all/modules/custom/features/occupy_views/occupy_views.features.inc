<?php
/**
 * @file
 * occupy_views.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function occupy_views_ctools_plugin_api() {
  return array("version" => "1");
}

/**
 * Implements hook_views_api().
 */
function occupy_views_views_api() {
  return array("version" => "3.0");
}
