/*global Drupal, jQuery, alert, $ */

/**
 * @file
 * The main JavaScript file for Ubercart Auction.
 *
 * @ingroup uc_auction
 */

/**
 * Start the auction countdown timer and dictate what should happen on each
 * "tick."
 */
Drupal.behaviors.ucAuction = function(context) {
  if (!$('body').hasClass('ucAuction-processed')) {
    // Declare an array of time units, for use by the formatInterval() function.
    // We're not going to declare it inside of formatInterval() because it only
    // needs to be declared once.
  
    // Convert the expiry time, which is using seconds, into milliseconds.
    Drupal.settings.ucAuction.expiry *= 1000;
  
    if (Drupal.settings.ucAuction.doCountdown) {
      // everyTime() and stopTime() are part of jQuery Timers, declared in
      // uc_auction.timers.js
      $('.uc-auction-expiry').everyTime(1000, 'countdown', function(i) {
        // Note that we're not going to assume 1000 milliseconds have passed
        // since the last tick; instead we'll get the current timestamp and work
        // with the difference between it and the expiry timestamp. This is
        // because the 1000 millisecond interval is *not* guaranteed; if the
        // browser hangs for a moment, it may be longer. WebKit seems to aim for
        // at least 1000 ms each tick, but sometimes goes over; Mozilla seems to
        // aim for an average of 1000 ms each tick, using less time on the next
        // tick if the previous tick took more time.
        // Note that this will be inaccurate for people whose computer's clock
        // is not set correctly. (And in cases when the *server's* clock is not
        // set correctly, it'll be inaccurate for everyone.) Given that all
        // operating systems worth counting can synchronize their time to a NTP
        // server, this will hopefully rarely be an issue.
        var that = $(this),
          now = new Date(),
          // Adjust for time zonage too.
          delta = Drupal.settings.ucAuction.expiry - now.getTime() + (now.getTimezoneOffset() * 60000);
        if (delta <= 0) {
          // The auction has expired.
          that.text(Drupal.t('expired')).stopTime('countdown');
        }
        else {
          // formatInterval() is declared below
          that.text(Drupal.formatInterval(Math.floor(delta / 1000), Drupal.settings.ucAuction.timeGran));
          if (delta < 60000 && !that.hasClass('uc-auction-expiry-min')) {
            // This minute
            that.removeClass('uc-auction-expiry-day').removeClass('uc-auction-expiry-hour').addClass('uc-auction-expiry-min');
          }
          else if (delta < 3600000 && !that.hasClass('uc-auction-expiry-hour')) {
            // This hour
            that.removeClass('uc-auction-expiry-day').addClass('uc-auction-expiry-hour');
          }
          else if (delta < 86400000 && !that.hasClass('uc-auction-expiry-day')) {
            // In 24 hours
            that.addClass('uc-auction-expiry-day');
          }
        }
      });
    }
    // When the bid form is submitted, let's do some client-side verification
    // (don't worry, we're checking things server-side too).
    $('#uc-auction-bid-table-form').submit(function() {
      // The below is analogous to _uc_auction_uncurrency().
      var bidVal = Number($('#edit-user-bid').val().replace(Drupal.settings.ucAuction.currencyThou, '').replace(Drupal.settings.ucAuction.currencyDec, '.').replace(/[^\d\.\-]/g, ''));
      // Is the bid value below the minimum bid value?
      if (bidVal < Drupal.settings.ucAuction.minBid) {
        alert(Drupal.t('The current minimum bid value is @val.', {'@val': Drupal.settings.ucAuction.minBidF}));
        $('#edit-user-bid').val(Drupal.settings.ucAuction.minBidFNoSign).addClass('error').focus();
        return false;
      }
      // Is the bid value above the maximum bid value? (Ignore this if the
      // minimum bid value is greater than the maximum bid value.)
      else if (Drupal.settings.ucAuction.maxBid > Drupal.settings.ucAuction.minBid && bidVal > Drupal.settings.ucAuction.maxBid) {
        alert(Drupal.t('The current maximum bid value is @val.', {'@val': Drupal.settings.ucAuction.maxBidF}));
        $('#edit-user-bid').val(Drupal.settings.ucAuction.maxBidFNoSign).addClass('error').focus();
        return false;
      }
      // Is the bid value a multiple of the bid increment value?
      else if (bidVal % Drupal.settings.ucAuction.bidIncrement !== 0) {
        alert(Drupal.t('Your bid must be a multiple of @inc to be accepted.', {'@inc': Drupal.settings.ucAuction.bidIncrementF}));
        $('#edit-user-bid').addClass('error').focus();
        return false;
      }
      // Allow the form to be submitted.
      return true;
    });
  $('body').addClass('ucAuction-processed');
  }
};

/**
 * Given a timestamp, return a formatted time interval.
 *
 * This is a rewrite of Drupal's format_interval() function in JS. It's called
 * the same way and uses the same parameters.
 *
 * @param timestamp
 *   The length of time in seconds to format. (Note this is seconds, not
 *   milliseconds as JavaScript is fond of using.)
 * @param granularity
 *   The granularity of the returned formatted time interval.
 * @param langcode
 *   The language code as used by Drupal.formatPlural().
 * @return
 *   A formatted, translated time interval string.
 */
Drupal.formatInterval = function(timestamp, granularity, langcode) {
  granularity = parseInt(granularity, 10) || 2;
  langcode = langcode || null;
  var units = [
    {
      'singular' : '1 year',
      'plural' : '@count years',
      'secs' : 31536000
    },
    {
      'singular' : '1 week',
      'plural' : '@count weeks',
      'secs' : 604800
    },
    {
      'singular' : '1 day',
      'plural' : '@count days',
      'secs' : 86400
    },
    {
      'singular' : '1 hour',
      'plural' : '@count hours',
      'secs' : 3600
    },
    {
      'singular' : '1 min',
      'plural' : '@count min',
      'secs' : 60
    },
    {
      'singular' : '1 sec',
      'plural' : '@count sec',
      'secs' : 1
    }
  ],
    output = '';
  $.each(units, function(i, val) {
    if (timestamp >= val.secs && granularity > 0) {
      output += (output ? ' ' : '') + Drupal.formatPlural(Math.floor(timestamp / val.secs), val.singular, val.plural, {}, langcode);
      timestamp %= val.secs;
      granularity--;
    }
    if (granularity === 0) {
      return false;
    }
  });
  return output ? output : Drupal.t('0 sec', {}, langcode);
};