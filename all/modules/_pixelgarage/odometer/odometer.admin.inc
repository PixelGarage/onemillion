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
    '#description'   => t('A time based value is added to the odometer in a given time period, starting with the addition of the start value at the start time and ending with the addition of the end value at the end time. In between the value is linearly increasing.'),
    '#collapsible'  => FALSE,
    '#collapsed'    => FALSE,
  );
  $form['odometer_value_period']['odometer_time_based_start_value'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Time based start value'),
    '#default_value' => variable_get('odometer_time_based_start_value', 0),
    '#description'   => t('The start value added at the beginning of the time period.'),
    '#required' => TRUE,
  );
  $form['odometer_value_period']['odometer_time_based_end_value'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Time based value'),
    '#default_value' => variable_get('odometer_time_based_end_value', 0),
    '#description'   => t('The end value added at the end of the time period.'),
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
