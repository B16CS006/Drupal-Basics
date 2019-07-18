<?php

/**
 * wrapper for text_with_summary field_type
 */
function text_with_summary_wrapper($entity_type, $entity, $bundle, $field_name, $data){
    if(!isset($entity->language)) $entity->language = LANGUAGE_NONE;
    $field_info = field_info_instance($entity_type, $field_name, $bundle);
    $field_read = field_read_field($field_name);
    if(!isset($data)){
        if($field_info['required']) return services_error('Missing ' . $field_name . ' attribute');
        else return;
    }
    if($field_read['cardinality'] == 0) return;
    else if($field_read['cardinality'] == 1){
        $temp = array();
        if(is_array($data)){
            if(is_array(current($data))){
                $temp['value'] = isset(current($data)['value']) ? current($data)['value'] : $field_info['default_value'];
                $temp['summary'] = isset(current($data)['summary']) ? current($data)['summary'] : NULL;
                $temp['format'] = isset(current($data)['format']) ? current($data['format']) : NULL;
                if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
            }else{
                $temp['value'] = isset($data['value']) ? $data['value'] : $field_info['default_value'];
                $temp['summary'] = isset($data['summary']) ? $data['summary'] : NULL;
                $temp['format'] = isset($data['format']) ? $data['format'] : NULL;
                if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
            }
        }else{
            $temp['value'] = isset($data) ? $data : NULL;
            if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . ' attribute');
        }
        $entity->{$field_name}[$entity->language][0] = $temp;
    }else{
        $count = 0;
        if(!is_array($data)){
            return services_error($field_name . ' should be array');
        }
        foreach($data as $element){
            if($field_read['cardinality'] >1 && $count >=  $field_read['cardinality']){
                // return services_error($field_name . ' had cardinality: ' . $field_read['cardinality']);
                break;
            }
            $count++;
            if(is_array($element)){
                $temp = array();
                $temp['value'] = isset($element['value']) ? $element['value'] : $field_info['default_value'];
                $temp['summary'] = isset($element['summary'])? $element['summary'] : NULL;
                $temp['format'] = isset($element['format'])? $element['format'] : NULL;
                if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
                $entity->{$field_name}[$entity->language][] = $temp;
            }else{
                if($field_info['required'] && !isset($element)) return services_error('Missing ' . $field_name . ' attribute');
                $entity->{$field_name}[$entity->language][]['value'] = $element;
            }
        }
    }
}

/**
 * wrapper for taxonomy_term_reference field_type
 */
function taxonomy_term_reference_wrapper($entity_type, $entity, $bundle, $field_name, $data){
    if(!isset($entity->language)) $entity->language = LANGUAGE_NONE;
    $field_info = field_info_instance($entity_type, $field_name, $bundle);
    $field_read = field_read_field($field_name);

    if(!isset($data)){
        if($field_info['required']) return services_error('Missing ' . $field_name . ' attribute');
        else return;
    }

    if($field_read['cardinality'] == 0) return;
    else if($field_read['cardinality'] == 1){
        $temp = array();
        if(is_array($data)){
            if(is_array(current($data))){
                $temp['tid'] = isset(current($data)['tid']) ? current($data)['tid'] : $field_info['default_value'];
            }else{
                $temp['tid'] = isset($data['tid']) ? $data['tid'] : $field_info['default_value'];
            }
            if($field_info['required'] && !isset($temp['tid'])) return services_error('Missing ' . $field_name . '->tid attribute');
        }else{
            $temp['tid'] = isset($data) ? $data : NULL;
            if($field_info['required'] && !isset($temp['tid'])) return services_error('Missing ' . $field_name . ' attribute');
        }
        $entity->{$field_name}[$entity->language][0] = $temp;
    }else{
        $count = 0;
        if(!is_array($data)){
            return services_error($field_name . ' should be array');
        }
        foreach($data as $element){
            if($field_read['cardinality'] >1 && $count >=  $field_read['cardinality']){
                // return services_error($field_name . ' had cardinality: ' . $field_read['cardinality']);
                break;
            }
            $count++;
            if(is_array($element)){
                $temp = array();
                $temp['tid'] = isset($element['tid']) ? $element['tid'] : $field_info['default_value'];
                if($field_info['required'] && !isset($temp['tid'])) return services_error('Missing ' . $field_name . '->tid attribute');
                $entity->{$field_name}[$entity->language][] = $temp;
            }else{
                if($field_info['required'] && !isset($element)) return services_error('Missing ' . $field_name . ' attribute');
                $entity->{$field_name}[$entity->language][]['tid'] = $element;
            }
        }
    }
}

