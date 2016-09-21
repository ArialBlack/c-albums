<?php

/**
 * @file
 * Provides a filter on the Buy Now-ness of a product.
 */

/**
 * Filter on the auction-ness of a product.
 */
class uc_auction_now_handler_filter_is_now extends uc_product_handler_filter_product {
  function query() {
    $join = new views_join();
    $join->table = 'uc_auction_now';
    $join->field = 'nid';
    $join->left_table = 'node';
    $join->left_field = 'nid';
    if ($this->value) {
      // Okay. Calling parent::query() will add a filter to filter on product-
      // ness, as Ubercart's "Is product" filter does. However, if both this
      // filter and that filter are used, the WHERE clause is added twice. To
      // avoid this, we'll check to see if the WHERE clause for "Is product" is
      // already present, and not call parent::query() if that's the case.
      // However, this only works if "Is product" is sorted so it's before "Is
      // an auction!" Hmm.
      if (!in_array('product', $this->query->get_where_args())) {
        parent::query();
      }
      $join->type = 'INNER';
    }
    else {
      $join->type = 'LEFT';
      $this->query->add_where(0, 'uc_auction_now.nid IS NULL');
    }
    $this->query->queue_table('uc_auction_now', 'node', $join);
  }
}
