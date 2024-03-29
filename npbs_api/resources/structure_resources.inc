<?php

/**
 * check whether the entity type is enabled or not
 */
function check_enabled($entity_type, $element = NULL){
    $is_element_enabled = variable_get('npbs_api_config_variables', array())[$entity_type];
    $result = '';
    if($element !== NULL){
        $is_element_enabled = $is_element_enabled[$element];
        $result = '->' . $element;
    }
    if(!$is_element_enabled) return services_error($entity_type . $result . ' is not enabled.');
    return TRUE;
}

/**
 * For creating new content type element
 */
function _npbs_api_node_create($data){
    if(isset($data) && is_array($data)) $data = (object)$data;

    global $user;
    if(!isset($user->uid)) return services_error('User is not logged in');
    if(empty($data->title)) return services_error('Missing required attribute title', 406);
    if(empty($data->type)) return services_error('Missing required attribute type', 406);
    else check_enabled('node', $data->type);
    $node = (object)NULL;
    $node->type = $data->type;
    node_object_prepare($node);
    $node->title = $data->title;
    $node->uid = $user->uid;
    $node->language = isset($data->language)? $data->language : LANGUAGE_NONE;
    $node->status = isset($data->status)? $data->status : 1;
    $node->promote = isset($data->promote)? $data->promote : 1;
    $node->sticky = isset($data->sticky)? $data->sticky : 1;

    module_load_include('inc', 'npbs_api', 'resources/node_wrapper_resources');
    module_load_include('inc', 'npbs_api', 'resources/fields_resources');
    $fields = _npbs_api_fields_for($node->type, 'node');
    foreach($fields as $field_name => $bundle){
        $temp = $bundle . '_wrapper';
        $value = isset($data->$field_name)? $data->$field_name : NULL;
        $temp('node', $node, $node->type, $field_name, $value);
    }

    // Todo find out why below is not working
    // Validate the node. If there is validation error Exception will be thrown so code below won't be executed.
    // _node_resource_validate_type($node);

    $node = node_submit($node);
    node_save($node);

    return $node;
}

/**
 * For retrieve a content type using nid
 */
function _npbs_api_node_retrieve($nid){
    $node = node_load($nid);
    check_enabled('node', $node->type);
    module_load_include('inc', 'npbs_api', 'resources/fields_resources');
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


/**
 * For Creating a taxonomy_term of some taxonomy_vocabulary
 */
function _npbs_api_taxonomy_term_create($data){
    if(isset($data) && is_array($data)) $data = (object)$data;
    if(empty($data->vocabulary_machine_name)) return services_error('Missing Required attribute vocabulary_machine_name', 406);
    if(!isset($data->name)) return services_error('Missing required attribute name',406);
    else check_enabled('taxonomy_term', $data->vocabulary_machine_name);
    
    $voc = taxonomy_vocabulary_machine_name_load($data->vocabulary_machine_name);
    if(!isset($voc->vid)) return services_error('Invalid Taxonomy Vocabulary machine name');
    
    $term = (object)NULL;
    $term->vid = $voc->vid;
    $term->name = $data->name;
    $term->language = !isset($data->language)? $data->language : LANGUAGE_NONE;
    $term->description = isset($data->description) ? $data->description : NULL;
    
    
    module_load_include('inc', 'npbs_api', 'resources/node_wrapper_resources');
    module_load_include('inc', 'npbs_api', 'resources/fields_resources');
    $fields = _npbs_api_fields_for($data->vocabulary_machine_name, 'taxonomy_term');

    foreach($fields as $field_name => $bundle){
        $temp = $bundle . '_wrapper';
        $value = isset($data->$field_name)? $data->$field_name : NULL;
        $temp('taxonomy_term', $term, $data->vocabulary_machine_name, $field_name, $value);
    }

    return $term;

    $result = taxonomy_term_save($term);
    return $result;
}

/**
 * For retrieving the taxonomy_term using tid
 */
function _npbs_api_taxonomy_term_retrieve($tid){
    $term = taxonomy_term_load($tid);
    check_enabled('taxonomy_term', $term->vocabulary_machine_name);
    module_load_include('inc', 'npbs_api', 'resources/fields_resources');
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


/**
 * For creating new taxonomy_vocabulary
 */
function _npbs_api_taxonomy_vocabulary_create($data){
    if(isset($data) && is_array($data)) $data = (object)$data;
    if(empty($data->name)) return services_error('Missing Required attribute name', 406);
    if(empty($data->machine_name)) return services_error('Missing Required attribute machine_name', 406);
    else check_enabled('taxonomy_vocabulary');

    $vocavulary = (object)NULL;
    $vocavulary->name = $data->name;
    $vocavulary->machine_name = $data->machine_name;
    $vocavulary->decription = isset($data->description) ? $data->description : NULL;
    $vocavulary->module = 'taxonomy';

    return $vocavulary;

    $result = taxonomy_vocabulary_save($vocavulary);
    return $result;
}

/**
 * For Retrieve a taxonomy_vocabulary using machine_name
 */
function _npbs_api_taxonomy_vocabulary_retrieve($vocabulary_machine_name){
    $voc = taxonomy_vocabulary_machine_name_load($vocabulary_machine_name);
    check_enabled('taxonomy_vocabulary');
    module_load_include('inc', 'npbs_api', 'resources/fields_resources');
    unset($voc->rdf_mapping);
    return $voc;
}


/**
 * For Creating a new field_collection_item element
 */
function _npbs_api_field_collection_item_create($data){
    if(isset($data) && is_array($data)) $data = (object)$data;
    if(empty($data->field_collection_item)) return services_error('Missing Required attribute field_collection_item', 406);
    else check_enabled('field_collection_item', $data->field_collection_item);
    
    $item = entity_create('field_collection_item', array('field_name' => $data->field_collection_item));
    // $item->setHostEntity('node', $node);
    
    module_load_include('inc', 'npbs_api', 'resources/node_wrapper_resources');
    module_load_include('inc', 'npbs_api', 'resources/fields_resources');
    $fields = _npbs_api_fields_for($data->field_collection_item, 'field_collection_item');

    foreach($fields as $field_name => $bundle){
        $temp = $bundle . '_wrapper';
        $value = isset($data->$field_name)? $data->$field_name : NULL;
        $temp('field_collection_item', $item, $data->field_collection_item, $field_name, $value);
    }
    
    // $item->save();
    return $item;
}

/**
 * For retrieving a field_collection_item using item_id
 */
function _npbs_api_field_collection_item_retrieve($item_id){
    $term = entity_load_single('field_collection_item', array($item_id));
    check_enabled('field_collection_item', $term->field_name);
    $result = array(
        'term_id' => $term->term_id,
        'revision_id' => $term->revision_id,
        'field_name' => $term->field_name,
        'default_revision' => $term->default_revision,
        'archived' => $term->archived,
    );

    module_load_include('inc', 'npbs_api', 'resources/fields_resources');
    $fields = _npbs_api_fields_for($term->field_name, 'field_collection_item');
    foreach($fields as $field_name => $bundle){
        $result[$field_name] = $term->{$field_name}[LANGUAGE_NONE]; 
    }
    return $result;
}