/* vim: set ts=4 sw=4 nowrap: */

/* Include the header files we need, especially ease.h */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ease.h>

/* A test function to show our easing values at each step.
We pass in va_list ap to allow us to receive misc variables
from our wrapper. These can then be passed into the call
you are using the ease value on. */
int show_step(Ease *testEase,va_list ap);

/* Our main function called on program execution */
int main()
{
	/* Register an int for the return value and create a string
	that we will use as an example of passing arbitrary variables
	into our ease function. This value will then get passed into
	whatever we set our callback function to at each step of the
	easing process. */
	register int retval;
	char *test_str = "Value";

	/* Create the Ease structure and populate it. For more info
	on what the values are, please read the description of the
	Ease structure above. */
	Ease example;
	example.type			= &easeIn;
	example.initial			= 0;
	example.duration		= 100;
	example.difference		= 100;
	example.fpoint			= show_step;

	/* Execute the ease wrapper passing in a pointer to our ease
	structure. We also pass in the test string that we defined to
	demonstrate how to pass variables into the ease wrapper and
	then pull them out at the other side. Any quantity of variables
	can be passed in and recalled from the wrapper. */
	retval					= ease(&example, test_str);
	return(retval);
}

int show_step(Ease *testEase, va_list ap)
{
	printf("%s: %d\n", va_arg(ap,char*), testEase->value);
	return 0;
}
