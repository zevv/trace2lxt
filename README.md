
```
+ 166587792140971 evq.select
- 166587792253679 evq.select
+ 166587792279304 evq.timers
- 166587792301023 evq.timers
+ 166587792349669 evq.sockets 14
- 166587792946544 evq.sockets
+ 166587793039096 evq.select
- 166587794687847 evq.select
```

```
sudo perf record -a -e 'syscalls:*' --exclude-perf -e 'timer:*' --exclude-perf
sudo perf script --fields 'comm,tid,pid,time,event,trace' | ./perf2trace
```