/**
 * wrapper for text_long field_type
 */
function text_long_wrapper($entity_type, $entity, $bundle, $field_name, $data){
    if(!isset($entity->language)) $entity->language = LANGUAGE_NONE;
    $field_info = field_info_instance($entity_type, $field_name, $bundle);
    $field_read = field_read_field($field_name);

    if(!isset($data)){
        if($field_info['required']) return services_error('Missing ' . $field_name . ' attribute');
        else return;
    }

    if($field_read['cardinality'] == 0) return;
    else if($field_read['cardinality'] == 1){
        $temp = array();
        if(is_array($data)){
            if(is_array(current($data))){
                $temp['value'] = isset(current($data)['value']) ? current($data)['value'] : $field_info['default_value'];
                $temp['format'] = isset(current($data)['format']) ? current($data['format']) : NULL;
                if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
            }else{
                $temp['value'] = isset($data['value']) ? $data['value'] : $field_info['default_value'];
                $temp['format'] = isset($data['format']) ? $data['format'] : NULL;
                if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
            }
        }else{
            $temp['value'] = isset($data) ? $data : NULL;
            if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . ' attribute');
        }
        $entity->{$field_name}[$entity->language][0] = $temp;
    }else{
        $count = 0;
        if(!is_array($data)){
            return services_error($field_name . ' should be array');
        }
        foreach($data as $element){
            if($field_read['cardinality'] >1 && $count >=  $field_read['cardinality']){
                // return services_error($field_name . ' had cardinality: ' . $field_read['cardinality']);
                break;
            }
            $count++;
            if(is_array($element)){
                $temp = array();
                $temp['value'] = isset($element['value']) ? $element['value'] : $field_info['default_value'];
                $temp['format'] = isset($element['format'])? $element['format'] : NULL;
                if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
                $entity->{$field_name}[$entity->language][] = $temp;
            }else{
                if($field_info['required'] && !isset($element)) return services_error('Missing ' . $field_name . ' attribute');
                $entity->{$field_name}[$entity->language][]['value'] = $element;
            }
        }
    }
}

/**
 * wrapper for image field_type
 */
