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
  $box->delta = 'contact_phone_number';
  $box->plugin_key = 'simple';
  $box->title = '<none>';
  $box->description = 'Contact Us: Phone Number';
  $box->options = array(
    'body' => array(
      'value' => '<div class="contact-phone-background">1
	<div class="contact-number-text">855 NYCGA 411</div>
	<div class="contact-phone-text">Toll-free, real time voice access to events, schedule and announcements</div>
</div>
',
      'format' => 'full_html',
    ),
    'additional_classes' => 'box-class',
  );
  $export['contact_phone_number'] = $box;

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
  $box->delta = 'how_to_find_us';
  $box->plugin_key = 'simple';
  $box->title = '<none>';
  $box->description = 'How to find us ';
  $box->options = array(
    'body' => array(
      'value' => '<div class="contact-background">1
	<div class="contact-main-text">How to find us</div>
	<div class="contact-text">The best way to find us is to check out our</div>
	<div class="contact-icon">1</div>
	<div class="contact-bold-text">events listing on <a href="http://www.nycga.net/events/">nycga.net</a></div>
</div>',
      'format' => 'full_html',
    ),
    'additional_classes' => 'box-class',
  );
  $export['how_to_find_us'] = $box;

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
