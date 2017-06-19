/* select 网络服务 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define LISTEN_Q_MAX	20
#define MAX_CLIENTS		1024

int socket_listen(char *host, int port)
{
	int		ret, listenfd;
	struct sockaddr_in server;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd < 0)
	{
		fprintf(stderr, "fail to socket: %s\n", strerror(errno));
		return -1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(host);
	
	ret = bind(listenfd, (struct sockaddr *)&server, sizeof(server));
	if(ret < 0)
	{
		fprintf(stderr, "fail to bind: %s\n", strerror(errno));
		close(listenfd);
		return -1;
	}

	ret = listen(listenfd, LISTEN_Q_MAX);
	if(ret < 0)
	{
		fprintf(stderr, "listen error: %s\n", strerror(errno));
		close(listenfd);
		return -1;
	}

	return listenfd;
}

int socket_select(int listenfd)
{
	int			fd[MAX_CLIENTS];
	fd_set		fdsets;

	for ( ; ; )
	{
		numOfCli = select(maxfd, readfds, NULL, NULL, tv);
		if(numOfCli == -1)
		{
			fprintf(stderr, "seelct error: %s\n", strerror(errno));
			return -1;
		}
		
		if(numOfCli == 0)
		{
			continue;
		}

		
	}

	return 0;
}

int main(int args, char *argv[])
{

	return 0;
}

