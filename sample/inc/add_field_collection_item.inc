<?php

function add_field_collection_item_form($form, &$form_state){
    $voc = taxonomy_vocabulary_machine_name_load('city');
    $_city = entity_load('taxonomy_term', FALSE, array('vid' => $voc->vid));
    unset($voc);
    $city = array();
    foreach($_city as $x){
        $city[$x->tid] = $x->name;
    }

    // $field_info = field_info_field('field_salary');
    // $designation = list_allowed_values($field_info);     //
    // unset($field_info);
    // dpm($designation);

    $form['#tree'] = TRUE;

    $form['title'] = array(
        '#title' => t('Title'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#size' => 30,
        '#maxlength' => 30,
    );

    $form['details'] = array(
        '#title' => t("Employee's Details"),
        '#type' => 'fieldset',
    );

    $form['details']['username'] = array(
        '#title' => t('Username'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#size' => 30,
        '#maxlength' => 30,
    );
    $form['details']['first_name'] = array(
        '#title' => t('First Name'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#size' => 30,
        '#maxlength' => 30,
    );
    $form['details']['middle_name'] = array(
        '#title' => t('Middle Name'),
        '#type' => 'textfield',
        '#size' => 30,
        '#maxlength' => 30,
    );
    $form['details']['last_name'] = array(
        '#title' => t('Last Name'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#size' => 30,
        '#maxlength' => 30,
    );
    $form['details']['email'] = array(
        '#title' => t('Email'),
        '#type' => 'textfield',
        '#required' => TRUE,
        // '#description' => "Please enter your email.",
        '#size' => 30,
        '#maxlength' => 30,
        '#element_validate' => array('sample_email_element_validate'),
    );

    $form['details']['country_code'] = array(
        '#title' => t('Country Code'),
        '#type' => 'textfield',
        '#default_value' => '+91',
        '#required' => TRUE,
        '#size' => 4,
        '#maxlength' => 4,
    );
    $form['details']['mobile_number'] = array(
        '#title' => t('Mobile Number'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#size' => 30,
        '#maxlength' => 30,
    );
    $form['details']['age'] = array(
        '#title' => t('Age'),
        '#type' => 'select',
        '#options' => array('1' => '1'),
        '#required' => TRUE,
    );
    $form['details']['city'] = array(
        '#title' => t('City'),
        '#type' => 'select',
        '#options' => $city,
        '#required' => TRUE,
    );
    $form['details']['salary'] = array(
        '#title' => t('Salary'),
        '#type' => 'select',
        '#options' => array('1' => '1'),
        '#required' => TRUE,
    );

    $form['submit'] = array(
        '#value' => t('Submit'),
        '#type' => 'submit',
    );

    $form['#submit'][] = 'add_field_collection_item_form_submit';
    return $form;
}

function add_field_collection_item_form_submit($form, $form_state){
    $fields = (object)NULL;
    $fields->username = $form_state['values']['details']['username'];
    $fields->first_name = $form_state['values']['details']['first_name'];
    $fields->middle_name = $form_state['values']['details']['middle_name'];
    $fields->last_name = $form_state['values']['details']['last_name'];
    $fields->age = $form_state['values']['details']['age'];
    $fields->salary = $form_state['values']['details']['salary'];
    
    $fields->city = array(
        'tid' => $form_state['values']['details']['city'],
    );
    $fields->email = array(
        'email' => $form_state['values']['details']['email'],
    );
    $fields->mobile_number = array(
        'country' => $form_state['values']['details']['country_code'],
        'local_number' => $form_state['values']['details']['mobile_number'],
        'value' => $form_state['values']['details']['country_code'] . $form_state['values']['details']['mobile_number'],
        'verified' => 0,
    );
    
    $node = create_employee_node($form_state['values']['title'], $fields);
}

function sample_email_element_validate($element, &$form_state, $form) {
   if (!valid_email_address($element['#value'])) {
     form_error($element, t('Please enter a valid email address.'));
   }
}


/////////////////////////////////////////////////////// Custom Function///////////////////////////////////

function create_employee_node($title, $fields){
    global $user;

    $node = (object)NULL;
    $node->type = 'employee';
    node_object_prepare($node);
    
    $node->language = LANGUAGE_NONE;
    $node->title = $title;
    $node->uid = $user->uid;
    $node->status = 1;
    $node->promote = 1;
    $node->sticky = 1;
    // $node->field_employee_details[$node->language][]['value'] = create_employee_details_field_collection($node, $fields);

    $term = create_employee_details_field_collection($node, $fields);
    if($term->item_id){
        $node = node_submit($node);
        node_save($node);
        drupal_set_message('Node Save');
        return $node;
    }else{
        dpm($term);
    }

    drupal_set_message('Node save failed');
}

function create_employee_details_field_collection($node, $fields){
    $item = entity_create('field_collection_item', array('field_name' => 'field_employee_details'));
    $item->setHostEntity('node', $node);

    $item->field_first_name[$node->language][]['value'] = $fields->first_name;
    $item->field_middle_name[$node->language][]['value'] = $fields->middle_name;
    $item->field_last_name[$node->language][]['value'] = $fields->last_name;
    $item->field_age[$node->language][]['value'] = $fields->age;
    $item->field_salary[$node->language][]['value'] = $fields->salary;
    $item->field_username[$node->language][]['value'] = $fields->username;

    $item->field_city[$node->language][] = $fields->city;
    $item->field_email[$node->language][] = $fields->email;
    $item->field_mobile_number[$node->language][] = $fields->mobile_number;

    // try{
    //     field_attached_validate('field_collection_item', $item);
    // }catch(Exception $e){
    //     print($e->getMessage);
    //     return NULL;
    // }
    
    $item->save();
    return $item;
}