(function($){
  $(function(){

      var initCid = null,
          newCid = null,
          toastSubject = null,
          newData = [];

      function loadCommentFromServer () {
          $.ajax({
              url: '/api/comments/last.json',
              dataType: 'json',
              success: function(data) {

                  $.each(data, function(i) {
                      newData[i] = data[i];
                      newCid = newData[i]['cid'];
                      toastSubject = '<i class="icon ion-ios-chatbubble"></i> <b class="bq">“</b>' + newData[i]['subject'] + '...';
                      //console.log('t: ', newCid, initCid, toastSubject);

                      if (newCid != initCid) {
                          if (initCid != null) {
                              Materialize.toast(toastSubject, 3000);
                          }
                          initCid = newCid;
                          //console.log('new comment');
                      }
                  });

              }.bind(this),
              error: function(xhr, status, err) {
                  console.error(status, err.toString());
              }.bind(this)
          });
      }

      function sendForm() {
          $('#send-form .show-form').on('click', function() {$('#send-form').addClass("open");});
          $('#send-form .btn-close').on('click', function() {$('#send-form').removeClass("open");});
      }

      function preloader() {
          if ($('.preloader-overlay').length > 0 ) {
              $('body').css({
                  'overflow-y': 'hidden'
              });
          }
      }

      function _init() {
        //$('.facetapi-facet-field-sell-item a').wrapInner( "<label></label>" );
      }

      //todo move to backend
      function setLinkedSwitches() {
          var $switches = $('.switch[data-linked-facet-chekbox]');
          $switches.each(function() {
              var $switch = $( this ),
                  $switchInput =  $switch.find('input'),
                  $class = $switch.data('linked-facet-chekbox'),
                  $input = $('.' + $class + ' input.facetapi-checkbox'),
                  $parent = $input.parent('li'),
                  $link = $parent.find('a.facetapi-checkbox');
                  $parent.parent('ul').hide();
              if ($link.hasClass('facetapi-active')) {
                  $switchInput.prop('checked', true);
              } else {
                  $switchInput.prop('checked', false);
              }
          });
      }

      $(document).ready(function() {
          _init();
          preloader();
          sendForm();
          setLinkedSwitches(); //todo move to backend

         // var toastLastComment = setInterval(function() {
          //    loadCommentFromServer();
         // }, 6000);

          $('.button-collapse').sideNav({
              menuWidth: 300, // Default is 240
              edge: 'left', // Choose the horizontal origin
              closeOnClick: true // Closes side-nav on <a> clicks, useful for Angular/Meteor
          });

          $('ul.tabs').tabs();

          $myselect = $('select').not('select.shs-select');
          //console.log($myselect);
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
                  $insertlink.addClass('chip').append('<i class="icon ion-ios-close-empty"></i>');
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
          $myselect = $('select').not('select.shs-select');
          $myselect.material_select();
      });

      $(document).ajaxComplete(function() {
          $myselect = $('select').not('select.shs-select');
          $myselect.material_select();
      });

      $('.empty-switch input').change(function () {
          console.log($(this).prop('checked'));
          var check = $(this).prop('checked'),
              $catalog = $('#catalog');
          if (check) {
              $catalog.removeClass('hide-empty');
          } else {
              $catalog.addClass('hide-empty');
          }
      });

      //todo move to backend
      $('.switch[data-linked-facet-chekbox] input').change(function () {
          console.log($(this).prop('checked'));
          var $class = $(this).parents('.switch[data-linked-facet-chekbox]').data('linked-facet-chekbox'),
              $input = $('.' + $class + ' input.facetapi-checkbox'),
              $parent = $input.parent('li'),
              $url = $parent.find('a.facetapi-checkbox').attr('href');

          location.href = $url;
      });



      //$('#edit-field-sell-item input:checkbox').change(function () {
      //    var check = $(this).prop('checked'),
      //        $form = $(this).parents('.coin-form');
      //    if (check) {
     //         $form.addClass('just-sell');
     //         $form.find('.form-item-sell-price input').addClass('required');
     //         ////$form.find('.form-item-sell-price label').html($form.find('.form-item-sell-price label').html() + '<span class="form-required" title="This field is required.">*</span>');
     //         //$form.find('span.form-required').show();
     //     } else {
      //        $form.removeClass('just-sell');
      //        ////$form.find('.form-item-sell-price input').removeClass('required');
      //        ////$form.find('span.form-required').hide();
      //    }
     // });


      $(window).load(function () {
          $('.preloader-overlay').remove();
          $('body').css({
              'overflow-y': 'auto'
          });
      });

  }); // end of document ready
})(jQuery); // end of jQuery name space