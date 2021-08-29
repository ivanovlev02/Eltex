cmd_/home/lion/My_Kernel/modules/modules.order := {   echo /home/lion/My_Kernel/modules/hello.ko; :; } | awk '!x[$$0]++' - > /home/lion/My_Kernel/modules/modules.order
