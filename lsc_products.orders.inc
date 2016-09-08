<?php

/**
 * Implements ajax callback().
 */
function lsc_products_order_history_ajax_callback($form, $form_state) {
    return $form['lsc_products_order_result'];
}

/**
 * Implements callback submit form for ajax
 */
function lsc_products_order_history_submit($form, &$form_state) {
    $form_state['rebuild'] = true;
}

/**
 *  Main builder form.
 */
function lsc_products_order_history($form, &$form_state) {
    global $user;

    $matches = NULL;
    if (!empty($form_state['triggering_element']['#name']) AND
            preg_match("@order-(\d{1,10})@i", $form_state['triggering_element']['#name'], $matches)) {
        $selected_order = commerce_order_load($matches[1]);
    } 
        drupal_static('css-order-history', 1);
        $form['lsc_products_order'] = array(
            '#type' => 'container',
            '#attributes' => array(
                'class' => array(
                    'button-history-wrapper',
                ),
            ),
        );

        if ($orders = commerce_order_load_multiple(array(), array('uid' => $user->uid, 'status' => 'pending'))) {

            reset($orders);
            $selected_order = current($orders);

            foreach ($orders as $korders => $vorders) {
                $form['lsc_products_order'][$korders] = array(
                    '#type' => 'submit',
                    '#name' => 'order-' . $vorders->order_id,
                    '#value' => $vorders->order_id,
                    '#submit' => array('lsc_products_order_history_submit'),
                    '#ajax' => array(
                        'callback' => 'lsc_products_order_history_ajax_callback',
                        'wrapper' => 'order-hystory-result-wrapper',
                        'method' => 'replace',
                        'progress' => array('type' => 'none'),
                    ),
                );
            }
        }else{
             return array('no-result'=>array('#markup'=>"You don't have orders"));
        }
        // Temporary hidden 
        $form2['add_to_cart'] = array(
            '#type' => 'submit',
            '#value' => 'Add to cart',
            '#submit' => array('lsc_cable_builder_wizard_add_submit'),
            '#weight' => 90,
        );
    

        $curr_el = $selected_order->order_id;
        //     shat($curr_el);
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
    
  
    return $form;
}
