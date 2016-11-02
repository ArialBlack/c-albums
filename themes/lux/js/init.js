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

          $('#catalog-tree li a').click(function( event ) {
              $link = $(this);
              $next =  $link.next();
              //console.log($next);
              //
              if($next.hasClass('item-list')) {
                 // $('.item-list').removeClass('open');
                  $insertlink = $link.clone().prop('outerHTML');
                  $link.addClass('hide');
                  $link.parent('li').siblings().addClass('hide');
                  $navhtml = $('#catalog-nav').html();
                  $('#catalog-nav').html($navhtml + $insertlink);
                  $next.addClass('open');
                  event.preventDefault();
              }
          });

          $(document).on('click', $('#catalog-nav a'), function( event ) {

              $navlink = $(event.target);
              //console.log($navlink.parent('#catalog-nav').length);
              if ($navlink.parent('#catalog-nav').length > 0 ) {
                  $selector = $('.' + $navlink.attr('class'));
                  //console.log($selector);
                  $chainnedLink =  $('#catalog-tree').find($selector);
                  $chainnedLink.removeClass('hide');
                  $('#catalog-nav').find($selector).remove();
                  event.preventDefault();

                  //если первый то показыать корень
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