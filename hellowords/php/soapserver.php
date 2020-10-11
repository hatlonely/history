<?php

Class HelloWords
{
    public function helloWords() {
        global $wordsArray;
        return $wordsArray[rand(0, count($wordsArray) - 1)];
    }
}

$wordsArray = array();
$wordsFile = fopen("../data/one.txt", "r");
while (!feof($wordsFile)) {
    $line = fgets($wordsFile);
    if (strpos($line, "\t") > 0) {
        array_push($wordsArray, split("\t", substr($line, 0, strlen($line) - 1))[1]);
    }
}

$server = new SoapServer(null, array(
        "location"=>"http://localhost/soapserver.php",
        "uri"=>"soapserver.php"));
$server->setClass("HelloWords");
$server->handle();
