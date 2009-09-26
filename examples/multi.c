/* vim: set ts=4 sw=4 nowrap: */
/* compile:	gcc -Wall -g -c multi_test.c -o multi_test.o
			gcc -g -o multi_test multi_test.o -I/usr/include -L/usr/lib -lease
*/

/* Include the header files we need, especially ease.h */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ease.h>

/* . */
int show_step_multi(Ease_Multi *testEase, va_list ap)
{
	printf("%s: x=%d y=%d\n",
		va_arg(ap,char*),
		testEase->dimension[0].value,
		testEase->dimension[1].value);
	return 0;
}

/* Our main function called on program execution */
int main()
{
	/* Register variables. */
	register int retval;
	char *test_str = "Value";

	/* In this example we use the Ease_Multi structure. */
	Ease_Multi example;
	register int t;
	for (t=0; t<MULTI_MAX; ++t) example.dimension[t].type = '\0';

	/* Set the callback method */
	example.fpoint						= show_step_multi;

	/* X dimension */
	example.dimension[0].type			= &easeBackIo;
	example.dimension[0].initial		= 10;
	example.dimension[0].duration		= 20;
	example.dimension[0].difference		= 50;

	/* Y dimension */
	example.dimension[1].type			= &easeIn;
	example.dimension[1].initial		= 0;
	example.dimension[1].duration		= 10;
	example.dimension[1].difference		= 20;

	/* Execute the ease wrapper passing in a pointer to our ease
	structure. We also pass in the test string that we defined to
	demonstrate how to pass variables into the ease wrapper and
	then pull them out at the other side. Any quantity of variables
	can be passed in and recalled from the wrapper. */
	retval								= ease_multi(&example, test_str);
	return(retval);
}

