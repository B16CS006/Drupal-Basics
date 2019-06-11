<?php

function add_new_term_form($form, &$form_state){
    $form['#tree'] = TRUE;

    if(empty($form_state['num_fields'])){
        $form_state['num_fields'] = 0;
    }

    $form['voc'] = array(
        '#type' => 'textfield',
        '#title' => 'Vocabulary Machine Name',
        '#description' => 'Use ~ to list all vocubalaries.',
        '#required' => TRUE,
        '#autocomplete_path' => 'samples/vocubalaryAutocomplete',
        '#ajax' => array(
            'callback' => 'change_name_title_ajax_callback',
            'wrapper' => 'change_name_title_wrapper',
        ),
    );
    $form['name'] = array(
        '#type' => 'textfield',
        '#title' => 'Add term for above Vocabulary:',
        '#required' => TRUE,
        '#prefix' => '<div id="change_name_title_wrapper">',
        '#suffix' => '</div>',
        '#ajax' => array(
            'callback' => 'change_description_title_ajax_callback',
            'wrapper' => 'change_description_title_wrapper',
        ),
    );
    $form['description'] = array(
        '#type' => 'textarea',
        '#title' => 'Description about above Term:',
        '#prefix' => '<div id="change_description_title_wrapper">',
        '#suffix' => '</div>',
    );

    $node = db_select('node_type', 'tr')
                 ->fields('tr',array('type'))
                 ->execute()
                 ->fetchCol();
    // dpm($node);
    $node_type = array();
    foreach($node as $n){
        $node_type[$n] = $n;
    }
    unset($node);

    // !empty($form_state['values'])?
    // !empty($form_state['values']['field'])?
    // !empty($form_state['values']['field'][1])?
    // !empty($form_state['values']['field'][1]['field_type'])?
    // $form_state['values']['field'][1]['field_type']:'':'':'':''

    
    $form['field'] = array(
        '#prefix' => '<div id="change_field_type_wrapper">',
        '#suffix' => '</div>',
    );

    for($i = 1; $i <= $form_state['num_fields']; $i++){
        $form['field'][$i] = array(
            '#type' => 'fieldset',
            '#title' => t('Field @num', array('@num' => $i)),
            '#collapsible' => TRUE,
            '#collapsed' => FALSE,
        );
        $form['field'][$i]['field_type'] = array(
            '#title' => t('Node Type'),
            '#type' => 'select',
            '#description' => t('Enter State Name.'),
            '#options'=> $node_type,
            '#required' => TRUE,
            '#ajax' => array(
                'callback' => 'change_field_type_ajax_callback',
                'wrapper' => 'change_field_type_wrapper',
            ),
        );
        
        if(!empty($form_state['values']['field'][$i]['field_type'])){
            $form['field'][$i]['field_name'] = array(
                '#title' => t('Node'),
                '#type' => 'textfield',
                '#description' => t('Use ~ to list all options'),
                '#autocomplete_path' => 'samples/nodeAutocomplete/'. $form_state['values']['field'][$i]['field_type'],
                '#required' => TRUE,
            );
        }
    }

    $form['add_new_field'] = array(
        '#type' => 'submit',
        '#value' => 'Add Field',
        '#submit' => array(
            'add_new_field_callback',
        ),
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Submit',
        '#submit' => array('add_new_term_form_submit'),
    );

    if(isset($form_state['values']['field'][1]['field_type'])){
        $form['name']['#title'] = t('Add new ');
    }

    if(isset($form_state['values']['field'][1]['field_type'])){
        $type = $form_state['values']['field'][1]['field_type'];
    }

    if(isset($form_state['values']['voc'])){
        if($form_state['values']['voc'] == '' || $form_state['values']['voc'] == '~'){
            $form['name']['#title'] = t('Add new term for above Vocabulary');
        }else{
            $form['name']['#title'] = t('Add new term for '. $form_state['values']['voc']. ':');
        }
    }

    if(isset($form_state['values']['name'])){
        if($form_state['values']['name'] == ''){
            $form['description']['#title'] = t('Description about above Term:');
        }else{
            $form['description']['#title'] = t('Description about '. $form_state['values']['name']. ':');
        }
    }

    return $form;
}

function add_new_term_form_submit($form, &$form_state){
    //to add new vacobalory use taxonomy_vacobalary_save($vac);
    //to add new term use       taxonomy_term_save($term);
    //to list all term for      dpm(entity_load('taxonomy', FALSE, array('vid' => $voc->vid)));    // to show all its terms
    //to load term              dpm(taxonomy_term_load(64));


    $voc = taxonomy_vocabulary_machine_name_load($form_state['values']['voc']);
    // dpm($voc);
    
    if(!$voc){
        drupal_set_message('Incorrect Vocabulary Machine Name');
        return;
    }
    
    $term = array();
    $term['name'] = $form_state['values']['name'];
    $term['description'] = $form_state['values']['description'];
    $term['vid'] = $voc->vid;
    $term['language'] = LANGUAGE_NONE;

    if(!empty($form_state['values']['field'])){
        foreach($form_state['values']['field'] as $field){
            $value = db_select('node ', 'tv')
                        ->fields('tv', array('nid'))
                        ->condition('type', $field['field_type'])
                        ->condition('title', $field['field_name'])
                        ->execute()
                        ->fetchCol();
            $term['field_'.$field['field_type']][$term['language']][]['target_id'] = current($value);
        }
    }
    $term = (object)$term;
    // dpm($term);
    // return;

    $result = taxonomy_term_save($term);
    if($result == 1){
        drupal_set_message($form_state['values']['name']. ' is added to the '. $form_state['values']['voc']);
    }else{
        drupal_set_message($result);
    }
}

function vocubalary_autocomplete($string = ''){
    $matches = array();
    $vocubalaries = db_select('taxonomy_vocabulary ', 'tv')
                        ->fields('tv', array('machine_name'))
                        ->execute()
                        ->fetchCol();
    foreach($vocubalaries as $vocubalary){
        if(stristr($vocubalary, $string)){
            $matches[$vocubalary] = $vocubalary;
        }
    }
    if($string == '~'){
        $matches = $vocubalaries;
    }
    drupal_json_output($matches);
}

function node_autocomplete($type, $string = ''){
    // dpm('type: '. $type);
    // dpm('string: '. $string);
    $matches = array();
    $nodes = db_select('node ', 'tv')
                        ->fields('tv', array('title'))
                        ->condition('type', $type)
                        ->execute()
                        ->fetchCol();
    foreach($nodes as $node){
        if(stristr($node, $string)){
            $matches[$node] = $node;
        }
    }
    if($string == '~'){
        $matches = $nodes;
    }
    drupal_json_output($matches);
}

function change_name_title_ajax_callback($form, &$form_state){
    return $form['name'];
}

function change_description_title_ajax_callback($form, &$form_state){
    return $form['description'];
}

function change_field_type_ajax_callback($form){
    // dpm('asdf');
    // drupal_set_message('asdf');
    return $form['field'];
}

function add_new_field_callback($form, &$form_state){
    $form_state['num_fields']++;
    drupal_set_message('num_field '. $form_state['num_fields']);
    $form_state['rebuild'] = TRUE;
}