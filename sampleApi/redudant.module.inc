<?php

function sampleApi_services_resources(){

    $my_services = array();
    // return $my_services;

    $node_types = array();
    foreach(node_type_get_types() as $type){
        $node_types[] = $type->type;
    }

    foreach($node_types as $node_type){
        $my_services[$node_type] = array(
            'retrieve' => array(
                'help' => t($node_type . ' Retrieve'),
                'file' => array('type' => 'inc', 'module' => 'sampleApi', 'name' => 'resource/'. $node_type . '_resource'),
                'callback' => '_sampleApi_' . $node_type . '_retrieve',
                'access callback' => '_ngo_service_access',
                'args' => array(
                    array(
                        'name' => 'nid',
                        'type' => 'int',
                        'description' => 'Node nid',
                        'source' => array('path' => 0),
                        'optional' => FALSE,
                    ),
                ),
            ),
            'create' => array(
                'help' => t($node_type . ' Create'),
                'file' => array('type' => 'inc', 'module' => 'sampleApi', 'name' => 'resource/structure_resource'),
                'callback' => '_sampleApi_node_create',
                // 'access callback' => '_ngo_service_access',
                'access arguments' => array($node_type . ' resrource create'),
                'access arguments append' => FALSE,
                'args' => array(
                    array(
                        'name' => 'data',
                        'type' => 'struct',
                        'description' => 'The Node-' . $node_type . ' object',
                        'source' => 'data',
                        'optional' => FALSE,
                    ),
                ),
            ),
        );
    }

    $my_services['allfields'] = array(
        'index' => array(
            'help' => t('Fetch all fields'),
            'file' => array('type' => 'inc', 'module' => 'sampleApi', 'name' => 'resource/fields_resource'),
            'callback' => '_sampleApi_all_fields',
            'access callback' => '_ngo_service_access',
        ),
    );

    $my_services['term'] = array(
        'create' => array(
            'help' => t('Taxonomy Term Create'),
            'file' => array('type' => 'inc', 'module' => 'sampleApi', 'name' => 'resource/structure_resource'),
            'callback' => '_sampleApi_taxonomy_term_create',
            // 'access callback' => '_ngo_service_access',
            'access arguments' => array($node_type . ' resrource create'),
            'access arguments append' => FALSE,
            'args' => array(
                array(
                    'name' => 'data',
                    'type' => 'struct',
                    'description' => 'The object',
                    'source' => 'data',
                    'optional' => FALSE,
                ),
            ),
        ),
    );
    $my_services['vocabulary'] = array(
        'create' => array(
            'help' => t('Taxonomy Vocabulary Create'),
            'file' => array('type' => 'inc', 'module' => 'sampleApi', 'name' => 'resource/structure_resource'),
            'callback' => '_sampleApi_taxonomy_vocabulary_create',
            // 'access callback' => '_ngo_service_access',
            'access arguments' => array($node_type . ' resrource create'),
            'access arguments append' => FALSE,
            'args' => array(
                array(
                    'name' => 'data',
                    'type' => 'struct',
                    'description' => 'The object',
                    'source' => 'data',
                    'optional' => FALSE,
                ),
            ),
        ),
    );
    $my_services['field_collection'] = array(
        'create' => array(
            'help' => t('Field Collection Create'),
            'file' => array('type' => 'inc', 'module' => 'sampleApi', 'name' => 'resource/structure_resource'),
            'callback' => '_sampleApi_field_collection_create',
            // 'access callback' => '_ngo_service_access',
            'access arguments' => array($node_type . ' resrource create'),
            'access arguments append' => FALSE,
            'args' => array(
                array(
                    'name' => 'data',
                    'type' => 'struct',
                    'description' => 'The object',
                    'source' => 'data',
                    'optional' => FALSE,
                ),
            ),
        ),
    );
    // dpm($my_services);
    return $my_services;
}