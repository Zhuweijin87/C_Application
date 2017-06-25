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
	int				maxfd;
	int				fdsets[MAX_CLIENTS];
	fd_set			readfds, allfds;
	struct timeval	tv;

	FD_ZERO(&allfds);
	FD_SET(listenfd, &allfds);
	
	for ( ; ; )
	{
		readfds = allfds;
		tv.tv_sec = 10;
		tv.tv_usec = 0;
		numOfCli = select(maxfd, &readfds, NULL, NULL, &tv);
		if(numOfCli == -1)
		{
			fprintf(stderr, "select error: %s\n", strerror(errno));
			return -1;
		}
		
		if(numOfCli == 0)
		{
			continue;
		}

		if(FD_ISSET(listenfd, &readfds))
		{
			/* handle Accept */
			handle_accpet();
		}
		else
		{
			/* handle Read/Write */
			handle_recv();
		}	
	}

	return 0;
}

int handle_accpet(int listenfd, int *fdsets, fd_set *readfds, fd_set *allfds)
{
	int		clifd;
	struct sockaddr_in client;
	socklen_t	clientlen;
	
	clientlen = sizeof(struct sockaddr_in);
	clifd = accept(listenfd, (struct sockaddr *)&client, &clientlen);
	if(clifd == -1)
	{
		return -1;
	}

	for(i=0; i<MAX_CLIENTS; i++)
	{
		if(fdsets[i] == -1)
		{
			fdsets[i] = clifd;
			FD_SET(clifd, allfds);
		}
	}

	return 0;
}

int handle_read(int numOfCli, int *fdsets, fd_set *allfds)
{
	int 	len, i;
	char	buf[1028] = {'\0'};

	for(i=0; i<numOfCli; i++)
	{
		if(FD_ISSET(fdset[i], allfds))
		{
			memset(buf, 0, sizeof(buf));
			len = read(fdset[i], buf, 1024);
			if(len == -1)
			{
				fprintf(stderr, "recv error:%s\n", strerror(errno));
				FD_CLR(fdset[i], allfds);
				fdset[i] = -1;
			}
			else if(len == 0)
			{
				fprintf(stderr, "client[%d] closed\n", fdset[i]);
				FD_CLR(fdset[i], allfds);
				fdset[i] = -1;
			}
			else
			{
				fprintf(stderr, "recv: %s\n", buf);
			}
		}
	}
	return 0;
}

int main(int args, char *argv[])
{

	return 0;
}