function image_wrapper($entity_type, $entity, $bundle, $field_name, $data){
    if(!isset($entity->language)) $entity->language = LANGUAGE_NONE;
    $field_info = field_info_instance($entity_type, $field_name, $bundle);
    $field_read = field_read_field($field_name);
    if(!isset($data)){
        if($field_info['required']) return services_error('Missing ' . $field_name . ' attribute');
        else return;
    }

    if($field_read['cardinality'] == 0) return;
    else if($field_read['cardinality'] == 1){
        $temp = array();
        if(is_array($data)){
            if(is_array(current($data))){
                $temp['fid'] = isset(current($data)['fid']) ? current($data)['fid'] : (isset($field_info['default_value']) ? $field_info['default_value'] : NULL);
                $temp['alt'] = isset(current($data)['alt']) ? current($data)['alt'] : NULL;
                $temp['title'] = isset(current($data)['title']) ? current($data['title']) : NULL;
                $temp['width'] = isset(current($data)['width']) ? current($data['width']) : NULL;
                $temp['height'] = isset(current($data)['height']) ? current($data['height']) : NULL;
            }else{
                $temp['fid'] = isset($data['fid']) ? $data['fid'] : (isset($field_info['default_value']) ? $field_info['default_value'] : NULL);
                $temp['alt'] = isset($data['alt']) ? $data['alt'] : NULL;
                $temp['title'] = isset($data['title']) ? $data['title'] : NULL;
                $temp['width'] = isset($data['width']) ? $data['width'] : NULL;
                $temp['height'] = isset($data['height']) ? $data['height'] : NULL;
            }
        }else{
            $temp['fid'] = isset($data) ? $data : NULL;
            if($field_info['required'] && !isset($temp['fid'])) return services_error('Missing ' . $field_name . ' attribute');
        }
        if($field_info['required'] && !isset($temp['fid'])){
            return services_error($field_name . '->fid can not be empty');
        }
        $entity->{$field_name}[$entity->language][0] = $temp;
    }else{
        $count = 0;
        if(!is_array($data)){
            return services_error($field_name . ' should be array');
        }
        foreach($data as $element){
            if($field_read['cardinality'] >1 && $count >=  $field_read['cardinality']){
                // return services_error($field_name . ' had cardinality: ' . $field_read['cardinality']);
                break;
            }
            if(is_array($element)){
                $temp = array();
                $temp['fid'] = isset($element['fid']) ? $element['fid'] : (isset($field_info['default_value']) ? $field_info['default_value'] : NULL);
                $temp['alt'] = isset($element['alt'])? $element['alt'] : NULL;
                $temp['title'] = isset($element['title'])? $element['title'] : NULL;
                $temp['width'] = isset($data['width']) ? $data['width'] : NULL;
                $temp['height'] = isset($data['height']) ? $data['height'] : NULL;
                if($field_info['required'] && !isset($temp['fid'])){
                    return services_error('Missing '. $field_name . '->fid attributes');
                }
                $entity->{$field_name}[$entity->language][] = $temp;
            }else{
                if($field_info['required'] && !isset($element)) return services_error($field_name . '->fid can not be empty');
                $entity->{$field_name}[$entity->language][]['fid'] = $element;
            }
            $count++;
        }
        if($field_info['required'] && $count<1) return services_error($field_name . ' is required and while empty array is send');
    }
}

/**
 * wrapper for entitiyreference field_type
 */
function entityreference_wrapper($entity_type, $entity, $bundle, $field_name, $data){
    if(!isset($entity->language)) $entity->language = LANGUAGE_NONE;
    $field_info = field_info_instance($entity_type, $field_name, $bundle);
    $field_read = field_read_field($field_name);

    if(!isset($data)){
        if($field_info['required']) return services_error('Missing ' . $field_name . ' attribute');
        else return;
    }

    if($field_read['cardinality'] == 0) return;
    else if($field_read['cardinality'] == 1){
        $temp = array();
        if(is_array($data)){
            if(is_array(current($data))){
                $temp['target_id'] = isset(current($data)['target_id']) ? current($data)['target_id'] : $field_info['default_value'];
            }else{
                $temp['target_id'] = isset($data['target_id']) ? $data['target_id'] : $field_info['default_value'];
            }
            if($field_info['required'] && !isset($temp['target_id'])) return services_error('Missing ' . $field_name . '->target_id attribute');
        }else{
            $temp['target_id'] = isset($data) ? $data : NULL;
            if($field_info['required'] && !isset($temp['target_id'])) return services_error('Missing ' . $field_name . ' attribute');
        }
        $entity->{$field_name}[$entity->language][0] = $temp;
    }else{
        $count = 0;
        if(!is_array($data)){
            return services_error($field_name . ' should be array');
        }
        foreach($data as $element){
            if($field_read['cardinality'] >1 && $count >=  $field_read['cardinality']){
                // return services_error($field_name . ' had cardinality: ' . $field_read['cardinality']);
                break;
            }
            $count++;
            if(is_array($element)){
                $temp = array();
                $temp['target_id'] = isset($element['target_id']) ? $element['target_id'] : $field_info['default_value'];
                if($field_info['required'] && !isset($temp['target_id'])) return services_error('Missing ' . $field_name . '->target_id attribute');
                $entity->{$field_name}[$entity->language][] = $temp;
            }else{
                if($field_info['required'] && !isset($element)) return services_error('Missing ' . $field_name . ' attribute');
                $entity->{$field_name}[$entity->language][]['target_id'] = $element;
            }
        }
    }
}

