/*
 * @Author: zhang_yeda@163.com
 * @Date: 2023-02-23 16:27:48
 * @LastEditors: Zhang Yeda
 * @LastEditTime: 2023-03-09 17:25:57
 * @FilePath: /test-svirt/server.c
 * @Description: Licensed under the Apache License, Version 2.0, January 2004.
 * 
 * Copyright (c) 2023 by Zhang Yeda, All Rights Reserved. 
 */

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


#define PORT 28080
#define MAX_LENGTH 4096

int main(int argc, char const* argv[])
{
	int server_fd, conn_fd, num_read, exec_res;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[MAX_LENGTH] = { 0 };
	char cmd[MAX_LENGTH] = { 0 };

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Channel creation failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("Channel attaching failed");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		perror("Channel bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 10) < 0) {
		perror("Channel listen failed");
		exit(EXIT_FAILURE);
	}
	
	printf("------------------------------Start test----------------------------------\n");
	printf("--------------------Ctrl+C to quit server_utils---------------------------\n");
	while (1) {
		if ((conn_fd = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
			perror("Message accept failed");
			exit(EXIT_FAILURE);
		}
		num_read = recv(conn_fd, buffer, MAX_LENGTH, 0);
		buffer[num_read] = '\0';

		sscanf(buffer, "%s", cmd);
		if (strcmp(cmd, "fake_escape") == 0) {
			exec_res = system("/root/test-svirt/fake_escape");
			if (exec_res != 0) {
				printf("Stop vm escape successfully!\n");
				printf("---------------------------------------------------------------------\n");
		    }
		} else {
		    // print cmd
			printf("%s\n", cmd);
			if (strcmp(cmd, "quit") == 0) {
				break;
			}
		}

		// closing the connected socket
		close(conn_fd);
	}
	
	// closing the listening socket
	printf("------------------------------End test----------------------------------\n");
	shutdown(server_fd, SHUT_RDWR);
	return EXIT_SUCCESS;
}
