<?php

/**
 * @file
 * Customize confirmation screen after successful submission.
 *
 * This file may be renamed "webform-confirmation-[nid].tpl.php" to target a
 * specific webform e-mail on your site. Or you can leave it
 * "webform-confirmation.tpl.php" to affect all webform confirmations on your
 * site.
 *
 * Available variables:
 * - $node: The node object for this webform.
 * - $progressbar: The progress bar 100% filled (if configured). This may not
 *   print out anything if a progress bar is not enabled for this node.
 * - $confirmation_message: The confirmation message input by the webform
 *   author.
 * - $sid: The unique submission ID of this submission.
 * - $url: The URL of the form (or for in-block confirmations, the same page).
 */
?>
<?php print $progressbar; ?>

<div class="webform-confirmation">
  <div class="confirmation-message">
    <?php if ($confirmation_message): ?>
      <?php print $confirmation_message ?>
    <?php else: ?>
      <p><?php print t("Von der einen Hand zur andern... <br><br>Danke, dass Du den Taler zum wandern gebracht hast. Falls Du nochmals einen Taler auf die Wanderung schicken möchtest, kannst Du <a href='@shopify' target='_blank'>hier</a> einen Neuen bestellen. <br><br>Danke für's Mitmachen!", array('@shopify' => 'https://ja-oui-si.myshopify.com/products/der-wandertaler')); ?></p>
    <?php endif; ?>
  </div>
  <div class="confirmation-share">
    <?php if ($share_buttons): ?>
      <?php print render($share_buttons) ?>
    <?php endif; ?>
  </div>
  <div class="confirmation-donate">
    <?php if ($donate_buttons): ?>
      <?php print render($donate_buttons) ?>
    <?php endif; ?>
  </div>
</div>

<div class="links">
  <a href="<?php print $url; ?>"><?php print t('Go back to home') ?></a>
</div>

