<?php¬
  // generate a random number and serve it as JSON
  $hash = array();¬
  $hash['number'] = floor(rand(0,999));¬
  echo json_encode($hash);¬
?>¬