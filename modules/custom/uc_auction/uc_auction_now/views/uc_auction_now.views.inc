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
function uc_auction_now_views_data() {
  return array(
    'uc_auction_now' => array(
      'is_now' => array(
        'title' => t('Buy Now enabled'),
        'help' => t('Is the &ldquo;Buy Now&rdquo; feature enabled for this product?'),
        'group' => t('Product'),
        'filter' => array(
          'handler' => 'uc_auction_now_handler_filter_is_now',
          'label' => t('Buy Now enabled'),
        ),
      ),
      'table' => array(
        'field' => 'nid',
        'title' => t('Auction Buy Now information'),
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
function uc_auction_now_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'uc_auction_now') . '/views',
    ),
    'handlers' => array(
      'uc_auction_now_handler_filter_is_now' => array(
        'parent' => 'uc_product_handler_filter_product',
      ),
    ),
  );
}
