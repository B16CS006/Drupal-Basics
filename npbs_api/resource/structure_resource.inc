<?php

///////////////////////////////////////////////////// Content Type ////////////////////////////////////////////////////
function _npbs_api_node_create($data){
    if(isset($data) && is_array($data)) $data = (object)$data;
    // $node_type = end(explode('/', $_GET['q']));  // to get the url

    global $user;
    if(!isset($user->uid)) return services_error('User is not logged in');
    if(empty($data->title)) return services_error('Missing required attribute title', 406);
    if(empty($data->type)) return services_error('Missing required attribute type', 406);
    else if(!in_array($data->type, array_keys(field_info_bundles()['node']))) return services_error('Such content type not found');

    $node = (object)NULL;
    $node->type = $data->type;
    node_object_prepare($node);
    $node->title = $data->title;
    $node->uid = $user->uid;
    $node->language = isset($data->language)? $data->language : LANGUAGE_NONE;
    $node->status = isset($data->status)? $data->status : 1;
    $node->promote = isset($data->promote)? $data->promote : 1;
    $node->sticky = isset($data->sticky)? $data->sticky : 1;

    module_load_include('inc', 'npbs_api', 'resource/node_wrapper_resource');
    module_load_include('inc', 'npbs_api', 'resource/fields_resource');
    $fields = _npbs_api_fields_for($node->type, 'node');
    foreach($fields as $field_name => $bundle){
        $temp = $bundle . '_wrapper';
        $value = isset($data->$field_name)? $data->$field_name : NULL;
        $temp('node', $node, $node->type, $field_name, $value);
    }

    return $node;

    // Validate the node. If there is validation error Exception will be thrown
    // so code below won't be executed.
    _node_resource_validate_type($node);
    $node = node_submit($node);
    return node_save($node);

    return $node;
}

function _npbs_api_node_retrieve($nid){
    $node = node_load($nid);
    module_load_include('inc', 'npbs_api', 'resource/fields_resource');
    $fields = _npbs_api_fields_for($node->type, 'node');

    $result = array(
        'vid' => $node->vid,
        'nid' => $node->nid,
        'title' => $node->title,
        'status' => $node->status,
        'language' => $node->language,
        'created' => $node->created,
        'changed' => $node->changed,
        'comment' => $node->comment,
        'cid' => $node->cid,
        'comment_count' => $node->comment_count,
        'uid' => $node->uid,
        'name' => $node->name,
        'picture' => $node->picture,
    );
    foreach($fields as $field_name => $bundle){
        $result[$field_name] = $node->{$field_name}[$node->language]; 
    }
    return $result;
}

///////////////////////////////////////////////////// Taxonomy Term ////////////////////////////////////////////////////
function _npbs_api_taxonomy_term_create($data){
    if(isset($data) && is_array($data)) $data = (object)$data;
    if(empty($data->vocabulary)) return services_error('Missing Required attribute vocabulary', 406);
    if(!isset($data->name)) return services_error('Missing required attribute name',406);
    
    $voc = taxonomy_vocabulary_machine_name_load($data->vocabulary);
    if(!isset($voc->vid)) return services_error('Invalid Taxonomy Vocabulary machine name');
    
    $term = (object)NULL;
    $term->vid = $voc->vid;
    $term->name = $data->name;
    $term->language = !isset($data->language)? $data->language : LANGUAGE_NONE;
    $term->description = isset($data->description) ? $data->description : NULL;
    
    
    module_load_include('inc', 'npbs_api', 'resource/node_wrapper_resource');
    module_load_include('inc', 'npbs_api', 'resource/fields_resource');
    $fields = _npbs_api_fields_for($data->vocabulary, 'taxonomy_term');

    foreach($fields as $field_name => $bundle){
        $temp = $bundle . '_wrapper';
        $value = isset($data->$field_name)? $data->$field_name : NULL;
        $temp('taxonomy_term', $term, $data->vocabulary, $field_name, $value);
    }

    return $term;

    $result = taxonomy_term_save($term);
    return $result;
}

function _npbs_api_taxonomy_term_retrieve($tid){
    $term = taxonomy_term_load($tid);
    module_load_include('inc', 'npbs_api', 'resource/fields_resource');
    $fields = _npbs_api_fields_for($term->vocabulary_machine_name, 'taxonomy_term');
    $result = array(
        'tid' => $term->tid,
        'vid' => $term->vid,
        'name' => $term->name,
        'description' => $term->description,
        'weight' => $term->weight,
        'vocabulary_machine_name' => $term->vocabulary_machine_name,
    );
    foreach($fields as $field_name => $bundle){
        $result[$field_name] = $term->{$field_name}[LANGUAGE_NONE]; 
    }
    return $result;
}

///////////////////////////////////////////////////// Taxonomy Vocabulary ////////////////////////////////////////////////////
function _npbs_api_taxonomy_vocabulary_create($data){
    if(isset($data) && is_array($data)) $data = (object)$data;
    if(empty($data->name)) return services_error('Missing Required attribute name', 406);
    if(empty($data->machine_name)) return services_error('Missing Required attribute machine_name', 406);

    $vocavulary = (object)NULL;
    $vocavulary->name = $data->name;
    $vocavulary->machine_name = $data->machine_name;
    $vocavulary->decription = isset($data->description) ? $data->description : NULL;
    $vocavulary->module = 'taxonomy';

    return $vocavulary;

    $result = taxonomy_vocabulary_save($vocavulary);
    return $result;
}

function _npbs_api_taxonomy_vocabulary_retrieve($vocabulary_machine_name){
    // return $_GET['q'];
    $voc = taxonomy_vocabulary_machine_name_load($vocabulary_machine_name);
    module_load_include('inc', 'npbs_api', 'resource/fields_resource');
    unset($voc->rdf_mapping);
    return $voc;
}

///////////////////////////////////////////////////// Field Collection Item ////////////////////////////////////////////////////
function _npbs_api_field_collection_create($data){
    if(isset($data) && is_array($data)) $data = (object)$data;
    if(empty($data->field_collection)) return services_error('Missing Required attribute field_collection', 406);
    
    $item = entity_create('field_collection_item', array('field_name' => $data->field_collection));
    // $item->setHostEntity('node', $node);
    
    module_load_include('inc', 'npbs_api', 'resource/node_wrapper_resource');
    module_load_include('inc', 'npbs_api', 'resource/fields_resource');
    $fields = _npbs_api_fields_for($data->field_collection, 'field_collection_item');

    foreach($fields as $field_name => $bundle){
        $temp = $bundle . '_wrapper';
        $value = isset($data->$field_name)? $data->$field_name : NULL;
        $temp('field_collection_item', $item, $data->field_collection, $field_name, $value);
    }

    // try{
    //     field_attached_validate('field_collection_item', $item);
    // }catch(Exception $e){
    //     print($e->getMessage);
    //     return NULL;
    // }
    
    // $item->save();
    return $item;
}

function _npbs_api_field_collection_retrieve($item_id){
    $term = entity_load_single('field_collection_item', array($item_id));
    $result = array(
        'term_id' => $term->term_id,
        'revision_id' => $term->revision_id,
        'field_name' => $term->field_name,
        'default_revision' => $term->default_revision,
        'archived' => $term->archived,
    );

    module_load_include('inc', 'npbs_api', 'resource/fields_resource');
    $fields = _npbs_api_fields_for($term->field_name, 'field_collection_item');
    foreach($fields as $field_name => $bundle){
        $result[$field_name] = $term->{$field_name}[LANGUAGE_NONE]; 
    }
    return $result;
}