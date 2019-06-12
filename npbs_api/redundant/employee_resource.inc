<?php

function _npbs_api_employee_retrieve($nid){
    // return $nid;
    $node = node_load($nid);
    // echo $node;
    return $node;
}

function _npbs_api_employee_create($data){
    module_load_include('inc', 'npbs_api', 'resources/node_wrapper_resources');
    module_load_include('inc', 'npbs_api', 'resources/fields_resources');
    $fields = _npbs_api_fields_for_node('employee');
    if(isset($data) && is_array($data)){
        $data = (object)$data;
    }
  
    global $user;
    $node = (object)NULL;
    $node->type = 'employee';
    node_object_prepare($node);
    $node->language = isset($data->language)? $data->language : LANGUAGE_NONE;
    $node->status = isset($data->status)? $data->status : 1;
    $node->promote = isset($data->promote)? $data->promote : 1;
    $node->sticky = isset($data->sticky)? $data->sticky : 1;

    if(!isset($user->uid)){
        return services_error('User is not logged in');
    }
    $node->uid = $user->uid;
  
    if(empty($data->title)){
        return services_error('Missing Title attribute', 406);
    }else{
        $node->title = $data->title;
    }
  
    // return $fields;
    foreach($fields as $field => $type){
        $temp = $type . '_wrapper';
        $value = isset($data->$field)? $data->$field : NULL;
        $temp($node, $field, $value);
    }

    return $node;


    // Validate the node. If there is validation error Exception will be thrown
    // so code below won't be executed.
    _node_resource_validate_type($node);
    // $node = node_submit($node);
    // return node_save($node);

    return $node;
}