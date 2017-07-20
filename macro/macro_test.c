#include <stdio.h>

#define println(fmt, ...) ({ printf(fmt "\n", __VA_ARGS__);})
#define debug(fmt, ...) ({ printf("%s:"fmt"\n", __func__,__VA_ARGS__);})
#define debug01(...) printf(__VA_ARGS__)

#define debug02(fmt, ...) printf("%s:"fmt"\n", __func__, ##__VA_ARGS__)
int main()
{
	println("Hello this is line: %d", 12345);
	debug("hello: %s", "sdd");
	debug01("HelloWorld\n");

	debug02("greate");

	return 0;
}
