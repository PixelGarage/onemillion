/**
 * This file contains behaviors for the stripe button.
 *
 * Created by ralph on 31.01.15.
 */

(function ($) {

  /**
   * Handles the Stripe checkout dialog and the returns the Stripe token to the server.
   * This script handles all Stripe buttons with a predefined value.
   *
   * @see https://stripe.com/docs/checkout#integration-custom
   */
  Drupal.behaviors.stripeCheckoutPredefinedButton = {
    attach: function () {
      var currentSettings,
          $currentButton,
          checkoutHandler = StripeCheckout.configure({
            key: Drupal.settings.stripe_button.stripe_public_key,
            image: Drupal.settings.stripe_button.icon,
            locale: 'auto',
            token: function (token) {
              // get button container for responses
              var $fieldItemDiv = $currentButton.parents('.field-item');

              // Use the token to create the charge with a server-side script.
              if ((typeof token != 'undefined') && token.id) {
                //
                // prepare transaction data (PCI compliant)
                var id     = $currentButton.attr('id'),
                    params = {
                      stripeToken: token.id,
                      btnID: id,  // used to recreate button in ajax response
                      email: token.email,
                      amount: currentSettings.amount,
                      currency: currentSettings.currency
                    };

                //
                // charge the customer with the token and display response
                $fieldItemDiv.load('stripe/ajax/token', params, function (response, status, xhr) {
                  if (status == "error") {
                    var msg = "Server error ";
                    $fieldItemDiv.html(msg + xhr.status + ": " + xhr.statusText);
                  }
                  else {
                    // do NOT attach behaviours to button, it is disabled
                    //Drupal.attachBehaviors($fieldItemsDiv);
                  }
                });
              }
              else {
                // no valid token returned => should never happen
                var msg = "Stripe Checkout unavailable.";
                $fieldItemDiv.html(msg);
              }

            }
          });

      // Iterate through all defined stripe button instances
      $.each(Drupal.settings.stripe_button.stripe_buttons, function (button, settings) {
        var $button = $('#' + button);

        $button.on('click', function (e) {
          // set current settings
          currentSettings = settings;
          $currentButton  = $(this);

          // Open Checkout with further options
          checkoutHandler.open({
            name: Drupal.settings.stripe_button.name,
            description: settings.description,
            currency: settings.currency,
            amount: settings.amount,
            panelLabel: settings.buttonLabel,
            zipCode: settings.zipCode == 1,
            billingAddress: settings.billingAddress == 1,
            shippingAddress: settings.shippingAddress == 1,
            allowRememberMe: settings.allowRememberMe == 1
          });
          e.preventDefault();
        });
      });

      //
      // Close Checkout on page navigation
      $(window).on('popstate', function () {
        checkoutHandler.close();
      });
    }
  };


  /**
   * Handles the Stripe checkout dialog and the returns the Stripe token to the server.
   * This script handles all Stripe buttons with a customizable value.
   *
   * @see https://stripe.com/docs/checkout#integration-custom
   */
  Drupal.behaviors.stripeCheckoutCustomButton = {
    attach: function () {

    }
  }


})(jQuery);

