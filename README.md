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
