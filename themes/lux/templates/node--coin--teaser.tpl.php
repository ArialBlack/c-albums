<?php
/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 *
 * @ingroup templates
 * <header>
<?php print render($title_prefix); ?>
<?php if (!$page && !empty($title)): ?>
<h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
<?php endif; ?>
<?php print render($title_suffix); ?>

</header>
 *
 * <footer>
<?php print render($content['field_tags']); ?>
<?php print render($content['links']); ?>
</footer>
 *
 *
 * <?php print render($content['comments']); ?>
 *
 */

global $user;
$current_user = $user->uid;
$author_id = $node->uid;
$author = user_load($author_id);
$author_name = $author->name;

$coin_actions_variant = 3;
$expiry_string = '';
$bid_string = '';

if (isset($node->uc_auction)) {

  $expiry_string = render($content['uc_auction']['expiry']['#title']) . ': ' . render($content['uc_auction']['expiry']['#markup']);
  $bid_string = render($content['uc_auction']['high_bid']['#title']) . ': ' . render($content['uc_auction']['high_bid']['#markup']);
  //auction
  $expiry = $node->uc_auction['expiry'];
  $now = time();
  if ($expiry > $now) {
    //active auction
    $coin_actions_variant = 11;

    if ($node->uc_auction['buy_now']) {
      //can buy now
      $coin_actions_variant = 12;
    }

    if ($node->uc_auction['high_bid_uid'] == $current_user ) {
      //active and you are high
      $coin_actions_variant = 33;
    }

  } else {
    //finished auction
    $coin_actions_variant = 31;

    if ($node->uc_auction['high_bid_uid'] == $current_user ) {
      //you won
      $coin_actions_variant = 1;
    }
  }
} else if ($node->field_sell_item ) {
  //sel item
  $coin_actions_variant = 2;

} else {
  //just show coin
  $coin_actions_variant = 3;
}

if ($current_user == $author_id) {
  //owner
  $coin_actions_variant = 32;
}






?>

  <?php
  // Hide comments, tags, and links now so that we can render them later.
  hide($content['comments']);
  hide($content['links']);
  hide($content['field_tags']);
  //hide($content);
  ?>

<div class="card <?php print $classes; ?>" id="node-<?php print $node->nid; ?>" <?php print $attributes; ?>>

    <?php print render($content['field_coin']) ?>

    <div class="card-content">
      <span class="card-title activator grey-text text-darken-4"><?php print $title; ?><i class="icon ion-android-more-vertical"></i></span>

      <?php if ($node->field_condition): ?><div><i class="icon ion-ios-pulse-strong"></i><?php print render($content['field_condition']); ?></div><?php endif; ?>
      <?php if ($node->field_metal): ?><div><i class="icon ion-erlenmeyer-flask"></i><?php print render($content['field_metal']); ?></div><?php endif; ?>
      <?php if ($node->field_issuer): ?><div><i class="icon ion-wand"></i><?php print render($content['field_issuer']); ?></div><?php endif; ?>
      <?php if ($node->field_denomination): ?><div><i class="icon ion-ios-pie-outline"></i><?php print render($content['field_denomination']); ?></div><?php endif; ?>
      <?php if ($node->field_date_on_coin): ?><div><i class="icon ion-ios-calendar-outline"></i><?php print render($content['field_date_on_coin']); ?></div><?php endif; ?>

      <div><i class="icon ion-location"></i><?php print $user_location; ?></div>

      <div><i class="icon ion-chatbubbles"></i><p>commnents</p></div>

      <?php
      //print render($content['add_to_cart']);
      ?>

      <?php if ($coin_actions_variant == 1): ?>
          <!-- curent user won -->
          <div><i class="icon ion-trophy"></i><p>You won auction</p></div>
          <?php print render($content['add_to_cart']); ?>
      <?php endif; ?>

      <?php if ($coin_actions_variant == 11): ?>
          <!-- active auction -->
          <?php if ($node->uc_auction['bid_count']): ?><div><i class="icon ion-arrow-graph-up-right"></i><p><?php print t('Bids: ') . $node->uc_auction['bid_count'] . ' / ' . $bid_string ?></p></div><?php endif; ?>
          <?php if ($node->uc_auction['expiry']): ?><div><i class="icon ion-clock"></i><p><?php print $expiry_string; ?></p></div><?php endif; ?>
          <a href="/node/<?php print $node->nid ?>" class="node-add-to-cart btn btn light-blue waves-effect waves-light btn-default form-submit"><?php print t('Place bid'); ?></a>
      <?php endif; ?>

      <?php if ($coin_actions_variant == 12): ?>
          <!-- can buy now -->
          <a href="/node/<?php print $node->nid ?>" class="node-add-to-cart btn btn light-blue waves-effect waves-light btn-default form-submit"><?php print t('Buy now / place bid'); ?></a>
      <?php endif; ?>

      <?php if ($coin_actions_variant == 2): ?>
          <!-- just sell -->
          <?php print render($content['add_to_cart']); ?>
          <div><?php print '$'. round($node->sell_price, 0) ?></div>
      <?php endif; ?>

      <?php if ($coin_actions_variant == 3 || $coin_actions_variant == 31 || $coin_actions_variant == 32 || $coin_actions_variant == 33): ?>
          <?php if (isset($node->uc_auction) && $node->uc_auction['bid_count']): ?><div><i class="icon ion-arrow-graph-up-right"></i><p><?php print t('Bids: ') . $node->uc_auction['bid_count'] . ' / ' . $bid_string?></p></div><?php endif; ?>
          <?php if (isset($node->uc_auction) && $node->uc_auction['expiry']): ?><div><i class="icon ion-clock"></i><p><?php print $expiry_string; ?></p></div><?php endif; ?>
          <p><a href="/node/<?php print $node->nid ?>"><?php print t('View full info'); ?></a></p>

          <?php if ($coin_actions_variant == 31): ?>
            <div><?php print '$'. round($node->uc_auction['start_price']) ?></div>
          <?php endif; ?>

      <?php endif; ?>







    </div>
    <div class="card-reveal">
      <span class="card-title grey-text text-darken-4">Card Title<i class="icon ion-android-close"></i></span>
      <div><a href="/user/<?php print $author_id ?>"><i class="icon ion-person"></i><?php print $author->name ?></a></div>
      <p>Here is some more information about this product that is only revealed once clicked on.</p>
      <?php
      print render($content);
      ?>
    </div>
</div>




  <?php if ((!$page && !empty($title)) || !empty($title_prefix) || !empty($title_suffix) || $display_submitted): ?>


  <?php endif; ?>






  <?php if (!empty($content['field_tags']) || !empty($content['links'])): ?>

  <?php endif; ?>


