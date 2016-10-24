<?php

/**
 * @file
 * Views 2 hooks and callback registries.
 *
 * I'm still very much a Views n00b, so if any Views l33ts out there can give
 * this code a look-see and fix any areas of suckitude, I'd greatly appreciate
 * it.
 */

/**
 * Implements hook_views_data() (a Views hook)().
 */
function uc_auction_views_data() {
  return array(
    'uc_auction' => array(
      'is_auc' => array(
        'title' => t('Is auction'),
        'help' => t('Is this node a product up for auction?'),
        'group' => t('Product'),
        'filter' => array(
          'handler' => 'uc_auction_handler_filter_is_auc',
          'label' => t('Is up for auction'),
        ),
      ),
      'high_bid' => array(
        'title' => t('High bid'),
        'help' => t('An auctioned product&rsquo;s highest bid.'),
        'group' => t('Product'),
        'field' => array(
          'handler' => 'uc_auction_handler_field_high_bid',
          'click sortable' => TRUE,
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'filter' => array(
          'handler' => 'uc_auction_handler_filter_high_bid',
          'label' => t('High bid'),
        ),
      ),
      'expiry' => array(
        'title' => t('Auction expiry'),
        'help' => t('The time when this auction expires (ends).'),
        'group' => t('Product'),
        'field' => array(
          'handler' => 'uc_auction_handler_field_expires',
          'click sortable' => TRUE,
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_date',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_date',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort_date',
        ),
      ),
      'notified' => array(
        'title' => t('Winner notified'),
        'help' => t('Has the winner been notified by email that they have won the auction?'),
        'group' => t('Product'),
        'field' => array(
          'handler' => 'views_handler_field_boolean',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_boolean_operator',
          'label' => t('User has been notified'),
        ),
        'sort' => array(
          'handler' => 'views_handler_sort_date',
        ),
      ),
      'purchased' => array(
        'title' => t('Item purchased by winner'),
        'help' => t('Has the item been purchased?'),
        'group' => t('Product'),
        'field' => array(
          'handler' => 'views_handler_field_boolean',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_boolean_operator',
          'label' => t('Item has been purchased'),
        ),
        'sort' => array(
          'handler' => 'views_handler_sort_date',
        ),
      ),
      'start_price' => array(
        'title' => t('Auction start price'),
        'help' => t('The initial price for this auctioned item.'),
        'group' => t('Product'),
        'field' => array(
          'handler' => 'uc_product_handler_field_price',
          'click sortable' => TRUE,
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
        ),
      ),
      'high_bidder' => array(
        'title' => t('Current high bidder'),
        'help' => t('The current high bidder of the auction (or the winner if the auction has expired).'),
        'group' => t('Product'),
        'field' => array(
          'handler' => 'uc_auction_handler_field_high_bidder',
          'click sortable' => TRUE,
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_string',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      'bid_count' => array(
        'title' => t('Bid count'),
        'help' => t('The number of bids this auctioned item has received.'),
        'group' => t('Product'),
        'field' => array(
          'handler' => 'uc_auction_handler_field_bid_count',
          'click sortable' => TRUE,
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
          'title' => t('Name'),
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      'table' => array(
        'field' => 'nid',
        'title' => t('Auction information'),
        'group' => t('Product'),
        'join' => array(
          'node' => array(
            'left_field' => 'nid',
            'field' => 'nid',
          ),
        ),
      ),
    ),
  );
}

/**
 * Implements hook_views_handlers() (a Views hook)().
 */
function uc_auction_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'uc_auction') . '/views',
    ),
    'handlers' => array(
      'uc_auction_handler_field_high_bidder' => array(
        'parent' => 'views_handler_field',
      ),
      'uc_auction_handler_filter_is_auc' => array(
        'parent' => 'uc_product_handler_filter_product',
      ),
      'uc_auction_handler_field_expires' => array(
        'parent' => 'views_handler_field',
      ),
      'uc_auction_handler_field_bid_count' => array(
        'parent' => 'views_handler_field_numeric',
      ),
      'uc_auction_handler_field_high_bid' => array(
        'parent' => 'uc_product_handler_field_price',
      ),
      'uc_auction_handler_filter_high_bid' => array(
        'parent' => 'views_handler_filter_numeric',
      ),
    ),
  );
}
