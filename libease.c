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
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ease.h>

/************************************************************************/
/*					Single dimension wrapper Function					*/
/************************************************************************/
int ease(Ease *e, ...)
{
	/* Lets parse the variadic call */
	va_list ap, ap_copy;
	va_start(ap, e);
	int retval	= 0;
	e->time		= 0;

	/* Make sure our duration is larger than zero */
	e->duration = abs(e->duration);

	/* Loop through our time value for (duration) iterations */
	while(e->time <= e->duration) {
		/* Run the function pointed to in e->type. This should be a ease type */
		retval = e->type(e);

		/* For each iteration, we need to copy the ap and pass it into ease */
#ifdef __va_copy
		/* Create a copy of ap */
		__va_copy(ap_copy, ap);
#else
		/* We dont have __va_copy, just try copy it */
		ap_copy = ap;
#endif
		/* Lets call our function pointer */
		(*e->fpoint)(e,ap_copy);
		e->time++;
	}

	va_end(ap);
	return(retval);
}

/************************************************************************/
/*					Multi dimension wrapper Function					*/
/************************************************************************/
int ease_multi(Ease_Multi *e, ...)
{
	/* Lets parse the variadic call */
	va_list ap, ap_copy;
	va_start(ap, e);
	int retval = 0;
	int time = 0;
	register int t;
	register int duration = 1;

	/* Reset the times on all dimensions and calculate the highest duration */
	for(t=0; t<MULTI_MAX; ++t) {
		if (e->dimension[t].type) {
			e->dimension[t].time = 0;
			e->dimension[t].duration = abs(e->dimension[t].duration);
			if (e->dimension[t].duration > duration) {
				duration = e->dimension[t].duration;
			}
		}
	}

	/* Loop through our time value for (duration) iterations */
	while(time <= duration) {
		for(t=0; t<MULTI_MAX; ++t) {
			if (e->dimension[t].type) {
				if (e->dimension[t].time <= e->dimension[t].duration) {
					/* Run the function pointed to in e->type. This should be a ease type */
					retval = e->dimension[t].type(&e->dimension[t]);
					e->dimension[t].time++;
				}
			}
		}

		/* For each iteration, we call the callback function */
#ifdef __va_copy
		/* Create a copy of ap */
		__va_copy(ap_copy, ap);
#else
		/* We dont have __va_copy, just try copy it */
		ap_copy = ap;
#endif
		/* Lets call our function pointer */
		(*e->fpoint)(e,ap_copy);
		time++;
	}

	va_end(ap);
	return(retval);
}

/************************************************************************/
/*							Easing methods								*/
/************************************************************************/
/* Ease in method - This method eases the value from small increments to
   larger increments. eg. 0 0 0 0 1 2 4 6 10 14 20 */
int easeIn(Ease *e)
{
	float tmpTime	=  e->time;
	tmpTime			/= e->duration;
	e->value		=  e->difference*tmpTime*tmpTime*tmpTime + e->initial;
	return 0;
}

/* Ease out method - This method esases the value from large increments to
   smaller increments. eg. 0 5 9 13 15 17 18 19 19 19 20 */
int easeOut(Ease *e)
{
	float tmpTime	=  e->time;
	tmpTime			/= e->duration;
	tmpTime--;
	e->value		=  e->difference*(tmpTime*tmpTime*tmpTime + 1) + e->initial;
	return 0;
}

/* Ease in/out method - This method starts by slowly incrementing the value.
   At the center point the spead increases, then slows down to the end.
   eg. 0 0 0 2 5 10 14 17 19 19 20 */
int easeIo(Ease *e)
{
	float tmpTime	=  e->time;
	tmpTime			/= e->duration/2;
	if (tmpTime < 1) {
		e->value	=  e->difference/2*tmpTime*tmpTime*tmpTime + e->initial;
		return 0;
	}
	tmpTime			-= 2;
	e->value		=  e->difference/2*(tmpTime*tmpTime*tmpTime + 2) + e->initial;
	return 0;
}

/* Ease out/in method - This method starts quickly, slows in the middle, then
   increases speed at the end. eg. 0 4 7 9 9 10 10 10 12 15 20 */
