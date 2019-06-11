<?php

function file_upload_form($form, &$form_state){

    $form['vertical_tabs'] = array(
        '#title' => 'Vertical Tabs',
        '#type' => 'vertical_tabs',

    );
    $form['tab1'] = array(
        '#type' => 'fieldset',
        '#title' => t('Tab1'),
        '#collapsable' => TRUE,
        '#group' => 'vertical_tabs'
    );
    $form['tab2'] = array(
        '#type' => 'fieldset',
        '#title' => t('Tab2'),
        '#collapsable' => TRUE,
        '#group' => 'vertical_tabs'
    );
    $form['tab3'] = array(
        '#type' => 'fieldset',
        '#title' => t('Tab3'),
        '#collapsable' => TRUE,
        '#group' => 'vertical_tabs'
    );
    $form['tab4'] = array(
        '#type' => 'fieldset',
        '#title' => t('Tab4'),
        '#collapsable' => TRUE,
        '#group' => 'vertical_tabs'
    );
    $form['tab5'] = array(
        '#type' => 'fieldset',
        '#title' => t('Tab5'),
        '#collapsable' => TRUE,
        '#group' => 'vertical_tabs'
    );
    $form['tab6'] = array(
        '#type' => 'fieldset',
        '#title' => t('Tab6'),
        '#collapsable' => TRUE,
        '#group' => 'vertical_tabs'
    );
    
    $form['tab1']['firstName'] = array(
        '#type' => 'textfield',
        '#title' => t('First Name'),
    );
    $form['tab1']['middleName'] = array(
        '#type' => 'textfield',
        '#title' => t('Middle Name'),
    );
    $form['tab1']['lastName'] = array(
        '#type' => 'textfield',
        '#title' => t('Last Name'),
    );
    $form['tab1']['upload'] = array(
        '#title' => 'File Upload',
        '#type' => 'file',
    );
    $form['tab1']['token'] = array(
        '#title' => 'Token', 
        '#type' => 'token',
        '#default_value' => 'asdf',
    );
    
    $form['tab2']['weight'] = array(
        '#title' => 'weight',
        '#type' => 'weight',
        '#default_value' => 9,
        '#delta' => 11,
    );
    $form['tab2']['date'] = array(
        '#title' => 'Date',
        '#type' => 'date',
    );
    $form['tab2']['date_popup'] = array(
        '#title' => 'Date Popup',
        '#type' => 'date_popup',
        '#date_format' => 'd/m/Y H:i',
        '#date_timezone' => date_default_timezone(),
    );
    $form['tab2']['date_select'] = array(                   // Require Date API, need to download
        '#title' => 'Date Select',
        '#type' => 'date_select',
        '#default_value' => '2018-11-19 00:00',
        '#date_year_range' => '-3:+3',
    );
    $form['tab2']['date_text'] = array(                 // Require Date API, need to download
        '#title' => 'Date Text',
        '#type' => 'date_text',
        // '#default_value' => '2018-11-19 00:00',
    );
    $form['tab2']['date_timezone'] = array(                 // Require Date API, need to download
        '#title' => 'Date Timezone',
        '#type' => 'date_timezone',
        '#date_label_position' => 'within',
        '#default_value' => 'Asia/Kolkata',
        // '#default_value' => '2018-11-19 00:00',
    );
    $form['tab2']['password_confirm'] = array(
        '#title' => 'password_confirm',
        '#type' => 'password_confirm',
    );
    $form['tab2']['password'] = array(
        '#title' => 'password',
        '#type' => 'password',
    );

    $form['tab3']['textarea'] = array(
        '#title' => 'textarea',
        '#type' => 'textarea',
    );
    $form['tab3']['text_format'] = array(
        '#title' => 'text_format',
        '#type' => 'text_format',
    );
    
    // $form['value'] = array(      // don't know how to use
    //     '#title' => 'Value',
    //     '#type' => 'value',
    // );
    
    $header = array(
        'title' => array('data' => t('title'), 'field' => 'n.title'), 
        'type' => array('data' => t('type'), 'field' => 'n.type'), 
        'author' => t('author'), 
        'status' => array('data' => t('status'), 'field' => 'n.status'), 
        'changed' => array('data' => t('changed'), 'field' => 'n.changed', 'sort' => 'desc'),
    );
    $nids = db_select('node', 'tr')
            ->fields('tr', array('nid'))
            ->execute()
            ->fetchCol();
    $nodes = node_load_multiple($nids);
    //Build the rows
    $options = array();
    $index = 0;
    foreach($nodes as $node){
        if($index >= 10){
            break;
        }
        $index += 1;
        $options[$node->nid] = array(
            'title' => array(
                'data' => array(
                    '#type' => 'link',
                    '#title' => $node->title,
                    '#href' => 'node/'. $node->nid,
                    // '#options' => $l_options,
                    '#suffix' => ''. theme('mark', array('type' => node_mark($node->nid, $node->changed))),
                ),
            ),
            // 'title' => $node->title,
            'type' => check_plain(node_type_get_name($node)),
            'author' => theme('username', array('account' => $node)),
            'status' => $node->status ? t('published') : t('not published'),
            'changed' => format_date($node->changed,'short'),
        );
    }
    $form['tab4']['tableselect'] = array(
        '#title' => 'tableselect',
        '#type' => 'tableselect',
        '#header' => $header,
        '#options' => $options,
        '#empty' => t('No content available'),
    );

    $form['tab5']['action'] = array(
        '#title' => 'Action',
        '#type' => 'action',
        '#value' => 'Action',
    );

    $form['tab6']['mobile'] = array(
        '#title' => 'Mobile Number',
        '#type' => 'mobile',
    );
    $form['tab6']['email'] = array(
        '#title' => 'Email',
        '#type' => 'email',
    );
    $form['tab6']['link'] = array(
        '#title' => 'Google',
        '#type' => 'link',
        '#href' => 'http://www.google.com',
    );
    
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Submit',
        '#submit' => array('submit_callback'),
    );

    return $form;
}


function submit_callback($form, &$form_state){
    // $validators = array(
        //     'file_validate_size' => array('2097152'),
        //     'file_validate_extensions' => array('jpg png jpeg gif'),
        // );
        // $location = 'public://';
        // $upload_check = file_save_upload('upload', $validators, $location);
    // $file_temp = $_FILES['files']['tmp_name']['upload'];
    // $file_temp = file_get_contents('./sites/default/files/1.jpg');
    // $upload_check_ = file_save_data();

    dpm($form_state['values']);
    dpm(strtotime(''.$form_state['values']['date']['day'].'-'
                    .$form_state['values']['date']['month'].'-'
                    .$form_state['values']['date']['year'].''
                ));//    dpm($form_state['values']['date']['month']);
    
}