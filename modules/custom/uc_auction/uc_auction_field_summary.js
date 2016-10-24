(function ($) {

Drupal.behaviors.ucAuctionFieldsetSummaries = {
  attach: function (context) {
    $('fieldset.auction-field', context).drupalSetSummary(function (context) {

      var vals = [];
      var auctionCheckbox = $('#edit-is-auction', context);

      if (auctionCheckbox.is(':checked')) {
        vals.push(Drupal.t('Auctioned'));
        vals.push(Drupal.t('Start price')+': '+ Drupal.checkPlain($('#edit-start-price-disp', context).val()));
        vals.push(Drupal.t('Expires')+': '+ Drupal.checkPlain($('input[name="expiry[date]"]', context).val())+' '+Drupal.t('at')+' '+ Drupal.checkPlain($('input[name="expiry[time]"]', context).val()));
      }else vals.push(Drupal.t('Not auctioned'));

      return vals.join(', ');
    });
  }
};

})(jQuery);
