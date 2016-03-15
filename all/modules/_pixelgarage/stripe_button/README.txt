The stripe_button module provides a field formatter for the number (decimal) field that can display one or more
Stripe Checkout buttons with a predefined or customizable amount in one of the given currencies.

To use this Drupal module for Test and Live payments, you need to open a Stripe account (https://stripe.com/global).


See also http://stripe.com/checkout

-----------------------------------------------------------------------------
VERSION INFO
-----------------------------------------------------------------------------
Version 1.x supports the Stripe Checkout payment gateway since March 2016.


-----------------------------------------------------------------------------
ABOUT THIS MODULE
-----------------------------------------------------------------------------
This module provides a field formatter for the number decimal field. This formatter allows
to display one or more Stripe Checkout buttons in two different modes:

1) Predefined value stripe button
This formatter displays one or more buttons with a fixed (configurable) value and currency as chargable amount. Clicking this
button opens the Stripe Checkout dialog with the given amount and currency already set, ready to be paid right away.

2) Custom value stripe button
This formatter displays one button with a text field to add a custom amount in a configurable currency. Clicking this
button opens the Stripe Checkout dialog with the user specified amount in the configured currency.



-----------------------------------------------------------------------------
INSTALLATION
-----------------------------------------------------------------------------
Flexpaper Library:
This module requires the FlexPaper Webserver package available as drupal library. Follow these steps to create the
flexpaper library:

1. Install and enable Libraries API module (see https://www.drupal.org/project/libraries).
2. Create a stripe folder in the libraries directory (sites/all/libraries) and download the Stripe PHP library from GitHub in it.
3. Download and install the stripe_api and the stripe_button (this module) modules.
4. Configure the Stripe account access on the configuration page of the Stripe API (/admin/config/services/stripe_api).
5. Add a decimal number field to one of your content types and configure it in the view mode.
6. Set one of the two field formatters (Predefined or Custom value button) and configure more options for the Checkout dialog
    - the currency
    - the dialog title
    - the dialog description
    - the dialog button label (the amount and currency are always added at the end of the defined label)
    - if a billing address form should be displayed
    - if a shipping address form should be displayed
    - if one click payment (remember me) should be enabled


-----------------------------------------------------------------------------
CREDITS
-----------------------------------------------------------------------------
This project uses the really great Payment Gateway of Stripe, a new era of payment, simple, secure and fast.

Sponsored by Pixelgarage (http://www.pixelgarage.ch)