/**
 * wrapper for list_text field_type
 */
function list_text_wrapper($entity_type, $entity, $bundle, $field_name, $data){
    if(!isset($entity->language)) $entity->language = LANGUAGE_NONE;
    $field_info = field_info_instance($entity_type, $field_name, $bundle);
    $field_read = field_read_field($field_name);

    if(!isset($data)){
        if($field_info['required']) return services_error('Missing ' . $field_name . ' attribute');
        else return;
    }

    if($field_read['cardinality'] == 0) return;
    else if($field_read['cardinality'] == 1){
        $temp = array();
        if(is_array($data)){
            if(is_array(current($data))){
                $temp['value'] = isset(current($data)['value']) ? current($data)['value'] : $field_info['default_value'];
            }else{
                $temp['value'] = isset($data['value']) ? $data['value'] : $field_info['default_value'];
            }
            if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
        }else{
            $temp['value'] = isset($data) ? $data : NULL;
            if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . ' attribute');
        }
        $entity->{$field_name}[$entity->language][0] = $temp;
    }else{
        $count = 0;
        if(!is_array($data)){
            return services_error($field_name . ' should be array');
        }
        foreach($data as $element){
            if($field_read['cardinality'] >1 && $count >=  $field_read['cardinality']){
                // return services_error($field_name . ' had cardinality: ' . $field_read['cardinality']);
                break;
            }
            $count++;
            if(is_array($element)){
                $temp = array();
                $temp['value'] = isset($element['value']) ? $element['value'] : $field_info['default_value'];
                if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
                $entity->{$field_name}[$entity->language][] = $temp;
            }else{
                if($field_info['required'] && !isset($element)) return services_error('Missing ' . $field_name . ' attribute');
                $entity->{$field_name}[$entity->language][]['value'] = $element;
            }
        }
    }
}

/**
 * wrapper for text field_type
 */
function text_wrapper($entity_type, $entity, $bundle, $field_name, $data){
    if(!isset($entity->language)) $entity->language = LANGUAGE_NONE;
    $field_info = field_info_instance($entity_type, $field_name, $bundle);
    $field_read = field_read_field($field_name);

    if(!isset($data)){
        if($field_info['required']) return services_error('Missing ' . $field_name . ' attribute');
        else return;
    }

    if($field_read['cardinality'] == 0) return;
    else if($field_read['cardinality'] == 1){
        $temp = array();
        if(is_array($data)){
            if(is_array(current($data))){
                $temp['value'] = isset(current($data)['value']) ? current($data)['value'] : $field_info['default_value'];
                $temp['format'] = isset(current($data)['format']) ? current($data['format']) : NULL;
                if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
            }else{
                $temp['value'] = isset($data['value']) ? $data['value'] : $field_info['default_value'];
                $temp['format'] = isset($data['format']) ? $data['format'] : NULL;
                if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
            }
        }else{
            $temp['value'] = isset($data) ? $data : NULL;
            if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . ' attribute');
        }
        $entity->{$field_name}[$entity->language][0] = $temp;
    }else{
        $count = 0;
        if(!is_array($data)){
            return services_error($field_name . ' should be array');
        }
        foreach($data as $element){
            if($field_read['cardinality'] >1 && $count >=  $field_read['cardinality']){
                // return services_error($field_name . ' had cardinality: ' . $field_read['cardinality']);
                break;
            }
            $count++;
            if(is_array($element)){
                $temp = array();
                $temp['value'] = isset($element['value']) ? $element['value'] : $field_info['default_value'];
                $temp['format'] = isset($element['format'])? $element['format'] : NULL;
                if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
                $entity->{$field_name}[$entity->language][] = $temp;
            }else{
                if($field_info['required'] && !isset($element)) return services_error('Missing ' . $field_name . ' attribute');
                $entity->{$field_name}[$entity->language][]['value'] = $element;
            }
        }
    }
}

/**
 * wrapper for mobile_number field_type
 */
