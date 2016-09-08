<?php

function get_order_view_result($order_id) {
    return array(
        '#markup' => views_embed_view('lsc_view_orders', 'block', array($order_id)),
        '#type' => 'markup',
        '#attributes' => array(
            'class' => array(
                'items-wrapper',
            ),
        ),
        '#prefix' => '<div id="order-hystory-result-wrapper">',
        '#suffix' => '</div>',
    );
}

/**
 * Implements ajax callback().
 */
function lsc_products_order_history_ajax_callback($form, $form_state) {
    $matches = array();
    if (!empty($form_state['triggering_element']['#name']) AND
            preg_match("@order-(\d{1,10})@i", $form_state['triggering_element']['#name'], $matches)) {
        $selected_order = commerce_order_load($matches[1]);
        $curr_el = $selected_order->order_id;
        $_SESSION['lsc-o-selected'] = $curr_el;
        return get_order_view_result($curr_el);
    }
    return '';
}

/**
 *  Main builder form.
 */
function lsc_products_order_history_form($form, &$form_state) {
    global $user;
    if (!$orders = commerce_order_load_multiple(array(), array('uid' => $user->uid, 'status' => 'pending'))) {
        return array('no-result' => array('#markup' => "You don't have orders"));
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

    reset($orders);
    $selected_order = (!empty($_SESSION['lsc-o-selected'])) ? $_SESSION['lsc-o-selected'] : current($orders)->order_id;

    foreach ($orders as $korders => $vorders) {
        $form['lsc_products_order'][$korders] = array(
            '#type' => 'submit',
            '#name' => 'order-' . $vorders->order_id,
            '#value' => $vorders->order_id,
            '#ajax' => array(
                'callback' => 'lsc_products_order_history_ajax_callback',
                'wrapper' => 'order-hystory-result-wrapper',
                'method' => 'replace',
                'progress' => array('type' => 'none'),
            ),
        );
    }

    if (!empty($form['lsc_products_order'][$selected_order])) {
        $form['lsc_products_order'][$selected_order]['#attributes']['class'][] = 'active';
    }

    $form['lsc_products_order_result'] = get_order_view_result($selected_order);
 
    // Temporary hidden 
    $form2['add_to_cart'] = array(
        '#type' => 'submit',
        '#value' => 'Add to cart',
        '#submit' => array('lsc_cable_builder_wizard_add_submit'),
        '#weight' => 90,
    );

    drupal_add_js(<<<'EOT'
(function($) {
  Drupal.behaviors.lsc_order_history = {
    attach:function (context, settings) {
       active_name = "active";
        tags_name = '#lsc-products-order-history-form .button-history-wrapper .form-submit';
        $(tags_name, context).once("lsc_order_history").mousedown(function () {
            $(tags_name).removeClass(active_name);
          $(this).addClass(active_name);
        });
    }
  };
})(jQuery);
EOT
            , 'inline');
    
    return $form;
}
