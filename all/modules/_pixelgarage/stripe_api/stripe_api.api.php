<?php
/**
 * Stripe API hook examples.
 */

/**
 * Interact with all incoming Stripe webhooks.
 *
 * @param string $type
 *   Webhook type, such as customer.created, charge.captured, etc.
 *
 * @param object $data
 *   Incoming data object.
 *
 * @param Stripe\Event $event
 *   The verified Stripe Event that is being sent.
 *   Only available in live mode with real events (not test events).
 *
 * @throws \Exception
 */
function hook_stripe_api_webhook($type, $data, Stripe\Event $event = NULL) {
  switch ($type) {
    case 'customer.created':
      // Create a new Drupal user for this customer.
      $email = $data->object->email;
      if (!user_load_by_mail($email)) {
        user_save(NULL, array(
          'name' => $data->object->id,
          'mail' => $email,
        ));
      }
      break;
  }
}

/**
 * Interact with a specific incoming webhook type.
 *
 * @param object $data
 *   Incoming data object.
 *
 * @param Stripe\Event $event
 *   The verified Stripe Event that is being sent.
 *   Only available in live mode with real events (not test events).
 *
 * @throws \Exception
 */
function hook_stripe_api_webhook_EVENT_TYPE($data, Stripe\Event $event = NULL) {
  $email = $data->object->email;
  if (!user_load_by_mail($email)) {
    user_save(NULL, array(
      'name' => $data->object->id,
      'mail' => $email,
    ));
  }
}

/**
 * Alter the stripe account, that is used for the transaction.
 *
 * @param string $account
 *   Stripe account to choose, either 'default' or 'second'. Leave blank to use the default account.
 */
function hook_stripe_account_alter(&$account) {
  // return the account depending on the set language
  global $language;
  if ($language->language == 'fr') {
    $account = 'second';
  }
  else {
    $account = 'default';
  }
}
