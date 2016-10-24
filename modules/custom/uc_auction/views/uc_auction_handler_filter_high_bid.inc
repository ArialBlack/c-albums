<?php

/**
 * @file
 * Filter on the value of a product's high bid value.
 */

/**
 * Filter on the value of a product's high bid value.
 */
class uc_auction_handler_filter_high_bid extends views_handler_filter_numeric {
  function query() {
    $join = new views_join();
    $join->table = 'uc_auction_bids';
    $join->field = 'bid';
    $join->left_table = 'uc_auction';
    $join->left_field = 'high_bid';
    $join->type = 'LEFT';

    $this->query->queue_table('uc_auction_bids', 'uc_auction', $join);

    $this->ensure_my_table();

    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $this->{$info[$this->operator]['method']}('uc_auction_bids.amount');
    }
  }
}
