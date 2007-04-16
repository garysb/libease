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
#include <ease.h>

/************************************************************************/
/*							Wrapper Function							*/
/************************************************************************/
int ease(Ease *e, ...)													/* Function to check which ease method to use */
{
	/* Lets parse the variadic call */
	va_list ap, ap_copy;												/* Extract our variable arguments */
	va_start(ap, e);													/* Start our variadic argument parsing */
	int retval	= 0;													/* Set our default return value */

	/* Loop to get all our results */
	e->time		= 0;													/* Reset out time marker */

	while(e->time <= e->duration) {
		/* Need to find an efective way of doing this, anybody know		*/
		/* how to call a function from a string name, or a func_exists,	*/
		/* or define a pointer to a function from a string name???		*/
		switch( e->type )
		{
			case IN:													/* Call the easeIn function */
				retval		= easeIn(e);								/* Run our easeIn function */
				break;
			case OUT:													/* Call the easeOut function */
				retval		= easeOut(e);								/* Run our easeOut function */
				break;
			case IO:													/* Call the easeIo function */
				retval		= easeIo(e);								/* Run our easeIo function */
				break;
			case OI:													/* Call the easeOi function */
				retval		= easeOi(e);								/* Run our easeOi function */
				break;
			case BI:													/* Call the easeOi function */
				retval		= easeBounceIn(e);							/* Run our easeOi function */
				break;
			case BO:													/* Call the easeOi function */
				retval		= easeBounceOut(e);							/* Run our easeOi function */
				break;
			case NONE:													/* Call the easeNone function (linear) */
			default:
				retval		= easeNone(e);								/* Run our easeNone function */
				break;
		}

		/* For each iteration, we need to copy the ap and pass it into ease */
#ifdef __va_copy
		__va_copy(ap_copy, ap);											/* Create a copy of ap */
#else
		ap_copy = ap;													/* We dont have __va_copy, just try copy it */
#endif
		/* Lets call our function pointer */
		(*e->fpoint)(e,ap_copy);										/* Call our function pointed to in fpoint and pass in our args*/
		e->time++;														/* Increase out time */
	}

	va_end(ap);
	return(retval);														/* Return our result */
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
