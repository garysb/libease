/* vim: set ts=4 sw=4 nowrap: */
/*
Copyright (C) 2005 Stroppytux

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
#include <string.h>
#include <ease.h>

/* This is a 'test/example' case for the ease library	*/
/* You are free to use any of this code for whatever	*/
/* uses you need.										*/
int call(Ease *testEase);								/* Function decraration */
/* Our main function to run our test/example program.	*/
int main(int argc, char **argv) {
	int retval			= 1;							/* Our return value */
	if (argc < 2) {										/* If we have no arguments */
		printf("Usage: ./ease [in|out|none|io|oi]\n");	/* Print program usage */
		return 1;										/* Return error in command */
	}
	int i;												/* Loop counter */
	/* Get any information typed on the command line	*/
	for (i = 1; i < argc; i++) {						/* Loop through arguments */
		if (!strcmp(argv[i], "in")) {					/* If we have a in argument */
			/* Create an in ease */
			Ease inEase;								/* Create our structure */
			inEase.type			= IN;					/* Set our ease type. (IN,OUT,IO,OI,NONE) */
			inEase.initial		= 0;					/* Set our starting point */
			inEase.duration		= 10;					/* The quantity of times the easing should take to complete */
			inEase.difference	= 20;					/* Set the difference (eg.we want to move the object 10 px) */
			inEase.fpoint		= call;					/* We set the function pointer to 'call' on each stage of the ease */
			printf("Testing IN Easing\n");				/* Inform we are running in testing */
			retval				= ease(&inEase);		/* Run our easing function */
			continue;									/* And break loop */
		}
		if (!strcmp(argv[i], "out")) {					/* If we have a out argument */
			/* Create an out ease */
			Ease outEase;								/* Create our structure */
			outEase.type		= OUT;					/* Set our ease type. (IN,OUT,IO,OI,NONE) */
			outEase.initial		= 0;					/* Set our starting point */
			outEase.duration	= 10;					/* The quantity of times the easing should take to complete */
			outEase.difference	= 20;					/* Set the difference (eg.we want to move the object 10 px) */
			outEase.fpoint		= call;					/* We set the function pointer to 'call' on each stage of the ease */
			printf("Testing OUT Easing\n");				/* Inform we are running out testing */
			retval				= ease(&outEase);		/* Run our easing function */
			continue;									/* And break loop */
		}
		if (!strcmp(argv[i], "io")) {					/* If we have a io argument */
			/* Create an io ease */
			Ease ioEase;								/* Create our structure */
			ioEase.type			= IO;					/* Set our ease type. (IN,OUT,IO,OI,NONE) */
			ioEase.initial		= 0;					/* Set our starting point */
			ioEase.duration		= 10;					/* The quantity of times the easing should take to complete */
			ioEase.difference	= 20;					/* Set the difference (eg.we want to move the object 10 px) */
			ioEase.fpoint		= call;					/* We set the function pointer to 'call' on each stage of the ease */
			printf("Testing IO Easing\n");				/* Inform we are running io testing */
			retval				= ease(&ioEase);		/* Run our easing function */
			continue;									/* And break loop */
		}
		if (!strcmp(argv[i], "oi")) {					/* If we have a oi argument */
			/* Create an oi ease */
			Ease oiEase;								/* Create our structure */
			oiEase.type			= OI;					/* Set our ease type. (IN,OUT,IO,OI,NONE) */
			oiEase.initial		= 0;					/* Set our starting point */
			oiEase.duration		= 10;					/* The quantity of times the easing should take to complete */
			oiEase.difference	= 20;					/* Set the difference (eg.we want to move the object 10 px) */
			oiEase.fpoint		= call;					/* We set the function pointer to 'call' on each stage of the ease */
			printf("Testing OI Easing\n");				/* Inform we are running oi testing */
			retval				= ease(&oiEase);		/* Run our easing function */
			continue;									/* And break loop */
		}
		if (!strcmp(argv[i], "none")) {					/* If we have a none argument */
			/* Create a linear ease */
			Ease noneEase;								/* Create our structure */
			noneEase.type		= NONE;					/* Set our ease type. (IN,OUT,IO,OI,NONE) */
			noneEase.initial	= 0;					/* Set our starting point */
			noneEase.duration	= 10;					/* The quantity of times the easing should take to complete */
			noneEase.difference	= 20;					/* Set the difference (eg.we want to move the object 10 px) */
			noneEase.fpoint		= call;					/* We set the function pointer to 'call' on each stage of the ease */
			printf("Testing Linear Easing\n");			/* Inform which test we are doing */
			retval				= ease(&noneEase);		/* Run our easing function */
			continue;									/* And break loop */
		}
	}
	return( retval );									/* Return our result */
}

/* Our function called on each step of the ease.		*/
int call(Ease *testEase) {
	printf("Ease result: %d\n",testEase->value);		/* Print out our current ease value */
	return 0;											/* All went well, continue with ease */
}
