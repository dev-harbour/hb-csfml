/*
 * Language bindings to CSFML library: SoundBufferRecorder.c
 * version 2.5.1
 *
 * Copyright Rafał Jopek ( rafaljopek at hotmail com )
 * created: 2021-03-22
 * updated: 2021-11-14
 *
 */

#include "hbcsfml.h"

/* Audio/sfSoundBufferRecorder */
static HB_GARBAGE_FUNC( hb_sfSoundBufferRecorder_destructor )
{
   sfSoundBufferRecorder ** ppSfSoundBufferRecorder = ( sfSoundBufferRecorder ** ) Cargo;

   if( *ppSfSoundBufferRecorder )
   {
      sfSoundBufferRecorder_destroy( *ppSfSoundBufferRecorder );
      *ppSfSoundBufferRecorder = NULL;
   }
}

static const HB_GC_FUNCS s_gcSfSoundBufferRecorderFuncs =
{
   hb_sfSoundBufferRecorder_destructor,
   hb_gcDummyMark
};

PHB_ITEM hb_sfSoundBufferRecorderItemPut( PHB_ITEM pItem, sfSoundBufferRecorder * pSfSoundBuffer )
{
   sfSoundBufferRecorder ** ppSfSoundBufferRecorder = ( sfSoundBufferRecorder ** ) hb_gcAllocate( sizeof( sfSoundBufferRecorder * ), &s_gcSfSoundBufferRecorderFuncs );

   *ppSfSoundBufferRecorder = pSfSoundBuffer;
   return hb_itemPutPtrGC( pItem, ppSfSoundBufferRecorder );
}

sfSoundBufferRecorder * hb_sfSoundBufferRecorder_param( int iParam )
{
   sfSoundBufferRecorder ** ppSfSoundBufferRecorder = ( sfSoundBufferRecorder ** ) hb_parptrGC( &s_gcSfSoundBufferRecorderFuncs, iParam );

   if( ppSfSoundBufferRecorder && *ppSfSoundBufferRecorder )
   {
      return *ppSfSoundBufferRecorder;
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
      return NULL;
   }
}

void hb_sfSoundBufferRecorder_ret( sfSoundBufferRecorder * pSfSoundBuffer )
{
   hb_sfSoundBufferRecorderItemPut( hb_stackReturnItem(), pSfSoundBuffer );
}

// sfSoundBufferRecorder* sfSoundBufferRecorder_create(void);
HB_FUNC( SFSOUNDBUFFERRECORDER_CREATE )
{
   hb_sfSoundBufferRecorder_ret( sfSoundBufferRecorder_create() );
}

// void sfSoundBufferRecorder_destroy(sfSoundBufferRecorder* soundBufferRecorder);
HB_FUNC( SFSOUNDBUFFERRECORDER_DESTROY )
{
   sfSoundBufferRecorder ** ppSfSoundBufferRecorder = ( sfSoundBufferRecorder ** ) hb_parptrGC( &s_gcSfSoundBufferRecorderFuncs, 1 );

   if( ppSfSoundBufferRecorder && *ppSfSoundBufferRecorder )
   {
      sfSoundBufferRecorder_destroy( *ppSfSoundBufferRecorder );
      *ppSfSoundBufferRecorder = NULL;
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfBool sfSoundBufferRecorder_start(sfSoundBufferRecorder* soundBufferRecorder, unsigned int sampleRate);
HB_FUNC( SFSOUNDBUFFERRECORDER_START )
{
   sfSoundBufferRecorder* soundBufferRecorder = hb_sfSoundBufferRecorder_param( 1 );

   if( soundBufferRecorder && hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_parl( sfSoundBufferRecorder_start( soundBufferRecorder, ( unsigned int ) hb_parni( 2 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSoundBufferRecorder_stop(sfSoundBufferRecorder* soundBufferRecorder);
HB_FUNC( SFSOUNDBUFFERRECORDER_STOP )
{
   sfSoundBufferRecorder* soundBufferRecorder = hb_sfSoundBufferRecorder_param( 1 );

   if( soundBufferRecorder )
   {
      sfSoundBufferRecorder_stop( soundBufferRecorder );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// unsigned int sfSoundBufferRecorder_getSampleRate(const sfSoundBufferRecorder* soundBufferRecorder);
HB_FUNC( SFSOUNDBUFFERRECORDER_GETSAMPLERATE )
{
   const sfSoundBufferRecorder* soundBufferRecorder = hb_sfSoundBufferRecorder_param( 1 );

   if( soundBufferRecorder )
   {
      hb_retni( ( unsigned int ) sfSoundBufferRecorder_getSampleRate( soundBufferRecorder ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// const sfSoundBuffer* sfSoundBufferRecorder_getBuffer(const sfSoundBufferRecorder* soundBufferRecorder);
HB_FUNC( SFSOUNDBUFFERRECORDER_GETBUFFER )
{
   const sfSoundBufferRecorder* soundBufferRecorder = hb_sfSoundBufferRecorder_param( 1 );

   if( soundBufferRecorder )
   {
      hb_sfSoundBuffer_ret( ( sfSoundBuffer* ) sfSoundBufferRecorder_getBuffer( soundBufferRecorder ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfBool sfSoundBufferRecorder_setDevice(sfSoundBufferRecorder* soundBufferRecorder, const char* name);
HB_FUNC( SFSOUNDBUFFERRECORDER_SETDEVICE )
{
   sfSoundBufferRecorder* soundBufferRecorder = hb_sfSoundBufferRecorder_param( 1 );

   if( soundBufferRecorder && hb_param( 1, HB_IT_STRING ) != NULL )
   {
      hb_retl( sfSoundBufferRecorder_setDevice( soundBufferRecorder, hb_parc( 2 ) ) ) ;
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// const char* sfSoundBufferRecorder_getDevice(sfSoundBufferRecorder* soundBufferRecorder);
HB_FUNC( SFSOUNDBUFFERRECORDER_GETDEVICE )
{
   sfSoundBufferRecorder* soundBufferRecorder = hb_sfSoundBufferRecorder_param( 1 );

   if( soundBufferRecorder )
   {
      hb_retc( sfSoundBufferRecorder_getDevice( soundBufferRecorder ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}
