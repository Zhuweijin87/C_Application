#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define exit_if(r, ...) if(r) {printf(__VA_ARGS__); \
			printf("%s:%d error no: %d error msg %s\n", __FILE__, __LINE__, errno, strerror(errno)); exit(1);}

int main()
{
	exit_if(1, "function occur error: %d", 10000);
	
	printf("next string\n");

	return 0;
}
