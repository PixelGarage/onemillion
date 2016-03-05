/**
 * This file contains behaviors for the odometer animation.
 *
 * Created by ralph on 31.01.15.
 */

(function ($) {

  /**
   * Animates the odometer when shown.
   */
  Drupal.behaviors.odometerAnim = {
    attach: function () {
      var $odometer = $('.odometer'),
          counter = parseInt($odometer.html()),
          animatedRange = Drupal.settings.odometer.animated_range,
          startValue = Math.max(counter - animatedRange, 0);

      // set the odometer value (reduced by the range)
      $odometer.html(startValue);

      setTimeout(function() {
        $odometer.html(counter);
      }, 400);
    }
  }

})(jQuery);

