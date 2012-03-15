<?php

/**
 * @file
 * This file is empty by default because the base theme chain (Alpha & Omega) provides
 * all the basic functionality. However, in case you wish to customize the output that Drupal
 * generates through Alpha & Omega this file is a good place to do so.
 * 
 * Alpha comes with a neat solution for keeping this file as clean as possible while the code
 * for your subtheme grows. Please read the README.txt in the /preprocess and /process subfolders
 * for more information on this topic.
 */

/**
 * Implements hook_preprocess_page().
 */
function occupy_preprocess_html(&$vars) {
  // add our in-field css/js
  drupal_add_css('sites/all/themes/occupy/css/ows_infield_labels.css');
  drupal_add_js('sites/all/libraries/jquery.infieldlabel/jquery.infieldlabel.min.js');
  drupal_add_js('sites/all/themes/occupy/js/ows_infield_labels.js');
  
}