<?php
/**
 * @file
 * Contains forms/functions for admin use.
 */

/**
 * Stripe API admin settings form.
 */
function stripe_api_admin_settings_form($form, $form_state) {
  $form['stripe_api_link'] = array(
    '#markup' => t('!dashboard | !api_keys | !docs<br /><br />', array(
      '!dashboard' => l(t('Dashboard'), 'https://dashboard.stripe.com', array('attributes' => array('target' => '_blank'))),
      '!api_keys' => l(t('API Keys'), 'https://dashboard.stripe.com/account/apikeys', array('attributes' => array('target' => '_blank'))),
      '!docs' => l(t('Docs'), 'https://stripe.com/docs/api', array('attributes' => array('target' => '_blank'))),
    )),
    '#weight' => 0,
  );
  $form['stripe_api_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Mode'),
    '#options' => array(
      'test' => t('Test'),
      'live' => t('Live'),
    ),
    '#default_value' => variable_get('stripe_api_mode', 'test'),
    '#weight' => 1,
  );

  $form['stripe_api_webhook_url'] = array(
    '#type' => 'textfield',
    '#disabled' => TRUE,
    '#title' => t('Webhook URL'),
    '#default_value' => url('stripe/webhook', array('absolute' => TRUE)),
    '#description' => t('Add this webhook path in the !link', array(
      '!link' => l(t('Stripe Dashboard'), 'https://dashboard.stripe.com/account/webhooks', array('attributes' => array('target' => '_blank'))),
    )),
    '#weight' => 2,
  );

  $form['stripe_api_log_webhooks'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log incoming webhooks'),
    '#default_value' => variable_get('stripe_api_log_webhooks', TRUE),
    '#weight' => 3,
  );

  $form['stripe_accounts'] = array(
    '#type' => 'vertical_tabs',
    '#weight' => 10,
  );

  $form['default_account'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default account'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    // The #group value must match the name of the vertical tabs element.
    '#group' => 'stripe_accounts',
  );

  $form['default_account']['stripe_api_test_secret_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Stripe Secret Key (test)'),
    '#default_value' => variable_get('stripe_api_test_secret_key', ''),
  );
  $form['default_account']['stripe_api_test_public_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Stripe Public Key (test)'),
    '#default_value' => variable_get('stripe_api_test_public_key', ''),
  );
  $form['default_account']['stripe_api_live_secret_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Stripe Secret Key (live)'),
    '#default_value' => variable_get('stripe_api_live_secret_key', ''),
  );
  $form['default_account']['stripe_api_live_public_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Stripe Public Key (live)'),
    '#default_value' => variable_get('stripe_api_live_public_key', ''),
  );

  if (_stripe_api_secret_key()) {
    $form['default_account']['stripe_test'] = array(
      '#type' => 'button',
      '#value' => t('Test Stripe Connection'),
      '#ajax' => array(
        'callback' => '_stripe_api_admin_test_connection',
        'wrapper' => 'stripe-connect-results',
        'method' => 'append',
      ),
      '#suffix' => '<div id="stripe-connect-results"></div>',
    );
  }

  $form['second_account'] = array(
    '#type' => 'fieldset',
    '#title' => t('Second account'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    // The #group value must match the name of the vertical tabs element.
    '#group' => 'stripe_accounts',
  );

  $form['second_account']['stripe_api_test_secret_key_account2'] = array(
    '#type' => 'textfield',
    '#title' => t('Stripe Secret Key (test)'),
    '#default_value' => variable_get('stripe_api_test_secret_key_account2', ''),
  );
  $form['second_account']['stripe_api_test_public_key_account2'] = array(
    '#type' => 'textfield',
    '#title' => t('Stripe Public Key (test)'),
    '#default_value' => variable_get('stripe_api_test_public_key_account2', ''),
  );
  $form['second_account']['stripe_api_live_secret_key_account2'] = array(
    '#type' => 'textfield',
    '#title' => t('Stripe Secret Key (live)'),
    '#default_value' => variable_get('stripe_api_live_secret_key_account2', ''),
  );
  $form['second_account']['stripe_api_live_public_key_account2'] = array(
    '#type' => 'textfield',
    '#title' => t('Stripe Public Key (live)'),
    '#default_value' => variable_get('stripe_api_live_public_key_account2', ''),
  );

  if (_stripe_api_secret_key(null, 'second')) {
    $form['second_account']['stripe_test'] = array(
      '#type' => 'button',
      '#value' => t('Test Stripe Connection'),
      '#ajax' => array(
        'callback' => '_stripe_api_admin_test_connection_2',
        'wrapper' => 'stripe-connect-results-2',
        'method' => 'append',
      ),
      '#suffix' => '<div id="stripe-connect-results-2"></div>',
    );
  }

  return system_settings_form($form);
}

/**
 * AJAX callback to test the Stripe connection.
 */
function _stripe_api_admin_test_connection($form, $form_state) {
  $account = stripe_api_call('account', 'retrieve');
  if ($account && $account->email) {
    return 'Success! Account email: ' . $account->email;
  }
  else {
    return 'Error! Could not connect!';
  }
}

/**
 * AJAX callback to test the Stripe connection of account 2.
 */
function _stripe_api_admin_test_connection_2($form, $form_state) {
  $account = stripe_api_call('account', 'retrieve', null, 'second');
  if ($account && $account->email) {
    return 'Success! Account email: ' . $account->email;
  }
  else {
    return 'Error! Could not connect!';
  }
}
