cmd_/home/lion/My_Kernel/modules/Module.symvers := sed 's/\.ko$$/\.o/' /home/lion/My_Kernel/modules/modules.order | scripts/mod/modpost    -o /home/lion/My_Kernel/modules/Module.symvers -e    -w -T -
