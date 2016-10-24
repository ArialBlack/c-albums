<?php

/**
 * @file
 * Auction expiry field handler.
 */

/**
 * Show the relative time the auction will expire/has expired.
 */
class uc_auction_handler_field_expires extends views_handler_field {
  function render($values) {
    $value = $values->{$this->field_alias};
    if ($value !== NULL) {
      // This call to drupal_add_css() doesn't work…?
      drupal_add_css(drupal_get_path('modules', 'uc_auction') . '/uc_auction.css');
      $time = REQUEST_TIME;
      if ($value >= $time) {
        $in = $value - $time;
        $in_text = format_interval($in, variable_get('uc_auction_time_gran', 2));
        if ($in < 60) {
          // Within a minute
          return '<div class="uc-auction-expiry-min">' . $in_text . '</div>';
        }
        elseif ($in < 3600) {
          // Within an hour
          return '<div class="uc-auction-expiry-hour">' . $in_text . '</div>';
        }
        elseif ($in < 86400) {
          // Within 24 hours
          return '<div class="uc-auction-expiry-day">' . $in_text . '</div>';
        }
        else {
          return $in_text;
        }
      }
      else {
        return t('@time ago', array('@time' => format_interval($time - $value, variable_get('uc_auction_time_gran', 2))));
      }
    }
  }
}
