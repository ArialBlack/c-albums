<?php

/**
 * @file
 * Contains callbacks for administering Ubercart Auction. Only those with the
 * 'access store' permission can access these pages.
 *
 * @ingroup uc_auction
 */

/**
 * Show the administration form. drupal_get_form() callback.
 */
function uc_auction_settings_form($form, &$form_state) {
  $incr = variable_get('uc_auction_max_increase', 1000);
  $pctg = variable_get('uc_auction_max_increase_pctg', 100);
  if (variable_get('uc_sign_after_amount', FALSE)) {
    $prefix = '';
    $suffix = variable_get('uc_currency_sign', '$');
  }
  else {
    $prefix = variable_get('uc_currency_sign', '$');
    $suffix = '';
  }
  // system_settings_form() is waeome.
  return system_settings_form(array(
    'uc_auction_default_fset' => array(
      '#type' => 'fieldset',
      '#title' => t('Defaults'),
      '#weight' => -30,
      'uc_auction_new_default' => array(
        '#type' => 'checkbox',
        '#title' => t('New products are auctions by default'),
        '#description' => t('If checked, the new product form will have the <em>This is an auction</em> check box checked by default, and the <em>Expiration date &amp; time</em> field will have the value of the <em>Default expiration date &amp; time</em> field below.'),
        '#default_value' => variable_get('uc_auction_new_default', FALSE),
        '#weight' => 0,
      ),
      'uc_auction_time_gran' => array(
        '#type' => 'select',
        '#title' => t('Time interval granularity'),
        '#options' => array(
          '1' => '1',
          '2' => '2',
          '3' => '3',
          '4' => '4',
          '5' => '5',
          '6' => '6',
        ),
        '#description' => t('When UC Auction formats time intervals, how specific should it be? The N largest units of time will be displayed. For example, if an interval of five days, four hours, three minutes and two seconds is to be represented, selecting &ldquo;1&rdquo; will cause &ldquo;5 days&rdquo; to be shown, whereas selecting &ldquo;3&rdquo; will cause &ldquo;5 days 4 hours 3 mins&rdquo; to be shown.'),
        '#default_value' => variable_get('uc_auction_time_gran', '2'),
        '#weight' => 10,
      ),
      'uc_auction_countdown' => array(
        '#type' => 'checkbox',
        '#title' => t('Active expiration countdown'),
        '#description' => t('When an auction product is viewed, a JavaScript script can update &ldquo;Expires in&rdquo; information every second, so users do not have to reload the page to see how much time they have left to place a bid. However, if a user&rsquo;s computer&rsquo;s clock is inaccurate, this countdown will be inaccurate as well.'),
        '#default_value' => variable_get('uc_auction_countdown', TRUE),
        '#weight' => 15,
      ),
      'uc_auction_hide_prices' => array(
        '#type' => 'checkbox',
        '#title' => t('Hide standard price fields for auctioned items'),
        '#description' => t('If checked, the standard price fields for Ubercart products will be hidden when auctioned products are shown to site visitors. This is recommended to reduce confusion and redundancy with the standard auction box. <a href="!fields">Enable/disable or reorder product fields</a>', array('!fields' => url('admin/store/settings/products/edit/fields'))),
        '#default_value' => variable_get('uc_auction_hide_prices', TRUE),
        '#weight' => 20,
      ),
    ),
    'uc_auction_bid_fset' => array(
      '#type' => 'fieldset',
      '#title' => t('Bid limits'),
      '#weight' => -25,
      'warning' => array(
        '#type' => 'item',
        '#value' => t('Changing these values while auctions are in progress is not advised. Please allow any current auctions to expire before changing these values. These values may be overriden on a per-product basis when editing an auctioned node product.'),
        '#weight' => 0,
      ),
      'uc_auction_force_one' => array(
        '#type' => 'checkbox',
        '#title' => t('Force quantities of one for auctioned items'),
        '#description' => t('When checked, Ubercart Auction will attempt to make sure that customers cannot purchase more than one of an auctioned item. Enabling this feature is strongly encouraged; however, you may want to disable it if you are limiting customer purchase quantites some other way.'),
        '#default_value' => variable_get('uc_auction_force_one', TRUE),
        '#weight' => 5,
      ),
      'uc_auction_bid_increment' => array(
        '#type' => 'textfield',
        '#title' => t('Bid increment'),
        '#description' => t('Bids must be a multiple of this increment to be accepted. If your site is using a currency which does not have subunits in circulation (JPY, KRW), this should be an integer.'),
        '#size' => 20,
        '#default_value' => uc_currency_format(variable_get('uc_auction_bid_increment', .25), FALSE, FALSE),
        '#field_prefix' => $prefix,
        '#field_suffix' => $suffix,
        '#weight' => 10,
      ),
      'uc_auction_min_increase' => array(
        '#type' => 'textfield',
        '#title' => t('Minimum bid increase'),
        '#description' => t('New bids must be at least this much higher than the current high bid to be accepted. This value should be a multiple of the <em>Bid increment</em> value.'),
        '#size' => 20,
        '#default_value' => uc_currency_format(variable_get('uc_auction_min_increase', .5), FALSE, FALSE),
        '#field_prefix' => $prefix,
        '#field_suffix' => $suffix,
        '#weight' => 15,
      ),
      'uc_auction_max_increase' => array(
        '#type' => 'textfield',
        '#title' => t('Maximum bid increase'),
        '#description' => t('New bids which are this much higher than the current high bid will not be accepted. Setting a maximum bid increase can make it more difficult for bidders to place a ridiculously high bid, either accidentally or otherwise. Enter zero or leave blank to not enforce this limit. In the case that both the <em>Maximum bid increase</em> and <em>Maximum bid increase percentage</em> values are set, both limits will be enforced.'),
        '#size' => 20,
        '#default_value' => $incr ? uc_currency_format($incr, FALSE, FALSE) : '',
        '#field_prefix' => $prefix,
        '#field_suffix' => $suffix,
        '#weight' => 20,
      ),
      'uc_auction_max_increase_pctg' => array(
        '#type' => 'textfield',
        '#title' => t('Maximum bid increase percentage'),
        '#description' => t('Bids which increase the high bid value by this percentage will not be accepted. For example, if this value is set to 50% and an item&rsquo;s current high bid is &curren;1000, bids larger than &curren;1500 will not be accepted (as &curren;500 is 50% of &curren;1000). Setting a maximum bid increase percentage can make it more difficult for bidders to place a ridiculously high bid, either accidentally or otherwise. Enter zero or leave blank to not enforce this limit. In the case that both the <em>Maximum bid increase</em> and <em>Maximum bid increase percentage</em> values are set, both limits will be enforced.'),
        '#field_suffix' => t('%'),
        '#size' => 6,
        '#default_value' => $pctg ? $pctg : '',
        '#weight' => 25,
      ),
    ),
    'uc_auction_notify_win_fset' => array(
      '#type' => 'fieldset',
      '#title' => t('Auction winner notification'),
      '#weight' => -20,
      'uc_auction_notify_win' => array(
        '#type' => 'checkbox',
        '#title' => t('Notify auction winners by email after auction ends'),
        '#description' => t('Auction winner notification emails will be sent <a href="http://drupal.org/cron" title="Configuring cron jobs">when cron jobs run</a>. It is recommended that you run cron jobs fairly frequently (at least hourly) when using this setting. If you are going to enable this setting after it has been disabled for some time, please <a href="!check">ensure that cron has run recently</a> before enabling, or else winners of very old auctions may receive notifications.', array('!check' => url('admin/reports/status'))),
        '#default_value' => variable_get('uc_auction_notify_win', TRUE),
        '#weight' => 0,
      ),
      'uc_auction_notify_win_subj' => array(
        '#type' => 'textfield',
        '#title' => t('Notification message subject'),
        '#default_value' => variable_get('uc_auction_notify_win_subj', uc_get_message('uc_auction_notify_win_subj')),
        '#weight' => 5,
      ),
      'uc_auction_notify_win_msg' => array(
        '#type' => 'textarea',
        '#title' => t('Notification message body'),
        '#description' => t('The message emailed to the auction winner. <a href="!uses">Uses auction, product and global tokens</a>.', array('!uses' => url('admin/store/help/tokens'))),
        '#default_value' => variable_get('uc_auction_notify_win_msg', uc_get_message('uc_auction_notify_win_msg')),
        '#weight' => 10,
      ),
    ),
    'uc_auction_notify_outbid_fset' => array(
      '#type' => 'fieldset',
      '#title' => t('Outbid notification'),
      '#weight' => -15,
      'uc_auction_notify_outbid' => array(
        '#type' => 'checkbox',
        '#title' => t('Notify bidders by email when they&rsquo;ve been outbid on an auction'),
        '#description' => t('Outbid notification emails will be sent immediately after the higher bid is accepted. Users can individually opt out of these notifications by editing their user account.'),
        '#default_value' => variable_get('uc_auction_notify_outbid', TRUE),
        '#weight' => 0,
      ),
      'uc_auction_notify_outbid_subj' => array(
        '#type' => 'textfield',
        '#title' => t('Notification message subject'),
        '#default_value' => variable_get('uc_auction_notify_outbid_subj', uc_get_message('uc_auction_notify_outbid_subj')),
        '#weight' => 5,
      ),
      'uc_auction_notify_outbid_msg' => array(
        '#type' => 'textarea',
        '#title' => t('Notification message body'),
        '#description' => t('The message emailed to the outbid bidder. <a href="!uses">Uses auction, product and global tokens</a>.', array('!uses' => url('admin/store/help/tokens'))),
        '#default_value' => variable_get('uc_auction_notify_outbid_msg', uc_get_message('uc_auction_notify_outbid_msg')),
        '#weight' => 10,
      ),
    ),
  ));
}

