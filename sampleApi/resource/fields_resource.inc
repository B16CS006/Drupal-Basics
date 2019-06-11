<?php

function sampleApi_main_form($form, $form_state){
    
    // dpm(field_info_field_types());
    dpm(field_info_bundles());

    // dpm(_sampleApi_all_fields());
    // $node = node_load(12);
    // dpm($node);
    // $types = array();
    // foreach(node_type_get_types() as $type){
    //     $types[] = $type->type;
    // }
    // dpm($types);
    // // $node = _node_resource_validate_type($node);
    // dpm($types);
    // $allowed_node_types = variable_get('services_allowed_create_content_types', $types);
    // dpm($allowed_node_types);
    // dpm(_sampleApi_fields_for_node('skills'));

    // dpm(field_read_field('field_designation'));
    // dpm(field_info_instance('node', 'field_designation', 'hero'));



    // $instance = field_info_instance('node', $field_name, $node_type);
    //   $field = field_read_field('field_designation');


    // $fields = _sampleApi_fields_for_node('skills');
    // dpm($fields);
    // $required_fields = _sampleApi_required_fields_for_type('skills');
    // dpm($required_fields);

    // dpm(explode('_','field_designation_value',-2));
    // dpm(strpos('asdf','a') === 0);

    // dpm(field_info_instance('node', 'field_nature','skills'));
    // dpm(field_read_field('body'));

    // $data


    // $node = (object)NULL;
    // $node->type = 'hero';

    // $data = array(
    //     'body' => 'asdf',
    //     'title' => 'title',
    //     'field_technique' => array(1,2,3),
    // );

    // dpm(tempss($data));

    dpm(_sampleApi_fields_for('favourite_hero', 'taxonomy_term'));

    return $form;
}

function _sampleApi_all_fields(){
    return field_info_fields();
}

function _sampleApi_fields_for_node($type){
    $fields = field_info_fields();
    $required_fields = array();
    foreach($fields as $field){
        if(isset($field['bundles']['node']) && in_array($type, $field['bundles']['node'])){
            $required_fields[$field['field_name']] = $field['type'];
        }
    }
    return $required_fields;
}

function _sampleApi_fields_for($bundle, $entity_type){
    $fields = field_info_fields();
    // return $fields;
    $required_fields = array();
    foreach($fields as $field){
        if(isset($field['bundles'][$entity_type]) && in_array($bundle, $field['bundles'][$entity_type])){
            $required_fields[$field['field_name']] = $field['type'];
        }
    }
    return $required_fields;
}

function _sampleApi_required_fields_for_type($type){
    $fields = _sampleApi_fields_for_node($type);
    foreach($fields as $field => $required){
        $temp = field_info_instance('node', $field, $type);
        if($temp['required'] == 1 || $temp['required'] == TRUE){
            $fields[$field] = 1;
        }
    }
    return $fields;
}


/*function field_designation_wrapper($node, $value){
    $field_info = field_info_instance('node', 'field_designation', $node->type);
    if(empty($value)){
        if($field_info['required']){
            return drupal_set_message('Missing field_designation attribute', 406);
        }else{
            //set default value to it
            return TRUE;
        }
    }
    $temp = array();
    $temp['value'] = $value;
    $temp['target_type'] = 'node';
    if(!isset($node->language)) $node->language = LANGUAGE_NONE;
    $node->field_designation[$node->language][] = $temp;
    return TRUE;
}

function field_skill_wrapper($node, $value){
    $field_info = field_info_instance('node', 'field_skill', $node->type);
    if(empty($value)){
        if($field_info['required']){
            return drupal_set_message('Missing field_skill attribute', 406);
        }else{
            //set default value to it
            return TRUE;
        }
    }
    $temp = array();
    if(!is_numeric($value)) $value = convert_name_to_nid($value, 'skills');
    $temp['target_id'] = $value;
    $temp['target_type'] = 'node';
    $node->field_skill[$node->language][] = $temp;
    return TRUE;
}

function field_nature_wrapper($node, $value, $field = NULL){
    $field_info = field_info_instance('node', 'field_nature', $node->type);
    if(empty($value)){
        if($field_info['required']){
            return drupal_set_message('Missing field_nature attribute', 406);
        }else{
            //set default value to it
            return TRUE;
        }
    }
    if(!is_numeric($value)) $value = convert_name_to_tid($value);
    if(!isset($node->language)) $node->language = LANGUAGE_NONE;
    $node->field_nature[$node->language][]['tid'] = $value;
    return TRUE;
}

function field_technique_wrapper($node, $value, $field = NULL){
    $field_info = field_info_instance('node', 'field_technique', $node->type);
    if(empty($value)){
        if($field_info['required']){
            return drupal_set_message('Missing field_technique attribute',406);
        }else{
            //set default value to it
            return TRUE;
        }
    }
    if(!is_array($value)){
        drupal_set_message('field_technique must be an array', 406);
        return;
    }
    if(!isset($node->language)) $node->language = LANGUAGE_NONE;
    foreach($value as $v){
        if(!is_numeric($v)) $v = convert_name_to_tid($v);
        $node->field_technique[$node->language][]['tid'] = $v;
    }
    return TRUE;
}

function body_wrapper($node, $value){
    $field_info = field_info_instance('node', 'body', $node->type);
    if(empty($value)){
        if($field_info['required']){
            return drupal_set_message('Missing body attribute', 406);
        }else{
            //set default value to it
            return TRUE;
        }
    }
    if(!isset($node->language)) $node->language = LANGUAGE_NONE;
    $node->body[$node->language][]['value'] = $value;
    return TRUE;
}

function field_tags_wrapper($node, $value){
    $field_info = field_info_instance('node', 'field_tags', $node->type);
    if(empty($value)){
        if($field_info['required']){
            return drupal_set_message('Missing field_tags attribute', 406);
        }else{
            //set default value to it
            return TRUE;
        }
    }
    if(!is_numeric($value)) $value = convert_name_to_tid($value);
    if(!isset($node->language)) $node->language = LANGUAGE_NONE;
    $node->field_tags[$node->language][]['tid'] = $value;
    return TRUE;
}*/

function convert_name_to_nid($title, $type){
    $result = db_select('node')
        ->fields('node', array('nid'))
        ->condition('type', $type)
        ->condition('title',$title)
        ->execute()
        ->fetchCol();

    return $result[0];
}

function convert_name_to_tid($name){
    $result = db_select('taxonomy_term_data')
    ->fields('taxonomy_term_data', array('tid'))
    ->condition('name',$name)
    ->execute()
    ->fetchCol();

    return $result[0];
}