/* vim: set ts=4 sw=4 nowrap: */
/*	This code is free of any copyright. Feel free to use anyway you like. */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ease.h>

/* This is a 'test/example' case for the ease library. */
int show_step(Ease *testEase,va_list ap);

/* Our main function to run our test/example program. */
int main(int argc, char **argv) {
	int retval = 1;
	int i;

	/* If we have no arguments, return program usage */
	if (argc < 2) {
		printf("Usage: ./ease [in|out|none|io|oi|bi|bo|ki|ko|kb]\n");
		return(retval);
	}

	/* Loop through arguments */
	for (i = 1; i < argc; i++) {
		/* If we have an 'in' argument */
		if (!strcmp(argv[i], "in")) {
			/* Create and populate our structure */
			Ease inEase;
			inEase.type			= &easeIn;				/* Create a pointer to one of our easing methods (defined in ease.h) */
			inEase.initial		= 0;					/* Set our starting point */
			inEase.duration		= 10;					/* The quantity of times the easing should take to complete */
			inEase.difference	= 20;					/* Set the difference (eg.we want to move the object 10 px) */
			inEase.fpoint		= show_step;			/* We set the function pointer to 'show' on each stage of the ease */
			char *j				= "EASE IN (number changes slowly at first, then increases)";	/* Just a test string to pass into our interation function */
			retval				= ease(&inEase,j,i);	/* Run our easing function i and j are to test passing random variables in */
			continue;									/* And break loop */
		}

		/* If we have an 'out' argument */
		if (!strcmp(argv[i], "out")) {
			Ease outEase;
			outEase.type		= &easeOut;
			outEase.initial		= 0;
			outEase.duration	= 10;
			outEase.difference	= 20;
			outEase.fpoint		= show_step;
			char *j				= "EASE OUT (large number changes in the beginning, then slows down)";
			retval				= ease(&outEase,j,i);
			continue;
		}

		/* If we have the 'io' argument */
		if (!strcmp(argv[i], "io")) {
			Ease ioEase;
			ioEase.type			= &easeIo;
			ioEase.initial		= 0;
			ioEase.duration		= 10;
			ioEase.difference	= 20;
			ioEase.fpoint		= show_step;
			char *j				= "EASE IN-OUT (small number changes in the beginning and end, large changes in the middle)";
			retval				= ease(&ioEase,j,i);
			continue;
		}

		/* If we have the 'oi' argument */
		if (!strcmp(argv[i], "oi")) {
			Ease oiEase;
			oiEase.type			= &easeOi;
			oiEase.initial		= 0;
			oiEase.duration		= 10;
			oiEase.difference	= 20;
			oiEase.fpoint		= show_step;
			char *j				= "EASE OUT-IN (big diference in numbers at beginning and end, small in the middle)";
			retval				= ease(&oiEase,j,i);
			continue;
		}

		/* If we have the 'bi' argument */
		if (!strcmp(argv[i], "bi")) {
			Ease biEase;
			biEase.type			= &easeBounceIn;
			biEase.initial		= 0;
			biEase.duration		= 10;
			biEase.difference	= 20;
			biEase.fpoint		= show_step;
			char *j				= "EASE BOUNCE-IN (numbers rise, then fall, then increase up to end)";
			retval				= ease(&biEase,j,i);
			continue;
		}

		/* If we have the 'bo' argument */
		if (!strcmp(argv[i], "bo")) {
			Ease boEase;
			boEase.type			= &easeBounceOut;
			boEase.initial		= 0;
			boEase.duration		= 10;
			boEase.difference	= 20;
			boEase.fpoint		= show_step;
			char *j				= "EASE BOUNCE-OUT (quick increase, then numbers drop, then rise to end)";
			retval				= ease(&boEase,j,i);
			continue;
		}

		/* If we have the 'ki' argument */
		if (!strcmp(argv[i], "ki")) {
			Ease kiEase;
			kiEase.type			= &easeBackIn;
			kiEase.initial		= 0;
			kiEase.duration		= 10;
			kiEase.difference	= 20;
			kiEase.overshot		= 2;
			kiEase.fpoint		= show_step;
			char *j				= "EASE BACK-IN (numbers decrease from start, then increase to end)(negatives if start from zero)";
			retval				= ease(&kiEase,j,i);
			continue;
		}

		/* If we have the 'ko' argument */
		if (!strcmp(argv[i], "ko")) {
			Ease koEase;
			koEase.type			= &easeBackOut;
			koEase.initial		= 0;
			koEase.duration		= 10;
			koEase.difference	= 20;
			koEase.overshot		= 2;
			koEase.fpoint		= show_step;
			char *j				= "EASE BACK-OUT (numbers increase past end, then reduce back to end)";
			retval				= ease(&koEase,j,i);
			continue;
		}

		/* If we have the 'kb' argument */
		if (!strcmp(argv[i], "kb")) {
			Ease kbEase;
			kbEase.type			= &easeBackIo;
			kbEase.initial		= 0;
			kbEase.duration		= 10;
			kbEase.difference	= 20;
			kbEase.overshot		= 2;
			kbEase.fpoint		= show_step;
			char *j				= "EASE BACK-IN-OUT (decrease below start, then increase past end, then back to end) (negative if from zero)";
			retval				= ease(&kbEase,j,i);
			continue;
		}

		/* If we have the 'none' argument */
		if (!strcmp(argv[i], "none")) {
			Ease noneEase;
			noneEase.type		= &easeNone;
			noneEase.initial	= 0;
			noneEase.duration	= 10;
			noneEase.difference	= 20;
			noneEase.fpoint		= show_step;
			char *j				= "EASE NONE (linear movement from start to end by dividing duration by steps)";
			retval				= ease(&noneEase,j,i);
			continue;
		}
	}

	return(retval);
}

/* Our function called on each step of the ease. (aka callback function) */
int show_step(Ease *testEase, va_list ap) {
	/* Display the passthru variables if time = 0 */
	if (testEase->time == 0) {
		printf("Test %d: %s\n", va_arg(ap,int), va_arg(ap,char*));
	}

	/* For each step, print out or step value */
	printf("\tStep value: %d\n", testEase->value);
	return 0;
}
