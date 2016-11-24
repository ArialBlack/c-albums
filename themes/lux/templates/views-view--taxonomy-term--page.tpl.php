<?php

/**
 * @file
 * Main view template.
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 *
 * @ingroup views_templates
 */

$tid = arg(2);
$description = '';
$img_fid = null;

$parents = taxonomy_get_parents_all($tid);
$c = 0;

foreach ( $parents as $parent ) {
  if ($c !=0) {
    $breadcrumb[] = '<span><a href="/taxonomy/term' . $parent->tid . '">' . $parent->name . '</a></span>';
  }

  if (strlen($description) == 0 && $parent->description) {
    $description = $parent->description;
  }

  if ($img_fid == null && $parent->field_cover_image) {
    $img_fid = $parent->field_cover_image['und']['0']['fid'];
  }
  $c++;
}

$file = file_load($img_fid);

if($file) {
  $uri = $file->uri;
  $img = image_style_url("large", $uri);
} else {
  $img = 'http://placekitten.com.s3.amazonaws.com/homepage-samples/408/287.jpg'; //todo
}

$breadcrumb[] = '<span><a href="/catalog">' . t('Catalog') . '</a></span>';
$breadcrumb = array_reverse($breadcrumb);
//$_breadcrumb = array_pop($breadcrumb);
//dsm($_breadcrumb);
drupal_set_breadcrumb($breadcrumb);

?>

<div class="term-header" style="background-image: url('<?php print $img; ?>');"></div>
<div class="term-title">
  <h1><?php print $parents[0]->name; ?></h1>
</div>


<div class="<?php print $classes; ?>">
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <?php print $title; ?>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php print $description; ?>

  <?php if ($header): ?>
    <div class="view-header">
      <?php print $header; ?>
    </div>
  <?php endif; ?>

  <?php if ($exposed): ?>
    <div class="view-filters">
      <?php print $exposed; ?>
    </div>
  <?php endif; ?>



  <?php if ($attachment_before): ?>
    <div class="attachment attachment-before">
      <?php
        print $attachment_before;
      ?>

    </div>
  <?php endif; ?>

  <?php if ($rows): ?>
    <div class="view-content">
      <?php print $rows; ?>
    </div>
  <?php elseif ($empty): ?>
    <div class="view-empty">
      <?php print $empty; ?>
    </div>
  <?php endif; ?>

  <?php if ($pager): ?>
    <?php print $pager; ?>
  <?php endif; ?>

  <?php if ($attachment_after): ?>
    <div class="attachment attachment-after">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <?php print $more; ?>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="view-footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <div class="feed-icon">
      <?php print $feed_icon; ?>
    </div>
  <?php endif; ?>

</div><?php /* class view */ ?>
