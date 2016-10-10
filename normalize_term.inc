<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
function create_term($vid, $name, $par_id) {

    $term = new stdClass();
$vid = $vid;
$term->name = $name ;  
$term->vid = $vid;
$term->parent = $par_id; 
 //   $file = file_save_data(file_get_contents($image_url), file_default_scheme().'://tmp/'.basename($image_url));
//$file->status = 1;
//$node->field_image['und'][0] = (array)$file;


    taxonomy_term_save($term);
    return $term;
}

function add_all_pin($vocabulary_name) {
    $terms4 = array('Male', 'Female');
    $terms5 = array('Yes', 'No');

    $vocabulary_manufacturer = taxonomy_vocabulary_machine_name_load($vocabulary_name);
    $current_categories1 = taxonomy_get_tree($vocabulary_manufacturer->vid, 0, 1);
    foreach ($current_categories1 as $term1) {
        $current_categories2 = taxonomy_get_tree($vocabulary_manufacturer->vid, $term1->tid, 1);
        foreach ($current_categories2 as $term2) {
        $pins = array(1 => 1, 2 => 2, 3 => 3, 4 => 4, 5 => 5, 6 => 6, 7 => 7, 8 => 8, 9 => 9, 10 => 10,
            11 => 11, 12 => 12, 13 => 13, 14 => 14, 15 => 15, 16 => 16, 17 => 17, 18 => 18, 19 => 19, 20 => 20,
            21 => 21, 22 => 22, 23 => 23, 24 => 24, 25 => 25, 26 => 26, 27 => 27, 28 => 28, 29 => 29, 30 => 30,
            31 => 31, 32 => 32, 33 => 33, 34 => 34, 35 => 35, 36 => 36, 37 => 37);
            $current_categories3 = taxonomy_get_tree($vocabulary_manufacturer->vid, $term2->tid, 1);
            foreach ($current_categories3 as $term3) {
                if (is_numeric($term3->name) AND ! empty($pins[intval($term3->name)])) {
                    unset($pins[intval($term3->name)]);
                }
            }
            foreach ($pins as $pin) {
                if ($term3 = create_term($vocabulary_manufacturer->vid, $pin, $term2->tid)) {
                    foreach ($terms4 as $vterms4) {
                        if ($term4 = create_term($vocabulary_manufacturer->vid, $vterms4, $term3->tid)) {
                            foreach ($terms5 as $vterms5) {
                                if ($term5 = create_term($vocabulary_manufacturer->vid, $vterms5, $term4->tid)) {
                                    drupal_set_message("Product created:{$term5->tid}  {$term5->name}");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

function sanitize_connectors_term($vocabulary_name=null) {
    drupal_set_message("Hello from sanitize!");
    $img_list = array('141926.jpg','505477_2012061142.jpg','5056225993.jpg','8109.jpg','cbaa4489c3e6f185c78a8d9968f98b37.jpg','computer-cables-big.jpg','img8649_14157.jpg','imgsocial.jpg','kl.jpg','micro-usb-cable-types-i5.JPG','technai-pc.jpg','vga_bnc.jpg');
    if($vocabulary_name){
        $leng=count($img_list)-1;
        $path_to_module_img = drupal_get_path('module', 'lsc_cable_builder') . '/img';
      $vocabulary_manufacturer = taxonomy_vocabulary_machine_name_load($vocabulary_name);
      $terms = taxonomy_get_tree($vocabulary_manufacturer->vid,0,null,true);
       foreach($terms as $term){
            if(empty($term->field_cable_image['und'][0])){
                $index = rand(0, $leng);
    $file = file_save_data(file_get_contents($path_to_module_img.'/'.$img_list[$index]), file_default_scheme().'://tmp/'.$img_list[$index]);
$file->status = 1;
$term->field_cable_image['und'][0] = (array)$file;
taxonomy_term_save($term);
            }
       }
    }
    return array('#markup'=>'sanize page');
}
