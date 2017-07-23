#include <stdio.h>

#define println(fmt, ...) ({ printf(fmt "\n", __VA_ARGS__);})
#define debug01(fmt, ...) ({ printf("%s:"fmt"\n", __func__,__VA_ARGS__);})
#define debug02(...) printf(__VA_ARGS__)

#define debug(fmt, ...) printf("%s:debug:"fmt"\n", __func__, ##__VA_ARGS__)
#define warn(fmt, ...) printf("%s:warn:"fmt"\n", __func__, ##__VA_ARGS__)
#define info(fmt, ...) printf("%s:info:"fmt"\n", __func__, ##__VA_ARGS__)

#define DEBUG	1
#define WARN	2
#define INFO	3

#define log(level, fmt, ...)	do { \
									if(level == DEBUG) \
										debug(fmt, ##__VA_ARGS__); \
									else if(level == WARN) \
										warn(fmt, ##__VA_ARGS__); \
									else \
										info(fmt, ##__VA_ARGS__); \
								} while(0)
							
int main()
{
	println("Hello this is line: %d", 12345);
	debug01("hello: %s", "sdd");
	debug02("HelloWorld\n");

	debug02("greate");

	log(DEBUG, "Hello");
	log(INFO, "Hello Info message");
	log(WARN, "hello time warn");

	return 0;
}
