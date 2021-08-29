# Eltex summer school
## Executed tasks:
:one: Bitwise operations - :heavy_check_mark:    
:two: Two-dimensional arrays - :heavy_check_mark:    
:three: Static phone directory - :heavy_check_mark:    
:four: Dynamic phone directory - :heavy_check_mark:    
:five: Password cracking, stack overflow - :x:    
:six: Calculator (static lib) - :heavy_check_mark:    
:seven: Calculator (dynamic lib) - :heavy_check_mark:    
:eight: Calculator (plagin dlopen) - :heavy_check_mark:    
:nine: File manager - :heavy_check_mark:    
:keycap_ten: Text editor - :heavy_check_mark:    
:one::one: Process management - :heavy_check_mark:    
:one::two: Thread - :heavy_check_mark:    
:one::three: Shop thread - :heavy_check_mark:    
:one::four: Command Interpreter - :heavy_check_mark:    
:one::five: Message queues - :heavy_check_mark:    
:one::six: Chat - :heavy_check_mark:    
:one::seven: Client-Server (socket) - :heavy_check_mark:    
:one::eight: Broadcast (socket) - :heavy_check_mark:    
:one::nine: Multicast (socket) - :heavy_check_mark:    
:two::zero: UDP-server Echo, RAW-client - :heavy_check_mark:    
:two::one: IP-header, UDP-server, RAW-client - :heavy_check_mark:    
:two::two: Eth-header, UDP-server, RAW-client - :heavy_check_mark:    
:two::three: Build kernel - :heavy_check_mark:    
:two::four: Kernel module - :x:   
    
##Static library
> gcc file1.c -c
> gcc file2.c
> ar rc **lib (bold)**myname.a file1.o file2.o
> gcc test.c -o test -L. -lmyname
> ./test
