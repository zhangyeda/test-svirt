#!/bin/sh
###
 # @Author: zhang_yeda@163.com
 # @Date: 2023-02-17 17:31:24
 # @LastEditors: Zhang Yeda
 # @LastEditTime: 2023-03-09 15:03:48
 # @FilePath: /test-svirt/make.sh
 # @Description: Licensed under the Apache License, Version 2.0, January 2004.
 # 
 # Copyright (c) 2023 by Zhang Yeda, All Rights Reserved. 
### 

touch test.qcow2
gcc -g -lselinux ./fake_escape.c -o fake_escape
gcc -g -lselinux ./fake_attack.c -o fake_attack
gcc -g ./vm.c -o vm_escape
gcc -g ./server.c -o server_utils
