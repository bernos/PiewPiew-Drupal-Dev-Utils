<?php

// $Id$

/**
 * @file %project%.profile
 */

/**
 * Implementation of hook_profile_details().
 */
function %project%_profile_details() {
  return array(
    'name' => '%project%',
    'description' => 'TODO: provide a description'
  );
}

/**
 * Implementation of hook_profile_modules().
 */
function %project%_profile_modules() {
  $modules = array(
    /* // Default Drupal modules.
    'help', 'menu', 'dblog', 'path',
   
    // Chaos Tools
    'ctools', 'context', 'context_ui',
   
    // Views
    'views', 'views_ui', 'views_content',
   
    // CCK
    'content', 'content_permissions', 'fieldgroup', 'text', 'filefield', 'imagefield',
    'optionwidgets', 'link', 'filefield_meta', 'nodereference',
   
    // Date
    'date_api', 'date_timezone', 'date',  'date_popup', 'date_tools',
     
    // ImageAPI + ImageCache
    'imageapi', 'imagecache', 'imageapi_gd', 'imagecache_ui',
   
    // Rules
    'token', 'rules', 'rules_admin',
   
    // Editor
    'wysiwyg', 'better_formats',

    // Install Profile
    'install_profile_api', 'node_export'
    // */
  );

  return $modules;
}