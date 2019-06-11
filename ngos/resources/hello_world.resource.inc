<?php


function _ngos_hello_world($name){
    $name = (!empty($name)) ? check_plain($name) : 'world';

    return array(
        'hello' => $name,
        'goodbye' => 'forever', 
        'php_cms' => array(
            'wordpress',
            'joomla',
            'drupal',
        ),
    );
}