<?php
/**
 * @file
 * occupy_content_types.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function occupy_content_types_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'articles_events';
  $context->description = 'Block placement on full nodes for stories and events';
  $context->tag = 'Articles and Events';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'event' => 'event',
        'story' => 'story',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-tags_block-block' => array(
          'module' => 'views',
          'delta' => 'tags_block-block',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
        'block-33' => array(
          'module' => 'block',
          'delta' => 33,
          'region' => 'sidebar_second',
          'weight' => '-9',
        ),
        'block-34' => array(
          'module' => 'block',
          'delta' => 34,
          'region' => 'sidebar_second',
          'weight' => '-8',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Articles and Events');
  t('Block placement on full nodes for stories and events');
  $export['articles_events'] = $context;

  return $export;
}