function mobile_number_wrapper($entity_type, $entity, $bundle, $field_name, $data){
    if(!isset($entity->language)) $entity->language = LANGUAGE_NONE;
    $field_info = field_info_instance($entity_type, $field_name, $bundle);
    $field_read = field_read_field($field_name);

    if(!isset($data)){
        if($field_info['required']) return services_error('Missing ' . $field_name . ' attribute');
        else return;
    }

    if($field_read['cardinality'] == 0) return;
    else if($field_read['cardinality'] == 1){
        $temp = array();
        if(is_array($data)){
            if(is_array(current($data))){
                $temp['country'] = isset(current($data)['country']) ? current($data)['country'] : $field_info['default_value'];
                $temp['local_number'] = isset(current($data)['local_number']) ? current($data)['local_number'] : NULL;
                $temp['value'] = isset(current($data)['value']) ? current($data['value']) : NULL;
                $temp['verified'] = isset(current($data)['verified']) ? current($data['verified']) : NULL;
                $temp['tfa'] = isset(current($data)['tfa']) ? current($data['tfa']) : NULL;
            }else{
                $temp['country'] = isset($data['country']) ? $data['country'] : $field_info['default_value'];
                $temp['local_number'] = isset($data['local_number']) ? $data['local_number'] : NULL;
                $temp['value'] = isset($data['value']) ? $data['value'] : NULL;
                $temp['verified'] = isset($data['verified']) ? $data['verified'] : NULL;
                $temp['tfa'] = isset($data['tfa']) ? $data['tfa'] : NULL;
            }
            if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
        }else{
            $temp['value'] = isset($data) ? $data : NULL;
            if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . ' attribute');
        }
        $entity->{$field_name}[$entity->language][0] = $temp;
    }else{
        $count = 0;
        if(!is_array($data)){
            return services_error($field_name . ' should be array');
        }
        foreach($data as $element){
            if($field_read['cardinality'] >1 && $count >=  $field_read['cardinality']){
                // return services_error($field_name . ' had cardinality: ' . $field_read['cardinality']);
                break;
            }
            $count++;
            if(is_array($element)){
                $temp = array();
                $temp['country'] = isset($element['country'])? $element['country'] : $field_info['default_value'];
                $temp['local_number'] = isset($element['local_number'])? $element['local_number'] : NULL;
                $temp['value'] = isset($element['value'])? $element['value'] : NULL;
                $temp['verified'] = isset($element['verified'])? $element['verified'] : NULL;
                $temp['tfa'] = isset($element['tfa'])? $element['tfa'] : NULL;
                if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
                $entity->{$field_name}[$entity->language][] = $temp;
            }else{
                if($field_info['required'] && !isset($element)) return services_error('Missing ' . $field_name . ' attribute');
                $entity->{$field_name}[$entity->language][]['value'] = $element;
            }
        }
    }
}

/**
 * wrapper for email field_type
 */
function email_wrapper($entity_type, $entity, $bundle, $field_name, $data){
    if(!isset($entity->language)) $entity->language = LANGUAGE_NONE;
    $field_info = field_info_instance($entity_type, $field_name, $bundle);
    $field_read = field_read_field($field_name);

    if(!isset($data)){
        if($field_info['required']) return services_error('Missing ' . $field_name . ' attribute');
        else return;
    }

    if($field_read['cardinality'] == 0) return;
    else if($field_read['cardinality'] == 1){
        $temp = array();
        if(is_array($data)){
            if(is_array(current($data))){
                $temp['email'] = isset(current($data)['email']) ? current($data)['email'] : $field_info['default_value'];
            }else{
                $temp['email'] = isset($data['email']) ? $data['email'] : $field_info['default_value'];
            }
            if($field_info['required'] && !isset($temp['email'])) return services_error('Missing ' . $field_name . '->email attribute');
        }else{
            $temp['email'] = isset($data) ? $data : NULL;
            if($field_info['required'] && !isset($temp['email'])) return services_error('Missing ' . $field_name . ' attribute');
        }
        $entity->{$field_name}[$entity->language][0] = $temp;
    }else{
        $count = 0;
        if(!is_array($data)){
            return services_error($field_name . ' should be array');
        }
        foreach($data as $element){
            if($field_read['cardinality'] >1 && $count >=  $field_read['cardinality']){
                // return services_error($field_name . ' had cardinality: ' . $field_read['cardinality']);
                break;
            }
            $count++;
            if(is_array($element)){
                $temp = array();
                $temp['email'] = isset($element['email']) ? $element['email'] : $field_info['default_value'];
                if($field_info['required'] && !isset($temp['email'])) return services_error('Missing ' . $field_name . '->email attribute');
                $entity->{$field_name}[$entity->language][] = $temp;
            }else{
                if($field_info['required'] && !isset($element)) return services_error('Missing ' . $field_name . ' attribute');
                $entity->{$field_name}[$entity->language][]['email'] = $element;
            }
        }
    }
}

