hhvm-sd-notify
==============

A simple HHVM extension to supply `sd_notify()` and some simple helpers
(eg `sd_notify_watchdog()`)

Writing this for my own use as I've found that HHVM + various third party
extensions can sometimes lock up and not respond to any requests for
minutes at a time, which is very noticable on a site which gets thousands
of hits per second. With a call to `sd_notify_watchdog()` inserted into
the main path of the web app, we can have systemd automatically restart
hhvm if it goes for say 5 seconds without generating a successful response.

The extension will automatically call `sd_notify_ready()` when it is loaded,
which is a lie by a fraction of a second (we're still mid-initialisation,
but hhvm initialises very quickly), but is useful (the alternative
seems to be "wait until you are serving traffic, and have that trigger the
ready-to-serve-traffic message")

service example
---------------

```ini
# mysite-hhvm.service
[Unit]
Description=HHVM FastCGI application server
After=syslog.target network.target

[Service]
PIDFile=/run/hhvm/mysite.pid
User=www-data
Group=www-data
ExecStart=/usr/bin/hhvm --mode server -vPidFile=/run/hhvm/mysite.pid --config=/etc/hhvm/mysite.hdf -vServer.Type=fastcgi -vServer.FileSocket=/tmp/php-mysite.socket
Restart=always

# automatically restart if we don't successfully serve at least one page per 10 seconds
Type=notify
WatchdogSec=10

[Install]
WantedBy=multi-user.target
```

page example
------------
With the call protected by `if(function_exists())` so that the same code also runs on vanilla PHP
```php
$app = new MyApp();
try {
  $app->run();
  
  // page was generated successfully; let systemd know we're ok
  if(function_exists("sd_notify_watchdog")) sd_notify_watchdog();
}
catch(Exception $e) {
  $app->log_error($e);
}
```
