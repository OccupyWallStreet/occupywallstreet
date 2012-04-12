<?php
/**
 * @file
 * occupy_misc.quicktabs.inc
 */

/**
 * Implements hook_quicktabs_default_quicktabs().
 */
function occupy_misc_quicktabs_default_quicktabs() {
  $export = array();

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'featured';
  $quicktabs->ajax = 1;
  $quicktabs->hide_empty_tabs = FALSE;
  $quicktabs->default_tab = 0;
  $quicktabs->title = 'Featured';
  $quicktabs->tabs = array(
    0 => array(
      'bid' => 'views_delta_nodequeue_1-block',
      'hide_title' => 1,
      'title' => 'Featured',
      'weight' => '-100',
      'type' => 'block',
    ),
    1 => array(
      'bid' => 'views_delta_nodequeue_2-block',
      'hide_title' => 1,
      'title' => 'Video',
      'weight' => '-99',
      'type' => 'block',
    ),
  );
  $quicktabs->renderer = 'quicktabs';
  $quicktabs->style = 'nostyle';
  $quicktabs->options = array();

  // Translatables
  // Included for use with string extractors like potx.
  t('Featured');
  t('Video');

  $export['featured'] = $quicktabs;

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'feeds';
  $quicktabs->ajax = 0;
  $quicktabs->hide_empty_tabs = TRUE;
  $quicktabs->default_tab = 0;
  $quicktabs->title = 'Feeds';
  $quicktabs->tabs = array(
    0 => array(
      'bid' => 'views_delta_ows_news_widget-block',
      'hide_title' => 1,
      'title' => 'In the News',
      'weight' => '-100',
      'type' => 'block',
    ),
    1 => array(
      'bid' => 'views_delta_ows_twitter_widget-block',
      'hide_title' => 1,
      'title' => 'On Twitter',
      'weight' => '-99',
      'type' => 'block',
    ),
  );
  $quicktabs->renderer = 'quicktabs';
  $quicktabs->style = 'nostyle';
  $quicktabs->options = array();

  // Translatables
  // Included for use with string extractors like potx.
  t('Feeds');
  t('In the News');
  t('On Twitter');

  $export['feeds'] = $quicktabs;

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'learn';
  $quicktabs->ajax = 0;
  $quicktabs->hide_empty_tabs = FALSE;
  $quicktabs->default_tab = 0;
  $quicktabs->title = 'Learn';
  $quicktabs->tabs = array(
    0 => array(
      'nid' => '20',
      'teaser' => 0,
      'hide_title' => 0,
      'title' => 'Declaration',
      'weight' => '-100',
      'type' => 'node',
    ),
    1 => array(
      'nid' => '22',
      'teaser' => 0,
      'hide_title' => 0,
      'title' => 'Solidarity',
      'weight' => '-99',
      'type' => 'node',
    ),
    2 => array(
      'nid' => '21',
      'teaser' => 0,
      'hide_title' => 0,
      'title' => 'Autonomy',
      'weight' => '-98',
      'type' => 'node',
    ),
    3 => array(
      'nid' => '23',
      'teaser' => 0,
      'hide_title' => 0,
      'title' => 'Good Neighbor',
      'weight' => '-97',
      'type' => 'node',
    ),
  );
  $quicktabs->renderer = 'quicktabs';
  $quicktabs->style = 'default';
  $quicktabs->options = array();

  // Translatables
  // Included for use with string extractors like potx.
  t('Autonomy');
  t('Declaration');
  t('Good Neighbor');
  t('Learn');
  t('Solidarity');

  $export['learn'] = $quicktabs;

  return $export;
}
