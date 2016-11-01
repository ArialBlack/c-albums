<?php

/**
 * @file
 * Auction high bid field handler.
 */

/**
 * Handle and display a product's high bid value.
 */
class uc_auction_handler_field_high_bid extends views_handler_field {
  function query() {
    $join = new views_join();
    $join->table = 'uc_auction_bids';
    $join->field = 'bid';
    $join->left_table = 'uc_auction';
    $join->left_field = 'high_bid';
    $join->type = 'LEFT';
    $this->query->queue_table('uc_auction_bids', NULL, $join);

    $this->query->add_field('uc_auction', 'start_price');
    $this->query->add_field('uc_auction_bids', 'amount');
  }

  function render($values) {
    return uc_currency_format($values->uc_auction_bids_amount === NULL ? $values->uc_auction_start_price : $values->uc_auction_bids_amount);
  }
}
