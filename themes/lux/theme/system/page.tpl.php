<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see lux_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see lux_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
$cart_block = module_invoke('coins', 'block_view', 'MiniCart');

$show_preloader = false;
switch (request_path()) {
    case 'catalog':
        $show_preloader = true;
        break;
}

?>

<?php if ($show_preloader): ?>
    <div class="preloader-overlay">
        <div class="preloader-container">
            <div class="preloader-wrapper big active">
                <div class="spinner-layer spinner-blue-only">
                    <div class="circle-clipper left">
                        <div class="circle"></div>
                    </div><div class="gap-patch">
                        <div class="circle"></div>
                    </div><div class="circle-clipper right">
                        <div class="circle"></div>
                    </div>
                </div>
            </div>
        </div>
    </div>

<?php endif; ?>

<header>
  <nav class="top-nav">
    <div class="full-container">
      <div class="nav-wrapper">
          <?php
              print render($primary_nav);


          print render($cart_block['content']);
          ?>

      </div>
    </div>
  </nav>

  <div class="container">
    <a href="#" data-activates="nav-mobile" class="button-collapse top-nav full hide-on-large-only"><i class="icon ion-navicon"></i></a>
  </div>

  <div id="nav-mobile" class="side-nav fixed">
    <?php if ($logo): ?>
      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo" class="brand-logo">
        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
      </a>
    <?php endif; ?>

      <div id="sidebar-first" class="column sidebar"><div class="section">
              <?php
                $cp = current_path();
                $path = substr($cp, 0, 6);
              ?>
              <?php if ($path != 'search'): ?>
                  <ul class="collapsible user-menu" data-collapsible="expandable">
                      <li>
                          <?php
                            $userlimits_block = module_invoke('coins', 'block_view', 'UserLimits');
                            $msg_block = module_invoke('privatemsg', 'block_view', 'privatemsg-new');
                          ?>
                          <div class="collapsible-header active"><i class="icon ion-person"></i> <?php print t('Profile'); ?></div>
                          <div class="collapsible-body">
                              <?php
                                print render($userlimits_block['content']);
                                print render($msg_block['content']);
                              ?>
                          </div>
                          <div class="collapsible-body"></div>
                      </li>
                      <li>
                          <?php $useractions_block = module_invoke('coins', 'block_view', 'UserActions'); ?>
                          <div class="collapsible-header active"><i class="icon ion-ios-bolt"></i> <?php print t('Actions'); ?></div>
                          <div class="collapsible-body"><?php print render($useractions_block['content']); ?></div>
                      </li>
                  </ul>
              <?php endif; ?>
              <?php if ($path == 'search'): ?>
                  <ul class="collapsible user-menu" data-collapsible="accordion">
                      <li>
                          <?php
                            $userlimits_block = module_invoke('coins', 'block_view', 'UserLimits');
                            $msg_block = module_invoke('privatemsg', 'block_view', 'privatemsg-new');
                          ?>
                          <div class="collapsible-header"><i class="icon ion-person"></i> <?php print t('Profile'); ?></div>
                          <div class="collapsible-body">
                              <?php
                                print render($userlimits_block['content']);
                                print render($msg_block['content']);
                              ?>
                      </li>
                      <li>
                          <?php $useractions_block = module_invoke('coins', 'block_view', 'UserActions'); ?>
                          <div class="collapsible-header"><i class="icon ion-ios-bolt"></i> <?php print t('Actions'); ?></div>
                          <div class="collapsible-body"><?php print render($useractions_block['content']); ?></div>
                      </li>
                  </ul>

                  <h6 class="side-menu-block-title"><?php print t('Filters:');?></h6>
                  <ul class="collapsible facet-search-menu" data-collapsible="expandable">
                      <?php
                        $facet_condition = module_invoke('facetapi', 'block_view', 'PVhLjDeLKfq5MBczJNYyGFmTFPGhxJjw');
                        $facet_date_on_coin = module_invoke('facetapi', 'block_view', '2jP2OGo3ozMxLgQQnTBur5CreEGNl7O7');
                        $facet_denomination = module_invoke('facetapi', 'block_view', 'otQY26r071KzVPfIYeaR67wCA1pYsTgc');
                        $facet_metal = module_invoke('facetapi', 'block_view', 'gc62eYWeLzjbCDHEShV0LKV1jAKMbY0x');
                        $facet_sell = module_invoke('facetapi', 'block_view', 'WunX70X0h1hXzbBmTtoAnjnBjP0iICEe');
                        $facet_price = module_invoke('facetapi', 'block_view', 'hsA18paT13IX1xFKuLrBNXEsnjjZnxgI');
                        $facet_type = module_invoke('facetapi', 'block_view', 'J2BnfgejIrkARaL30Z3gaWn95cOFxyz1');


                        $date_filter = strpos($cp, 'date-on-coin') > 0 ? true : false;
                        $denomination_filter = strpos($cp, 'denomination') > 0 ? true : false;
                        $metal_filter = strpos($cp, 'metal') > 0 ? true : false;
                        $sell_filter = strpos($cp, 'is-sell') > 0 ? true : false;
                        $price_filter = strpos($cp, 'price') > 0 ? true : false;
                        $type_filter = strpos($cp, 'type') > 0 ? true : false;

                        //open first filter if filter by first filter or all filters not opened
                        $is_all_filters_empty = $date_filter + $denomination_filter + $metal_filter + $sell_filter + $price_filter + $type_filter;
                        if (strpos($cp, 'condition') > 0 || !$is_all_filters_empty) {
                            $condition_filter = true;
                        } else $condition_filter = false;
                     ?>
                      <?php if ($facet_condition['content']): ?>
                      <li>
                          <div class="collapsible-header <?php if($condition_filter) {print ('active');} ?>"><i class="icon ion-ios-pulse-strong"></i> <?php print t('Filter by condition'); ?></div>
                          <div class="collapsible-body"><?php print render($facet_condition['content']); ?></div>
                      </li>
                      <?php endif; ?>
                      <?php if ($facet_date_on_coin['content']): ?>
                      <li>
                          <div class="collapsible-header <?php if($date_filter) {print ('active');} ?>"><i class="icon ion-ios-calendar-outline"></i> <?php print t('Filter by date'); ?></div>
                          <div class="collapsible-body"><?php print render($facet_date_on_coin['content']); ?></div>
                      </li>
                      <?php endif; ?>
                      <?php if ($facet_denomination['content']): ?>
                          <li>
                              <div class="collapsible-header <?php if($denomination_filter) {print ('active');} ?>"><i class="icon ion-ios-pie-outline"></i> <?php print t('Filter by denomination'); ?></div>
                              <div class="collapsible-body"><?php print render($facet_denomination['content']); ?></div>
                          </li>
                      <?php endif; ?>
                      <?php if ($facet_metal['content']): ?>
                      <li>
                          <div class="collapsible-header <?php if($metal_filter) {print ('active');} ?>"><i class="icon ion-erlenmeyer-flask"></i> <?php print t('Filter by metal'); ?></div>
                          <div class="collapsible-body"><?php print render($facet_metal['content']); ?></div>
                      </li>
                      <?php endif; ?>
                      <?php if ($facet_sell['content']): ?>
                      <li>
                          <div class="collapsible-header <?php if($sell_filter) {print ('active');} ?>"><i class="icon ion-bag"></i> <?php print t('Filter sell items'); ?></div>
                          <div class="collapsible-body"><?php print render($facet_sell['content']); ?></div>
                      </li>
                      <?php endif; ?>
                      <?php if ($facet_price['content']): ?>
                      <li>
                          <div class="collapsible-header <?php if($price_filter) {print ('active');} ?>"><i class="icon ion-social-usd"></i> <?php print t('Filter by price'); ?></div>
                          <div class="collapsible-body"><?php print render($facet_price['content']); ?></div>
                      </li>
                      <?php endif; ?>
                      <?php if ($facet_type['content']): ?>
                      <li>
                          <div class="collapsible-header <?php if($type_filter) {print ('active');} ?>"><i class="icon ion-ios-folder-outline"></i> <?php print t('Filter by type'); ?></div>
                          <div class="collapsible-body"><?php print render($facet_type['content']); ?></div>
                      </li>
                      <?php endif; ?>
                  </ul>

              <?php endif; ?>
          <?php print render($page['sidebar_first']); ?>
              <ul>
                  <li><a href="/user"></i><?php print t('My profile'); ?></a></li>
                  <li><a href="/user/logout"><?php print t('Logout'); ?></a></li>
              </ul>
        </div></div> <!-- /.section, /#sidebar-first -->

  </div>
