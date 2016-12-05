<?php
/*
 * coinType,
 * coinRegion,
   coinCity, - can
   coinIssuer,
 */

function _getcointype($_type, $_region, $_city, $_issuer) {

    $types = [];
    $root = taxonomy_get_tree(1, 0, 1);

    for($r = 0; $r < count($root); $r++) {
        $_types = taxonomy_get_tree(1, $root[$r]->tid, 1);
        $types = array_merge($types, $_types);
    }

    foreach ($types as $type) {
        if($type->name == $_type) {
            $type_tid = $type->tid;
            break;
        }
    }

    $issuers = taxonomy_get_tree(1, $type_tid, $max_depth = NULL, $load_entities = FALSE);

    $found_issuers = [];
    foreach ($issuers as $issuer) {
        if($issuer->name == $_issuer) {
            array_push($found_issuers, $issuer->tid);
        }
    }

    if (count($found_issuers) == 1) {
        return $found_issuers[0];
    } else if (count($found_issuers) > 1) {

        for($i = 0; $i < count($found_issuers); $i++) {
            dsm(taxonomy_get_parents_all($found_issuers[$i]));
        }

    } else {
        return false;
    }

}
