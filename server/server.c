#include "../erproc.h"

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int server = Socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in adr = {0};
	adr.sin_family = AF_INET;
	adr.sin_port = htons(728);
	Bind(server, (struct sockaddr *) &adr, sizeof adr);
	Listen(server, 5);
	socklen_t adrlen = sizeof adr;
	int fd = Accept(server, (struct sockaddr *) &adr, &adrlen); // adr now is absolut another variable (rewrite for new actions)

	write(STDOUT_FILENO, "CONNECTED\n\n", 11);
	
	char buf[256];
	ssize_t nread;

	//do
	//{
	
	//nread = 0;
	//memset (buf, '0', sizeof buf);

	nread = read(fd, buf, 256);

	if (nread == -1)
	{
		perror("read failed");
		exit(EXIT_FAILURE);
	}

	if (nread == 0)
	{
		printf("END OF FILE\n");
		
	}

	write(STDOUT_FILENO, buf, nread);
	write(fd, buf, nread); // Return message to client

	sleep(1);

	//}
	//while(strcmp(buf, "exit") != 0);

	//sleep(10);

	close(fd);
	close(server);

	return 0;
}
