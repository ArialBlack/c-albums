<?php

function _prepare_terms () {
    /*$terms = array(
        'type-1' => array(
            'city-1' => array(
                'region-1' => array(),
            ),
            'city-2' => array(
                'region-2' => array(
                    'issuer-2' => array(),
                ),
            ),
        ),
        'type-2' => array(
            'issuer-3' => array(),
        ),
    );*/

   // dsm($terms);
    //dsm($terms['type-1']);


    $keys_types = db_select('field_data_field_type', 't')
        ->fields('t', array('field_type_value'))
        ->distinct()
        ->execute()->fetchCol();
    //dsm($keys_types);

    $terms = array_fill_keys($keys_types, array());

    foreach ($terms as $key=>$value ){
       $type = $key;

        $query = db_select('node', 'n');
        $query->innerJoin('field_data_field_type', 't', 't.entity_id = n.nid');
        $query->leftJoin('field_data_field_region', 'r', 'r.entity_id = n.nid');
        //$query->leftJoin('field_data_field_city', 'c', 'c.entity_id = n.nid');
        //$query->leftJoin('field_data_field_issuer', 'i', 'i.entity_id = n.nid');
        //$query->fields('t', array('field_type_value'));
        $query->fields('r', array('field_region_value'));
        //$query->fields('c', array('field_city_value'));
        //$query->fields('i', array('field_issuer_value'));
        $query->condition('n.type', 'coin');
        $query->condition('t.field_type_value', $type);
        $query->distinct();
        $regions_keys = $query->execute()->fetchCol();

        //dsm($regions_keys);

        $terms[$type] = array_fill_keys($regions_keys, array());

        foreach ($terms[$type] as $key2=>$value ){
            $region = $key2;
            //dsm($region);

            $query = db_select('node', 'n');
            $query->innerJoin('field_data_field_type', 't', 't.entity_id = n.nid');
            $query->leftJoin('field_data_field_region', 'r', 'r.entity_id = n.nid');
            $query->leftJoin('field_data_field_city', 'c', 'c.entity_id = n.nid');
            //$query->leftJoin('field_data_field_issuer', 'i', 'i.entity_id = n.nid');
            //$query->fields('t', array('field_type_value'));
            //$query->fields('r', array('field_region_value'));
            $query->fields('c', array('field_city_value'));
            //$query->fields('i', array('field_issuer_value'));
            $query->condition('n.type', 'coin');
            $query->condition('t.field_type_value', $type);
            $query->condition('r.field_region_value', $region);
            $query->distinct();
            $city_keys = $query->execute()->fetchCol();

            $terms[$type][$region] = array_fill_keys($city_keys, array());

        }

    }

    dsm($terms);
    return $terms;
}

function _create_taxonomy($terms) {
    // Create your vocabulary.
    // First check if the vocabulary exists otherwise an error will be thrown when trying to create it.
    $vocabs = taxonomy_get_vocabularies(NULL);
    $vocab = new stdClass();

    foreach ($vocabs as $vocab_object) {
        if ($vocab_object->machine_name == 'vocab_short_name') {
            // Vocab found.  Grab the object.
            $vocab = $vocab_object;
            break;
        }
    }
    // If the vid is not set then create the vocab.
    if(!isset($vocab->vid)) {
        $vocab = new stdClass();
        $vocab->name = 'Vocabulary Name';
        $vocab->machine_name = 'vocab_short_name';
        taxonomy_vocabulary_save($vocab);
    }
    // Recursive function that will create the hierarchical terms.
    coins_import_add_hierarchical_terms($terms, $vocab->vid);
}

function coins_import_add_hierarchical_terms($vocab, $vid, $parent = null) {

    foreach($vocab as $term_name => $term) {
        // Create the term
        $term_object = new stdClass();
        $term_object->vid = $vid;
        $term_object->name = $term_name;
        if(isset($parent)) {
            $term_object->parent = $parent;
        }
        taxonomy_term_save($term_object);

        if(is_array($term)) {
            // Recursively call the function, passing the term id of the parent.
            coins_import_add_hierarchical_terms($term, $vid, $term_object->tid);
        }
    }
}
