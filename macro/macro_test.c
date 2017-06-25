#include <stdio.h>

#define println(fmt, ...) ({ printf(fmt "\n", __VA_ARGS__);})

int main()
{
	println("Hello this is line: %d", 12345);

	return 0;
}
