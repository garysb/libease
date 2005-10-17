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

/* Stop multiple inclusions */
#ifndef _HAVE_LIBEASE_
#define _HAVE_LIBEASE_

/* Ease types */
#define IN		1													/* Starts slow, then speeds up to the end */
#define OUT		2													/* Starts fast, then slows down to the end */
#define IO		3													/* Starts slow, fast in middle, ends slow */
#define OI		4													/* Starts fast, slow in middle, ends fast */
#define NONE	5													/* Linear, just changes at same rate */

/* Easing structure */
typedef struct {
	int duration;													/* Easing duration */
	int time;														/* Easing time */
	int difference;													/* The ease difference */
	int initial;													/* The initial value */
	int value;														/* Hold our result value */
	int (*fpoint)();												/* Hold a pointer to our function */
	int type;														/* The ease type */
} Ease;

/* Wrapper Function */
int ease(Ease *e);													/* Our main 'caller' method */
/* Ease Functions */
int easeIn(Ease *e);												/* Ease value in */
int easeOut(Ease *e);												/* Ease value out */
int easeIo(Ease *e);												/* Ease value in half way, then out */
int easeOi(Ease *e);												/* Ease value out half way, the in */
int easeNone(Ease *e);												/* Linear inc/dec of value */
/* Delay functions */
//int timeDelay(int i);												/* Create a delay (pause) */
//int timeDiff();													/* Calculate function execution time */

#endif

