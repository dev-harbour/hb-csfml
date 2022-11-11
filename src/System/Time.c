/*
 * CSFML library: Time.c
 * version 2.5.1
 *
 * Copyright 2021 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hbcsfml.h"

// float sfTime_asSeconds(sfTime time);
HB_FUNC( SFTIME_ASSECONDS )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL )
   {
      sfTime time;

      time.microseconds = hb_parnll( 1 );

      hb_retnd( ( float ) sfTime_asSeconds( time ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// sfInt32 sfTime_asMilliseconds(sfTime time);
HB_FUNC( SFTIME_ASMILLISECONDS )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 1 )
   {
      sfTime time;

      time.microseconds = hb_arrayGetNLL( pItem, 1 );

      hb_retni( ( signed int ) sfTime_asMilliseconds( time ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// sfInt64 sfTime_asMicroseconds(sfTime time);
HB_FUNC( SFTIME_ASMICROSECONDS )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 1 )
   {
      sfTime time;

      time.microseconds = hb_arrayGetNLL( pItem, 1 );

      hb_retnll( sfTime_asMicroseconds( time ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// sfTime sfSeconds(float amount);
HB_FUNC( SFSECONDS )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL )
   {
      sfTime times = sfSeconds( ( float ) hb_parnd( 1 ) );
      hb_retnll( times.microseconds );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// sfTime sfMilliseconds(sfInt32 amount);
HB_FUNC( SFMILLISECONDS )
{
   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      sfTime times = sfMilliseconds( ( signed int ) hb_parni( 1 ) );

      PHB_ITEM info = hb_itemArrayNew( 1 );

      hb_arraySetNLL( info, 1, times.microseconds );

      hb_itemReturnRelease( info );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// sfTime sfMicroseconds(sfInt64 amount);
HB_FUNC( SFMICROSECONDS )
{
   if( hb_param( 1, HB_IT_LONG ) != NULL )
   {
      sfTime times = sfMicroseconds( hb_parnl( 1 ) );

      PHB_ITEM info = hb_itemArrayNew( 1 );

      hb_arraySetNLL( info, 1, times.microseconds );

      hb_itemReturnRelease( info );
   }
   else
   {
      HB_ERR_ARGS();
   }
}
