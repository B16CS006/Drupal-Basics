<?php
/*
*hook_menu to load tpl files from theme folder
* i.e sites/all/themes/custom/current_theme_name/templates/books
* current_theme_name = fiction
*/

    function books_theme(){
        $path_to_theme = drupal_get_path('theme',variable_get('theme_default', 'fiction'));
        $themes = array();
        $themes['books_list'] = array(
            'template' => 'books-list',
            'path' => $path_to_theme.'/templates/books',
        );
        return $themes;
    }