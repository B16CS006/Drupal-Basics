<?php

////////////////////////////////////////////////////////////////////////////
//hook_submit is useful when our data is large and server take more time and
//php compiler execute next line so nid value is unavailable at that time and 
//we got stuck, so use hook_submit()
////////////////////////////////////////////////////////////////////////////

function sample_dynamic_form($form, &$form_state){

    $form['#tree'] = TRUE;

    $_heroes = db_select('node')
        ->fields('node',array('title'))
        ->condition('type','hero')
        ->orderBy('title','ASC')
        ->execute()
        ->fetchCol();
    $_heroes[] = 'Not Listed';
    $heroes = array();      //
    foreach($_heroes as $x) $heroes[$x] = $x;
    unset($_heroes);

    $form['hero'] = array(
        '#title' => t('Favourite Hero:'),
        '#type' => 'select',
        '#options' => $heroes,
        '#required' => TRUE,
        '#ajax' => array(
            'callback' => 'update_favourite_hero_ajax_callback',
            'wrapper' => 'update_favourite_hero_wrapper',
        ),
    );

    $form['create_hero'] = array(
        '#prefix' => '<div id="update_favourite_hero_wrapper">',
        '#suffix' => '</div>',
        '#states' => array(
            'visible' => array(
                ':input[name="hero"]' => array('value' => 'Not Listed'),
            ),
        ),
    );

    if(isset($form_state['values']['hero']) &&
            $form_state['values']['hero'] == 'Not Listed'){

        $form['create_hero'] = array(
            '#title' => t("Create New Hero:"),
            '#type' => "fieldset",
            '#collapsible' => TRUE,
            '#collapsed' => FALSE,
        );

        $_skills = db_select('node')
            ->fields('node',array('title'))
            ->condition('type','skills')
            ->orderBy('title','ASC')
            ->execute()
            ->fetchCol();
        $_skills[] = 'Not Listed';
        $skills = array();      //
        foreach($_skills as $x) $skills[$x] = $x;
        unset($_skills);

        $field_info = field_info_field('field_designation');
        $designation = list_allowed_values($field_info);     //
        unset($field_info);

        $form['create_hero']['name'] = array(
            '#title' => t('Name of the Hero:'),
            '#type' => 'textfield',
            '#required' => TRUE,
        );
    
        $form['create_hero']['designation'] = array(
            '#title' => t('Designation of the Hero:'),
            '#type' => 'select',
            '#options' => $designation,
            '#required' => TRUE,
        );
    
        $form['create_hero']['skill'] = array(
            '#title' => t("Hero's skill:"),
            '#type' => 'select',
            '#options' => $skills,
            '#ajax' => array(
                'callback' => 'update_skill_ajax_callback',
                'wrapper' => 'update_skill_wrapper',
            ),
            '#required' => TRUE,
        );

        $form['create_hero']['create_skill'] = array(
            '#prefix' => '<div id="update_skill_wrapper">',
            '#suffix' => '</div>',
            '#states' => array(
                'visible' => array(
                    ':input[name="create_hero[skill]"]' => array('value' => 'Not Listed'),
                ),
            ),
        );

        if(isset($form_state['values']['create_hero']['skill']) &&
                $form_state['values']['create_hero']['skill'] == 'Not Listed'){

            $form['create_hero']['create_skill'] = array(
                '#title' => t("Create New Skill:"),
                '#type' => "fieldset",
                '#collapsible' => TRUE,
                '#collapsed' => FALSE,
            );
            
            $voc = taxonomy_vocabulary_machine_name_load('power_nature');
            $_nature = entity_load('taxonomy_term', FALSE, array('vid' => $voc->vid));
            unset($voc);
            $nature = array();
            foreach($_nature as $x){
                $nature[$x->tid] = $x->name;
            }
            unset($_nature);

            $voc = taxonomy_vocabulary_machine_name_load('technique');
            $_technique = entity_load('taxonomy_term', FALSE, array('vid' => $voc->vid));
            unset($voc);
            $technique = array();
            foreach($_technique as $x){
                $technique[$x->tid] = $x->name;
            }
            unset($_technique);

            $form['create_hero']['create_skill']['name'] = array(
                '#title' => t('Name of the Skill:'),
                '#type' => 'textfield',
                '#required' => TRUE,
            );
        
            $form['create_hero']['create_skill']['nature'] = array(
                '#type' => 'checkboxes',
                '#title' => 'Nature: ',
                '#options' => $nature,
                '#required' => TRUE,
            );
        
            $form['create_hero']['create_skill']['techniques'] = array(
                '#type' => 'checkboxes',
                '#title' => 'Techniques: ',
                '#options' => $technique,
                '#required' => TRUE,
            );
        }
    }

    $form['help'] = array(
        '#type' => 'markup',
        '#markup' => '<p>For more info checkout our <a target="blank" href="http://www.google.com">website</a>.</p>'
    );
    $form['submit'] = array(
        '#type' => 'submit', 
        '#value' => t("Submit"),
    );
    $form['#submit'][] = 'sample_dynamic_form_submit';
    return $form;
}

