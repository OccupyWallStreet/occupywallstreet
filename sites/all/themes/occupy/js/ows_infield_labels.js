(function ($) {
  Drupal.behaviors.owsinfield = {
    attach: function (context, settings) {
      // Add code here.
      $("div.newsletter-wrapper label").inFieldLabels();
    }
  }
})(jQuery);
