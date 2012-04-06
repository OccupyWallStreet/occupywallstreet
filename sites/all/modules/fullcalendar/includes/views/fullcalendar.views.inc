<?php

/**
 * @file
 * Contains Views module hooks.
 */

/**
 * Implements hook_views_plugins().
 */
function fullcalendar_views_plugins() {
  $path = drupal_get_path('module', 'fullcalendar');
  return array(
    'module' => 'fullcalendar',
    'style' => array(
      'fullcalendar' => array(
        'title' => t('FullCalendar'),
        'help' => t('Displays items on a calendar.'),
        'handler' => 'fullcalendar_plugin_style_fullcalendar',
        'path' => $path . '/includes/views/plugins',
        'theme' => 'fullcalendar',
        'theme file' => 'theme.inc',
        'theme path' => $path . '/theme',
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'uses grouping' => TRUE,
        'even empty' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}

/**
 * Implements hook_views_plugins_alter().
 */
function fullcalendar_views_plugins_alter(&$plugins) {
  $plugins['display']['fullcalendar'] = array(
    'title' => t('FullCalendar - Deprecated, use page display instead!'),
    'help' => t('Stop using this display, use page instead'),
    'no ui' => TRUE,
  ) + $plugins['display']['page'];
}

/**
 * Implements hook_views_data().
 */
function fullcalendar_views_data() {
  $data = array();

  $data['fullcalendar'] = array(
    'table' => array(
      'group' => t('FullCalendar'),
      'join' => array('#global' => array()),
    ),
    'gcal' => array(
      'title' => t('Google Calendar'),
      'help' => t('Display events from a Google Calendar.'),
      'field' => array(
        'handler' => 'fullcalendar_handler_field_gcal',
      ),
    ),
  );

  return $data;
}

/**
 * Implements hook_views_pre_view().
 *
 * Add an argument that provides the current date for each date field present.
 */
function fullcalendar_views_pre_view(&$view, &$display_id, &$args) {
  if ($view->display_handler->get_option('style_plugin') != 'fullcalendar') {
    return;
  }

  // Get the current view settings.
  $view->init_style();
  $settings = $view->style_plugin->options;

  fullcalendar_include_api();
  $fullcalendar_options = module_invoke_all('fullcalendar_options_info');
  uasort($fullcalendar_options, 'drupal_sort_weight');
  foreach (array_intersect(array_keys($fullcalendar_options), module_implements('fullcalendar_options_pre_view')) as $module) {
    $function = $module . '_fullcalendar_options_pre_view';
    $function($settings, $view);
  }

  // Set the new view settings.
  $view->style_plugin->options = $settings;

  // If we're not using ajax, we're done.
  if (!$view->display_handler->get_option('use_ajax')) {
    return;
  }

  // If a date is specifed to be the default find the range needed.
  if (!empty($settings['date'])) {
    $date_string = $settings['date']['year'] . '-' . $settings['date']['month'];
    // The month value is zero-based, so use that for start and add 2 for end.
    $start = date('Y-m', strtotime($date_string));
    $end = date('Y-m', strtotime($date_string . ' +2 months'));
    $range = $start . '--' . $end;
  }
  else {
    $range = date('Y-m', strtotime('-1 month')) . '--' . date('Y-m', strtotime('+1 month'));
  }

  // Loop through each date field and provide an argument for it.
  foreach ($view->display_handler->get_handlers('field') as $field) {
    if (fullcalendar_field_is_date($field)) {
      // Add an argument for the date field.
      $options = array(
        'default_action' => 'default',
        'default_argument_type' => 'fixed',
        'default_argument_options' => array(
          'argument' => $range,
        ),
      );
      if (!empty($field->options['relationship'])) {
        $options['relationship'] = $field->options['relationship'];
      }
      $view->add_item($display_id, 'argument', 'field_data_' . $field->field, $field->field . '_value', $options);
      $view->fullcalendar_args++;
    }
  }
}

/**
 * Implements hook_views_query_alter().
 *
 * Force the query to be distinct. Also, if there are multiple date arguments,
 * group them with 'OR'.
 */
function fullcalendar_views_query_alter(&$view, &$query) {
  if ($view->display_handler->get_option('style_plugin') != 'fullcalendar') {
    return;
  }

  $query->distinct = TRUE;

  if (empty($view->fullcalendar_args) || count($view->args) < $view->fullcalendar_args) {
    return;
  }

  // @todo Remove this once http://drupal.org/node/1367304 is resolved.
  $query->group_operator = 'AND';

  // Remove our arguments from the main set.
  $arguments = array();
  for ($i = 0; $i < $view->fullcalendar_args; $i++) {
    $arguments[] = array_pop($query->where[0]['conditions']);
  }
  // Add them as a second set of conditions.
  $query->where[] = array(
    'conditions' => $arguments,
    'args' => array(),
    'type' => 'OR',
  );
}
