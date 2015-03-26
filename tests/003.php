<?php
$decompressed = lzf_decompress(base64_decode("BFRoaXMgIAIUdGVzdCBvZiBMWkYgZXh0ZW5zaW9u"));

echo $decompressed;
?>
