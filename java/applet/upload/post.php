<?php
$fp = fopen('data.txt', 'w');

ob_start();
print_r($_POST);
print_r($_GET);
print_r($_FILES);
fwrite($fp, ob_get_contents());
ob_end_clean();
fclose($fp);

?>