///////////////////////////////////////////////////////////Submit/////////////////////////////////////////////
function sample_dynamic_form_submit($form, &$form_state){
    // dpm($form_state);
    if($form_state['values']['create_hero']['skill'] == 'Not Listed'){
        // drupal_set_message('skill is not listed');
        //create skill
        $nature = array();
        foreach($form_state['values']['create_hero']['create_skill']['nature'] as $x){
            if($x == 0){
                break;
            }
            $nature[$x] = $x;
        }
        $technique = array();
        foreach($form_state['values']['create_hero']['create_skill']['techniques'] as $x){
            if($x == 0){
                break;
            }
            $technique[$x] = $x;
        }

        if(!isset($form_state['values']['create_hero']['create_skill']['name']) || !count($nature) || !count($technique)){
            drupal_set_message('Either Name, Nature, or Technique are not provided');
            return;
        }

        create_skills_node($form_state['values']['create_hero']['create_skill']['name'],$nature, $technique);
        drupal_set_message('Skill is uploaded successfully');
    }
    if($form_state['values']['hero'] == 'Not Listed'){
        //create Hero
        // drupal_set_message('hero is not listed');
        //create skill
        if(!isset($form_state['values']['create_hero']['name']) ||
            !isset($form_state['values']['create_hero']['designation']) ||
            !isset($form_state['values']['create_hero']['skill'])
        ){
            drupal_set_message('Either Name, Designation, or Skill are not provided');
            return;
        }

        create_hero_node($form_state['values']['create_hero']['name'],
            $form_state['values']['create_hero']['designation'], 
            ($form_state['values']['create_hero']['skill'] == 'Not Listed')?
                $form_state['values']['create_hero']['create_skill']['name'] : $form_state['values']['create_hero']['skill']);
        drupal_set_message('Hero is uploaded successfully');
    }

    if(!isset($form_state['values']['hero'])){
        drupal_set_message('Hero is not selected, please select it first');
        return;
    }

    create_fav_hero_term(($form_state['values']['hero'] == 'Not Listed')?
        $form_state['values']['create_hero']['name'] : $form_state['values']['hero']);
    drupal_set_message('Favourite Hero is uploaded successfully');

}

///////////////////////////////////////////////////////////Callback///////////////////////////////////////////
function update_favourite_hero_ajax_callback($form , &$form_state){
    return $form['create_hero'];
}

function update_skill_ajax_callback($form){
    return $form['create_hero']['create_skill'];
}

////////////////////////////////////////////////////////////Custom Function//////////////////////////////////
function convert_name_to_nid($title, $type){
    $result = db_select('node')
        ->fields('node', array('nid'))
        ->condition('type', $type)
        ->condition('title',$title)
        ->execute()
        ->fetchCol();

    return $result[0];
}

function create_skills_node($title, $nature, $technique){
    global $user;

    $node = (object)NULL;
    $node->type = 'skills';
    node_object_prepare($node);
    
    $node->language = LANGUAGE_NONE;
    $node->title = $title;
    $node->uid = $user->uid;
    $node->status = 1;
    $node->promote = 1;
    $node->sticky = 1;

    foreach($nature as $x){
        $node->field_nature[$node->language][]['tid'] = $x;
    }
    foreach($technique as $x){
        $node->field_technique[$node->language][]['tid'] = $x;
    }

    $node = node_submit($node);
    return node_save($node);
}

function create_hero_node($title, $designation, $skill){
    global $user;

    $node = (object)NULL;
    $node->type = 'hero';
    node_object_prepare($node);
    
    $node->language = LANGUAGE_NONE;
    $node->title = $title;
    $node->uid = $user->uid;
    $node->status = 1;
    $node->promote = 1;
    $node->sticky = 1;


    $temp = array();
    $temp['value'] = $designation;
    $temp['target_type'] = 'node';
    $node->field_designation[$node->language][] = $temp;
    unset($temp);

    $temp = array();
    $temp['target_id'] = convert_name_to_nid($skill, 'skills');
    $temp['target_type'] = 'node';
    $node->field_skill[$node->language][] = $temp;
    unset($temp);
    
    $node = node_submit($node);
    return node_save($node);
}

function create_fav_hero_term($fav_hero){
    $voc = taxonomy_vocabulary_machine_name_load('favourite_hero');
    
    if(!$voc){
        drupal_set_message('Error: tax voc mac nam loa som wen wro');
        return;
    }
    
    $term = (object)NULL;
    $term->name = $fav_hero;
    $term->vid = $voc->vid;
    $term->language = LANGUAGE_NONE;
    $temp = array();
    $temp['target_id'] = convert_name_to_nid($fav_hero, 'hero');
    $temp['target_type'] = 'node';
    $term->field_hero[$term->language][] = $temp;
    $term = (object)$term;
    return taxonomy_term_save($term);
}