<?php

function _ngos_city_retrieve($id){
    if(!isset($id)){
        return services_error('Missing City attribute ID', 406);
    }

    $voc = taxonomy_vocabulary_machine_name_load('city');
    $_city = entity_load('taxonomy_term', FALSE, array('vid' => $voc->vid));
    unset($voc);

    return array(
        'tid' => $_city[$id]->tid,
        'vid' => $_city[$id]->vid,
        'name' => $_city[$id]->name,
        'vocabulary_machine_name' => $_city[$id]->vocabulary_machine_name,
    );
}

function _ngos_city_create($data){
    global $user;
    if(isset($data) && is_array($data)){
        $data = (object)$data;
    }

    unset($data->id);
    $data->uid = $user->uid;
    $data->created = time();
    if(!isset($data->name)){
        return services_error('Missing City attribute name', 406);
    }

    return (object)array(
        'name' => $data->name,
        'uri' => services_resource_uri(array('city', $data->name)),
    );
}

function _ngos_city_access($op, $args){
    global $user;
    $access = FALSE;

    // switch($op){
    //     case 'view': {
    //         $city = 
    //     }
    // }

    return TRUE;
}