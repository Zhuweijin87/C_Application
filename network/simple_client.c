#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>


int main(int args, char *argv[])
{
	int		ret;
	char	*host;
	int		port;

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

	
}
