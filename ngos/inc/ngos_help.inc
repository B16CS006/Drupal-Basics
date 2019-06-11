<?php

function ngos_help_form(/*$form, &$form_state*/){
    // $info = field_info_instance('node', 'field_designation','hero');
    $info = field_info_fields();
    // $info = field_get_items('user', user_load($GLOBALS['user']->uid), 'field_designation');

    // $form['title'] = array(
    //     '#title' => 'Title',
    //     '#type' => 'textfield',
    // );
    dpm($info);

    // return $form;
}