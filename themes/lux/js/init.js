(function($){
  $(function(){

      $('.button-collapse').sideNav({
          menuWidth: 300, // Default is 240
          edge: 'left', // Choose the horizontal origin
          closeOnClick: true // Closes side-nav on <a> clicks, useful for Angular/Meteor
          });

      $('ul.tabs').tabs();
      $('select').material_select();


      $(document).on('CToolsAttachBehaviors', function () {
          $('select').material_select();
      });

      $( document ).ajaxComplete(function() {
          $('select').material_select();

      });

      $('.form-item-is-product input:checkbox').change(function () {
          var check = $(this).prop('checked'),
              $form = $(this).parents('.coin-form');
          if (check) {
              $form.addClass('is-product');
              $form.find('.form-item-sell-price input').addClass('required');
              $form.find('span.form-required').show();
          } else {
              $form.removeClass('is-product');
              $form.find('.form-item-sell-price input').removeClass('required');
              $form.find('span.form-required').hide();
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