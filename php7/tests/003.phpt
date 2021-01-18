--TEST--
opaque_test3() Basic test
--SKIPIF--
<?php
if (!extension_loaded('opaque')) {
	echo 'skip';
}
?>
--FILE--
<?php
$r=opaque_create_registration_request("simple guessable dictionary password");
$alpha = $r[0];
$ctx = $r[1];
$r=opaque_create_registration_response($alpha);
$rsec = $r[0];
$rpub = $r[1];
$cfg = [opaque_InSecEnv, opaque_InSecEnv, opaque_InSecEnv, opaque_InSecEnv, opaque_InSecEnv];
$r=opaque_finalize_request($ctx, $rpub, "user", "server", $cfg);
$rrec = $r[0];
$export_key = $r[1];
$rec = opaque_store_user_record($rsec, $rrec);
$r=opaque_create_credential_request("simple guessable dictionary password");
$sec = $r[0];
$pub = $r[1];
$r=opaque_create_credential_response($pub, $rec, "user", "server", $cfg);
$resp=$r[0];
$sk=$r[1];
$ctx=$r[2];
$r=opaque_recover_credentials($resp, $sec, $cfg);
$sk=$r[0];
$authU=$r[1];
$export_key=$r[2];
$idU=$r[3];
$idS=$r[4];
var_dump(opaque_user_auth($ctx, $authU));
?>
--EXPECT--
bool(true)