int easeOi(Ease *e)
{
	float tmpTime	= e->time;
	float ts=(tmpTime/=e->duration)*tmpTime;
	float tc=ts*tmpTime;
	e->value		= e->initial+e->difference*(4*tc + -6*ts + 3*tmpTime);
	return 0;
}

/* Ease none method - This will just return a linear result with increments
   of the different between the beginning and ending values devided by the
   number of steps needed. eg. 0 2 4 6 8 10 12 14 16 18 20 */
int easeNone(Ease *e)
{
	float tmpTime	= e->time;
	e->value		= e->difference*tmpTime/e->duration + e->initial;
	return 0;
}

/* Ease bounce in method - This will make the value bounce before it eases
   into its value. eg. 0 0 1 1 4 4 1 6 13 18 20 */
int easeBounceIn(Ease *e)
{
	float tmpTime	= e->time;
	tmpTime			= e->duration - e->time;

	if ((tmpTime/=e->duration) < (1/2.75)) {
		e->value	= e->difference - e->difference*(7.5625*tmpTime*tmpTime) + e->initial;
		return 0;
	} else if (tmpTime < (2/2.75)) {
		tmpTime		= tmpTime - (1.5/2.75);
		e->value	= e->difference - e->difference*(7.5625*tmpTime*tmpTime + .75) + e->initial;
		return 0;
	} else if (tmpTime < (2.5/2.75)) {
		tmpTime		= tmpTime- (2.25/2.75);
		e->value	= e->difference - e->difference*(7.5625*tmpTime*tmpTime + .9375) + e->initial;
		return 0;
	}
	tmpTime			= tmpTime- (2.625/2.75);
	e->value		= e->difference - e->difference*(7.5625*tmpTime*tmpTime + .984375) + e->initial;

	return 0;
}

/* Ease bounce out method - This will make the value bounce after it eases
   into its value. eg. 0 1 6 13 18 15 15 18 18 19 20 */
int easeBounceOut(Ease *e)
{
	float tmpTime	= e->time;

	if ((tmpTime/=e->duration) < (1/2.75)) {
		e->value	= e->difference*(7.5625*tmpTime*tmpTime) + e->initial;
		return 0;
	} else if (tmpTime < (2/2.75)) {
		tmpTime		= tmpTime - (1.5/2.75);
		e->value	= e->difference*(7.5625*tmpTime*tmpTime + .75) + e->initial;
		return 0;
	} else if (tmpTime < (2.5/2.75)) {
		tmpTime		= tmpTime- (2.25/2.75);
		e->value	= e->difference*(7.5625*tmpTime*tmpTime + .9375) + e->initial;
		return 0;
	}
	tmpTime			= tmpTime- (2.625/2.75);
	e->value		= e->difference*(7.5625*tmpTime*tmpTime + .984375) + e->initial;
	return 0;
}

/* Ease back in method - This will first negate the number before easing in. */
int easeBackIn(Ease *e)
{
	float tmpTime	= e->time;
	e->value		= e->difference*(tmpTime/=e->duration)*tmpTime*((e->overshot+1)*tmpTime - e->overshot) + e->initial;
	return 0;
}

/* Ease back in method - This will first negate the number before easing in. */
int easeBackOut(Ease *e)
{
	float tmpTime	= e->time;
	e->value		= e->difference*((tmpTime=tmpTime/e->duration-1)*tmpTime*((e->overshot+1)*tmpTime + e->overshot) + 1) + e->initial;
	return 0;
}

/* Ease back in method - This will first negate the number before easing in. */
int easeBackIo(Ease *e)
{
	float tmpTime	= e->time;

	if ((tmpTime /= e->duration/2 ) < 1) {
		float tmpOvershot = e->overshot;
		e->value	= e->difference/2*(tmpTime*tmpTime*(((tmpOvershot*=(1.525))+1)*tmpTime - tmpOvershot)) + e->initial;
		return 0;
	}
	float tmpOvershot = e->overshot;
	e->value		= e->difference/2*((tmpTime-=2)*tmpTime*(((tmpOvershot*=(1.525))+1)*tmpTime + tmpOvershot) + 2) + e->initial;
	return 0;
}
