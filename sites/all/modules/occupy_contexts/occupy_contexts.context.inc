<?php
/**
 * @file
 * occupy_contexts.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function occupy_contexts_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'contact_page';
  $context->description = 'Context for applying contact page delta & blocks';
  $context->tag = 'Contact Page';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'contact' => 'contact',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-30' => array(
          'module' => 'block',
          'delta' => 30,
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
        'block-31' => array(
          'module' => 'block',
          'delta' => 31,
          'region' => 'sidebar_second',
          'weight' => '-9',
        ),
        'block-26' => array(
          'module' => 'block',
          'delta' => 26,
          'region' => 'postscript_first',
          'weight' => '-10',
        ),
        'block-22' => array(
          'module' => 'block',
          'delta' => 22,
          'region' => 'postscript_second',
          'weight' => '-10',
        ),
        'block-23' => array(
          'module' => 'block',
          'delta' => 23,
          'region' => 'postscript_third',
          'weight' => '-10',
        ),
      ),
    ),
    'delta' => array(
      'delta_template' => 'contact',
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Contact Page');
  t('Context for applying contact page delta & blocks');
  $export['contact_page'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'contribute';
  $context->description = 'Context for contribute page layout';
  $context->tag = 'Contribute Page';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'content/contribute' => 'content/contribute',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-24' => array(
          'module' => 'block',
          'delta' => 24,
          'region' => 'preface_first',
          'weight' => '-10',
        ),
        'block-14' => array(
          'module' => 'block',
          'delta' => 14,
          'region' => 'preface_second',
          'weight' => '-10',
        ),
        'views-ows_events-block' => array(
          'module' => 'views',
          'delta' => 'ows_events-block',
          'region' => 'preface_third',
          'weight' => '-10',
        ),
        'webform-client-block-30' => array(
          'module' => 'webform',
          'delta' => 'client-block-30',
          'region' => 'preface_fourth',
          'weight' => '-10',
        ),
        'block-16' => array(
          'module' => 'block',
          'delta' => 16,
          'region' => 'preface_fifth',
          'weight' => '-10',
        ),
        'block-17' => array(
          'module' => 'block',
          'delta' => 17,
          'region' => 'preface_sixth',
          'weight' => '-10',
        ),
        'block-18' => array(
          'module' => 'block',
          'delta' => 18,
          'region' => 'preface_seventh',
          'weight' => '-10',
        ),
        'block-19' => array(
          'module' => 'block',
          'delta' => 19,
          'region' => 'postscript_first',
          'weight' => '-10',
        ),
        'block-20' => array(
          'module' => 'block',
          'delta' => 20,
          'region' => 'postscript_second',
          'weight' => '-10',
        ),
      ),
    ),
    'delta' => array(
      'delta_template' => 'contribute',
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Context for contribute page layout');
  t('Contribute Page');
  $export['contribute'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'front';
  $context->description = 'Front Page Layout';
  $context->tag = 'Front Page Layout';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'front' => 'front',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-ows_stories-block_1' => array(
          'module' => 'views',
          'delta' => 'ows_stories-block_1',
          'region' => 'content',
          'weight' => '-10',
        ),
        'block-11' => array(
          'module' => 'block',
          'delta' => 11,
          'region' => 'user_second',
          'weight' => '-10',
        ),
        'quicktabs-featured' => array(
          'module' => 'quicktabs',
          'delta' => 'featured',
          'region' => 'preface_first',
          'weight' => '-10',
        ),
        'quicktabs-feeds' => array(
          'module' => 'quicktabs',
          'delta' => 'feeds',
          'region' => 'preface_second',
          'weight' => '-10',
        ),
        'block-13' => array(
          'module' => 'block',
          'delta' => 13,
          'region' => 'preface_third',
          'weight' => '-10',
        ),
        'node-syndicate' => array(
          'module' => 'node',
          'delta' => 'syndicate',
          'region' => 'preface_fourth',
          'weight' => '-10',
        ),
        'block-10' => array(
          'module' => 'block',
          'delta' => 10,
          'region' => 'postscript_first',
          'weight' => '-10',
        ),
        'views-ows_news-block' => array(
          'module' => 'views',
          'delta' => 'ows_news-block',
          'region' => 'postscript_third',
          'weight' => '-10',
        ),
      ),
    ),
    'delta' => array(
      'delta_template' => 'front',
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Front Page Layout');
  $export['front'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'learn_page';
  $context->description = 'Context for applying Learn Page Delta';
  $context->tag = 'Learn Page';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'learn' => 'learn',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'quicktabs-learn' => array(
          'module' => 'quicktabs',
          'delta' => 'learn',
          'region' => 'content',
          'weight' => '-10',
        ),
        'block-27' => array(
          'module' => 'block',
          'delta' => 27,
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
        'block-28' => array(
          'module' => 'block',
          'delta' => 28,
          'region' => 'sidebar_second',
          'weight' => '-9',
        ),
        'block-29' => array(
          'module' => 'block',
          'delta' => 29,
          'region' => 'sidebar_second',
          'weight' => '-8',
        ),
        'block-25' => array(
          'module' => 'block',
          'delta' => 25,
          'region' => 'preface_first',
          'weight' => '-10',
        ),
      ),
    ),
    'delta' => array(
      'delta_template' => 'learn_page',
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Context for applying Learn Page Delta');
  t('Learn Page');
  $export['learn_page'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'read';
  $context->description = 'Read page context';
  $context->tag = 'Read Page';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'read' => 'read',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-nodequeue_3-block' => array(
          'module' => 'views',
          'delta' => 'nodequeue_3-block',
          'region' => 'preface_first',
          'weight' => '-10',
        ),
        'views-ows_stories_read_page_-block_1' => array(
          'module' => 'views',
          'delta' => 'ows_stories_read_page_-block_1',
          'region' => 'preface_second',
          'weight' => '-10',
        ),
      ),
    ),
    'delta' => array(
      'delta_template' => 'read',
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Read Page');
  t('Read page context');
  $export['read'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'sitewide';
  $context->description = 'Sitewide context';
  $context->tag = 'Sitewide Context';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'delta_blocks-site-name' => array(
          'module' => 'delta_blocks',
          'delta' => 'site-name',
          'region' => 'branding',
          'weight' => '-10',
        ),
        'delta_blocks-site-slogan' => array(
          'module' => 'delta_blocks',
          'delta' => 'site-slogan',
          'region' => 'branding',
          'weight' => '-9',
        ),
        'system-main-menu' => array(
          'module' => 'system',
          'delta' => 'main-menu',
          'region' => 'menu',
          'weight' => '-10',
        ),
        'block-2' => array(
          'module' => 'block',
          'delta' => 2,
          'region' => 'header_first',
          'weight' => '-10',
        ),
        'block-15' => array(
          'module' => 'block',
          'delta' => 15,
          'region' => 'header_second',
          'weight' => '-10',
        ),
        'block-12' => array(
          'module' => 'block',
          'delta' => 12,
          'region' => 'header_second',
          'weight' => '-9',
        ),
        'views-ows_announcements-block' => array(
          'module' => 'views',
          'delta' => 'ows_announcements-block',
          'region' => 'header_second',
          'weight' => '-8',
        ),
        'block-6' => array(
          'module' => 'block',
          'delta' => 6,
          'region' => 'footer_first',
          'weight' => '-10',
        ),
        'block-7' => array(
          'module' => 'block',
          'delta' => 7,
          'region' => 'footer_second',
          'weight' => '-10',
        ),
        'block-8' => array(
          'module' => 'block',
          'delta' => 8,
          'region' => 'footer_third',
          'weight' => '-10',
        ),
        'block-9' => array(
          'module' => 'block',
          'delta' => 9,
          'region' => 'footer_fourth',
          'weight' => '-10',
        ),
        'block-4' => array(
          'module' => 'block',
          'delta' => 4,
          'region' => 'footer_fifth',
          'weight' => '-10',
        ),
        'block-5' => array(
          'module' => 'block',
          'delta' => 5,
          'region' => 'footer_sixth',
          'weight' => '-10',
        ),
        'multiblock-1' => array(
          'module' => 'multiblock',
          'delta' => 1,
          'region' => 'footer_seventh',
          'weight' => '-10',
        ),
        'block-3' => array(
          'module' => 'block',
          'delta' => 3,
          'region' => 'footer_eighth',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Sitewide Context');
  t('Sitewide context');
  $export['sitewide'] = $context;

  return $export;
}
