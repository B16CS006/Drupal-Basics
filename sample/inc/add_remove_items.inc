<?php

function add_remove_items_form($form, &$form_state){
    $form['#tree'] = TRUE;
    $form['description'] = array(
        '#type' => 'item',
        '#title' => t('A form with dynamically added a new state'),
    );
    
    if(empty($form_state['num_states'])){
        $form_state['num_states'] = 1;
    }

    for($i = 1; $i <= $form_state['num_states']; $i++){
        $form['states'][$i] = array(
            '#type' => 'fieldset',
            '#title' => t('State @num', array('@num' => $i)),
            '#collapsible' => TRUE,
            '#collapsed' => FALSE,
        );
        $form['states'][$i]['state'] = array(
            '#title' => t('State'),
            '#type' => 'textfield',
            '#description' => t('Enter State Name.'),
            '#size' => 20,
            '#maxlength' => 20,
            '#required' => TRUE,
        );
        $form['states'][$i]['capital'] = array(
            '#title' => t('Capital'),
            '#type' => 'textfield',
            '#description' => t('Enter Capital of above State.'),
            '#size' => 20,
            '#maxlength' => 20,
            '#required' => TRUE,
        );
    }

    $form['add_new_state'] = array(
        '#type' => 'submit',
        '#value' => 'Add',
        '#submit' => array(
            'add_new_state_callback',
        ),
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Submit',
        '#submit' => array('add_remove_items_form_submit'),
    );
    dpm($form_state);
    return $form;
}

function add_new_state_callback($form, &$form_state){
    $form_state['num_states']++;
    $form_state['rebuild'] = TRUE;
}

function add_remove_items_form_submit($form, &$form_state){
    $output = t("Form 9 has been submitted.");
    for($i = 1; $i <= $form_state['num_names']; $i++) {
        $output .= t("@num. @state -> @capital\n", array(
            '@num' => $i,
            '@state' => $form_state['values']['name'][$i]['state'],
            '@capital' => $form_state['values']['name'][$i]['capital'],
        )) . ' ';
    }
    drupal_set_message($output);
}