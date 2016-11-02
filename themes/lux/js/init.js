(function($){
  $(function(){



      $(document).ready(function() {
          $('.button-collapse').sideNav({
              menuWidth: 300, // Default is 240
              edge: 'left', // Choose the horizontal origin
              closeOnClick: true // Closes side-nav on <a> clicks, useful for Angular/Meteor
          });

          $('ul.tabs').tabs();

          $myselect = $('select');//.not('.field-widget-taxonomy-shs select');
          $myselect.material_select();
          $('.tooltipped').tooltip({
              delay: 50,
              html: true
          });

          $('#catalog-tree li .card-link').click(function( event ) {
              $link = $(this);
              $card = $link.parents('.card');
              $next =  $card.next();

              if($next.hasClass('item-list')) {
                  event.preventDefault();

                  $insertlink = $link.clone();
                  $insertlink.find('img').remove();
                  $insertlink = $insertlink.prop('outerHTML');

                  $card.addClass('hide');
                  $card.parent('li').siblings().addClass('hide');
                  $navhtml = $('#catalog-nav').html();
                  $('#catalog-nav').html($navhtml + $insertlink);
                  $next.addClass('open');
                  $next.find('> ul > li').removeClass('hide');
                  $next.find('> ul > li > .card').removeClass('hide');
                  $next.find('> ul > li .open').removeClass('open');
              }
          });

          $(document).on('click', $('#catalog-nav a'), function( event ) {
              $navlink = $(event.target).parent('.card-link');

              if ($navlink.parent('#catalog-nav').length > 0 ) {
                  event.preventDefault();

                  cardid = $navlink.data('cardid');
                  $chainnedLink =  $('#catalog-tree').find('.card[data-cardid="' + cardid + '"]');
                  $chainnedLink.removeClass('hide');
                  $('#catalog-nav').find($navlink).nextAll().remove();
                  $('#catalog-nav').find($navlink).remove();

                  $chainnedLink.parent('li').siblings().removeClass('hide');
                  $chainnedLink.siblings().removeClass('open');
              }
          });
      });

      $(document).on('CToolsAttachBehaviors', function () {
          $myselect = $('select');//.not('.field-widget-taxonomy-shs select');
          $myselect.material_select();
      });

      $(document).ajaxComplete(function() {
          $myselect = $('select');//.not('.field-widget-taxonomy-shs select');
          $myselect.material_select();
      });



      $('#edit-field-sell-item input:checkbox').change(function () {
          var check = $(this).prop('checked'),
              $form = $(this).parents('.coin-form');
          if (check) {
              $form.addClass('just-sell');
              $form.find('.form-item-sell-price input').addClass('required');
              //$form.find('.form-item-sell-price label').html($form.find('.form-item-sell-price label').html() + '<span class="form-required" title="This field is required.">*</span>');
              //$form.find('span.form-required').show();
          } else {
              $form.removeClass('just-sell');
              //$form.find('.form-item-sell-price input').removeClass('required');
              //$form.find('span.form-required').hide();
          }
      });

      /*$(window).on('selectDropdownInputChanged', function() {
          $val = $('.view-mycoinslist #user-album-select ul li.active span').text();
          console.log($val);
          if( $val === '- Any -') {
            $val = '';
          }
          $('.view-mycoinslist .view-filters .form-item-title input').val($val);
      });*/


  }); // end of document ready
})(jQuery); // end of jQuery name space