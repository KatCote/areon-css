#include "../erproc.h"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int fd = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in adr = {0};
	adr.sin_family = AF_INET;
	adr.sin_port = htons(728);
	Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr);
	Connect(fd, (struct sockaddr *) &adr, sizeof adr);
	 
	char msg[256];
	scanf("%256[^\n]", msg);
	write(fd, msg, strlen(msg));
	char buf[256];
	ssize_t nread;
	nread = read(fd, buf, 256);

	if (nread == -1)
	{
		perror("read failed");
		exit(EXIT_FAILURE);
	}
	if (nread == 0)
	{
		printf("EOF occured\n");
	}

	write(STDOUT_FILENO, buf, nread);
	sleep(1);
	close(fd);

	return 0;
}
