<?php

function sampleApi_config_form($form, &$form_state){

    if ($form_state['rebuild']) {
        $form_state['input'] = array();
    }

    $node = array();
    $taxonomy_term = array();
    $field_collection_item = array();
    
    $bundles = field_info_bundles();
    foreach($bundles['node'] as $key => $value) $node[$key] = $value['label'];
    foreach($bundles['taxonomy_term'] as $key => $value) $taxonomy_term[$key] = $value['label'];
    foreach($bundles['field_collection_item'] as $key => $value) $field_collection_item[$key] = $value['label'];
    unset($bundles);

    $form['#tree'] = TRUE;
    $config_variables = variable_get('sampleapi_config_variables', array());

    if(!isset($config_variables['endpoint_prefix'])) $config_variables['endpoint_prefix'] = '';
    if(!isset($config_variables['taxonomy_vocabulary'])) $config_variables['taxonomy_vocabulary'] = FALSE;
    if(!isset($config_variables['node'])) $config_variables['node'] = array();
    if(!isset($config_variables['taxonomy_term'])) $config_variables['taxonomy_term'] = array();
    if(!isset($config_variables['field_collection_item'])) $config_variables['field_collection_item'] = array();

    foreach($node as $key => $value) if(!isset($config_variables['node'][$key])) $config_variables['node'][$key] = 0;
    foreach($taxonomy_term as $key => $value) if(!isset($config_variables['taxonomy_term'][$key])) $config_variables['taxonomy_term'][$key] = 0;
    foreach($field_collection_item as $key => $value) if(!isset($config_variables['field_collection_item'][$key])) $config_variables['field_collection_item'][$key] = 0;

    $form['endpoint_prefix'] = array(
        '#title' => t('Endpoint Prefix'),
        '#type' => 'textfield',
        // '#description' => 'Used between Endpoint and drupal similar url to add new entity',
        '#default_value' => t($config_variables['endpoint_prefix']),
        '#required' => TRUE,
    );
    
    $form['node'] = array(
        '#title' => t('Content Type'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
    );
    $form['taxonomy_term'] = array(
        '#title' => t('Taxonomy Term'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
    );
    $form['field_collection_item'] = array(
        '#title' => t('Field Collection Item'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
    );
    {
        foreach($node as $key => $value){
            $form['node'][$key] = array(
                '#title' => t($value),
                '#type' => 'checkbox',
                '#description' => 'Machine Name: ' . $key,
                '#default_value' => $config_variables['node'][$key],
            );    
        }

        foreach($taxonomy_term as $key => $value){
            $form['taxonomy_term'][$key] = array(
                '#title' => t($value),
                '#type' => 'checkbox',
                '#description' => 'Machine Name: ' . $key,
                '#default_value' => $config_variables['taxonomy_term'][$key],
            );    
        }

        foreach($field_collection_item as $key => $value){
            $form['field_collection_item'][$key] = array(
                '#title' => t($value),
                '#type' => 'checkbox',
                '#description' => 'Machine Name: ' . $key,
                '#default_value' => $config_variables['field_collection_item'][$key],
            );    
        }
        
        // $form['node'] = array(
        //     '#tree' => TRUE,
        //     '#title' => t('Content Types'),
        //     '#type' => 'checkboxes',
        //     // '#description' => 'Enable services for checked Content Types',
        //     '#options' => $node,
        //     '#default_value' => $config_variables['node'],
        // );
    
        // $form['taxonomy_term'] = array(
        //     '#title' => t('Taxonomy Terms'),
        //     '#type' => 'checkboxes',
        //     // '#description' => 'Enable services for checked Taxonomy Terms',
        //     '#options' => $taxonomy_term,
        //     '#default_value' => $config_variables['taxonomy_term'],
        // );
    
        // $form['field_collection_item'] = array(
        //     '#title' => t('Field Collections'),
        //     '#type' => 'checkboxes',
        //     // '#description' => 'Enable services for checked Field Collections',
        //     '#options' => $field_collection_item,
        //     '#default_value' => $config_variables['field_collection_item'],
        // );
    }

    $form['taxonomy_vocabulary'] = array(
        '#title' => t('Taxonomy Vocabulary'),
        '#type' => 'checkbox',
        '#default_value' => $config_variables['taxonomy_vocabulary'],
    );


    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Submit',
    );
    
    return $form;
}

function sampleApi_config_form_submit($form, $form_state){
    $config_variables = array();
    $config_variables['endpoint_prefix'] = $form_state['values']['endpoint_prefix'];
    $config_variables['taxonomy_vocabulary'] = $form_state['values']['taxonomy_vocabulary'];
    $config_variables['node'] = $form_state['values']['node'];
    $config_variables['taxonomy_term'] = $form_state['values']['taxonomy_term'];
    $config_variables['field_collection_item'] = $form_state['values']['field_collection_item'];
    $result = variable_set('sampleapi_config_variables', $config_variables);
    drupal_set_message('Successfully Updated');

}