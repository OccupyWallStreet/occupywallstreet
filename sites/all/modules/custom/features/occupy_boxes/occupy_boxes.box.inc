<?php
/**
 * @file
 * occupy_boxes.box.inc
 */

/**
 * Implements hook_default_box().
 */
function occupy_boxes_default_box() {
  $export = array();

  $box = new stdClass();
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'download_press_kit';
  $box->plugin_key = 'simple';
  $box->title = '<none>';
  $box->description = 'Download Our Press Kit.';
  $box->options = array(
    'body' => array(
      'value' => '<div class="contact-phone-background">1<div class="contact-number-text">Download Our Press Kit.</div><div class="contact-phone-text">Some messages about what that involves.</div></div>',
      'format' => 'full_html',
    ),
    'additional_classes' => 'box-class',
  );
  $export['download_press_kit'] = $box;

  $box = new stdClass();
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'join_team_box';
  $box->plugin_key = 'simple';
  $box->title = '<none>';
  $box->description = 'Join Our Content Team Box';
  $box->options = array(
    'body' => array(
      'value' => '<div class="node-blocks-background">1<div class="contact-number-text">Join Our Content Team.</div><div class="contact-phone-text">Some messages about what that involves.</div></div>',
      'format' => 'full_html',
    ),
    'additional_classes' => 'box-class',
  );
  $export['join_team_box'] = $box;

  return $export;
}
