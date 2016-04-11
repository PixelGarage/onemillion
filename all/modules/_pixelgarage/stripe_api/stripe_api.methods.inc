<?php
/**
 * @file
 * Contains methods directly related to the Stripe API.
 */

/**
 * Makes a call to the Stripe API.
 *
 * @param string $obj
 *   Stripe object. Can be a Charge, Refund, Customer, Subscription, Card, Plan,
 *   Coupon, Discount, Invoice, InvoiceItem, Dispute, Transfer, TransferReversal,
 *   Recipient, BankAccount, ApplicationFee, FeeRefund, Account, Balance, Event,
 *   Token, BitcoinReceiver, FileUpload.
 *
 * @param string $method
 *   Stripe object method. Common operations include retrieve, all, create,
 *
 * @param mixed $params
 *   Additional params to pass to the method. Can be an array, string.
 *
 * @param string $account
 *   Stripe account to choose, either 'default' or 'second'. Leave blank to use the default account.
 *
 * @return Stripe\ApiResource
 *   Returns the ApiResource or NULL on error.
 */
function stripe_api_call($obj, $method = NULL, $params = NULL, $account = 'default') {
  $library = libraries_load('stripe');
  if (!empty($library['loaded'])) {
    \Stripe\Stripe::setApiKey(_stripe_api_secret_key(null, $account));
  }

  $obj = ucfirst($obj);
  $class = 'Stripe\\' . $obj;
  if ($method) {
    try {
      return call_user_func(array($class, $method), $params);
    } catch (Exception $e) {
      watchdog('stripe_api', 'Error: @error <br /> @args', array(
        '@args' => json_encode(array(
          'object' => $obj,
          'method' => $method,
          'params' => $params,
        )),
        '@error' => $e->getMessage(),
      ), WATCHDOG_ERROR);
      return NULL;
    }
  }
  return $class;
}
