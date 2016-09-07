<?php

 
function lsc_products_order_history_ajax_callback($form,$formstate,$order) 
{
    return $form['lsc_products_order_result'];
}



function lsc_products_order_history($form, &$form_state) {

    global $user;
    $form = [];
    $values = $form_state['values'];



    $matches = NULL;
    if (!empty($form_state['triggering_element']['#name']) AND
            preg_match("@order-(\d{1,10})@i", $form_state['triggering_element']['#name'], $matches)) {
        $selected_order = commerce_order_load($matches[1]);
    } else {
        $form['lsc_products_order'] = array(
            '#type' => 'container',
            '#attributes' => array(
                'class' => array(
                    'button-history-wrapper',
                ),
            ),
        );

        if ($orders = commerce_order_load_multiple(array(26, 27, 28))) {
            reset($orders);
            $selected_order = current($orders);

            foreach ($orders as $korders => $vorders) {
                $form['lsc_products_order'][$korders] = array(
                    '#type' => 'submit',
                    '#name' => 'order-' . $vorders->order_id,
                    '#value' => $vorders->order_id,
                    '#submit' => array('lsc_products_order_history'),
                    '#ajax' => array(
                        'callback' => 'lsc_products_order_history_ajax_callback',
                        'wrapper' => 'order-hystory-result-wrapper',
                        'method' => 'replace',
                    //   'progress' => array('type' => 'none'),
                    ),
                );
            }
        }

        $form['add_to_cart'] = array(
            '#type' => 'submit',
            '#value' => 'Add to cart',
            '#submit' => array('lsc_cable_builder_wizard_add_submit'),
            '#weight' => 90,
        );
    }
    if ($selected_line_items = field_get_items('commerce_order', $selected_order, 'commerce_line_items')) {
        reset($selected_line_items);

        $curr_el = current($selected_line_items)['line_item_id'];

        $form['lsc_products_order_result'] = array(
            '#markup' => views_embed_view('lsc_view_orders', 'block', array($curr_el)),
            '#type' => 'markup',
            '#attributes' => array(
                'class' => array(
                    'items-wrapper',
                ),
            ),
            '#suffix' => '</div>',
            '#prefix' => '<div id="order-hystory-result-wrapper">',
        );
    }



    return $form;
}

