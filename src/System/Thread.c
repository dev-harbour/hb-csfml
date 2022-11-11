/*
 * CFML library: Thread.c
 * version 2.5.1
 *
 * Copyright 2021 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hbcsfml.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* System/sfThread */
static HB_GARBAGE_FUNC( hb_sfThread_destructor )
{
   sfThread ** ppSfThread = ( sfThread ** ) Cargo;

   if( *ppSfThread )
   {
      sfThread_destroy( *ppSfThread );
      *ppSfThread = NULL;
   }
}

static const HB_GC_FUNCS s_gcSfThreadFuncs =
{
   hb_sfThread_destructor,
   hb_gcDummyMark
};

PHB_ITEM hb_sfThread_ItemPut( PHB_ITEM pItem, sfThread * pSfThread )
{
   sfThread ** ppSfThread = ( sfThread ** ) hb_gcAllocate( sizeof( sfThread * ), &s_gcSfThreadFuncs );
   *ppSfThread = pSfThread;
   return hb_itemPutPtrGC( pItem, ppSfThread );
}

sfThread * hb_sfThread_Param( int iParam )
{
   sfThread ** ppSfThread = ( sfThread ** ) hb_parptrGC( &s_gcSfThreadFuncs, iParam );

   if( ppSfThread && *ppSfThread )
   {
      return *ppSfThread;
   }
   else
   {
      HB_ERR_ARGS();
      return NULL;
   }
}

void hb_sfThread_Return( sfThread * pSfThread )
{
   if( pSfThread )
   {
      hb_sfThread_ItemPut( hb_param( -1, HB_IT_ANY ), pSfThread );
   }
   else
   {
      hb_ret();
   }
}

static void entry_point( void* data )
{
   ( void ) data;
}

// sfThread* sfThread_create(void (*function)(void*), void* userData);
HB_FUNC( SFTHREAD_CREATE )
{
   void* userData = hb_sfThread_Param( 1 );

   if( userData )
   {
      sfThread_create( entry_point, userData );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void sfThread_destroy(sfThread* thread);
HB_FUNC( SFTHREAD_DESTROY )
{
   sfThread ** ppSfThread = ( sfThread ** ) hb_parptrGC( &s_gcSfThreadFuncs, 1 );

   if( ppSfThread && *ppSfThread )
   {
      sfThread_destroy( *ppSfThread );
      *ppSfThread = NULL;
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void sfThread_launch(sfThread* thread);
HB_FUNC( SFTHREAD_LAUNCH )
{
   sfThread* thread = hb_sfThread_Param( 1 );

   if( thread )
   {
      sfThread_launch( thread );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void sfThread_wait(sfThread* thread);
HB_FUNC( SFTHREAD_WAIT )
{
   sfThread* thread = hb_sfThread_Param( 1 );

   if( thread )
   {
      sfThread_wait( thread );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void sfThread_terminate(sfThread* thread);
HB_FUNC( SFTHREAD_TERMINATE )
{
   sfThread* thread = hb_sfThread_Param( 1 );

   if( thread )
   {
      sfThread_terminate( thread );
   }
   else
   {
      HB_ERR_ARGS();
   }
}
