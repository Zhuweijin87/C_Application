#include <stdio.h>

int main(){
    #if _WIN32
        printf("Windows: http://c.biancheng.net\n");
    #elif __linux__
        printf("Linux: http://c.biancheng.net\n");
    #else
        printf("Notdefine: http://c.biancheng.net\n");
    #endif
    return 0;
}

