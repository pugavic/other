<?php

/**
 * @file
 * View mode switcher content type
 */
$plugin = array(
  'title' => t('LSC: Preloader widget'),
  'single' => TRUE,
  'description' => t('LSC: Preloader widget'),
  'category' => t('LSC'),
  'no title override' => TRUE,
  'edit form' => 'lsc_widgets_preloader_edit_form',
  'render callback' => 'lsc_widgets_preloader_widget_render',
  'defaults' => array(// Array of defaults for the settings form.
    'lsc_widgets_preloader_file' => NULL,
    'lsc_widgets_background_opacity' => NULL,
    'lsc_widgets_background' => NULL,
  ),
);

/**
 * 'render callback' callback for panel pane.
 */
function lsc_widgets_preloader_widget_render($subtype, $conf, $panel_args, $contexts) {

  $block = new stdClass;
  $block->content = lsc_widgets_block_content();

  return $block;
}



/**
 * An edit form for the pane's settings.
 */
function lsc_widgets_preloader_edit_form($form, &$form_state) {

  $form['lsc_widgets_background_opacity'] = array(
    '#type' => 'textfield',
    '#title' => t('Opacity background'),
    '#description' => t('Please enter opacity'),
    '#default_value' => variable_get('lsc_widgets_background_opacity', '0.5'),
  );

  $form['lsc_widgets_background'] = array(
    '#type' => 'textfield',
    '#title' => t('Background color (with # how in css)'),
    '#description' => t('Please enter backround color'),
    '#default_value' => variable_get('lsc_widgets_background', '#fff'),
  );

  $form['lsc_widgets_preloader_file'] = array(
    '#title' => t('Image for cable builder'),
    '#type' => 'managed_file',
    '#upload_location' => 'public://preloader/',
    '#description' => t("Please select image file."),
    '#default_value' => variable_get('lsc_widgets_preloader_file'),
    // '#required' => TRUE,
  );

  return $form;
}

/**
 *  Inserts all you need items on the page for working preloader
 */
function lsc_widgets_block_content() {
  global $base_url;

  $opacity = variable_get('lsc_widgets_background_opacity', '0.5');

  $background = variable_get('lsc_widgets_background', '#fff');

  $path = $base_url . '/' . drupal_get_path('module', 'lsc_widgets') . '/images/preloader.gif';
  if ($id_file = variable_get('lsc_widgets_preloader_file') AND $file = file_load($id_file)) {
    $path = $file->uri;
  }


// Javascript  set script online
  drupal_add_js(<<<EOT
(function($) {

  $(window).on('load', function() {
    var preloader = $('#page-preloader'),
        spinner   = preloader.find('.spinner');
    spinner.fadeOut();
    preloader.delay(350).fadeOut('slow');

});
})(jQuery);
EOT
    , 'inline');


//  CSS  set inline really need
  drupal_add_css(<<<EOT
#page-preloader {
    position: fixed;
    left: 0;
    top: 0;
    right: 0;
    bottom: 0;
    background: $background;
    opacity:$opacity;
    z-index: 100500;
}

#page-preloader .spinner {
    width: 296px;
    height: 296px;
    position: absolute;
    left: 40%;
    top: 40%;
    background: url('$path') no-repeat 50% 50%;
    margin: -16px 0 0 -16px;
EOT
    , 'inline');



  return '<div id="page-preloader2"><span class="spinner"></span></div>';
}
