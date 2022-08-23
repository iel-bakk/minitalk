# MINITALK 
    
### About signal() syscall :
##### Description :

The C library function void (*signal(int sig, void (*func)(int)))(int) sets a function to handle signal i.e. a signal handler with signal number sig.

##### Declaration :

Following is the declaration for signal() function.

```
void (*signal(int sig, void (*func)(int)))(int)
```
##### Parameters :

sig − This is the signal number to which a handling function is set. The following are few important standard signal numbers −

###### We can get the list of signals supported on our unix/linux systeme by using the following command :
```
$> kill -l
```
```
HUP INT QUIT ILL TRAP ABRT EMT FPE KILL BUS SEGV SYS PIPE ALRM TERM URG STOP TSTP CONT CHLD TTIN TTOU IO XCPU XFSZ VTALRM PROF WINCH INFO USR1 USR2
``` 
    
