#include <stdio.h>
#include "ft_printf.h"

int main ()
{
    //char *x = "hello";
    //const char * y = "monkeys";

	//int x = 12;
	//int *ptr = &x;
	//int num = 42;
	//char c = 23450;
	//long x = 2147483648;
	//ft_printf("%%.f '%.f' %%.0f '%.0f' %%.1f '%.1f' %%.10f '%.10f' %%.15f '%.15f'\n", 0.005, 0.005, 0.005, 0.005, 0.005);
	//printf("%0 d", 42);
	//double x = 0;
	//double y = 0;
	ft_printf("%%f '%10.f'\n", -0.0);
	//double v = .2012685;
	//printf("   printf: %.6f\n", v);
	//ft_printf("ft_printf: %.6f\n", v);

	// check num 1.135
	// new_num: 113.5
	// diff: 0.5
	//	if diff >= 0.5 -> (int)new_num + 1
	// else             -> (int)new_num

	// (int)new_num + 1  = 114 -> even -> round 1.14
	
	//printf("%.2f\n", 1.145);
	// check num 1.145
	// new_num: 114.5
	// diff: 0.5
	// (int)new_num + 1  = 115 -> odd -> trim 1.14 
	
	//ft_printf("|%.d|", 0);
	//ft_printf("%Lf\n", -0.0L);
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