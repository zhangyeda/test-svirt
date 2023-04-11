/*
 * @Author: zhang_yeda@163.com
 * @Date: 2023-02-17 15:10:05
 * @LastEditors: Zhang Yeda
 * @LastEditTime: 2023-03-09 15:59:09
 * @FilePath: /test-svirt/fake_escape.c
 * @Description: Licensed under the Apache License, Version 2.0, January 2004.
 * 
 * Copyright (c) 2023 by Zhang Yeda, All Rights Reserved. 
 */

#include<selinux/selinux.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main(int argc, char const* argv[])
{

    //set selinux lable
	const char *strlabel="system_u:system_r:svirt_t:s0:c97,c105";
	int res = 0;
	int exec_res = 0;
	res = setexeccon(strlabel);
	if (res == -1) {
		printf("Set selinux context failed!\n");
	}
	else
	{
		printf("Set selinux context success!\n");
		// exec fake attack
		exec_res = system("/root/test-svirt/fake_attack");
		if (exec_res != 0) {
			printf("Exec attack failed!\n");
			exec_res = -1;
		} else {
			printf("Exec attack success!\n");
			printf("---------------------------------------------------------------------\n");
		}
	}

	return exec_res;
}