<?php
/**
 * API functions of the odometer module.
 */

/**
 * Alter the odometer current value, before it is displayed.
 *
 * @param $counter
 *   The current value of the odometer to be altered.
 */
function hook_odometer_counter_alter(&$counter) {
  // add one to the counter
  $counter++;
}
