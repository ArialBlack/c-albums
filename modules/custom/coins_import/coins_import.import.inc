<?php

function coins_import_createnode($row, $u) {
    $node = new stdClass();
    $node->type = 'coin';
    node_object_prepare($node);

    $combined_title = '';

    $node->language = LANGUAGE_NONE;
    $node->uid = $u;
    $node->status = 0;
    $node->revision = FALSE;
    $node->comment = 2;
    $node->promote = 0;
    $node->sticky = 0;
    $node->log = NULL;
    $node->created = time();

    //General
    if (isset($row->grade)) {
        $node->field_condition['und'][0]['value'] = coins_import__grades($row->grade);
    } else {
        $node->field_condition['und'][0]['value'] = 'c0';
    }

    if (isset($row->metal)) {
        $node->field_metal['und'][0]['value'] = coins_import__metals($row->metal);
    }

    if (isset($row->weight)) {
        $node->field_weight['und'][0]['value'] = intval($row->weight);
    }

    if (isset($row->diameter)) {
        $node->field_diameter['und'][0]['value'] = intval($row->diameter);
    }

    if (isset($row->struck_cast)) {
        $node->field_struck_cast['und'][0]['value'] = coins_import__struck($row->struck_cast);
    }

    //Details
    if (isset($row->type)) {
        $node->field_type['und'][0]['value'] = $row->type;
    }

    if (isset($row->region)) {
        $node->field_region['und'][0]['value'] = $row->region;
    }

    if (isset($row->city)) {
        $node->field_city['und'][0]['value'] = $row->city;
    }

    if (isset($row->issuer)) {
        $node->field_issuer['und'][0]['value'] = $row->issuer;
        $combined_title = $combined_title . $row->issuer;
    }

    if (isset($row->denomination)) {
        $node->field_denomination['und'][0]['value'] = $row->denomination;
        $combined_title = $combined_title . ', ' . $row->denomination;
    }

    if (isset($row->date_struck)) {
        $node->field_date_struck['und'][0]['value'] = $row->date_struck;
        $combined_title = $combined_title . ', ' . $row->date_struck;
    }

    if (isset($row->date_ruled)) {
        $node->field_date_ruled['und'][0]['value'] = $row->date_ruled;
    }

    //Description
    if (isset($row->obverse_legend)) {
        $node->field_obverse_legend['und'][0]['value'] = $row->obverse_legend;
    }

    if (isset($row->obverse_description)) {
        $node->field_obverse_description['und'][0]['value'] = $row->obverse_description;
    }

    if (isset($row->reverse_legend)) {
        $node->field_reverse_legend['und'][0]['value'] = $row->reverse_legend;
    }

    if (isset($row->reverse_description)) {
        $node->field_reverse_description['und'][0]['value'] = $row->reverse_description;
    }

    if (isset($row->mint)) {
        $node->field_mint['und'][0]['value'] = $row->mint;
    }

    if (isset($row->originalid)) { //todo hide
        $node->field_originalid['und'][0]['value'] = $row->originalid;
    }

    $node->title = $combined_title;

    if (strlen($combined_title) > 3) {
        $furl = str_replace(array( '[', ']', '"' ), '', $row->photo);
        $furls = explode(",", $furl);

        $img_count = count($furls);

        if($img_count == 1) {

            $directory = file_build_uri('coinsphotoimport');
            if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
                // If our directory doesn't exist and can't be created, use the default.
                $directory = NULL;
            }

            //we need to duplicate file for cropping and B-side
            for ($f=0; $f <2; $f++) {
                $image = str_replace(' ', '%20', $furls[0]);
                $file_info = system_retrieve_file($image, $directory, TRUE);

                if($file_info->fid){
                    $node->field_coin['und'][$f]['fid'] = $file_info->fid;
                }
            }

        }

        if($img_count > 1) {
            for ($f = 0; $f < $img_count; $f++) {
                $furl = str_replace(array( '[', ']', '"' ), '', $furls[$f]);
                $directory = file_build_uri('coinsphotoimport');
                if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY)) {
                    // If our directory doesn't exist and can't be created, use the default.
                    $directory = NULL;
                }
                $image = str_replace(' ', '%20', $furls[$f]);
                $file_info = system_retrieve_file($image, $directory, TRUE);

                if($file_info->fid){
                    $node->field_coin['und'][$f]['fid'] = $file_info->fid;
                }
            }
        }
    }

    $node->model = generateRandomString();

    $processed_id = $row->_id;
    $url_delete = 'http://localhost:3000/coins/' . $processed_id;
    $options = array(
        'method' => 'DELETE',
    );

    $node = node_submit($node);

    if (strlen($combined_title) > 3) {
        node_save($node);
        $result_delete = drupal_http_request($url_delete, $options);
    }

    return $node;
}