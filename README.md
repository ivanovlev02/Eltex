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
    
## Static library
> gcc file1.c -c    
> gcc file2.c    
> ar rc **lib (bold)**myname.a file1.o file2.o    
> gcc test.c -o test -L. -lmyname    
> ./test    

## Dynamic library
> gcc -fPIC -c file1.c    
> gcc -fPIC -c file2.c    
> gcc -shared -o **lib (bold)**my_func.so file1.o file2.o    
> gcc -c main.c    
> gcc main.o -L. my_func -o main    
    
## Build kernel ARM
> apt-get update    
> cd /usr/src/linux/    
> ARCH=arm make menuconfig    
> make ARCH=arm multi_v7_defconfig    
> ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- make zImage
> qemu-system-arm -nographic -machine vexpress-a9 -k zImage
> qemu-system-arm -nographic -machine vexpress-a9 -kernel zImage -dtb 
vexpress-v2p-ca9.dtb -append "console=ttyS0"    
>> vexpress-v2p-ca9.dtb --> /urs/src/linux/arch/arm/boot/dts    
    
## File system
> QEMU_AUDIO_DRV=none qemu-sestem-arm -nographic -M vexpress-a9 -kernel zImage 
initrdramfs.cpio.gz -dtb vexpress-v2p-ca9.dtb -append "console=ttyS0"
    
## BusyBox
> cd busybox/    
> make menuconfig    
>> Settings->Cross compiler prefix->arm-linux-gnueabihf-    
    
> make defconfig    
> cd _install    
> make install    
> find . | cpio -o -H newc | gzip > initramfs.cpio.gz    

## UDP Header
![alt tag](https://2.bp.blogspot.com/-WEzVJxjLQNw/WRXYG7DhdQI/AAAAAAAAAVA/qmKBeplC1EQfIv5T9oxit8e79XDpD05SQCLcB/s1600/Screen%2BShot%2B2017-05-12%2Bat%2B9.09.56%2BPM.png)    
## TCP Header
![alt tag](https://2.bp.blogspot.com/-WEzVJxjLQNw/WRXYG7DhdQI/AAAAAAAAAVA/qmKBeplC1EQfIv5T9oxit8e79XDpD05SQCLcB/s1600/Screen%2BShot%2B2017-05-12%2Bat%2B9.09.56%2BPM.png)    
## IP Header
![alt tag](https://img.wonderhowto.com/img/99/78/63589085364482/0/hack-like-pro-networking-basics-for-aspiring-hacker-part-2-tcp-ip.w1456.jpg)    
## Ethernet Header
![alt tag](https://1.bp.blogspot.com/-4_335OfoWcg/WlgQ0DBQnqI/AAAAAAAABq8/nIJAtzo3vzYRTnbOwr_INFqJGprh9lXFQCLcBGAs/s1600/Ethernet%2B%2528DIX%2529%2Bframe%2B11111.png)