</header>

<main>
    <div class="full-container">
    <div class="row">

      <div class="col s12">
        <?php if ($breadcrumb): ?>
          <div id="breadcrumb"><?php print $breadcrumb; ?></div>
        <?php endif; ?>

        <?php print $messages; ?>

        <div id="content" class="column"><div class="section">
            <?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
            <a id="main-content"></a>
            <?php print render($title_prefix); ?>
            <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
            <?php print render($title_suffix); ?>
            <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
            <?php print render($page['help']); ?>
            <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
            <?php print render($page['content']); ?>
            <?php print $feed_icons; ?>
          </div></div> <!-- /.section, /#content -->

    </div>
  </div>

</main>

<footer class="page-footer">
    <div id="send-form" class="animated print-hidden">
        <a class="btn-close" href="#closeform"><i class="icon ion-close-circled"></i></a>
        <div class="form-container">

                <a class="show-form" href="#showform">Report / Feedback</a>
            <?php
            $feedback_block = module_invoke('webform', 'block_view', 'client-block-967');

            ?>
            <div class="form-content">
                <div class="form">


                    <?php
                    print render($feedback_block['content']);

                    ?>
                </div>
            </div>
        </div>
    </div>

    <?php print render($page['footer']); ?>
  <div class="footer-copyright">
    <div class="container">© 2016 jj, All rights reserved.</div>
  </div>
</footer>
