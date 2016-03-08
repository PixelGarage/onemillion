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
  //
  // LOCALIZATION BY STRING TRANSLATION
  // The node is in the current language, but the attached webform is already replaced with the master webform
  $node = $vars['node'];
  $tnid = $node->tnid ? $node->tnid : $node->nid;
  $tnode = node_load($tnid);

  // Replace tokens (corrects webform_localization preprocess function)
  module_load_include('inc', 'webform', 'includes/webform.submissions');
  $confirmation = $vars['confirmation_message'];
  $submissions = webform_get_submissions(array('nid' => $tnid, 'sid' => $vars['sid']));
  $submission = isset($submissions[$vars['sid']]) ? $submissions[$vars['sid']] : NULL;
  $vars['confirmation_message'] = webform_replace_tokens($confirmation, $tnode, $submission, NULL, $node->webform['confirmation_format']);

  // override links to go back to home
  $vars['url'] = url();

  // get localized share node and render it
  switch ($vars['node']->language) {
    case 'de':
      $nid_share = 28;
      break;
    case 'fr':
      $nid_share = 39;
      break;
  }
  $share = node_load($nid_share);
  $vars['share_buttons'] = node_view($share, 'full');
}

