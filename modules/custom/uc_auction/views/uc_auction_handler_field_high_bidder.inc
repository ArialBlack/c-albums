<?php

/**
 * @file
 * Auction high bidder field handler.
 */

/**
 * Show the username of the current high bidder for an auction.
 */
class uc_auction_handler_field_high_bidder extends views_handler_field {
  function query() {
    $join = new views_join();
    $join->table = 'uc_auction_bids';
    $join->field = 'bid';
    $join->left_table = 'uc_auction';
    $join->left_field = 'high_bid';
    $join->type = 'LEFT';
    $this->query->queue_table('uc_auction_bids', NULL, $join);

    $join = new views_join();
    $join->table = 'users';
    $join->field = 'uid';
    $join->left_table = 'uc_auction_bids';
    $join->left_field = 'uid';
    $join->type = 'LEFT';
    $this->query->queue_table('users', NULL, $join);

    $this->query->add_field('users', 'uid', 'uc_auction_high_bidder');
    $this->query->add_field('users', 'name', 'uc_auction_high_bidder_name');
  }

  function render($values) {
    if ($values->uc_auction_high_bidder) {
      $acct = new stdClass();
      $acct->name = $values->uc_auction_high_bidder_name;
      $acct->uid = $values->uc_auction_high_bidder;
      return theme('username', array('account' => $acct));
    }
  }
}
