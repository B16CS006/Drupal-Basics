<?php

function sample_dynamic_form(){    
    $form['create_hero']['type']=array(
        '#title' => t('Choose the type of your hero'),
        '#type' => 'select',
        '#options' => array(            //u can use drupal_map_assoc(array('','Air Style, 'Water Style','Earth Style'));
            '' => t('Select'),
            'wind' => t('Wind Style'),
            'water' => t('Water Style'),
            'earth' => t('Earth Style'),
            'fire' => t('Fire Style'),
            'light' => t('Lightning Style'),
        ),
        // '#ajax' => array(
        //     'callback' => 'sample_hero_detail_ajax_callback',
        //     'wrapper' => 'sample_hero_details_wrapper',
        // ),
    );
    $form['create_hero']['hero_details'] = array(
        '#type' => 'markup',
        '#prefix' => '<div id="sample_hero_details_wrapper">',
        '#suffix' => '</div>',
    );


    if(isset($form_state['values']['type'])){
        // dpm($form_state);
        $message = '';
        switch($form_state['values']['type']){
            case 'wind':{
                $message = 'Control Wind';
                break;
            }
            case 'water':{
                $message = 'Control Water';
                break;
            }
            case 'earth':{
                $message = 'Control Earth';
                break;
            }
            case 'fire':{
                $message = 'Control Fire';
                break;
            }
            case 'light':{
                $message = 'Control Light';
                break;
            }
        }
        $form['create_hero']['hero_details']['#markup'] = '<h3>'.t($message).'</h3>';
    }
}

function sample_hero_detail_ajax_callback($form, &$form_state){
    /* we need to return this because we want to change html content show we need to refresh content
    so by doing this we are doing similar things.*/
    return $form['create_hero']['hero_details'];
}


function vocabulary_term_options(){
    $vid = 6; // Vocabulary ID
    $term = taxonomy_get_tree($vid, $parent = 0, $depth = -1, $max_depth = NULL);

    $vocabulary_name = array();
    foreach ($term as $key => $value) {
    $vocabulary_name[$value->tid] = $value->name;
    }

    return $vocabulary_name;
}
function sample_options_hero(){
    $_heroes = db_select('node')
        ->fields('node',array('title'))
        ->condition('type','hero')
        ->orderBy('title','ASC')
        ->execute()
        ->fetchCol();
    $_heroes[] = 'Not Listed';
    
    $heroes = array();      //
    foreach($_heroes as $x){
        $heroes[$x] = $x;
    }
    unset($_heroes);
    
    return $heroes;
}

function sample_options_skills(){
    $_skills = db_select('node')
        ->fields('node',array('title'))
        ->condition('type','skills')
        ->orderBy('title','ASC')
        ->execute()
        ->fetchCol();
    $_skills[] = 'Not Listed';

    $skills = array();      //
    foreach($_skills as $x){
        $skills[$x] = $x;
    }
    unset($_skills);   

    return $skills;
}

function sample_options_designation(){
    $field_info = field_info_field('field_designation');
    $designation = list_allowed_values($field_info);     //

    return $designation;
}

function sample_options_nature(){
    $voc = taxonomy_vocabulary_machine_name_load('power_nature');
    $_nature = entity_load('taxonomy_term', FALSE, array('vid' => $voc->vid));
    unset($voc);

    $nature = array();
    foreach($_nature as $x){
        $nature[$x->name] = $x->name;
    }

    unset($_nature);

    return $nature;
}

function sample_options_technique(){
    $voc = taxonomy_vocabulary_machine_name_load('technique');
    $_technique = entity_load('taxonomy_term', FALSE, array('vid' => $voc->vid));
    unset($voc);
    $technique = array();
    foreach($_technique as $x){
        $technique[$x->name] = $x->name;
    }
    unset($_technique);

    return $technique;
}