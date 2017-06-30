/* 获取主机信息 */
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int args, char *argv[])
{
	int		ret, i;
	char	ch;
	char	*netaddr = "www.sina.com.cn";
	struct hostent *ht = NULL;
	char	addr[31] = {'\0'};
	
	while( (ch = getopt(args, argv, "s:h:")) != -1 )
	{
		switch(ch)
		{
			case 's':
				netaddr = optarg;
				break;
			case 'h':
				break;
			default:
				break;
		}
	}

	printf("NetInfo: %s\n", netaddr);
	/* gethostbyname具有不可重复性 */
	ht = gethostbyname(netaddr);
	if(ht)
	{
		printf("Name: %s\n", ht->h_name);
		printf("Type: %s\n", ht->h_addrtype == AF_INET ? "AF_INET":"AF_INET6");
		printf("Length: %d\n", ht->h_length);

		/* IP地址信息 */
		for( i=0; ; i++)
		{
			if(ht->h_addr_list[i] == NULL)
				break;
			printf("IP:%s\n", inet_ntop(ht->h_addrtype, ht->h_addr_list[i], addr, 30)); 
		}

		/* 域名信息 */
		for(i=0; ; i++)
		{
			if(ht->h_aliases[i] == NULL)
				break;
			printf("Alias: %s\n", ht->h_aliases[i]);	
		}
	}

	return 0;
}

