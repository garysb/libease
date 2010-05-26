/* vim: set ts=4 sw=4 nowrap: */
/*
Copyright (C) 2009 Gary Stidston-Broadbent.

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

/* Set the maximum amount of dimensions for multi easing */
#define MULTI_MAX 11

/* Easing structure */
typedef struct {
	int duration;													/* Easing duration */
	int time;														/* Easing time */
	int difference;													/* The ease difference */
	int initial;													/* The initial value */
	float overshot;													/* How far to overshoot the value when easing */
	int value;														/* Hold our result value */
	int (*fpoint)();												/* Hold a pointer to our callback function */
	int (*type)();													/* The ease type (pointer to one of the methods below) */
} Ease;

/* Multi dimension easing structure */
typedef struct {
	Ease dimension[MULTI_MAX];										/* The diferent easing dimensions */
	int (*fpoint)();												/* Hold a pointer to our callback function */
} Ease_Multi;

/* Wrapper Functions */
int ease(Ease *e, ...);												/* single dimension easing caller */
int ease_multi(Ease_Multi *e, ...);									/* multi dimension easing caller */

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
