<?php
/**
 * @file
 * occupy_misc.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function occupy_misc_ctools_plugin_api() {
  return array("version" => "1");
}

/**
 * Implements hook_fontyourface_features_default_font().
 */
function occupy_misc_fontyourface_features_default_font() {
  return array(
    'League Gothic' => array(
      'name' => 'League Gothic',
      'enabled' => '1',
      'url' => 'http://www.fontsquirrel.com/fonts/League-Gothic',
      'provider' => 'fontsquirrel',
      'css_selector' => 'h1, h2, h3, h4, h5, h6, block-menu, a.active',
      'css_family' => '\'LeagueGothicRegular\'',
      'css_style' => '',
      'css_weight' => '',
      'css_fallbacks' => '',
      'foundry' => 'The League of Moveable Type',
      'foundry_url' => 'http://www.fontsquirrel.com/foundry/The-League-of-Moveable-Type',
      'license' => 'See Font Squirrel license page',
      'license_url' => 'http://www.fontsquirrel.com/fonts/League-Gothic#eula',
      'designer' => '',
      'designer_url' => '',
      'metadata' => 'a:3:{s:2:"id";s:3:"816";s:4:"path";s:13:"League-Gothic";s:13:"font_filename";s:17:"League_Gothic.otf";}',
    ),
    'PT Sans' => array(
      'name' => 'PT Sans',
      'enabled' => '1',
      'url' => 'http://www.fontsquirrel.com/fonts/PT-Sans',
      'provider' => 'fontsquirrel',
      'css_selector' => 'p, div',
      'css_family' => '\'PTSansRegular\'',
      'css_style' => '',
      'css_weight' => '',
      'css_fallbacks' => '',
      'foundry' => 'Paratype',
      'foundry_url' => 'http://www.fontsquirrel.com/foundry/Paratype',
      'license' => 'See Font Squirrel license page',
      'license_url' => 'http://www.fontsquirrel.com/fonts/PT-Sans#eula',
      'designer' => '',
      'designer_url' => '',
      'metadata' => 'a:3:{s:2:"id";s:3:"922";s:4:"path";s:7:"PT-Sans";s:13:"font_filename";s:10:"PTS55F.ttf";}',
    ),
  );
}
