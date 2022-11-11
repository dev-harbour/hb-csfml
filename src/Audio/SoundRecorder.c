/*
 * Language bindings to CSFML library: SoundRecorder.c
 * version 2.5.1
 *
 * Copyright Rafał Jopek ( rafaljopek at hotmail com )
 * created: 2021-03-22
 * updated: 2021-11-14
 *
 */

#include "hbcsfml.h"

/* Audio/sfSoundRecorder */
static HB_GARBAGE_FUNC( hb_sfSoundRecorder_destructor )
{
   sfSoundRecorder ** ppSfSoundRecorder = ( sfSoundRecorder ** ) Cargo;

   if( *ppSfSoundRecorder )
   {
      sfSoundRecorder_destroy( *ppSfSoundRecorder );
      *ppSfSoundRecorder = NULL;
   }
}

static const HB_GC_FUNCS s_gcSfSoundRecorderFuncs =
{
   hb_sfSoundRecorder_destructor,
   hb_gcDummyMark
};

PHB_ITEM hb_sfSoundRecorderItemPut( PHB_ITEM pItem, sfSoundRecorder * pSfSoundBuffer )
{
   sfSoundRecorder ** ppSfSoundRecorder = ( sfSoundRecorder ** ) hb_gcAllocate( sizeof( sfSoundRecorder * ), &s_gcSfSoundRecorderFuncs );

   *ppSfSoundRecorder = pSfSoundBuffer;
   return hb_itemPutPtrGC( pItem, ppSfSoundRecorder );
}

sfSoundRecorder * hb_sfSoundRecorder_param( int iParam )
{
   sfSoundRecorder ** ppSfSoundRecorder = ( sfSoundRecorder ** ) hb_parptrGC( &s_gcSfSoundRecorderFuncs, iParam );

   if( ppSfSoundRecorder && *ppSfSoundRecorder )
   {
      return *ppSfSoundRecorder;
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
      return NULL;
   }
}

void hb_sfSoundRecorder_ret( sfSoundRecorder * pSfSoundBuffer )
{
   hb_sfSoundRecorderItemPut( hb_stackReturnItem(), pSfSoundBuffer );
}

// typedef sfBool (*sfSoundRecorderStartCallback)(void*);                           ///< Type of the callback used when starting a capture
// typedef sfBool (*sfSoundRecorderProcessCallback)(const sfInt16*, size_t, void*); ///< Type of the callback used to process audio data
// typedef void   (*sfSoundRecorderStopCallback)(void*);                            ///< Type of the callback used when stopping a capture

// sfSoundRecorder* sfSoundRecorder_create(sfSoundRecorderStartCallback onStart, sfSoundRecorderProcessCallback onProcess, sfSoundRecorderStopCallback onStop, void* userData);

// void sfSoundRecorder_destroy(sfSoundRecorder* soundRecorder);
HB_FUNC( SFSOUNDRECORDER_DESTROY )
{
   sfSoundRecorder ** ppSfSoundRecorder = ( sfSoundRecorder ** ) hb_parptrGC( &s_gcSfSoundRecorderFuncs, 1 );

   if( ppSfSoundRecorder && *ppSfSoundRecorder )
   {
      sfSoundRecorder_destroy( *ppSfSoundRecorder );
      *ppSfSoundRecorder = NULL;
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfBool sfSoundRecorder_start(sfSoundRecorder* soundRecorder, unsigned int sampleRate);
HB_FUNC( SFSOUNDRECORDER_START )
{
   sfSoundRecorder* soundRecorder = hb_sfSoundRecorder_param( 1 );

   if( soundRecorder && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      hb_retl( sfSoundRecorder_start( soundRecorder, ( unsigned int ) hb_parni( 2 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSoundRecorder_stop(sfSoundRecorder* soundRecorder);
HB_FUNC( SFSOUNDRECORDER_STOP )
{
   sfSoundRecorder* soundRecorder = hb_sfSoundRecorder_param( 1 );

   if( soundRecorder )
   {
      sfSoundRecorder_stop( soundRecorder );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// unsigned int sfSoundRecorder_getSampleRate(const sfSoundRecorder* soundRecorder);
HB_FUNC( SFSOUNDRECORDER_GETSAMPLERATE )
{
   sfSoundRecorder* soundRecorder = hb_sfSoundRecorder_param( 1 );

   if( soundRecorder )
   {
      hb_retni( ( unsigned int ) sfSoundRecorder_getSampleRate( soundRecorder ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfBool sfSoundRecorder_isAvailable(void);
HB_FUNC( SFSOUNDRECORDER_ISAVAILABLE )
{
   hb_retl( sfSoundRecorder_isAvailable() );
}

// void sfSoundRecorder_setProcessingInterval(sfSoundRecorder* soundRecorder, sfTime interval);
HB_FUNC( SFSOUNDRECORDER_SETPROCESSINGINTERVAL )
{
   sfSoundRecorder* soundRecorder = hb_sfSoundRecorder_param( 1 );
   PHB_ITEM pItem;

   if( soundRecorder && ( pItem = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 1 )
   {
      sfTime interval;

      interval.microseconds = hb_arrayGetNLL( pItem, 1 );

      sfSoundRecorder_setProcessingInterval( soundRecorder, interval );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// const char** sfSoundRecorder_getAvailableDevices(size_t* count);

// const char* sfSoundRecorder_getDefaultDevice();
HB_FUNC( SFSOUNDRECORDER_GETDEFAULTDEVICE )
{
   hb_retc( sfSoundRecorder_getDefaultDevice() );
}

// sfBool sfSoundRecorder_setDevice(sfSoundRecorder* soundRecorder, const char* name);
HB_FUNC( SFSOUNDRECORDER_SETDEVICE )
{
   sfSoundRecorder* soundRecorder = hb_sfSoundRecorder_param( 1 );

   if( soundRecorder && hb_param( 2, HB_IT_STRING ) != NULL )
   {
      hb_retl( sfSoundRecorder_setDevice( soundRecorder, hb_parc( 2 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// const char* sfSoundRecorder_getDevice(sfSoundRecorder* soundRecorder);
HB_FUNC( SFSOUNDRECORDER_GETDEVICE )
{
   sfSoundRecorder* soundRecorder = hb_sfSoundRecorder_param( 1 );

   if( soundRecorder )
   {
      hb_retc( sfSoundRecorder_getDevice( soundRecorder ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSoundRecorder_setChannelCount(sfSoundRecorder* soundRecorder, unsigned int channelCount);
HB_FUNC( SFSOUNDRECORDER_SETCHANNELCOUNT )
{
   sfSoundRecorder* soundRecorder = hb_sfSoundRecorder_param( 1 );

   if( soundRecorder )
   {
      sfSoundRecorder_setChannelCount( soundRecorder, ( unsigned int ) hb_parni( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// unsigned int sfSoundRecorder_getChannelCount(const sfSoundRecorder* soundRecorder);
HB_FUNC( SFSOUNDRECORDER_GETCHANNELCOUNT )
{
   const sfSoundRecorder* soundRecorder = hb_sfSoundRecorder_param( 1 );

   if( soundRecorder )
   {
      hb_retni( ( unsigned int ) sfSoundRecorder_getChannelCount( soundRecorder ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}
