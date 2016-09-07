<?php
  global $base_url;
//var_export($fields,true);
  
                $img_func = function($image_uri, $def_image = '/app/img/default-connectors-cables.jpg'){
                global $base_url;
                if (empty($image_uri)) {
                   return theme('image', array(
                        'path' => $base_url . path_to_theme() . $def_image,
                        'alt' => '',
                        'title' => '',
                    ));
                } else {
                    return theme('image_style', array(
                        'style_name' => 'home_custom_item_475x125',
                        'path' => $image_uri,
                        'alt' => '',
                        'title' => '',));
                }
  };
  foreach ($fields as $id => $field){
    if (!empty($field->content)){
        
    
         $line_item = commerce_line_item_load(strval($field->raw));
     
        
          $prod = field_get_items('commerce_line_item',$line_item, 'commerce_product');
        if(count($prod)){
            $id_product = array_shift($prod);
            
            
            if(!empty($product = commerce_product_load($id_product['product_id']))){
                
                $product_wrapper = entity_metadata_wrapper('commerce_product', $product);
                
                    
                        
                
             
               
                 $default_image= "";
                $connector = $product_wrapper->field_connector->value();
                $end_connector = $product_wrapper->field_end_connector->value();
                $cable = $product_wrapper->field_cable->value();
                $diagram = $product_wrapper->field_diagram->value();
                
                $connector_terms  = taxonomy_get_parents_all($connector->tid);
                if($connecor_image = field_get_items('taxonomy_term',$connector, 'field_cable_image')){
                  $connecor_image_html = $img_func(current($connecor_image)['uri']);
                };
                $end_connector_terms  = taxonomy_get_parents_all($end_connector->tid);
                $cable_terms  = taxonomy_get_parents_all($cable->tid);
                if(!empty($diagram->tid)){
                  $diagram_term  = taxonomy_term_load($diagram->tid);
                }
}
            }
        }
    }
  

  
?>

<?php if (count($connector_terms)): ?>
<div class="connector-image">
    <?php echo (!empty($connecor_image_html))? $connecor_image_html : ""; ?>
</div>
    <?php foreach ($connector_terms as $key => $term): ?>
        <div><?php echo $term->name; ?></div>
    <?php endforeach; ?>
<?php endif; ?>

<?php if (count($end_connector_terms)): ?>
    <?php foreach ($end_connector_terms as $key => $term): ?>
        <div><?php echo $term->name; ?></div>
    <?php endforeach; ?>
<?php endif; ?>

<?php if (count($cable_terms)): ?>
    <?php foreach ($cable_terms as $key => $term): ?>
        <div><?php echo $term->name; ?></div>
    <?php endforeach; ?>
        <?php if (!empty($diagram_term)): ?>
                 <div><?php echo $diagram_term->name; ?></div>
        <?php endif; ?>
<?php endif; ?>