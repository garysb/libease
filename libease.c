/* vim: set ts=4 sw=4 nowrap: */
/*
Copyright (C) 2005 Plasmaperfect Ltd.

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
/*							Ease functions								*/
/************************************************************************/
int easeIn(Ease *e)														/* Ease in Function */
{
	float tmpTime	=  e->time;											/* Create local time float */
	tmpTime			/= e->duration;
	e->value		=  e->difference*tmpTime*tmpTime*tmpTime + e->initial;
	return 0;															/* All went fine */
}
int easeOut(Ease *e)													/* Ease out Function */
{
	float tmpTime	=  e->time;
	tmpTime			/= e->duration;
	tmpTime--;
	e->value		=  e->difference*(tmpTime*tmpTime*tmpTime + 1) + e->initial;
	return 0;															/* All went well */
}
int easeIo(Ease *e)														/* Ease in/out Function */
{
	float tmpTime	=  e->time;
	tmpTime			/= e->duration/2;
	if (tmpTime < 1) {
		e->value	=  e->difference/2*tmpTime*tmpTime*tmpTime + e->initial;
		return 0;														/* All went well */
	}
	tmpTime			-= 2;
	e->value		=  e->difference/2*(tmpTime*tmpTime*tmpTime + 2) + e->initial;
	return 0;															/* All went well */
}
int easeOi(Ease *e)														/* Ease in/out Function */
{
	float tmpTime	= e->time;
	float ts=(tmpTime/=e->duration)*tmpTime;
	float tc=ts*tmpTime;
	e->value		= e->initial+e->difference*(4*tc + -6*ts + 3*tmpTime);
	return 0;															/* All went well */
}
int easeNone(Ease *e)													/* No Easing, just scroll */
{
	float tmpTime	= e->time;
	e->value		= e->difference*tmpTime/e->duration + e->initial;
	return 0;															/* All went well */
}
