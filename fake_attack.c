/*
 * @Author: zhang_yeda@163.com
 * @Date: 2023-02-17 17:25:12
 * @LastEditors: Zhang Yeda
 * @LastEditTime: 2023-03-09 15:53:02
 * @FilePath: /test-svirt/fake_attack.c
 * @Description: Licensed under the Apache License, Version 2.0, January 2004.
 * 
 * Copyright (c) 2023 by Zhang Yeda, All Rights Reserved. 
 */

#include<selinux/selinux.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

typedef char *security_context_t;

int main(int argc, char const* argv[]) 
{
	FILE *fp;
	security_context_t process_context;
	getcon(&process_context);
	printf("I am an escaped process! My selinux label is: %s\n", process_context);

	printf("Now I want to attack host file!\n");
	fp = fopen("/root/anaconda-ks.cfg", "r+");
	if (fp == NULL)
			printf("Attack host failed!\n");
	else {
			printf("Attack host succeed!\n");
			fclose(fp);
	}

	printf("Now I want to attack VM file!\n");
	fp = fopen("/root/test-svirt/test.qcow2", "rb");
	if (fp == NULL)
			printf("Attack VM failed!\n");
	else {
			printf("Attack VM succeed!\n");
			fclose(fp);
	}

	printf("Now I want to execute shell command: 'getenforce'！\n");
	int exec_res = 0;
	exec_res = system("/usr/sbin/getenforce");
	if (exec_res != 0) {
		perror("Exec getenforce failed");
		return -1;
	} else {
		printf("Exec getenforce success!\n");
	}
	
	return 0;
}
