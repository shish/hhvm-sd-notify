<?hh
<<__Native>>
function sd_notify(string $notify): int;
<<__Native>>
function sd_notify_ready(): int;
<<__Native>>
function sd_notify_status(string $status): int;
<<__Native>>
function sd_notify_errno(int $errno): int;
<<__Native>>
function sd_notify_buserror(int $err): int;
<<__Native>>
function sd_notify_mainpid(int $pid): int;
<<__Native>>
function sd_notify_watchdog(): int;
