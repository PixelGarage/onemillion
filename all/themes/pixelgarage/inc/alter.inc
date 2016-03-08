<?php
/**
 * Created by PhpStorm.
 * User: ralph
 * Date: 06.02.15
 * Time: 17:22
 */

/**
 * Alters the menu entries.
 * @param $items
 */
function pixelgarage_menu_alter(&$items) {
  // hides local task tabs
  pg_login_menu_alter($items);
}

/**
 * Implements hook_webform_component_render_alter().
 */
function pixelgarage_webform_component_render_alter(&$element, $component) {
  //
  // OVERRIDE WEBFORM LOCALIZATION
  // Webform_localization adds the title as placeholder without checking the placeholder field
  // Override: If placeholder is set in form, take the placeholder value.
  if (!empty($component['extra']['placeholder'])) {
    $element['#attributes']['placeholder'] = t($component['extra']['placeholder']);
  }
}



/* =============================================================================
 *      Odometer counter calculation
 * ========================================================================== */

/**
 * Alter the odometer current value, before it is displayed.
 *
 * 1) Adds the number of submissions of the 'Abstimmen' webform.
 * 2) Adds the sum of the number of friends field in the 'Mitmachen' webform.
 *
 * @param $counter
 *   The current value of the odometer to be altered.
 */
function pixelgarage_odometer_counter_alter(&$counter) {
  module_load_include('inc', 'webform', 'includes/webform.submissions');

  //
  // vote webform
  // add the count of submissions to the counter
  $tnid_vote = 18;
  $nr_submissions = webform_get_submission_count($tnid_vote);
  $counter += $nr_submissions;

  //
  // participate webform
  // add the sum of all given friends to the counter
  $tnid_part = 25;
  $form_key = 'number_friends';
  if (!($cid = _get_cid($tnid_part, $form_key))) {
    // cid could not be evaluated
    watchdog('odometer', 'Number of friends cannot be evaluated: No webform component with that name found!', array(), WATCHDOG_ALERT);
  }

  // get all field values of the submission
  $query = db_select('webform_submitted_data', 'sd')
    ->fields('sd', array('data'))
    ->condition('sd.nid', $tnid_part)
    ->condition('sd.cid', $cid);
  $result = $query->execute();
  $friends_count = 0;
  foreach ($result as $row) {
    switch ($row->data) {
      case 'five':
        $friends_count += 5;
        break;
      case 'twentyfive':
        $friends_count += 25;
        break;
      case 'fifty':
        $friends_count += 50;
        break;
      case 'more':
        $friends_count += 50;
        break;
      default:
        $friends_count += 0;
        break;
    }
  }

  // add all friends
  $counter += $friends_count;
}

/**
 * Internal function to retrieve a component id of a webform with the form key.
 */
function _get_cid($tnid_part, $form_key) {
  // get component id for friends field
  $query = db_select('webform_component', 'wc')
    ->fields('wc', array('cid'))
    ->condition('wc.nid', $tnid_part)
    ->condition('wc.form_key', $form_key);
  $result = $query->execute();

  $cid = false;
  foreach ($result as $row) {
    $cid = $row->cid;
  }
  return $cid;
}
