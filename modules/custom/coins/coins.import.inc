<?php

function import_coins_form() {
    $form['description'] = array(
        '#type' => 'markup',
        '#markup' => '<p>We will import coins</p>',
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Import',
    );

    return $form;
}

function import_coins_form_submit($form, &$form_state) {
    // Подготавливаем данные для операций
    $result = db_select('node', 'n')->fields('n', array('nid'))->execute();

    // Создаём массив с операциями.
    foreach ($result as $row) {
        $operations[] = array('mymodule_change_date', array($row->nid));
    }

    $batch = array(
        // Массив операций и их параметров
        'operations' => $operations,
        // Функция, которая будет выполнена после окончания всех операций
        'finished' => 'mymodule_batch_finished',
        // Заголовок страницы с прогресс баром.
        // Опционально, по умолчанию t('Processing')
        'title' => 'Обновление дат',
        // Сообщение, показываемое при инициализации.
        // Опционально, по умолчанию t('Initializing.')
        'init_message' => 'Подготовка данных',
        // Сообщение, показывемое при выполнении операций.
        // Опционально, по умолчанию t('Completed @current of @total.')
        'progress_message' => 'Выполнено @current из @total.',
        // Сообщение показываемое при ошибке выполнения операции.
        // Опционально, по умолчанию t('An error has occurred.')
        'error_message' => 'Произошла ошибка.',
    );

    batch_set($batch);

    // Если Batch API используется не из _submit функции,
    // то дополнительно нужно вызвать batch_process();
}

function coins_import_batch() {
    $url = 'http://localhost:3000/coins';
    $result = drupal_http_request($url);
    $result_data = json_decode($result->data);

    $count_coins = count($result_data->message);
    dsm($count_coins);
    dsm($result_data->message[0]);
    /////////////////////
    /*
     *
photo (String, 55 characters ) ["http://www.coinproject.com/siteimages/31-PC10...
grade (String, 4 characters ) Fine
primary_reference (String, 9 characters ) SBCV 1719
mint (String, 7 characters ) Cherson
reverse_description (String, 47 characters ) Cross floriate on three steps, pellets in field
obverse_description (String, 57 characters ) Large B, standing on exergual line, pellet on e...
obverse_legend (String, 1 characters ) B
weight (String, 6 characters ) 5.38 g
diameter (String, 5 characters ) 18 mm
date_struck (String, 10 characters ) AD 867-886
struck_cast (String, 4 characters ) cast
denomination (String, 5 characters ) AE 18
metal (String, 6 characters ) Bronze
date_ruled (String, 10 characters ) AD 867-886
issuer (String, 22 characters ) Basil I the Macedonian
region (String, 16 characters ) BYZANTINE EMPIRE
type (String, 9 characters ) Byzantine
coinid (String, 6 characters ) PC1077
originalid (String, 4 characters ) 1525

    */

    $metals = [];
    $grades = [];

    for($i=0; $i < $count_coins; $i++) {
        if (isset($result_data->message[$i]->metal)) {
            $metal = $result_data->message[$i]->metal;
            if (!in_array($metal, $metals)) {
                array_push($metals, $metal);
            }
        }

        if (isset($result_data->message[$i]->grade)) {
            $grade = $result_data->message[$i]->grade;
            if (!in_array($grade, $grades)) {
                array_push($grades, $grade);
            }
        }
    }

    dsm($metals);
    dsm($grades);

    $uids = db_select('users_roles', 'u')
        ->fields('u', array('uid'))
        ->condition('u.rid', '7')
        ->execute()->fetchAll();

    $random_uid_position = intval(rand(0 , count($uids)-1));


    ////////////////////////////////

    $num_operations = 10;
    drupal_set_message(t('Creating an array of @num operations', array('@num' => $num_operations)));

    $operations = array();
    // Set up an operations array with 1000 elements, each doing function
    // batch_example_op_1.
    // Each operation in the operations array means at least one new HTTP request,
    // running Drupal from scratch to accomplish the operation. If the operation
    // returns with $context['finished'] != TRUE, then it will be called again.
    // In this example, $context['finished'] is always TRUE.
    for ($i = 0; $i < $num_operations; $i++) {
        // Each operation is an array consisting of
        // - The function to call.
        // - An array of arguments to that function.
        $uid = $uids[$random_uid_position]->uid;
        $operations[] = array(
            'coins_import_op',
        );
    }
    $batch = array(
        'operations' => $operations,
        'finished' => 'coins_import_finished',
    );
    return $batch;
}

function coins_import_op(&$context) {


    // Store some results for post-processing in the 'finished' callback.
    // The contents of 'results' will be available as $results in the
    // 'finished' function (in this example, batch_example_finished()).

    //$context['results'][] = $node->nid . ' : ' . check_plain($node->title);

    // Optional message displayed under the progressbar.
    //$context['message'] = t('Loading node "@title"', array('@title' => $node->title)) . ' ' . $operation_details;

    _coins_import_update_http_requests();
}

function _coins_import_update_http_requests() {
    $_SESSION['http_request_count']++;
}

function coins_import_finished($success, $results, $operations) {
    if ($success) {
        // Here we could do something meaningful with the results.
        // We just display the number of nodes we processed...
        drupal_set_message(t('@count results processed in @requests HTTP requests.', array('@count' => count($results), '@requests' => _coins_import_get_http_requests())));
        drupal_set_message(t('The final result was "%final"', array('%final' => end($results))));
    }
    else {
        // An error occurred.
        // $operations contains the operations that remained unprocessed.
        $error_operation = reset($operations);
        drupal_set_message(
            t('An error occurred while processing @operation with arguments : @args',
                array(
                    '@operation' => $error_operation[0],
                    '@args' => print_r($error_operation[0], TRUE),
                )
            ),
            'error'
        );
    }
}

function _coins_import_get_http_requests() {
    return !empty($_SESSION['http_request_count']) ? $_SESSION['http_request_count'] : 0;
}





function _import_coins() {
    ///////////////////////

    $node = new stdClass();
    $node->type = 'coin';
    node_object_prepare($node);

    $node->title =  $result_data->message[0]->denomination . ' ' . $result_data->message[0]->issuer . ' '. $result_data->message[0]->date_ruled;
    $node->language = LANGUAGE_NONE;
    $node->uid = $uids[$random_uid_position]->uid;
    $node->status = 1;
    $node->revision = FALSE;
    $node->comment = 0;
    $node->promote = 0;
    $node->sticky = 0;
    $node->log = NULL;
    $node->created = time();

    /*$node->field_src_url[$node->language][0]['value'] = $json->url;

    $img_count = count ( $json->imgsrc);

    for ($i = 0; $i < $img_count; $i++) {
        $url = $json->imgsrc[$i];
        $file_info = system_retrieve_file($url, 'public://pictures/', TRUE);
        if($file_info->fid){
            $node->field_image[LANGUAGE_NONE][$i]['fid'] = $file_info->fid;
        }
    }*/

    $node = node_submit($node);
    node_save($node);

}