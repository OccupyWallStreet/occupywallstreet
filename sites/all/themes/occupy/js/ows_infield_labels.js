(function ($) {
  Drupal.behaviors.owsinfield = {
    attach: function (context, settings) {
      // Add code here.
      $("label").inFieldLabels();
    }
  }
})(jQuery);