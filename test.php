<?php
var_dump(extension_loaded("sd_notify"));
var_dump(function_exists("sd_notify_watchdog"));
var_dump(sd_notify_watchdog());
