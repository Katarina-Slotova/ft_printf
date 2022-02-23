#include <stdio.h>
#include "ft_printf.h"

int main ()
{
    //char *x = "hello";
    //const char * y = "monkeys";

	//int x = 12;
	//int *ptr = &x;
	int num = 0;
	printf("The address is: %09o.\n", num);
    /* Demonstrate with numbers. */
    //ft_printf ("<%s> is not justified.\n", x);
    //printf ("<%5d> is right-justified.\n", x);
    //printf ("<%-2d> The minus sign makes it left-justified.\n", x);
    /* Demonstrate with strings. */
    //printf ("'%s' is not justified.\n", y);
    //printf ("'%10s' is right-justified.\n", y);
    //printf ("'%-10s' is left-justified using a minus sign.\n", y);

    return 0;
}