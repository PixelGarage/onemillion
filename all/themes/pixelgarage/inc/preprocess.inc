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
 * Session wide data container.
 *
 * @return array Returns the session data array.
 */
function &pixelgarage_session_data() {
  if (!isset($_SESSION['pixelgarage'])) {
    $_SESSION['pixelgarage'] = array();
  }
  return $_SESSION['pixelgarage'];
}

/**
 * Sets the submission value for the given form key.
 */
function pixelgarage_set_submission_value($master, $submission, $form_key, $value) {
  foreach ($master->webform['components'] as $key => $data) {
    if ($data['form_key'] == $form_key) {
      $submission->data[$key][0] = $value;
    }
  }
}

/**
 * Alter a submission after its creation and before it is saved to the db.
 */
function pixelgarage_webform_submission_create_alter(&$submission, &$node, &$account, &$form_state) {
  //
  // process only 'Abstimmen' webform
  $session_data = &pixelgarage_session_data();
  $lang = $node->language;

  if ($node->tnid == 18) {
    // get user email and save it in session
    $session_data['email'] = $submission->data[1][0];
  }
  else if ($node->tnid == 25) {
    // save email of 'Abstimmen' webform and language in submission
    $tnode = node_load($node->tnid);
    pixelgarage_set_submission_value($tnode, $submission, 'email', $session_data['email']);
    pixelgarage_set_submission_value($tnode, $submission, 'sprache', $lang);
  }
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
  $lang = $vars['node']->language;

  // Replace tokens (corrects webform_localization preprocess function)
  module_load_include('inc', 'webform', 'includes/webform.submissions');
  $confirmation = $vars['confirmation_message'];
  $submissions = webform_get_submissions(array('nid' => $tnid, 'sid' => $vars['sid']));
  $submission = isset($submissions[$vars['sid']]) ? $submissions[$vars['sid']] : NULL;
  $vars['confirmation_message'] = webform_replace_tokens($confirmation, $tnode, $submission, NULL, $node->webform['confirmation_format']);

  // override url to go back to home (instead of webform)
  $vars['url'] = url();

  // get localized share and donate node and render it
  switch ($lang) {
    case 'fr':
      $nid_share = 39;
      $nid_donate = 41;
      break;
    case 'de':
    default:
      $nid_share = 28;
      $nid_donate = 40;
      break;
  }
  $share = node_load($nid_share);
  $vars['share_buttons'] = node_view($share, 'full');
  $donate = node_load($nid_donate);
  $vars['donate_buttons'] = node_view($donate, 'full');
}

