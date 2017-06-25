#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int func(int a, int b)
{
	printf("a: %d, b: %d\n", a, b);
	return 0;
}


// __VA_ARGS__ 可变参数  
#define debug(...) printf(__VA_ARGS__)   //C99 支持 ?

#define COUNT_PARMS2(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _, ...) _  
#define COUNT_PARMS(...) COUNT_PARMS2(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)  
      
static void print_strings2(int count, ...)  
{  
    int i;  
      
    va_list v;  
    va_start(v, count);  
      
    for (i = 0; i < count; i++)  
    {  
        /* Grab next parameter + print it */  
        const char *s = va_arg(v, const char *);  
        printf("%s", s);  
    }  
	printf("\n") ;     
    va_end(v);  
}  
  
#define print_strings(...)  print_strings2(COUNT_PARMS(__VA_ARGS__), __VA_ARGS__)

void overload1(int p1)  
{  
    printf("One param: %d\n", p1);  
}  
  
void overload2(double p1, char* p2)  
{  
    printf("Two params: %f %s\n", p1, p2);  
}  
  
void overload3(int p1, int p2, int p3)  
{  
    printf("Three params: %d %d %d\n", p1, p2, p3);  
}  
  
void count_overload_aux(int count, ...)  
{  
    va_list v;  
    va_start(v, count);  
      
    switch(count)  
    {  
    	case 0:
		{
			fprintf(stderr, "0 param\n");
			break;
		}
	    case 1:  
        {  
            int p1 = va_arg(v, int);  
            overload1(p1);  
            break;  
        }  
          
        case 2:  
        {  
            double p1 = va_arg(v, double);  
            char *p2 = va_arg(v, char *);  
            overload2(p1, p2);  
            break;  
        }  
          
        case 3:  
        {  
            int p1 = va_arg(v, int);  
            int p2 = va_arg(v, int);  
            int p3 = va_arg(v, int);  
            overload3(p1, p2, p3);  
            break;  
        }  
      
        default:  
        {  
            va_end(v);  
              
            printf("Invalid arguments to function 'count_overload()'\n");  
            exit(1);  
        }  
    }  
      
    va_end(v);  
}  
#define count_overload(...) count_overload_aux(COUNT_PARMS(__VA_ARGS__), __VA_ARGS__) 
//#define count_overload() count_overload_aux(0)

int main()
{
	func(2, 3);

	debug("Hello: %s\n", "Gogo");

	print_strings("hello", "grunt", "tambo", "wollen");

	count_overload(23);
	count_overload(12, 20, 34);
	count_overload(34.8, "price");

	//count_overload(void);

	return 0;
}