/**
 * wrapper for geofield field_type
 */
function geofield_wrapper($entity_type, $entity, $bundle, $field_name, $data){
    if(!isset($entity->language)) $entity->language = LANGUAGE_NONE;
    $field_info = field_info_instance($entity_type, $field_name, $bundle);
    $field_read = field_read_field($field_name);

    if(!isset($data)){
        if($field_info['required']) return services_error('Missing ' . $field_name . ' attribute');
        else return;
    }

    if($field_read['cardinality'] == 0) return;
    else if($field_read['cardinality'] == 1){
        $temp = array();
        if(is_array($data)){
            if(is_array(current($data))){
                $temp['geom'] = isset(current($data)['geom']) ? current($data)['geom'] : NULL;
                $temp['geo_type'] = isset(current($data)['geo_type']) ? current($data)['geo_type'] : NULL;
                $temp['lat'] = isset(current($data)['lat']) ? current($data['lat']) : NULL;
                $temp['lon'] = isset(current($data)['lon']) ? current($data['lon']) : NULL;
                $temp['left'] = isset(current($data)['left']) ? current($data['left']) : NULL;
                $temp['top'] = isset(current($data)['top']) ? current($data['top']) : NULL;
                $temp['right'] = isset(current($data)['right']) ? current($data['right']) : NULL;
                $temp['bottom'] = isset(current($data)['bottom']) ? current($data['bottom']) : NULL;
                $temp['geohash'] = isset(current($data)['geohash']) ? current($data['geohash']) : NULL;
            }else{
                $temp['geom'] = isset($data['geom']) ? $data['geom'] : NULL;
                $temp['geo_type'] = isset($data['geo_type']) ? $data['geo_type'] : NULL;
                $temp['lat'] = isset($data['lat']) ? $data['lat'] : NULL;
                $temp['lon'] = isset($data['lon']) ? $data['lon'] : NULL;
                $temp['left'] = isset($data['left']) ? $data['left'] : NULL;
                $temp['top'] = isset($data['top']) ? $data['top'] : NULL;
                $temp['right'] = isset($data['right']) ? $data['right'] : NULL;
                $temp['bottom'] = isset($data['bottom']) ? $data['bottom'] : NULL;
                $temp['geohash'] = isset($data['geohash']) ? $data['geohash'] : NULL;
            }
        }else{
            return services_error('Missing '. $field_name . '->' . 'lat, lon attribute');
        }
        if($field_info['required']){
            $attributes = '';
            if(!isset($temp['lat'])) $attributes .= 'lat,';
            if(!isset($temp['lon'])) $attributes .= 'lon,';
            if(!!isset($attributes)){
                return services_error('Missing '. $field_name . '->' . $attributes . ' attributes');
            }
        }
        $entity->{$field_name}[$entity->language][0] = $temp;
    }else{
        $count = 0;
        if(!is_array($data)){
            return services_error($field_name . ' should be array');
        }
        foreach($data as $element){
            if($field_read['cardinality'] >1 && $count >=  $field_read['cardinality']){
                // return services_error($field_name . ' had cardinality: ' . $field_read['cardinality']);
                break;
            }
            $count++;
            if(is_array($element)){
                $temp = array();
                $temp['geom'] = isset($element['geom'])? $element['geom'] : NULL;
                $temp['geo_type'] = isset($element['geo_type'])? $element['geo_type'] : NULL;
                $temp['lat'] = isset($element['lat'])? $element['lat'] : NULL;
                $temp['lon'] = isset($element['lon'])? $element['lon'] : NULL;
                $temp['left'] = isset($element['left'])? $element['left'] : NULL;
                $temp['top'] = isset($element['top'])? $element['top'] : NULL;
                $temp['right'] = isset($element['right'])? $element['right'] : NULL;
                $temp['bottom'] = isset($element['bottom'])? $element['bottom'] : NULL;
                $temp['geohash'] = isset($element['geohash'])? $element['geohash'] : NULL;
                if($field_info['required']){
                    $attributes = '';
                    if(!isset($temp['lat'])) $attributes .= 'lat,';
                    if(!isset($temp['lon'])) $attributes .= 'lon,';
                    if(!!isset($attributes)){
                        return services_error('Missing '. $field_name . '->' . $attributes . ' attributes');
                    }
                }
                $entity->{$field_name}[$entity->language][] = $temp;
            }else{
                return services_error('Missing '. $field_name . '->' . 'lat, lon attribute');
            }
        }
    }
}

