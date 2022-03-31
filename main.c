#include <stdio.h>
#include "ft_printf.h"
#include <limits.h>
#include <float.h>

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
  //char *str = "%0-8.5u";
 /*  printf("%0 d", 42); 
  printf("%0 d", -42);
  printf("% 0d", 42); 
  printf("% 0d", -42); */
 ft_printf("%7d", -14);
 /*     ft_printf("FT D:% 8i\n", 42);
    printf("PF D:% 8i\n\n", 42);

    ft_printf("FT D:% -8i\n", 42);
    printf("PF D:% -8i\n\n", 42);

   ft_printf("FT D:%+i\n", 42);
    printf("PF D:%+i\n\n", 42);


    ft_printf("FT C: %c\n", 0);
    printf("PF C: %c\n\n", 0);

    ft_printf("FT D:{%03d}\n", 0);
    printf("PF D:{%03d}\n\n", 0);

    ft_printf("FT D:{%010.5d}\n", -216);
    printf("PF D:{%010.5d}\n\n", -216);


    ft_printf("FT X: %#2.8x\n", 34);
    printf("PF X: %#2.8x\n\n", 34);
    ft_printf("FT X: %#02.8x\n", 42);
    printf("PF X: %#02.8x\n\n", 42);



    ft_printf("FT O:%#08o\n", 42);
    printf("PF O:%#08o\n\n", 42);
    ft_printf("FT X: %#08.5x\n", 42);
    printf("PF X: %#08.5x\n\n", 42);
    ft_printf("FT X: %#8.5x\n", 42);
    printf("PF X: %#8.5x\n\n", 42);

    ft_printf("FT D: % 0i\n", 0);
    printf("PF D: % 0i\n\n", 0);

    ft_printf("FT D: % 0i\n", 42);
    printf("PF D: % 0i\n\n", 42);


    
    ft_printf("FT D: % 08i\n", 42);
    printf("PF D: % 08i\n\n", 42);

    ft_printf("FT *S:{%.*s}\n", 0, "hello");
    printf("PF *S:{%.*s}\n\n", 0, "hello");

    ft_printf("FT S:{%.0s}\n", "hello");
    printf("PF S:{%.0s}\n\n", "hello");

     ft_printf("FT S:{%-5.s}\n","42");
    printf("PF S:{%-5.s}\n\n","42");
 */
/*     ft_printf("FT O:%#-08o\n", 42);
    printf("PF O:%#-08o\n\n", 42); */
    
/*     ft_printf("FT O: %#08.2o\n", 42);
    printf("PF O: %#08.2o\n\n", 42);

    ft_printf("FT D: %#08d\n", 0);
    printf("PF D: %#08d\n\n", 0); */
  //ft_printf("%5+d", 42);
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

//int main ()
//{
    //ft_printf("FT D:% 8i\n", 42);
    /* printf("PF D:% 8i\n\n", 42);

    ft_printf("FT D:% -8i\n", 42);
    printf("PF D:% -8i\n\n", 42);

   ft_printf("FT D:%+i\n", 42);
    printf("PF D:%+i\n\n", 42);


    ft_printf("FT C: %c\n", 0);
    printf("PF C: %c\n\n", 0);

    ft_printf("FT D:{%03d}\n", 0);
    printf("PF D:{%03d}\n\n", 0);

    ft_printf("FT D:{%010.5d}\n", -216);
    printf("PF D:{%010.5d}\n\n", -216);


    ft_printf("FT X: %#2.8x\n", 34);
    printf("PF X: %#2.8x\n\n", 34);
    ft_printf("FT X: %#02.8x\n", 42);
    printf("PF X: %#02.8x\n\n", 42);



    ft_printf("FT O:%#08o\n", 42);
   printf("PF O:%#08o\n\n", 42);
    ft_printf("FT X: %#08.5x\n", 42);
    printf("PF X: %#08.5x\n\n", 42);
    ft_printf("FT X: %#8.5x\n", 42);
    printf("PF X: %#8.5x\n\n", 42);

    ft_printf("FT D: % 0i\n", 0);
    printf("PF D: % 0i\n\n", 0);

    ft_printf("FT D: % 0i\n", 42);
    printf("PF D: % 0i\n\n", 42);


    
    ft_printf("FT D: % 08i\n", 42);
    printf("PF D: % 08i\n\n", 42);

    ft_printf("FT *S:{%.*s}\n", 0, "hello");
    printf("PF *S:{%.*s}\n\n", 0, "hello");

    ft_printf("FT S:{%.0s}\n", "hello");
    printf("PF S:{%.0s}\n\n", "hello");

    ft_printf("FT *S:{%.*s}\n", -5, "42");
    printf("PF *S:{%.*s}\n\n", -5, "42");

    ft_printf("FT S:{%-5.s}\n","42");
    printf("PF S:{%-5.s}\n\n","42");

    ft_printf("FT O:%#-08o\n", 42);
    printf("PF O:%#-08o\n\n", 42);
    
    ft_printf("FT O: %#08.2o\n", 42);
    printf("PF O: %#08.2o\n\n", 42);

    ft_printf("FT D: %#08d\n", 0);
    printf("PF D: %#08d\n\n", 0);
 */
    //return (0);
//} 