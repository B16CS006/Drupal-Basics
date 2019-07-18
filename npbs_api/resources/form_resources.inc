<?php

// This Whole file is for testing purpose only

/**
 * hook_form
 */
function npbs_api_main_form($form, $form_state){
    watchdog(field_info_instance('node', 'field_image', 'chat_album'));

    // return $form;
    $data = [
        "title"=> "title",
        "type"=> "chat_album",
        "field_image"=>[
            "asdf"
        ],
    ];
    __npbs_api_node_create($data);
    // watchdog(field_info_bundles());
    // watchdog(field_info_fields());
    // watchdog(field_info_instance('node', 'field_link', 'email'));   
    return $form;
}

/**
 * Just for testing purpose
 */
function __npbs_api_node_create($data){
    if(isset($data) && is_array($data)) $data = (object)$data;

    global $user;
    if(!isset($user->uid)) return drupal_set_message('User is not logged in');
    if(empty($data->title)) return drupal_set_message('Missing required attribute title', 406);
    if(empty($data->type)) return drupal_set_message('Missing required attribute type', 406);
    // else check_enabled('node', $data->type);
    $node = (object)NULL;
    $node->type = $data->type;
    node_object_prepare($node);
    $node->title = $data->title;
    $node->uid = $user->uid;
    $node->language = isset($data->language)? $data->language : LANGUAGE_NONE;
    $node->status = isset($data->status)? $data->status : 1;
    $node->promote = isset($data->promote)? $data->promote : 1;
    $node->sticky = isset($data->sticky)? $data->sticky : 1;

    module_load_include('inc', 'npbs_api', 'resources/fields_resources');
    $fields = _npbs_api_fields_for($node->type, 'node');
    foreach($fields as $field_name => $bundle){
        watchdog($bundle);
        if($bundle != 'image')
            continue;
        $temp = $bundle . '_wrapper';
        $value = isset($data->$field_name)? $data->$field_name : NULL;
        $temp('node', $node, $node->type, $field_name, $value);
    }

    watchdog($node);
    return $node;
}



/**
 * Just for testing pupose
 */
function image_wrapper($entity_type, $entity, $bundle, $field_name, $data){
    if(!isset($entity->language)) $entity->language = LANGUAGE_NONE;
    $field_info = field_info_instance($entity_type, $field_name, $bundle);
    $field_read = field_read_field($field_name);

    if(empty($data)){
        if($field_info['required']) return drupal_set_message('Missing ' . $field_name . ' attribute');
        else return;
    }

    if($field_read['cardinality'] == 0) return;
    else if($field_read['cardinality'] == 1){
        $temp = array();
        if(is_array($data)){
            if(is_array(current($data))){
                $temp['fid'] = isset(current($data)['fid']) ? current($data)['fid'] : $field_info['default_value'];
                $temp['alt'] = isset(current($data)['alt']) ? current($data)['alt'] : NULL;
                $temp['title'] = isset(current($data)['title']) ? current($data['title']) : NULL;
                $temp['width'] = isset(current($data)['width']) ? current($data['width']) : NULL;
                $temp['height'] = isset(current($data)['height']) ? current($data['height']) : NULL;
            }else{
                $temp['fid'] = isset($data['fid']) ? $data['fid'] : $field_info['default_value'];
                $temp['alt'] = isset($data['alt']) ? $data['alt'] : NULL;
                $temp['title'] = isset($data['title']) ? $data['title'] : NULL;
                $temp['width'] = isset($data['width']) ? $data['width'] : NULL;
                $temp['height'] = isset($data['height']) ? $data['height'] : NULL;
            }
        }else{
            $temp['fid'] = isset($data) ? $data : NULL;
            if($field_info['required'] && empty($temp['fid'])) return drupal_set_message('Missing ' . $field_name . ' attribute');
        }
        if($field_info['required'] && empty($temp['fid'])){
            return drupal_set_message('Missing '. $field_name . '->fid attributes');
        }
        $entity->{$field_name}[$entity->language][0] = $temp;
    }else{
        $count = 0;
        if(!is_array($data)){
            return drupal_set_message($field_name . ' should be array');
        }
        foreach($data as $element){
            if($field_read['cardinality'] >1 && $count >=  $field_read['cardinality']){
                // return drupal_set_message($field_name . ' had cardinality: ' . $field_read['cardinality']);
                break;
            }
            $count++;
            if(is_array($element)){
                $temp = array();
                $temp['fid'] = isset($element['fid']) ? $element['fid'] : $field_info['default_value'];
                $temp['alt'] = isset($element['alt'])? $element['alt'] : NULL;
                $temp['title'] = isset($element['title'])? $element['title'] : NULL;
                $temp['width'] = isset($data['width']) ? $data['width'] : NULL;
                $temp['height'] = isset($data['height']) ? $data['height'] : NULL;
                if($field_info['required'] && empty($temp['fid'])){
                    return drupal_set_message('Missing '. $field_name . '->fid attributes');
                }
                $entity->{$field_name}[$entity->language][] = $temp;
            }else{
                if($field_info['required'] && empty($element)) return drupal_set_message('Missing ' . $field_name . ' attribute');
                $entity->{$field_name}[$entity->language][]['fid'] = $element;
            }
        }
    }
}