<?php
// $Id$

/**
 * @file piewpiew_utils.drush.inc
 * 
 */

function piewpiew_utils_drush_help($section) {
  switch($section) {
    case "drush:create-project" :
      return dt("Creates a new site");
    break;
  }
}

/**
 * Implementation of COMMANDFILE_drush_command()
 */
function piewpiew_utils_drush_command() {
  $items = array();

  $items["create-project"] = array(
    'description' => 'Creates a new project',
    'arguments' => array(
      'name' => 'The name of the project'
    ),
    'options' => array(
      'template' => 'Template to base the project on. New templates can be added to ' . dirname(__FILE__) . '/templates',
      'svn-path' => 'Optional URL to an svn repository to import the project into.'
    ),
    'aliases' => array('pp-cp'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH
  );

  return $items;
}

/**
 * Creates a new drupal project
 */
function drush_piewpiew_utils_create_project($name) {
  drush_log("Creating project " . $name, 'ok');

  if (is_dir($name)) {
    return drush_set_error("piewpiew_utils_create_project", "A folder or project named " . $name . " already exists");
  }

  if (mkdir($name . '/profile', 0777, true)) {

    $template = drush_get_option('template', 'default');
    
    if (!_piewpiew_utils_create_build_file($template, $name)) {
      return drush_set_error("piewpiew_utils_create_project", "Could not create build.make file for your project.");
    }

    if (!_piewpiew_utils_create_profile_file($template, $name)) {
      return drush_set_error("piewpiew_utils_create_project", "Could not create $name.profile file for your project.");
    }

    if (!_piewpiew_utils_create_profile_make($template, $name)) {
      return drush_set_error("piewpiew_utils_create_project", "Could not create $name.make file for your project.");
    }

    if (!_piewpiew_utils_create_update_script($template, $name)) {
      return drush_set_error("piewpiew_utils_create_project", "Could not create update.sh file for your project.");
    }

    

    $svn_url = drush_get_option('svn-path', false);

    if ($svn_url) {
      drush_log("Importing project to svn repository at $svn_url/trunk", "ok");
      drush_shell_exec_interactive("svn import $name $svn_url/trunk -m \"Initial import\"");
    }    
    
  } else {
    return drush_set_error("piewpiew_utils_create_project", "Could not create folder for your project.");
  }
}
  
/**
 * Creates a build.make file
 *
 * @param (string) $template
 *  The name of the template to use
 * @param (string) $project
 *  The name of the project
 */
function _piewpiew_utils_create_build_file($template, $project) {
  $src  = dirname(__FILE__) . '/templates/'.$template.'/build.make';
  $dest = $project . '/build.make';
  $replacements = array('%project%' => $project);
  $svn = drush_get_option('svn-path', false);

  if ($svn) {
    $replacements['%svn-path%'] = "$svn/trunk";
  }

  return _piewpiew_utils_replace_and_copy($src, $dest, $replacements);
}

/**
 * Creates a drupal install.profile file
 *
 * @param (string) $template
 *  The name of the template to use
 * @param (string) $project
 *  The name of the project
 */
function _piewpiew_utils_create_profile_file($template, $project) {
  $src  = dirname(__FILE__) . '/templates/'.$template.'/install.profile';
  $dest = $project . '/profile/' . $project . '.profile';
  
  return _piewpiew_utils_replace_and_copy($src, $dest, array(
    '%project%' => $project,
  ));
}

/**
 * Creates a drush make file for the install profile
 *
 * @param (string) $template
 *  The name of the template to use
 * @param (string) $project
 *  The name of the project
 */
function _piewpiew_utils_create_profile_make($template, $project) {
  $src  = dirname(__FILE__) . '/templates/'.$template.'/profile.make';
  $dest = $project . '/profile/' . $project . '.make';
  
  return _piewpiew_utils_replace_and_copy($src, $dest, array(
    '%project%' => $project,
  ));
}

/**
 * Creates an update script for the install profile
 *
 * @param (string) $template
 *  The name of the template to use
 * @param (string) $project
 *  The name of the project
 */
function _piewpiew_utils_create_update_script($template, $project) {
  $src  = dirname(__FILE__) . '/templates/'.$template.'/update.sh';
  $dest = $project . '/profile/update.sh';
  
  return _piewpiew_utils_replace_and_copy($src, $dest, array(
    '%project%' => $project,
  ));
}

/**
 * Copy one file to another, with text replacements.
 *
 * Copies the content of $src to $dest, replacing text using the keys/values found
 * in $replacements
 *
 * @param (string) $src
 *  Path to the file to copy from
 * @param (string) $dest
 *  Path to the file to copy to
 * @param (array) $replacements
 *  An array of string replacements. Each instance of each array key found in $src will
 *  be replaced by the corresponding value.
 * @return (boolean)
 */
function _piewpiew_utils_replace_and_copy($src, $dest, $replacements=array()) {
  $content = file_get_contents($src);

  if (($outfile = fopen($dest, 'w+')) != FALSE) {
    foreach($replacements as $key => $value) {
      $content = str_replace($key, $value, $content);
    }
    fwrite($outfile, $content);
    fclose($outfile);
    return true;
  } 
  
  return drush_set_error("piewpiew_utils_create_project", "Could not create ".$dest." file for your project.");
}