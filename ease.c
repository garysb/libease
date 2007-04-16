/* vim: set ts=4 sw=4 nowrap: */
/*
Copyright (C) 2007 Gary Stidston-Broadbent.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ease.h>

/* This is a 'test/example' case for the ease library	*/
/* You are free to use any of this code for whatever	*/
/* uses you need.					*/
int call(Ease *testEase,va_list ap);

/* Our main function to run our test/example program. */
int main(int argc, char **argv) {
	int retval					= 1;

	/* If we have no arguments, return program usage */
	if (argc < 2) {
		printf("Usage: ./ease [in|out|none|io|oi|bi|bo|ki|ko|kb]\n");
		return 1;
	}

	/* Loop counter to return test number */
	int i;

	/* Get any information typed on the command line */
			char passthru1[20];
			int passthru2;
			strcpy(passthru1,"Test string passthru");
			passthru2			= 10;

	/* Loop through arguments */
	for (i = 1; i < argc; i++) {

		/* If we have an 'in' argument */
		if (!strcmp(argv[i], "in")) {
			/* Create and populate our structure */
			Ease inEase;
			inEase.type			= IN;					/* Set our ease type. (IN,OUT,IO,OI,NONE,BI,BO) */
			inEase.initial		= 0;					/* Set our starting point */
			inEase.duration		= 10;					/* The quantity of times the easing should take to complete */
			inEase.difference	= 20;					/* Set the difference (eg.we want to move the object 10 px) */
			inEase.fpoint		= call;					/* We set the function pointer to 'call' on each stage of the ease */
			passthru2			= 1;					/* Set an intager to test variadic function call */
			strcpy(passthru1,"IN");						/* Set a string to test variadic function call */
			retval				= ease(&inEase,passthru1,passthru2);		/* Run our easing function */
			continue;									/* And break loop */
		}

		/* If we have an 'out' argument */
		if (!strcmp(argv[i], "out")) {
			Ease outEase;
			outEase.type		= OUT;
			outEase.initial		= 0;
			outEase.duration	= 10;
			outEase.difference	= 20;
			outEase.fpoint		= call;
			passthru2			= 2;
			strcpy(passthru1,"OUT");
			retval				= ease(&outEase,passthru1,passthru2);
			continue;
		}

		/* If we have the 'io' argument */
		if (!strcmp(argv[i], "io")) {
			Ease ioEase;
			ioEase.type			= IO;
			ioEase.initial		= 0;
			ioEase.duration		= 10;
			ioEase.difference	= 20;
			ioEase.fpoint		= call;
			passthru2			= 3;
			strcpy(passthru1,"IO");
			retval				= ease(&ioEase,passthru1,passthru2);
			continue;
		}

		/* If we have the 'oi' argument */
		if (!strcmp(argv[i], "oi")) {
			Ease oiEase;
			oiEase.type			= OI;
			oiEase.initial		= 0;
			oiEase.duration		= 10;
			oiEase.difference	= 20;
			oiEase.fpoint		= call;
			passthru2			= 4;
			strcpy(passthru1,"OI");
			retval				= ease(&oiEase,passthru1,passthru2);
			continue;
		}

		/* If we have the 'bi' argument */
		if (!strcmp(argv[i], "bi")) {
			Ease biEase;
			biEase.type			= BI;
			biEase.initial		= 0;
			biEase.duration		= 10;
			biEase.difference	= 20;
			biEase.fpoint		= call;
			passthru2			= 5;
			strcpy(passthru1,"BI");
			retval				= ease(&biEase,passthru1,passthru2);
			continue;
		}

		/* If we have the 'bo' argument */
		if (!strcmp(argv[i], "bo")) {
			Ease boEase;
			boEase.type			= BO;
			boEase.initial		= 0;
			boEase.duration		= 10;
			boEase.difference	= 20;
			boEase.fpoint		= call;
			passthru2			= 6;
			strcpy(passthru1,"BO");
			retval				= ease(&boEase,passthru1,passthru2);
			continue;
		}

		/* If we have the 'ki' argument */
		if (!strcmp(argv[i], "ki")) {
			Ease kiEase;
			kiEase.type			= KI;
			kiEase.initial		= 0;
			kiEase.duration		= 10;
			kiEase.difference	= 20;
			kiEase.overshot		= 2;
			kiEase.fpoint		= call;
			passthru2			= 7;
			strcpy(passthru1,"KI");
			retval				= ease(&kiEase,passthru1,passthru2);
			continue;
		}

		/* If we have the 'ko' argument */
		if (!strcmp(argv[i], "ko")) {
			Ease koEase;
			koEase.type			= KO;
			koEase.initial		= 0;
			koEase.duration		= 10;
			koEase.difference	= 20;
			koEase.overshot		= 2;
			koEase.fpoint		= call;
			passthru2			= 8;
			strcpy(passthru1,"KO");
			retval				= ease(&koEase,passthru1,passthru2);
			continue;
		}

		/* If we have the 'kb' argument */
		if (!strcmp(argv[i], "kb")) {
			Ease kbEase;
			kbEase.type			= KB;
			kbEase.initial		= 0;
			kbEase.duration		= 10;
			kbEase.difference	= 20;
			kbEase.overshot		= 2;
			kbEase.fpoint		= call;
			passthru2			= 9;
			strcpy(passthru1,"KB");
			retval				= ease(&kbEase,passthru1,passthru2);
			continue;
		}

		/* If we have the 'none' argument */
		if (!strcmp(argv[i], "none")) {
			Ease noneEase;
			noneEase.type		= NONE;
			noneEase.initial	= 0;
			noneEase.duration	= 10;
			noneEase.difference	= 20;
			noneEase.fpoint		= call;
			passthru2			= 10;
			strcpy(passthru1,"NONE");
			retval				= ease(&noneEase,passthru1,passthru2);
			continue;
		}
	}
	return(retval);
}

/* Our function called on each step of the ease. (aka callback function) */
int call(Ease *testEase, va_list ap) {
	/* Display the passthru variables if time = 0 */
	if (testEase->time == 0) {							/* If this is the first run, display our passthru variables */
		char *passthru1			= va_arg(ap,char*);		/* Copy the string from our pointer */
		printf("%d. Ease method: %s\n", va_arg(ap,int), passthru1);	/* Display our string passthru */
	}
	printf("Ease result: %d\n", testEase->value);		/* Print out our current ease value */
	return 0;											/* All went well, continue with ease */
}
