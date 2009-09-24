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

/* Stop multiple inclusions */
#ifndef _HAVE_LIBEASE_
#define _HAVE_LIBEASE_

/* Ease types */
#define NONE	1													/* Linear, just changes at same rate */
#define IN		2													/* Starts slow, then speeds up to the end */
#define OUT		3													/* Starts fast, then slows down to the end */
#define IO		4													/* Starts slow, fast in middle, ends slow */
#define OI		5													/* Starts fast, slow in middle, ends fast */
#define BI		6													/* Bounces the value before easing in */
#define BO		7													/* Bounces the value after easing out */
#define KI		8													/* Back in the easing (returns negative numbers) */
#define KO		9													/* Back out the easing (returns negative numbers) */
#define KB		10													/* Back in and out easing */

/* Easing structure */
typedef struct {
	int duration;													/* Easing duration */
	int time;														/* Easing time */
	int difference;													/* The ease difference */
	int initial;													/* The initial value */
	float overshot;													/* How far to overshoot the value when easing */
	int value;														/* Hold our result value */
	int (*fpoint)();												/* Hold a pointer to our callback function */
	int (*type)();													/* The ease type */
} Ease;

/* Wrapper Function */
int ease(Ease *e, ...);												/* Our main 'caller' method */

/* Ease Functions */
int easeIn(Ease *e);												/* Ease value in */
int easeOut(Ease *e);												/* Ease value out */
int easeIo(Ease *e);												/* Ease value in half way, then out */
int easeOi(Ease *e);												/* Ease value out half way, the in */
int easeNone(Ease *e);												/* Linear inc/dec of value */
int easeBounceIn(Ease *e);											/* Bounce the number before easing in */
int easeBounceOut(Ease *e);											/* Bouce the number after easeing out */
int easeBackIn(Ease *e);											/* Back in the number before easing */
int easeBackOut(Ease *e);											/* Back out the number after easing */
int easeBackIo(Ease *e);											/* Back the number in before and back the number out after easing */
#endif
