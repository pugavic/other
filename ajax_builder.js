/*
 * @file
 * JavaScript for ajax_builder.
 *
 */

(function($) {

  // Re-enable form elements that are disabled for non-ajax situations.
  Drupal.behaviors.lsc_cable_builder = {
    attach:function (context, settings) {

        // Emulate submit next-step.
        $('a.product-item-wrapper', context).once("lsc_cable_builder").click(function () {
            console.log("privet2");
            $('input[id^="edit-next-step"]').trigger('mousedown');
            return false;
        });

        // Emulate on diagram page submit button click where link.
        $('a.diagram-item-wrapper', context).once("lsc_cable_builder2").on("click", function (e) {
            id_elem = "#submit-diagram-" + $(this).attr("href").substr(1);
            $(id_elem).trigger('mousedown');
            return false;
        });

      // Set active options highlight.
      $('input[id^="link-"]').mousedown(function(){
        $('input[id^="link-"]').removeClass('active-option');
        $(this).addClass('active-option');
      });

      // Emulate "back" button.
      $('div[id*="-wizard-header-top-step"]').click(function(){
             var preloader = $('#page-preloader2'),
        spinner   = preloader.find('.spinner');
  
          var show_preloader = function(){
             spinner.fadeIn();
          };
          var hide_preloader = function(){
              spinner.hide();
              preloader.hide();
          };
                var interval,once_timer ;
                var id_wrapper = "#wizard-form-wrapper";
                var ajax_mark = "#ajax_mark";
                 var id_wrapper_obj = $(id_wrapper);
                var ajax_mark_obj = $(id_wrapper+">"+ajax_mark);
                var add_label = function() {
                     id_wrapper_obj.prepend($(ajax_mark));
                };

                 var remove_label = function() {
                    ajax_mark_obj.remove();

                };

                var check_label = function() {
                    if(! ajax_mark_obj.length()){
                        hide_preloader();
                       clearInterval(interval);
                    }
                      
                };
                
                
          
        var regexp = /\d+/g;
        var matches = $(this).attr('id').match(regexp);
        console.log(Drupal.settings.lsc_cable_builder.cablePath);
        console.log('back to step ' + matches[0]);
        show_preloader();
        add_label();
        
        interval = setInterval("check_label",50)
        once_timer = setTimeout(function(){alert("privet");hide_preloader();clearInterval(interval);},3000);
//        $.ajax({
//          type: "POST",
//          url: Drupal.settings.lsc_cable_builder.cablePath + '/builder/prev_step/' + matches[0],
//          //data: { prev_step: matches[0]},
//          success: function(return_data){
//            
//            $('input[id^="edit-prev-step"]', context ).trigger('mousedown');
//             hide_preloader();
//          }
//          
//          
//        });
      });
                   
       
    }
  };

})(jQuery);



function add_label(id_elem,lab_id){
    var el = $(id_elem);
    el.prepend($(lab_id));
}

function remove_label(id_elem,lab_id){
       $(id_elem+">"+lab_id).remove();
    
}

function check_label(id_elem,lab_id){
   return $(id_elem+">"+lab_id).length();
}