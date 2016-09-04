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
            preloader_watch();
            $('input[id^="edit-next-step"]').trigger('mousedown');
            return false;
        });

        // Emulate on diagram page submit button click where link.
        $('a.diagram-item-wrapper', context).once("lsc_cable_builder2").on("click", function (e) {
            preloader_watch();
            id_elem = "#submit-diagram-" + $(this).attr("href").substr(1);
            $(id_elem).trigger('mousedown');
            return false;
        });

      // Set active options highlight.
      $('input[id^="link-"]').mousedown(function(){
          preloader_watch("#wizard-products-content");
        $('input[id^="link-"]').removeClass('active-option');
        $(this).addClass('active-option');
      });

      // Emulate "back" button.
      $('.sel-prod-fields').click(function(){
        var regexp = /\d+/g;
        var matches = $(this).attr('id').match(regexp);
        console.log(Drupal.settings.lsc_cable_builder.cablePath);
        console.log('back to step ' + matches[0]);
        preloader_watch();
        $.ajax({
          type: "POST",
          url: Drupal.settings.lsc_cable_builder.cablePath + '/builder/prev_step/' + matches[0],
          //data: { prev_step: matches[0]},
          success: function(return_data){
            $('input[id^="edit-prev-step"]', context ).trigger('mousedown');
          }
        });
      });
            
       
    }
  };

})(jQuery);

function preloader_watch(id_wrapper, mark_name, min_time, max_time) {
    id_wrapper = id_wrapper || "#wizard-form-wrapper";
    mark_name = mark_name || "ajax-builder-mark";
    min_time = min_time || 50;
    max_time = max_time || 10000;

    var preloader = $('#page-preloader'),
            spinner = $('#page-preloader .spinner'),
            interval, once_timer;

    var start_proccess = function () {
        spinner.show();
        preloader.show();
        $(id_wrapper).addClass(mark_name);
    };

    var end_proccess = function () {
        $(id_wrapper).removeClass(mark_name);
        preloader.hide();
        clearInterval(interval);
        clearTimeout(once_timer);
    };

    start_proccess();

    interval = setInterval(function () {
        if (!$(id_wrapper).hasClass(mark_name)) {
            end_proccess();
        }
    }, min_time);

    once_timer = setTimeout(function () {
        end_proccess();
    }
    , max_time);

}