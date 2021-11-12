cmd_/home/linux-test/aks_linux_modules/modules.order := {   echo /home/linux-test/aks_linux_modules/mymodule.ko; :; } | awk '!x[$$0]++' - > /home/linux-test/aks_linux_modules/modules.order
