<?php
// try this html listing example for all nodes / includes a few getElementsByTagName options:

$file = $DOCUMENT_ROOT. "test.html";
$doc = new DOMDocument();
$doc->loadHTMLFile($file);

// example 1:
$elements = $doc->getElementsByTagName('*');
// example 2:
//$elements = $doc->getElementsByTagName('html');
// example 3:
//$elements = $doc->getElementsByTagName('body');
// example 4:
//$elements = $doc->getElementsByTagName('table');
// example 5:
//$elements = $doc->getElementsByTagName('div');

if (!is_null($elements)) {
  foreach ($elements as $element) {
    echo "<br/>". $element->nodeName. ": ";

    $nodes = $element->childNodes;
    foreach ($nodes as $node) {
      echo $node->nodeValue. "\n";
    }
  }
}
?>

<?php
$myhtml = <<<EOF
<div class="field field-name-commerce-customer-address field-type-addressfield field-label-hidden">
    <div class="field-items">
        <div class="field-item even">
            <div class="addressfield-container-inline name-block">
                <div class="name-block">asdasdas</div>
                    
            </div>
            <div class="street-block"><div class="thoroughfare">dasdasd</div><div class="premise">dasdasd</div></div>
            <div class="addressfield-container-inline locality-block country-AF"><span class="locality">dasdasd</span></div>
            <span class="country">Afghanistan</span>
        </div>
    </div>
</div>
<div class="field field-name-field-cc-email field-type-text field-label-above">
    <div class="field-label">CC-Email:&nbsp;</div>
    <div class="field-items"><div class="field-item even">dasdasdasd</div></div>
</div>
EOF;



$doc = new DOMDocument();
$doc->loadHTML($myhtml);

$cc_email_class = 'field-name-field-cc-email';
$address_class = 'field-name-commerce-customer-address';
$label_class = 'field-label';
$email_class = 'field-item';
$finder = new DomXPath($doc);
$cc_email = $finder->query("//*[contains(concat(' ', normalize-space(@class), ' '), ' $cc_email_class ')]//*[contains(concat(' ', normalize-space(@class), ' '), ' $email_class ')]");
$address = $finder->query("//*[contains(concat(' ', normalize-space(@class), ' '), ' $address_class ')]");
$label = $finder->query("//*[contains(concat(' ', normalize-space(@class), ' '), ' $cc_email_class ')]/*[contains(concat(' ', normalize-space(@class), ' '), ' $label_class ')]");


$tags = $doc->getElementsByTagName('a');
foreach ($cc_email as $cc_emailv) 
    {
 $value  = $cc_emailv->nodeValue ;
  echo  $node->nodeValue;
    }
    foreach ($address as $addressv) 
    {
 $value  = $addressv->nodeValue ;
  echo  $addressv->nodeValue;
    }
    
foreach ($label as $labelv) {
       echo $labelv->getAttribute('href').' | '.$labelv->nodeValue."\n";
     
}

$orgdoc = new DOMDocument;
$orgdoc->importNode($cc_emailv,true);


// $res1 =  $orgdoc->saveHTML($cc_emailv);
//[$cc_emailv->parentNode->removeChild($cc_emailv);]
 $res2 = $doc->saveHTML($addressv);
 $res3 = $doc->saveHTML($cc_emailv);
 $res4 = $doc->saveHTML($labelv);
?>