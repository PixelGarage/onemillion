<?php
/**
 * The administration settings form for an odometer.
 * @file
 */

/**
 * Administration settings form.
 *
 * @return
 *   The completed form definition.
 */
function odometer_admin_settings() {
  $form = array();

  $dateformat = 'd-m-Y';
  $now = date($dateformat);

  $form['odometer_value_period'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Timed value addition'),
    '#description'   => t('A value is added to the odometer in a given time period. The value is linearly distributed in the given time period so that at the end date the whole value is added.'),
    '#collapsible'  => FALSE,
    '#collapsed'    => FALSE,
  );
  $form['odometer_value_period']['odometer_time_based_value'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Time based value'),
    '#default_value' => variable_get('odometer_time_based_value', 0),
    '#description'   => t('A time based value added over the given time period (linearly distributed).'),
    '#required' => TRUE,
  );
  $form['odometer_value_period']['odometer_start_date'] = array(
    '#type' => 'date_popup',
    '#date_timezone' => date_default_timezone(),
    '#date_format' => $dateformat,
    '#date_year_range' => '-3:+3',
    '#title' => t('Start date'),
    '#default_value' => variable_get('odometer_start_date', $now),
    '#description'   => t('Add the start date of the period in which the value is added.'),
    '#required' => TRUE,
  );
  $form['odometer_value_period']['odometer_end_date'] = array(
    '#type' => 'date_popup',
    '#date_timezone' => date_default_timezone(),
    '#date_format' => $dateformat,
    '#date_year_range' => '-3:+3',
    '#title' => t('End date'),
    '#default_value' => variable_get('odometer_end_date', $now),
    '#description'   => t('Add the end date of the period in which the value is added.'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