/**
 * wrapper for field_collection_item field_type
 */
function field_collection_item_wrapper($entity_type, $entity, $bundle, $field_name, $data){
    if(!isset($entity->language)) $entity->language = LANGUAGE_NONE;
    $field_info = field_info_instance($entity_type, $field_name, $bundle);
    $field_read = field_read_field($field_name);

    if(!isset($data)){
        if($field_info['required']) return services_error('Missing ' . $field_name . ' attribute');
        else return;
    }

    if($field_read['cardinality'] == 0) return;
    else if($field_read['cardinality'] == 1){
        $temp = array();
        if(is_array($data)){
            if(is_array(current($data))){
                $temp['value'] = isset(current($data)['value']) ? current($data)['value'] : $field_info['default_value'];
                $temp['revision_id'] = isset(current($data)['revision_id']) ? current($data['revision_id']) : NULL;
                if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
            }else{
                $temp['value'] = isset($data['value']) ? $data['value'] : $field_info['default_value'];
                $temp['revision_id'] = isset($data['revision_id']) ? $data['revision_id'] : NULL;
                if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
            }
        }else{
            $temp['value'] = isset($data) ? $data : NULL;
            if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . ' attribute');
        }
        $entity->{$field_name}[$entity->language][0] = $temp;
    }else{
        $count = 0;
        if(!is_array($data)){
            return services_error($field_name . ' should be array');
        }
        foreach($data as $element){
            if($field_read['cardinality'] >1 && $count >=  $field_read['cardinality']){
                // return services_error($field_name . ' had cardinality: ' . $field_read['cardinality']);
                break;
            }
            $count++;
            if(is_array($element)){
                $temp = array();
                $temp['value'] = isset($element['value']) ? $element['value'] : $field_info['default_value'];
                $temp['revision_id'] = isset($element['revision_id'])? $element['revision_id'] : NULL;
                if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
                $entity->{$field_name}[$entity->language][] = $temp;
            }else{
                if($field_info['required'] && !isset($element)) return services_error('Missing ' . $field_name . ' attribute');
                $entity->{$field_name}[$entity->language][]['value'] = $element;
            }
        }
    }
}

/**
 * wrapper for number_integer field_type
 */
