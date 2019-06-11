<?php

function email_field_form($form, &$form_state){
    $form['details']['email'] = array(
        '#title' => t('Email'),
        '#type' => 'textfield',
        '#required' => TRUE,
        // '#description' => "Please enter your email.",
        '#size' => 30,
        '#maxlength' => 30,
        '#element_validate' => array('sample_email_element_validate'),
    );

    return $form;
}


function sample_email_element_validate($element, &$form_state, $form) {
    if (!valid_email_address($element['#value'])) {
      form_error($element, t('Please enter a valid email address.'));
    }
 }
 
