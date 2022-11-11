/*
 * CSFML library: Sleep.c
 * version 2.5.1
 *
 * Copyright 2021 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hbcsfml.h"

// void sfSleep(sfTime duration);
HB_FUNC( SFSLEEP )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL )
   {
      sfTime duration;

      duration.microseconds = hb_parnll( 1 );

      sfSleep( duration );
   }
   else
   {
      HB_ERR_ARGS();
   }
}
