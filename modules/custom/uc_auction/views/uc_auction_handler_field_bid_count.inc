<?php

/**
 * @file
 * Bid count field handler.
 */

/**
 * Show the bid count, and link it to the bid page if the user has 'view bids'
 * permission.
 *
 * This kinda parallels how views_handler_field_node_new_comments works. If
 * there's a way to do this without putting a query in pre_render(), please let
 * me know.
 */
class uc_auction_handler_field_bid_count extends views_handler_field_numeric {
  function query() {

  }

  function pre_render(&$values) {
    // Get all nids
    if (count($values)) {
      $nids = array();
      $keys_by_nid = array();
      foreach ($values as $key => $vals) {
        $nids[] = $vals->nid;
        $keys_by_nid[$vals->nid] = $key;
      }

      // TODO Please convert this statement to the D7 database API syntax.
      $rez = db_query('SELECT nid, COUNT(*) as count FROM {uc_auction_bids} WHERE nid IN (' . db_placeholders($nids) . ') GROUP BY nid', $nids);
      while ($count = db_fetch_object($rez)) {
        $values[$keys_by_nid[$count->nid]]->{$this->field_alias} = $count->count;
      }
    }
  }

  function render($values) {
    if (!isset($values->{$this->field_alias})) {
      $values->{$this->field_alias} = '0';
    }
    return user_access('view bids') ? l($values->{$this->field_alias}, "node/{$values->nid}/bids", array('title' => t('See bid history for this item'))) : $values->{$this->field_alias};
  }
}
