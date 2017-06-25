#include <stdio.h>
#include <string.h>

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
	fcntl(sockfd, F_GETFD);
	
}

int main(int args, char *argv[])
{
	int		ret;
	int 	sockfd;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		fprintf(stderr, "fail to socket: %s\n", strerror(errno));
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr_s_addr = inet_addr(host);

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
