<?php

function _npbs_api_fields_for($bundle, $entity_type){
    $fields = field_info_fields();
    $required_fields = array();
    foreach($fields as $field){
        if(isset($field['bundles'][$entity_type]) && in_array($bundle, $field['bundles'][$entity_type])){
            $required_fields[$field['field_name']] = $field['type'];
        }
    }
    return $required_fields;
}

function _convert_name_to_nid($title, $type){
    $result = db_select('node')
        ->fields('node', array('nid'))
        ->condition('type', $type)
        ->condition('title',$title)
        ->execute()
        ->fetchCol();

    return $result[0];
}

function _convert_name_to_tid($name){
    $result = db_select('taxonomy_term_data')
    ->fields('taxonomy_term_data', array('tid'))
    ->condition('name',$name)
    ->execute()
    ->fetchCol();

    return $result[0];
}