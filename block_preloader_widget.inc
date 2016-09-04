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
//  'edit form' => 'lsc_widgets_preloader_edit_form',
  'render callback' => 'lsc_widgets_preloader_widget_render',
  'defaults' => array(// Array of defaults for the settings form.
  //  'lsc_widgets_preloader_file' => NULL,
   // 'lsc_widgets_background_opacity' => NULL,
   // 'lsc_widgets_background' => NULL,
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
 *  Inserts all you need items on the page for working preloader
 */
function lsc_widgets_block_content() {
  
//  CSS  set inline really need
  drupal_add_css(<<<'EOT'
 #wizard-form-wrapper .ajax-progress .message,
#wizard-form-wrapper .ajax-progress-throbber .message{
  color: white;
  font-size: 20px;
  padding: 30px;
}
#wizard-form-wrapper .ajax-progress .throbber,
#wizard-form-wrapper  .ajax-progress-throbber .throbber {
  float: none;
  margin: 250px auto 0 auto;
  width: 128px;
  height: 128px;
  background: url("/sites/all/themes/landseacables/app/img/preloader.gif") no-repeat center center;
}
#wizard-form-wrapper .ajax-progress,
#wizard-form-wrapper  .ajax-progress-throbber {
  width: 100%;
  height: 100%;
  background-color: #fff;
  position: fixed !important;
  top: 0;
  left: 0;
  z-index: 100500;
  vertical-align: top;
  text-align: center;
  opacity:0.5;
}

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
    background: #000;
    opacity:0.5;
    z-index: 100500;
          display:none;
}

#page-preloader .spinner {
    width: 296px;
    height: 296px;
    position: absolute;
    left: 40%;
    top: 40%;
    background: url('/sites/all/themes/landseacables/app/img/preloader.gif') no-repeat 50% 50%;
    margin: -16px 0 0 -16px;
EOT
    , 'inline');

  return '<div id="page-preloader"><span class="spinner"></span></div>';
}
