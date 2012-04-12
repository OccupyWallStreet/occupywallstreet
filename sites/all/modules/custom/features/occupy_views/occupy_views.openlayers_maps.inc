<?php
/**
 * @file
 * occupy_views.openlayers_maps.inc
 */

/**
 * Implements hook_openlayers_maps().
 */
function occupy_views_openlayers_maps() {
  $export = array();

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'ows_locations';
  $openlayers_maps->title = 'Map of common Occupy Locations around NYC';
  $openlayers_maps->description = 'Map of common Occupy Locations around NYC';
  $openlayers_maps->data = array(
    'width' => 'auto',
    'height' => '520px',
    'image_path' => 'sites/all/modules/openlayers/themes/default_dark/img/',
    'css_path' => 'sites/all/modules/openlayers/themes/default_dark/style.css',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '-74.010202744059, 40.708686191417',
        'zoom' => '15',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_argparser' => array(
        'anchor' => 0,
      ),
      'openlayers_behavior_keyboarddefaults' => array(),
      'openlayers_behavior_layerswitcher' => array(
        'ascending' => 0,
        'roundedCorner' => 1,
        'roundedCornerColor' => '#222222',
      ),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 1,
        'zoomBoxEnabled' => 1,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_panzoombar' => array(
        'zoomWorldIcon' => 0,
        'panIcons' => 1,
      ),
      'openlayers_behavior_permalink' => array(
        'anchor' => 0,
      ),
      'openlayers_behavior_popup' => array(
        'layers' => array(
          'ows_locations_openlayers_1' => 'ows_locations_openlayers_1',
        ),
      ),
      'openlayers_behavior_scaleline' => array(),
    ),
    'default_layer' => 'mapquest_osm',
    'layers' => array(
      'osm_mapnik' => 'osm_mapnik',
      'osm_tah' => 'osm_tah',
      'osm_cycle' => 'osm_cycle',
      'mapquest_osm' => 'mapquest_osm',
      'mapquest_openaerial' => 'mapquest_openaerial',
      'ows_locations_openlayers_1' => 'ows_locations_openlayers_1',
    ),
    'layer_weight' => array(
      'ows_locations_openlayers_1' => '0',
      'openlayers_geojson_picture_this' => '0',
      'geofield_formatter' => '0',
    ),
    'layer_styles' => array(
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'ows_locations_openlayers_1' => 'default_marker_black_small',
    ),
    'layer_styles_select' => array(
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'ows_locations_openlayers_1' => 'default_marker_black_small',
    ),
    'layer_activated' => array(
      'ows_locations_openlayers_1' => 'ows_locations_openlayers_1',
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
    ),
    'layer_switcher' => array(
      'ows_locations_openlayers_1' => 0,
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
    ),
    'projection' => '900913',
    'displayProjection' => '4326',
    'styles' => array(
      'default' => 'default',
      'select' => 'default',
      'temporary' => 'default',
    ),
  );
  $export['ows_locations'] = $openlayers_maps;

  return $export;
}
