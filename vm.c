/*
 * @Author: zhang_yeda@163.com
 * @Date: 2023-02-23 16:27:48
 * @LastEditors: Zhang Yeda
 * @LastEditTime: 2023-03-09 17:25:30
 * @FilePath: /test-svirt/vm.c
 * @Description: Licensed under the Apache License, Version 2.0, January 2004.
 * 
 * Copyright (c) 2023 by Zhang Yeda, All Rights Reserved. 
 */


#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 28080
#define SERVER_IP "127.0.0.1"
#define MAX_LENGTH 4096

int main(int argc, char const* argv[])
{
	int status, valread, client_fd;
	struct sockaddr_in serv_addr;
	char* cmd = "fake_escape";
	char buffer[MAX_LENGTH] = { 0 };
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Attack channel creation error");
		exit(EXIT_FAILURE);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
		perror("Invalid server address or server address not supported");
		exit(EXIT_FAILURE);
	}

	if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
		perror("Attack channel connection Failed");
		exit(EXIT_FAILURE);
	}
	send(client_fd, cmd, strlen(cmd), 0);
	printf("Start attack ...\n");

	// closing the attack channel
	close(client_fd);
	return EXIT_SUCCESS;
}
