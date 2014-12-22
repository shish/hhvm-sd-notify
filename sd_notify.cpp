/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-2013 Facebook, Inc. (http://www.facebook.com)     |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include "hphp/runtime/base/base-includes.h"
#include <systemd/sd-daemon.h>

namespace HPHP {

static int HHVM_FUNCTION(sd_notify, char *notify) {
  return sd_notify(0, notify);
}
static int HHVM_FUNCTION(sd_notify_ready) {
  return sd_notify(0, "READY=1");
}
static int HHVM_FUNCTION(sd_notify_status, char *status) {
  return sd_notifyf(0, "STATUS=%s", status);
}
static int HHVM_FUNCTION(sd_notify_errno, int64_t errno) {
  return sd_notifyf(0, "ERRNO=%ld", errno);
}
static int HHVM_FUNCTION(sd_notify_buserror, int64_t err) {
  return sd_notifyf(0, "BUSERROR=%ld", err);
}
static int HHVM_FUNCTION(sd_notify_mainpid, int64_t pid) {
  return sd_notifyf(0, "MAINPID=%ld", pid);
}
static int HHVM_FUNCTION(sd_notify_watchdog) {
  return sd_notify(0, "WATCHDOG=1");
}

static class SdNotifyExtension : public Extension {
 public:
  SdNotifyExtension() : Extension("sd_notify") {}
  virtual void moduleInit() {
    HHVM_FE(sd_notify);
    HHVM_FE(sd_notify_ready);
    HHVM_FE(sd_notify_status);
    HHVM_FE(sd_notify_errno);
    HHVM_FE(sd_notify_buserror);
    HHVM_FE(sd_notify_mainpid);
    HHVM_FE(sd_notify_watchdog);
    loadSystemlib();

    sd_notify(0, "READY=1");
    sd_notify(0, "STATUS=PHP sd_notify loaded");
  }
} s_sd_notify_extension;

HHVM_GET_MODULE(sd_notify)

} // namespace HPHP
