<?php
/**
 * @file
 * occupy_content_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function occupy_content_types_ctools_plugin_api() {
  return array("version" => "1");
}

/**
 * Implements hook_image_default_styles().
 */
function occupy_content_types_image_default_styles() {
  $styles = array();

  // Exported image style: 220x117
  $styles['220x117'] = array(
    'name' => '220x117',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '220',
          'height' => '117',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: 450x465-featured-article
  $styles['450x465-featured-article'] = array(
    'name' => '450x465-featured-article',
    'effects' => array(
      3 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '450',
          'height' => '465',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: 540x380
  $styles['540x380'] = array(
    'name' => '540x380',
    'effects' => array(
      2 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '540',
          'height' => '380',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function occupy_content_types_node_info() {
  $items = array(
    'announcement' => array(
      'name' => t('Announcement'),
      'base' => 'node_content',
      'description' => t('Use <em>announcements</em> to display short, important messages on the home page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => t('The <em>Title</em> field is only using for administrative purposes; your <em>Announcement</em> should go in the <em>Body</em> field below.'),
    ),
    'event' => array(
      'name' => t('Event'),
      'base' => 'node_content',
      'description' => t('Create <em>events</em> if you need to include location and date information.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'ga_policy' => array(
      'name' => t('GA Policy'),
      'base' => 'node_content',
      'description' => t('Official GA Policy documents live here.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'occupy_location' => array(
      'name' => t('Occupy Location'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'page' => array(
      'name' => t('Basic page'),
      'base' => 'node_content',
      'description' => t('Use <em>basic pages</em> for your static content, such as an \'About us\' page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'story' => array(
      'name' => t('Story'),
      'base' => 'node_content',
      'description' => t('Use <em>stories</em> for time-sensitive content like news, press releases or blog posts.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'video' => array(
      'name' => t('Video'),
      'base' => 'node_content',
      'description' => t('Embedded video from a 3rd party provider (youtube, vimeo, etc).'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'webform' => array(
      'name' => t('Webform'),
      'base' => 'node_content',
      'description' => t('Create a new form or questionnaire accessible to users. Submission results and statistics are recorded and accessible to privileged users.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
