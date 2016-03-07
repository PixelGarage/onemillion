<?php
/**
 * Created by PhpStorm.
 * User: ralph
 * Date: 06.02.15
 * Time: 17:23
 */

/**
 * Preprocess variables for the html template.
 */
function pixelgarage_preprocess_html(&$vars) {
  // make sure jQuery UI and effects is loaded for anonymous users
  drupal_add_library('system', 'ui');
  drupal_add_library('system', 'effects');

}

/**
 * Override or insert variables for the page templates.
 */
function pixelgarage_preprocess_page(&$vars) {
  // hide titles on login forms
  pg_login_preprocess_page($vars);


}


/**
 * Implements template_preprocess_webform_confirmation().
 */
function pixelgarage_preprocess_webform_confirmation(&$vars) {
  // because we have translated webform nodes, we have to get the submissions
  // of the original node of the translation set, set in the "tnid" property
  $webform = $vars['node'];
  $tnid = $webform->tnid ? $webform->tnid : $webform->nid;
  $lang = $webform->language;

  // override links
  $vars['url'] = url();

  // get share node and render it
  if ($lang == 'fr') {
    $nid_share = 39;
  } else {
    $nid_share = 28;
  }
  $share = node_load($nid_share);
  $vars['share_buttons'] = node_view($share, 'full');
}