function lsc_product_get_order_var($order) {
    // extracts data from order
        
 /*$line_items = field_get_items('commerce_order', $order, 'commerce_line_items');
   foreach($line_items as $line){
      $line_item_obj = commerce_line_item_load($line['line_item_id']);
      $product_ids = field_get_items('commerce_line_items', $line_item_obj, 'commerce_product');

   }*/
    
    
    return [
        "first" => ['title' => 'First form','image'=>'sites/default/files/styles/medium/public/shutterstock_1650470.jpg?itok=NpQN6eFu','property1' => 'Subconn', 'property2' => 'Circular', 'property3' => 1,
            'property4' => 'Male', 'property5' => 'Yes'],
        "second" => [
            'title' => 'Second form',
            'image'=>'sites/default/files/styles/medium/public/default_images/no-cable.png?itok=0PbI8DnW',
            'property1' => 'Burton', 'property2' => 'CCP-RA',
            'property3' => 32, 'property4' => 2],
        "third" => [
            'title' => 'Third form',
            'image'=>'sites/default/files/styles/medium/public/default_images/no-cable.png?itok=0PbI8DnW','property1' => 'Subconn', 'property2' => 'Circular',
            'property3' => 1, 
            'property4' => ['title' => 'diagram 1',
                'image' => 'sites/default/files/styles/medium/public/%20news-img1_2.jpg?itok=yEEl2JUM']],
    ];
}


  /*  
  
    }
    $line_items commerce_line_item_load_multiple();
    
    $orders = commerce_order_load_multiple(array(), array('status' => 'pending'), TRUE);
foreach($orders as $order) {
  foreach ($order->commerce_line_items['und'] as $line) {
    $line_item = commerce_line_item_load($line['line_item_id']);
    $product_id = $line_item->commerce_product['und']...
  }
}
     	
commerce_product_load_multiple
    
    foreach($orders){
        oredrs-l
    }
   
    
   
    
    return 
}

function lsc_products_order_view($order) {
    

  }

  // Add firs choosen cable if already build.
  foreach ($available_forms as $rendered_forms) {
    if (isset($form_state['storage'][$rendered_forms . '_cable']) || isset($_SESSION['builder']['form'][$rendered_forms])) {
      $form['wizard_header_' . $rendered_forms]['wizard_selected'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array(
            'wizard-selected-' . $rendered_forms . '-wrapper',
          ),
          'id' => array(
            'wizard-selected-' . $rendered_forms . '-wrapper',
          ),
        ),
      );

      $form['wizard_header_' . $rendered_forms]['wizard_selected']['title'] = array(
        '#markup' => '<h3>' . t('You selected') . '</h3>',
      );

      // Check for valus in session. We know that if we reach this step then value alredy in form_states or in session.
      if (!isset($form_state['storage'][$rendered_forms . '_cable'])) {
        $form_state['storage'][$rendered_forms . '_cable'] = $_SESSION['builder']['form'][$rendered_forms];
      }

      $form['wizard_header_' . $rendered_forms]['wizard_selected'][$rendered_forms] = lsc_cable_builder_wizard_selected($form_state['storage'][$rendered_forms . '_cable'], $rendered_forms);

      if ($options_is_hidden) {
        $form['wizard_header_' . $rendered_forms]['wizard_header_top']['#attributes']['class'][] = 'element-invisible';
        $form['wizard_header_' . $rendered_forms]['wizard_header_bottom']['#attributes']['class'][] = 'element-invisible';
      }
    }
  }
    
    return array('#markup'=>'This text');
}



/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.



function _lsc_cable_builder_form_add_product_form(&$form){
   
    $form['add_to_cart'] = array(
      '#type' => 'submit',
      '#value' => 'Add to cart',
      '#submit' => array('lsc_cable_builder_wizard_add_submit'),
      '#weight' => 90,
    );

    $form['not_correct'] = array(
      '#type' => 'submit',
      '#value' => 'Not correct',
      '#submit' => array('lsc_cable_builder_wizard_show_options'),
      '#ajax' => array(
        'callback' => 'lsc_cable_builder_product_ajax_callback',
        'wrapper' => 'wizard-form-wrapper',
        'method' => 'replace',
        'progress' => array('type' => 'none'),
      ),
      '#weight' => 91,
    );
  }

  // Add firs choosen cable if already build.
  foreach ($available_forms as $rendered_forms) {
         $form['wizard_header_' . $rendered_forms]['wizard_selected'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array(
            'wizard-selected-' . $rendered_forms . '-wrapper',
          ),
          'id' => array(
            'wizard-selected-' . $rendered_forms . '-wrapper',
          ),
        ),
      );

      $form['wizard_header_' . $rendered_forms]['wizard_selected']['title'] = array(
        '#markup' => '<h3>' . t('You selected') . '</h3>',
      );

      // Check for valus in session. We know that if we reach this step then value alredy in form_states or in session.
      if (!isset($form_state['storage'][$rendered_forms . '_cable'])) {
        $form_state['storage'][$rendered_forms . '_cable'] = $_SESSION['builder']['form'][$rendered_forms];
      }

      $form['wizard_header_' . $rendered_forms]['wizard_selected'][$rendered_forms] = lsc_cable_builder_wizard_selected($form_state['storage'][$rendered_forms . '_cable'], $rendered_forms);

      if ($options_is_hidden) {
        $form['wizard_header_' . $rendered_forms]['wizard_header_top']['#attributes']['class'][] = 'element-invisible';
        $form['wizard_header_' . $rendered_forms]['wizard_header_bottom']['#attributes']['class'][] = 'element-invisible';
      }
    }
  
}

 */