function number_integer_wrapper($entity_type, $entity, $bundle, $field_name, $data){
    if(!isset($entity->language)) $entity->language = LANGUAGE_NONE;
    $field_info = field_info_instance($entity_type, $field_name, $bundle);
    $field_read = field_read_field($field_name);

    if(!isset($data)){
        if($field_info['required']) return services_error('Missing ' . $field_name . ' attribute');
        else return;
    }

    if($field_read['cardinality'] == 0) return;
    else if($field_read['cardinality'] == 1){
        $temp = array();
        if(is_array($data)){
            if(is_array(current($data))){
                $temp['value'] = isset(current($data)['value']) ? current($data)['value'] : $field_info['default_value'];
            }else{
                $temp['value'] = isset($data['value']) ? $data['value'] : $field_info['default_value'];
            }
            if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
        }else{
            $temp['value'] = isset($data) ? $data : NULL;
            if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . ' attribute');
        }
        $entity->{$field_name}[$entity->language][0] = $temp;
    }else{
        $count = 0;
        if(!is_array($data)){
            return services_error($field_name . ' should be array');
        }
        foreach($data as $element){
            if($field_read['cardinality'] >1 && $count >=  $field_read['cardinality']){
                // return services_error($field_name . ' had cardinality: ' . $field_read['cardinality']);
                break;
            }
            $count++;
            if(is_array($element)){
                $temp = array();
                $temp['value'] = isset($element['value']) ? $element['value'] : $field_info['default_value'];
                if($field_info['required'] && !isset($temp['value'])) return services_error('Missing ' . $field_name . '->value attribute');
                $entity->{$field_name}[$entity->language][] = $temp;
            }else{
                if($field_info['required'] && !isset($element)) return services_error('Missing ' . $field_name . ' attribute');
                $entity->{$field_name}[$entity->language][]['value'] = $element;
            }
        }
    }
}

/**
 * wrapper for link_field field_type
 */
function link_field_wrapper($entity_type, $entity, $bundle, $field_name, $data){
    if(!isset($entity->language)) $entity->language = LANGUAGE_NONE;
    $field_info = field_info_instance($entity_type, $field_name, $bundle);
    $field_read = field_read_field($field_name);

    if(!isset($data)){
        if($field_info['required']) return services_error('Missing ' . $field_name . ' attribute');
        else return;
    }

    if($field_read['cardinality'] == 0) return;
    else if($field_read['cardinality'] == 1){
        $temp = array();
        if(is_array($data)){
            if(is_array(current($data))){
                $temp['url'] = isset(current($data)['url']) ? current($data)['url'] : NULL;
                $temp['title'] = isset(current($data)['title']) ? current($data['title']) : NULL;
                if($field_info['required'] && !isset($temp['url'])) return services_error('Missing ' . $field_name . '->url attribute');
                if(($field_info['settings']['title'] =='required') && !isset($temp['title'])) return services_error('Missing ' . $field_name . '->title attribute');
            }else{
                $temp['url'] = isset($data['url']) ? $data['url'] : NULL;
                $temp['title'] = isset($data['title']) ? $data['title'] : NULL;
                if($field_info['required'] && !isset($temp['url'])) return services_error('Missing ' . $field_name . '->url attribute');
                if(($field_info['settings']['title'] =='required') && !isset($temp['title'])) return services_error('Missing ' . $field_name . '->title attribute');
            }
        }else{
            if($field_info['settings']['title'] =='required') return services_error('Missing ' . $field_name . '->title attribute');
            $temp['url'] = isset($data) ? $data : NULL;
            if($field_info['required'] && !isset($temp['url'])) return services_error('Missing ' . $field_name . ' attribute');
        }
        $entity->{$field_name}[$entity->language][0] = $temp;
    }else{
        $count = 0;
        if(!is_array($data)){
            return services_error($field_name . ' should be array');
        }
        foreach($data as $element){
            if($field_read['cardinality'] >1 && $count >=  $field_read['cardinality']){
                // return services_error($field_name . ' had cardinality: ' . $field_read['cardinality']);
                break;
            }
            $count++;
            if(is_array($element)){
                $temp = array();
                $temp['url'] = isset($element['url']) ? $element['url'] : NULL;
                $temp['title'] = isset($element['title'])? $element['title'] : NULL;
                if($field_info['required'] && !isset($temp['url'])) return services_error('Missing ' . $field_name . '->url attribute');
                if(($field_info['settings']['title'] =='required') && !isset($temp['title'])) return services_error('Missing ' . $field_name . '->title attribute');
                $entity->{$field_name}[$entity->language][] = $temp;
            }else{
                if($field_info['settings']['title'] =='required') return services_error('Missing ' . $field_name . '->title attribute');
                if($field_info['required'] && !isset($element)) return services_error('Missing ' . $field_name . ' attribute');
                $entity->{$field_name}[$entity->language][]['url'] = $element;
            }
        }
    }
}
