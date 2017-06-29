#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int handle_io(int connfd)
{

	return 0;
}

int main(int args, char *argv[])
{
	int		ret;
	char	*host = "192.168.1.46";
	int		port = 8010;
	struct	sockaddr_in client;

	while( (ch = getopt(args, argv, "s:p:")) != -1)
	{
		switch(ch)
		{
		case 's':
			host = optarg;
			break;
		case 'p':
			port = atoi(optarg);
			break;
		default:
			break;
		}
	}

	connfd = socket(AF_INET, SOCK_STREAM, 0);
	if(connfd == -1)
	{
		fprintf(stderr, "fail to socket: %s\n", strerror(errno));
		exit(-1);
	}

	memset(&client, 0, sizeof(client));	
	client.sin_family = AF_INET;
	client.sin_port = htons(port);
	client.sin_addr.s_addr = inet_addr(host);

	ret = connect(connfd, (struct sockaddr *)&client, sizeof(client));
	if(ret == -1)
	{
		fprintf(stderr, "fail to connect: %s\n", strerror(errno));
		exit(-1);
	}

	
	exit(0);
}

