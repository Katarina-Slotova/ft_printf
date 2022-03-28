#include <stdio.h>
#include "ft_printf.h"
#include <limits.h>

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
	//char *x = "%";
/* 	ft_printf("%s%s%s%s%s\n", "1", "2", "3", "4", "5");
	ft_printf("111%s333%s555\n", "222", "444");
	ft_printf("111%s333%s555%saaa%sccc\n", "222", "444", "666", "bbb"); */
/* 	int						len;
	int						len2;
	char 					*str;
	str = "\t|{%}|\n";
	printf("\n1. mine, 2. unix: Testing moulitest tests 49:\n");
	len = ft_printf(str, 0);
	len2 = printf(str, 0); */
	//ft_printf("%10d\n", 42);
	//char *str = "%0-8.5x";
/*   ft_printf("\\n");
  ft_printf("%%\\n");
  ft_printf("%d\\n", 42);
  ft_printf("%d%d\\n", 42, 41);
  ft_printf("%d%d%d\\n", 42, 43, 44);
  ft_printf("%ld\\n", 2147483647);
  ft_printf("%lld\\n", 9223372036854775807);
  ft_printf("%x\\n", 505);
  ft_printf("%X\\n", 505);
  ft_printf("%p\\n", &ft_printf);
  ft_printf("%20.15d\\n", 54321);
  ft_printf("%-10d\\n", 3);
  ft_printf("% d\\n", 3);
  ft_printf("%+d\\n", 3);
  ft_printf("%010d\\n", 1);
  ft_printf("%hhd\\n", 0);
  ft_printf("%jd\\n", 9223372036854775807);
  ft_printf("%zd\\n", 4294967295);
  ft_printf("%\\n");
  ft_printf("%U\\n", 4294967295);
  ft_printf("%u\\n", 4294967295);
  ft_printf("%o\\n", 40);
  ft_printf("%%#08x\\n", 42);
  ft_printf("%x\\n", 1000);
  ft_printf("%#X\\n", 1000);
  ft_printf("%s\\n", NULL);
  ft_printf("%S\\n", L"ݗݜशব");
  ft_printf("%s%s\\n", "test", "test");
  ft_printf("%s%s%s\\n", "test", "test", "test");
  ft_printf("%C\\n", 15000); */
  //int str = 1.0/0;
  ft_printf("%.1Lf", 0.05l);
  //long double my_var = 454423.343242374423425L;
	//printf("{%-12p}", &strlen);
	//printf("%30d", 10000);
	//double y = 0;
	//ft_printf("%%f '%10.f'\n", -0.0);
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