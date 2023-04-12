
This project aims to test sVirt protection on VM escape.
We use socket to simulate VM escape instead of reproducing really VM escape.

## How to use
1. Copy this project to /root dir of both host and vm.
2. Make sure network connection between vm and host is available and PORT 28080 is open.
3. Change /root/test-svirt/vm.c SERVER_IP to host IP.
4. Change host SElinux to Permissive mode.
5. Login to host shell, exec 'bash make.sh' in /root/test-svirt, then exec './server_utils'.
6. Login to vm shell, exec 'bash make.sh' in /root/test-svirt, then exec './vm_escape'.
7. VM 'escape' shoule be success, following output shows on vm shell:
```shell
Set selinux context success!
I am an escaped process! My selinux label is: system_u:system_r:svirt_t:s0:c97,c105
Now I want to attack host file!
Attack host succeed!
Now I want to attack VM file!
Attack VM succeed!
Now I want to execute shell command: 'getenforce'！
Permissive
Exec getenforce success!
Exec attack success!
---------------------------------------------------------------------
```
8. Login to host shell, exec 'setenforce 1', enable sVirt protection.
9. Login to vm shell, exec './vm_escape', the escape would be stopped with follow output:
```shell
Set selinux context success!
Exec attack failed!
Stop vm escape successfully!
---------------------------------------------------------------------
```
