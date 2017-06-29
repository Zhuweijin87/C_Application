#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

/* 设置服务端连接属性 */
int set_socket_opt(int sockfd)
{
	int             ret;

	/*reuse socket fd when closing the sock_fd in establish status*/
	int opt = 1;
	ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if(ret < 0){
		fprintf(stderr, "fail to set option to SO_REUSEADDR.(%d:%s)\n", errno, strerror(errno));
		return ret;
	}

	/*set send timeout when network exceptions occur*/
	int sndTimeout = 1000;  /* milseconds */
	ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &sndTimeout, sizeof(sndTimeout));
	if(ret < 0){
		fprintf(stderr, "fail to set option to SO_SNDTIMEO.(%d:%s)\n", errno, strerror(errno));
		return ret;
	}

	/*set recv timeout where network exceptions occur*/
	int rcvTimeout = 1000;
	ret = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &rcvTimeout, sizeof(rcvTimeout));
	if(ret < 0){
		fprintf(stderr, "fail to set option to SO_RCVTIMEO.(%d:%s)\n", errno, strerror(errno));
		return ret;
	}

	/*set send buffer size, system default about 8688 bytes, if buffer size is set to 0,
     buffer will not copy to system cache, it should be set before listen() or connect()*/
	int sndBufSize = 10 * 1024; /* 10KB */
	ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sndBufSize, sizeof(sndBufSize));
	if(ret < -1){
		fprintf(stderr, "fail to set option to SO_SNDBUF.\n");
		return ret;
	}

	/*set recv buffer size, as like above*/
	int rcvBufSize = 10 * 1024;
	ret = setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcvBufSize, sizeof(rcvBufSize));
	if(ret < 0){
		fprintf(stderr, "fail to set option to SO_RCVBUF.\n");
		return ret;
	}

	return 0;
}

/* 设置非阻塞 */
int set_socket_noblock(int sockfd)
{
	
	return 0;
}

/* 客户端读写 */
int handle_client_io(int clifd)
{
	int		n;
	char	buffer[512] = {'\0'};
	
	n = read(clifd, buffer, 512);
	if(n == -1)
	{

	}
	else if(n == 0)
	{
		fprintf(stderr, "client disconnect\n");
		close(clifd);
		return 0;
	}
	else
	{
		fprintf(stderr, "recv: %s\n", buffer);
	}

	return 0;
}

/* 处理链接请求 */
int handle_connection(int sockfd)
{
	int		clifd, quit = 0;
	struct	sockaddr_in 	client;
	socklen_t	clitlen;

	for(; quit != 1; )
	{
		memset(&client, 0, sizeof(client));
		clitlen = sizeof(client);
		clifd = accept(sockfd, (struct sockaddr *)&client, &clitlen);
		if(clifd == -1)
		{
			if(errno == EAGAIN)
			{
				continue;
			}
			fprintf(stderr, "accept fail: %s\n", strerror(errno));
			return -1;
		}
		
		handle_client_io(clifd);
	}
}

int main(int args, char *argv[])
{
	int		ret;
	int 	sockfd;
	char	ch;
	char	*host = "192.168.1.46";
	int		port = 8010;
	struct sockaddr_in	server;

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

	printf("Host:%s, Port:%d\n", host, port);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		fprintf(stderr, "fail to socket: %s\n", strerror(errno));
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(host);

	ret = bind(sockfd, (struct sockaddr *)&server, sizeof(server));
	if(ret == -1)
	{
		fprintf(stderr, "fail to bind: %s\n", strerror(errno));
		exit(1);
	}

	ret = listen(sockfd, 20);
	if(ret == -1)
	{
		fprintf(stderr, "fail to listen: %s\n", strerror(errno));
		exit(1);
	}

	exit(0);
}
