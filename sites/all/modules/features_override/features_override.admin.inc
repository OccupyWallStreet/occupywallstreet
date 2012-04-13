<?php

/**
 * @file
 * Page callbacks features overrides admin pages.
 */

/**
 * Renders the differences for a component and element
 */
function features_override_render_differences($component = '', $element = '') {
  module_load_include('inc', 'features_override', 'features_override.export');
  module_load_include('inc', 'features', 'features.export');
  drupal_add_css(drupal_get_path('module', 'features_override') . '/features_override.css');
  $differences = features_override_get_overrides($component, $element, TRUE, !empty($component));
  if (!$differences || !count(array_filter($differences))) {
    return t('No overrides were found.');    
  }
  if (!empty($element)) {
    $differences = array($element => $differences);
  }
  if (!empty($component)) {
    $differences = array($component => $differences);
  }
  $rows = array();
  foreach ($differences as $component_name => $item) {
    $code_change = array();
    $code_add = array();
    $code_delete = array();
    foreach ($item as $element_name => $difference) {
      $key = (isset($_GET['key'])) ? $_GET['key'] : '';
      if (!empty($key)) {
        if (!empty($difference['additions'][$key])) {
          return '<pre>' . implode("\n", 
            features_override_features_export_render_addition($difference['additions'][$key], $element_name, $component_name)) . 
            '</pre>';
        }
        elseif (!empty($difference['deletions'][$key])) {
          return '<pre>' . implode("\n", 
            features_override_features_export_render_deletion($difference['deletions'][$key], $element_name, $component_name)) . 
            '</pre>';
        }
        else {
          return t('Unable to find referenced information.');
        }
      }
      else {
        if (!empty($difference['additions'])) {
          foreach ($difference['additions'] as $alter) {
            if (is_scalar($alter['value'])) {
              $code_change[] = array('<pre>' . implode("\n", features_override_features_export_render_addition($alter, $element_name, $component_name)). '</pre>');
            }
            else {
              $code_add[] = array('<pre>' . implode("\n", features_override_features_export_render_addition($alter, $element_name, $component_name)). '</pre>');
            }
          }
        }
        if (!empty($difference['deletions'])) {
          foreach ($difference['deletions'] as $alter) {
            $code_delete[] = array('<pre>' . implode("\n", features_override_features_export_render_deletion($alter, $element_name, $component_name)). '</pre>');
          }
        }
      }
    }
    if (count($code_add) || count($code_delete) || count($code_change)) {
      $rows[] = array(array('data' => $component_name, 'header' => TRUE));
    }
    if (count($code_change)) {
      $rows[] = array('CHANGES');
      $rows = array_merge($rows, $code_change);
    }
    if (count($code_add)) {
      $rows[] = array('ADDITIONS');
      $rows = array_merge($rows, $code_add);
    }
    if (count($code_delete)) {
      $rows[] = array('DELETIONS');
      $rows = array_merge($rows, $code_delete);
    }
  }
  return theme('table', array('rows' => $rows, 'attributes' => array('class' => 'features_override_table')));
}

/**
 * Page callback to display the differences between what's in code and
 * what is in the db.
 *
 * @param $feature
 *   A loaded feature object to display differences for.
 * @param $component
 *   Optional: specific component to display differences for. If excluded, all components are used.
 *
 * @return Themed display of what is different.
 */
function features_override_feature_diff($feature, $component = NULL) {
  if (module_exists('diff')) {
    module_load_include('inc', 'features', 'features.admin');
    $output = features_feature_diff($feature, $component);
    $output['diff'] = array(
      '#prefix' => '<h2>',
      '#markup' => 'Code diff',
      '#suffix' => '</h2>',
      '#weight' => -98,
      );
  }
  $output['overrides'] = array(
    '#markup' => features_override_render_differences(),
    '#weight' => -99,
    );
  return $output;
}
