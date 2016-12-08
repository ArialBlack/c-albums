<?php
//cache_clear_all('*', 'my_module_data', TRUE);

function _get_terms() {
    if ($cache = cache_get('coins_data')) {
        // Возвращаем его данные, если он имеется.
        return $cache->data;
    }
    else {
        // Если кэш отсутствует, реализуем построение данных.
        $terms = db_query("
    SELECT td.tid, td.name, td.description, th.parent, f.field_cover_image_fid, (
      SELECT COUNT(*) FROM {taxonomy_index} ti
      LEFT JOIN {node} n ON ti.nid = n.nid
      WHERE ti.tid = td.tid AND n.status = 1
    ) node_count FROM {taxonomy_term_data} td
    INNER JOIN {taxonomy_term_hierarchy} th ON th.tid = td.tid
    LEFT JOIN {field_data_field_cover_image} f ON f.entity_id = td.tid
    WHERE vid = :vid
    ORDER BY weight
  ", array(':vid' => 1))->fetchAll();

        $terms_data = $terms;

        // Сохраняем данные в  кэш с именем:  my_module_data сегмента: {cache}.
        cache_set('coins_data', $terms_data, 'cache');

        // Возвращаем данные.
        return $terms_data;
    }
}

function coins_catalog_taxonomy_tree($vid, $parent) {
    $terms = _get_terms();

    $parents =  array_reverse(taxonomy_get_parents_all($parent), true);
    //array_pop($parents );

    $chips = '<div class="chip"><a href="/catalog">' . t('Catalog') .'</a></div>';
    $c = 0;
    $title = '';
    $count = count($parents);
    foreach ($parents as $parent_item) {
        $c++;

        if ($c != $count) {
            $chips .= '<div class="chip"><a href="/catalog-ajax?parent=' . $parent_item->tid . '">' . $parent_item->name .'<i class="icon ion-ios-close-empty"></i></a></div>';
        } else {
            $chips .= '<div class="chip">' . $parent_item->name .'</div>';
        }

        $title = $parent_item->name;
    }

    if ($title) {
        drupal_set_title($title);
    }

    //dsm($title);
    $output = '<div id="catalog"><div id="catalog-nav">' . $chips .'</div>';
    $output = $output  . '<div class="empty-switch switch"><label>Show empty items<input type="checkbox" checked="checked"><span class="lever"></span></label></div>';
    $output = $output  . '<div id="catalog-tree">' . theme('item_list', array('items' => _coins_catalog_taxonomy_tree($terms, $parent)));
    $output = $output . '</div></div>';
    return $output;
}

/**
 * Helper for mymodule_taxonomy_tree()
 */
function _coins_catalog_taxonomy_tree($terms, $parent = 0, &$node_count = 0) {
    $items = array();
    $node_count = 0;

    foreach ($terms as $term) {
        //dsm($term);
        if ($term->parent == $parent) {
            //$children = _coins_taxonomy_tree($terms, $term->tid, $childs_node_count);
            //$node_count += $term->node_count + $childs_node_count;
            $is_empty_class = '';

            //if (intval($term->node_count + $childs_node_count) == 0) {
                $is_empty_class = ' is-empty';
            //}

            if ($term->field_cover_image_fid) {
                $file = file_load($term->field_cover_image_fid);
                $uri = $file->uri;
                $img = '<img class="activator" src="' . image_style_url("taxonomy_card", $uri) . '"/>';
            } else {
                $img = '<img class="activator" src="http://placekitten.com/g/280/280"/>'; //TODO
            }

            $class_name = generateRandomClass();

            $term_childrens_count =  count(taxonomy_get_children($term->tid, 1));

            if ($term_childrens_count > 0 ) {
                $term_href = '/catalog?parent=' . $term->tid;
            } else {
                $term_href = '/taxonomy/term/' . $term->tid;
            }


            $cardtemplate = '<div class="card-container'  . $is_empty_class .'" data-cardid="' .$class_name . '"><div class="card"><div class="card-image waves-effect waves-block waves-light"><a data-cardid="' .$class_name . '" class="card-link" href='  . $term_href . '>' . $img . '<span class="card-hidden-title">' . $term->name . '</span></a></div>';
            $cardtemplate = $cardtemplate . '<div class="card-content"><span class="card-title">' . $term->name . '</span>';

            if ($term->description) {
                $cardtemplate = $cardtemplate . '<span class="card-title activator grey-text text-darken-4"><i class="icon ion-android-more-vertical"></i></span>';
            }

            $cardtemplate = $cardtemplate . '<p>' . (0) .'</p></div>';

            if ($term->description) {
                $cardtemplate = $cardtemplate . '<div class="card-reveal"><span class="card-title grey-text text-darken-4">' . $term->name . '<i class="icon ion-android-close"></i></span>';
                $cardtemplate = $cardtemplate . $term->description . '</div>';
            }

            $cardtemplate = $cardtemplate . '</div></div>';


            $items[] = array(
                //'data' =>  '<a href="/taxonomy/term/' . $term->tid  . '" class="' . generateRandomClass() . '">'  . $term->name .'</a>',
                'data' =>  $cardtemplate,
               // 'children' => $children,
            );
        }
    }

    return $items;
}


function coins_catalog() {
    $params = drupal_get_query_parameters();

    if (isset($params['parent'])) {
        $parent = $params['parent'];
    }

    if (!isset($parent)) {
        $parent = 0;
    }

    $markup = coins_catalog_taxonomy_tree(1, $parent);

    return $markup;
}
