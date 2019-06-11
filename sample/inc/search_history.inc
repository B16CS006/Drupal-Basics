<?php

function sample_search_history_form($form, &$form_state){
    $form['input'] = array(
        '#title' => t('Search'),
        '#type' => 'textfield',
        '#maxlength' => 25,
        '#size' => 15,
        '#autocomplete_path' => 'samples/searchHistoryAutocomplete',
    );
    $form['submit'] = array(
        '#type' => 'submit', 
        '#value' => t("Submit"),
    );
    $form['#submit'][] = 'sample_search_history_form_submit';
    return $form;
}

function sample_search_history_form_submit($form, &$form_state){
    $phrase = $form_state['values']['input'];
    // dpm($phrase);
    $search_history = variable_get('sample_search_history',array());    //if sample_search_history varialbe exist then return else create an new varialbe and return it with empty array
    $search_history[] = $phrase; // add phrase to the varaible
    variable_set('sample_search_history', $search_history);             //now update the variable in the main list
    drupal_set_message(t('New varaible is added to the search list: '. $phrase ));
}

function sample_search_history_autocomplete($string = ''){
    $matches = array();
    $search_history = variable_get('sample_search_history',array());
    dpm($search_history);
    foreach($search_history as $phrase){
        if(stristr($phrase, $string)){
            $matches[$phrase] = $phrase.'_demo';
        }
    }
    drupal_json_output($matches);
}
