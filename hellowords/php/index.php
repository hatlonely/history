<?php

$soap = new SoapClient(null, array(
            "location"=>"http://localhost/soapserver.php",
            "uri"=>"soapserver.php"));

echo $soap->helloWords();
