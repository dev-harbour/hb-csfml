/*
 * CSFML library: Clock.c
 * version 2.5.1
 *
 * Copyright 2021 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hbcsfml.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* System/sfClock */
static HB_GARBAGE_FUNC( hb_sfClock_destructor )
{
   sfClock ** ppSfClock = ( sfClock ** ) Cargo;

   if( *ppSfClock )
   {
      sfClock_destroy( *ppSfClock );
      *ppSfClock = NULL;
   }
}

static const HB_GC_FUNCS s_gcSfClockFuncs =
{
   hb_sfClock_destructor,
   hb_gcDummyMark
};

PHB_ITEM hb_sfClock_ItemPut( PHB_ITEM pItem, sfClock * pSfClock )
{
   sfClock ** ppSfClock = ( sfClock ** ) hb_gcAllocate( sizeof( sfClock * ), &s_gcSfClockFuncs );
   *ppSfClock = pSfClock;
   return hb_itemPutPtrGC( pItem, ppSfClock );
}

sfClock * hb_sfClock_Param( int iParam )
{
   sfClock ** ppSfClock = ( sfClock ** ) hb_parptrGC( &s_gcSfClockFuncs, iParam );

   if( ppSfClock && *ppSfClock )
   {
      return *ppSfClock;
   }
   else
   {
      HB_ERR_ARGS();
      return NULL;
   }
}

void hb_sfClock_Return( sfClock * pSfClock )
{
   if( pSfClock )
   {
      hb_sfClock_ItemPut( hb_param( -1, HB_IT_ANY ), pSfClock );
   }
   else
   {
      hb_ret();
   }
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

// sfClock* sfClock_create(void);
HB_FUNC( SFCLOCK_CREATE )
{
   hb_sfClock_Return( sfClock_create() );
}

// sfClock* sfClock_copy(const sfClock* clock);
HB_FUNC( SFCLOCK_COPY )
{
   const sfClock* clock = hb_sfClock_Param( 1 );

   if( clock )
   {
      hb_sfClock_Return( sfClock_copy( clock ) );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void sfClock_destroy(sfClock* clock);
HB_FUNC( SFCLOCK_DESTROY )
{
   sfClock ** ppSfClock = ( sfClock ** ) hb_parptrGC( &s_gcSfClockFuncs, 1 );

   if( ppSfClock && *ppSfClock )
   {
      sfClock_destroy( *ppSfClock );
      *ppSfClock = NULL;
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// sfTime sfClock_getElapsedTime(const sfClock* clock);
HB_FUNC( SFCLOCK_GETELAPSEDTIME )
{
   const sfClock* clock = hb_sfClock_Param( 1 );

   if( clock )
   {
      sfTime times = sfClock_getElapsedTime( clock );

      PHB_ITEM info = hb_itemArrayNew( 1 );

      hb_arraySetNLL( info, 1, times.microseconds );

      hb_itemReturnRelease( info );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// sfTime sfClock_restart(sfClock* clock);
HB_FUNC( SFCLOCK_RESTART )
{
   sfClock* clock = hb_sfClock_Param( 1 );

   if( clock )
   {
      sfTime times = sfClock_restart( clock );

      PHB_ITEM info = hb_itemArrayNew( 1 );

      hb_arraySetNLL( info, 1, times.microseconds );

      hb_itemReturnRelease( info );
   }
   else
   {
      HB_ERR_ARGS();
   }
}
