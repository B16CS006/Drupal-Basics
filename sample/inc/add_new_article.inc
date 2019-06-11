<?php

function sample_ajax_get_sample_callHandler(){
    global $user;
    if(empty($_GET['token'])/*||!drupal_valid_token($_GET['token'], 'my sercret value'.$user->uid)*/){
        echo 'asdf';
        return MENU_ACCESS_DENIED;
    }
    //to remove html tags from input use filter_xss() function
    $title = filter_xss($_GET['title']);
    $message = "Message through callback: ".$title;
    echo $message;
}

function sample_add_new_article(){
    $form = array();
    $form['title'] = array(
        '#type'=>'textfield',
        '#title'=> 'Title'
    );
    $form['body'] = array(
        '#type' => 'textarea',
        '#title' => 'Write Your Article Here'
    );
    $form['files']['image'] = array(
        '#type' => 'file',
        '#title' => t('Select an image'),
        '#description' => t('Upload an image allowed files png, jpeg, jpg'),
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Submit'
    );
    $form['#submit'][] = 'sample_add_new_article_submit';

    $form['#prefix'] = '<div id="prefix-preview">Prefix</div>';
    $form['#suffix'] = '<input type="button" id="edit-reset" value="Reset"><br>
                        <input type="button" id="submitAJAX" value="Submit AJAX"><br>
                        <div id="message-display-area"></div>';
    drupal_add_js(drupal_get_path('module', 'sample')."/js/sample.js");

    global $user;
    $newToken = drupal_get_token('my secret value'.$user->uid);
    drupal_add_js("var myToken='$newToken';", "inline");

    return $form;
}

function sample_add_new_article_submit($form, &$form_state){
    // dpm($form_state['storage']['file']);
    dpm($form_state);
    // dpm($form);
    // dpm($form_state);
    global $user;

    $node = (object)NULL;
    $node->type = 'article';
    node_object_prepare($node);
    
    $node->language = LANGUAGE_NONE;
    $node->title = $form_state['values']['title'];
    $node->uid = $user->uid; //user id
    $node->status = 1; //1: published, 0: unpublished
    $node->promote = 1; //1: promote to homepage while 0: not promote to home page
    $node->sticky = 1;

    $node->body[$node->language][]['value'] = $form_state['values']['body'];
    $node->field_tags[$node->language][]['tid'] = 10;


    $validators = array(
        'file_validate_size' => array('2097152'),
        'file_validate_extensions' => array('jpg png jpeg gif'),
    );
    $location = 'public://';
    $upload_check = file_save_upload('image', $validators, $location);
    // dpm($upload_check);

    $node->field_images[$node->language][0] = array(
        'fid' => $upload_check->fid,
        'filename' => $upload_check->filename,
        'filemime' => $upload_check->filemime,
        'uid' => $upload_check->uid,
        'uri' => $upload_check->uri,
        'status' => $upload_check->status,
    );


    $node = node_submit($node);
    node_save($node);

    // $node = node_load(4);
    // dpm($node);

    //for reference field
    // $node->field_customer_nid[$node->language][] = array(
    //     'target_id' => $form_state['valus']['entity id'],
    //     'target_type' => 'node', //user, taxonomy_term
    // );


}