/**
 * Validate the settings form.
 */
function uc_auction_settings_form_validate($form, &$form_state) {
  // Remove non-numeric stuff from input which should have been a currency
  // value. We're not going to remove minus signs with the preg_replace call
  // below because we will chastise users later specifically for entering a
  // negative number.
  // @TODO: Check that these values will fit in the database?
  $form_state['values']['uc_auction_bid_increment'] = _uc_auction_uncurrency($form_state['values']['uc_auction_bid_increment']);
  $form_state['values']['uc_auction_min_increase'] = _uc_auction_uncurrency($form_state['values']['uc_auction_min_increase']);
  $form_state['values']['uc_auction_max_increase'] = _uc_auction_uncurrency($form_state['values']['uc_auction_max_increase']);
  $form_state['values']['uc_auction_max_increase_pctg'] = floatval($form_state['values']['uc_auction_max_increase_pctg']);
  $calc_div = TRUE;
  if ($form_state['values']['uc_auction_bid_increment'] <= 0) {
    form_set_error('uc_auction_bid_increment', t('The <em>Bid increment</em> value must be a positive, non-zero number.'));
    $calc_div = FALSE;
  }
  if ($form_state['values']['uc_auction_min_increase'] <= 0) {
    form_set_error('uc_auction_min_increase', t('The <em>Minimum bid increase</em> value must be a positive, non-zero number.'));
    $calc_div = FALSE;
  }
  if ($calc_div) {
    // Modulus operator converts to ints before operating. _uc_auction_mod_zero
    // is a workaround to that. It's declared in uc_auction.module.
    if (!_uc_auction_mod_zero($form_state['values']['uc_auction_min_increase'], $form_state['values']['uc_auction_bid_increment'])) {
      form_set_error('uc_auction_min_increase', t('The <em>Minimum bid increase</em> value is not a multiple of the <em>Bid increment</em> value.'));
    }
  }
  // We won't bother checking if uc_auction_max_increase is negative because
  // we're going to check that it's not less than uc_auction_min_increase, and
  // uc_auction_min_increase can't be zero. uc_auction_max_increase can be zero,
  // though (indicating that the limit should be ignored).
  if ($form_state['values']['uc_auction_max_increase'] && $form_state['values']['uc_auction_max_increase'] < $form_state['values']['uc_auction_min_increase']) {
    form_set_error('uc_auction_max_increase', t('The <em>Maximum bid increase</em> value cannot be smaller than the <em>Minimum bid increase</em> value.'));
  }
  if ($form_state['values']['uc_auction_max_increase_pctg'] < 0) {
    form_set_error('uc_auction_max_increase_pctg', t('The <em>Maximum bid increase percentage</em> value must be a positive number.'));
  }
}
