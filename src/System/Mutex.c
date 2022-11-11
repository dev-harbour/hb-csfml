/*
 * CSFML library: Mutex.c
 * version 2.5.1
 *
 * Copyright 2021 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hbcsfml.h"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* System/sfMutex */
static HB_GARBAGE_FUNC( hb_sfMutex_destructor )
{
   sfMutex ** ppSfMutex = ( sfMutex ** ) Cargo;

   if( *ppSfMutex )
   {
      sfMutex_destroy( *ppSfMutex );
      *ppSfMutex = NULL;
   }
}

static const HB_GC_FUNCS s_gcSfMutexFuncs =
{
   hb_sfMutex_destructor,
   hb_gcDummyMark
};

PHB_ITEM hb_sfMutex_ItemPut( PHB_ITEM pItem, sfMutex * pSfMutex )
{
   sfMutex ** ppSfMutex = ( sfMutex ** ) hb_gcAllocate( sizeof( sfMutex * ), &s_gcSfMutexFuncs );
   *ppSfMutex = pSfMutex;
   return hb_itemPutPtrGC( pItem, ppSfMutex );
}

sfMutex * hb_sfMutex_Param( int iParam )
{
   sfMutex ** ppSfMutex = ( sfMutex ** ) hb_parptrGC( &s_gcSfMutexFuncs, iParam );

   if( ppSfMutex && *ppSfMutex )
   {
      return *ppSfMutex;
   }
   else
   {
      HB_ERR_ARGS();
      return NULL;
   }
}

void hb_sfMutex_Return( sfMutex * pSfMutex )
{
   if( pSfMutex )
   {
      hb_sfMutex_ItemPut( hb_param( -1, HB_IT_ANY ), pSfMutex );
   }
   else
   {
      hb_ret();
   }
}

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

// sfMutex* sfMutex_create(void);
HB_FUNC( SFMUTEX_CREATE )
{
   hb_sfMutex_Return( sfMutex_create() );
}

// void sfMutex_destroy(sfMutex* mutex);
HB_FUNC( SFMUTEX_DESTROY )
{
   sfMutex ** ppSfMutex = ( sfMutex ** ) hb_parptrGC( &s_gcSfMutexFuncs, 1 );

   if( ppSfMutex && *ppSfMutex )
   {
      sfMutex_destroy( *ppSfMutex );
      *ppSfMutex = NULL;
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void sfMutex_lock(sfMutex* mutex);
HB_FUNC( SFMUTEX_LOCK )
{
   sfMutex* mutex = hb_sfMutex_Param( 1 );

   if( mutex )
   {
      sfMutex_lock( mutex );
   }
   else
   {
      HB_ERR_ARGS();
   }
}

// void sfMutex_unlock(sfMutex* mutex);
HB_FUNC( SFMUTEX_UNLOCK )
{
   sfMutex* mutex = hb_sfMutex_Param( 1 );

   if( mutex )
   {
      sfMutex_unlock( mutex );
   }
   else
   {
      HB_ERR_ARGS();
   }
}
