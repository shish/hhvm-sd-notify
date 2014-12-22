HHVM_EXTENSION(sd_notify sd_notify.cpp)
target_link_libraries(sd_notify systemd)
HHVM_SYSTEMLIB(sd_notify ext_sd_notify.php)
