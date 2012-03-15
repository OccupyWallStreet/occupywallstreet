<?php
// $Id$

/**
 * @file
 * Plugin to provide a google geocoder.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Google Geocoder"),
  'description' => t('Geocodes via google geocoder'),
  'callback' => 'geocoder_google',
  'field_types' => array('text','text_long','addressfield','text_with_summary','computed'),
  'field_callback' => 'geocoder_google_field',
);

/**
 * Process Markup
 */
function geocoder_google($address, $return = 'point') {
  geocoder_load_geophp();
  
  $query = array(
    'address' => $address,
    'sensor' => 'false'
  );
  
  $url = url("http://maps.googleapis.com/maps/api/geocode/json", array('query' => $query));
  $result = drupal_http_request($url);
  
  if (isset($result->error)) {
    drupal_set_message('Error geocoding: '.$result->code.' '.$result->error,'error');
    return FALSE;
  }
  
  $data = json_decode($result->data);
  
  if ($data->status == 'OK') {
    $geometries = array();
    
    foreach ($data->results as $item) {
      $geom = new Point($item->geometry->location->lng, $item->geometry->location->lat);
      
      // Add additional metadata to the geometry - it might be useful!
      $geom->data = array();
      $geom->data['geocoder_accuracy'] = $item->geometry->location_type;
      $geom->data['geocoder_formatted_address'] = $item->formatted_address;
      $geom->data['geocoder_address_components'] = $item->address_components;
      
      $geometries[] = $geom;
    }
    
    // The connonical geometry is the first result
    $geometry = array_shift($geometries);
    
    // If there are any other geometries, these are auxiliary geometries that represent "alternatives"
    if (count($geometries)) $geometry->data['geocoder_alternatives'] = $geometries;
    
    return $geometry;
  }
  else {
    drupal_set_message('Error geocoding: '.$data->status,'error');
    return FALSE;
  }
}

function geocoder_google_field($field, $field_item) {
  if ($field['type'] == 'text' || $field['type'] == 'text_long' || $field['type'] == 'text_with_summary' || $field['type'] == 'computed') {
    return geocoder_google($field_item['value']);
  }
  if ($field['type'] == 'addressfield') {
    $address = geocoder_widget_parse_addressfield($field_item);
    return geocoder_google($address);
  }
}
