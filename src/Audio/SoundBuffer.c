/*
 * Language bindings to CSFML library: SoundBuffer.c
 * version 2.5.1
 *
 * Copyright Rafał Jopek ( rafaljopek at hotmail com )
 * created: 2021-03-22
 * updated: 2021-11-14
 *
 */

#include "hbcsfml.h"

/* Audio/sfSoundBuffer */
static HB_GARBAGE_FUNC( hb_sfSoundBuffer_destructor )
{
   sfSoundBuffer ** ppSfSoundBuffer = ( sfSoundBuffer ** ) Cargo;

   if( *ppSfSoundBuffer )
   {
      sfSoundBuffer_destroy( *ppSfSoundBuffer );
      *ppSfSoundBuffer = NULL;
   }
}

static const HB_GC_FUNCS s_gcSfSoundBufferFuncs =
{
   hb_sfSoundBuffer_destructor,
   hb_gcDummyMark
};

PHB_ITEM hb_sfSoundBufferItemPut( PHB_ITEM pItem, sfSoundBuffer * pSfSoundBuffer )
{
   sfSoundBuffer ** ppSfSoundBuffer = ( sfSoundBuffer ** ) hb_gcAllocate( sizeof( sfSoundBuffer * ), &s_gcSfSoundBufferFuncs );

   *ppSfSoundBuffer = pSfSoundBuffer;
   return hb_itemPutPtrGC( pItem, ppSfSoundBuffer );
}

sfSoundBuffer * hb_sfSoundBuffer_param( int iParam )
{
   sfSoundBuffer ** ppSfSoundBuffer = ( sfSoundBuffer ** ) hb_parptrGC( &s_gcSfSoundBufferFuncs, iParam );

   if( ppSfSoundBuffer && *ppSfSoundBuffer )
   {
      return *ppSfSoundBuffer;
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
      return NULL;
   }
}

void hb_sfSoundBuffer_ret( sfSoundBuffer * pSfSoundBuffer )
{
   hb_sfSoundBufferItemPut( hb_stackReturnItem(), pSfSoundBuffer );
}

// sfSoundBuffer* sfSoundBuffer_createFromFile(const char* filename);
HB_FUNC( SFSOUNDBUFFER_CREATEFROMFILE )
{
   if( hb_param( 1, HB_IT_STRING ) != NULL )
   {
      hb_sfSoundBuffer_ret( sfSoundBuffer_createFromFile( hb_parc( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfSoundBuffer* sfSoundBuffer_createFromMemory(const void* data, size_t sizeInBytes);
HB_FUNC( SFSOUNDBUFFER_CREATEFROMMEMORY )
{
   const void* data = hb_parptr( 1 );

   if( data )
   {
      size_t sizeInBytes = ( size_t ) hb_parns( 2 );

      hb_sfSoundBuffer_ret( sfSoundBuffer_createFromMemory( data, sizeInBytes ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfSoundBuffer* sfSoundBuffer_createFromStream(sfInputStream* stream);
HB_FUNC( SFSOUNDBUFFER_CREATEFROMSTREAM )
{
   sfInputStream* stream = hb_parptr( 1 );

   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_sfSoundBuffer_ret( sfSoundBuffer_createFromStream( stream ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfSoundBuffer* sfSoundBuffer_createFromSamples(const sfInt16* samples, sfUint64 sampleCount, unsigned int channelCount, unsigned int sampleRate);
HB_FUNC( SFSOUNDBUFFER_CREATEFROMSAMPLES )
{
   const sfInt16* samples = hb_parptr( 1 );

   if( samples && hb_param( 2, HB_IT_INTEGER ) != NULL &&
                  hb_param( 3, HB_IT_INTEGER ) != NULL &&
                  hb_param( 4, HB_IT_INTEGER ) != NULL )
   {
      hb_sfSoundBuffer_ret( sfSoundBuffer_createFromSamples( samples, ( sfUint64 ) hb_parni( 2 ), ( unsigned int ) hb_parni( 3 ), ( unsigned int ) hb_parni( 4 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfSoundBuffer* sfSoundBuffer_copy(const sfSoundBuffer* soundBuffer);
HB_FUNC( SFSOUNDBUFFER_COPY )
{
   sfSoundBuffer* soundBuffer = hb_sfSoundBuffer_param( 1 );

   if( soundBuffer )
   {
      hb_sfSoundBuffer_ret( sfSoundBuffer_copy( soundBuffer ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSoundBuffer_destroy(sfSoundBuffer* soundBuffer);
HB_FUNC( SFSOUNDBUFFER_DESTROY )
{
   sfSoundBuffer ** ppSfSoundBuffer = ( sfSoundBuffer ** ) hb_parptrGC( &s_gcSfSoundBufferFuncs, 1 );

   if( ppSfSoundBuffer && *ppSfSoundBuffer )
   {
      sfSoundBuffer_destroy( *ppSfSoundBuffer );
      *ppSfSoundBuffer = NULL;
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfBool sfSoundBuffer_saveToFile(const sfSoundBuffer* soundBuffer, const char* filename);
HB_FUNC( SFSOUNDBUFFER_SAVETOFILE )
{
   sfSoundBuffer* soundBuffer = hb_sfSoundBuffer_param( 1 );

   if( soundBuffer && hb_param( 2, HB_IT_STRING ) != NULL )
   {
      hb_retl( sfSoundBuffer_saveToFile( soundBuffer, hb_parc( 2 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// const sfInt16* sfSoundBuffer_getSamples(const sfSoundBuffer* soundBuffer);
HB_FUNC( SFSOUNDBUFFER_GETSAMPLES )
{
   sfSoundBuffer* soundBuffer = hb_sfSoundBuffer_param( 1 );

   if( soundBuffer )
   {
      hb_retptr( ( sfInt16* ) sfSoundBuffer_getSamples( soundBuffer ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfUint64 sfSoundBuffer_getSampleCount(const sfSoundBuffer* soundBuffer);
HB_FUNC( SFSOUNDBUFFER_GETSAMPLECOUNT )
{
   sfSoundBuffer* soundBuffer = hb_sfSoundBuffer_param( 1 );

   if( soundBuffer )
   {
      hb_retni( ( sfUint64 ) sfSoundBuffer_getSampleCount( soundBuffer ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// unsigned int sfSoundBuffer_getSampleRate(const sfSoundBuffer* soundBuffer);
HB_FUNC( SFSOUNDBUFFER_GETSAMPLERATE )
{
   sfSoundBuffer* soundBuffer = hb_sfSoundBuffer_param( 1 );

   if( soundBuffer )
   {
      hb_retni( ( unsigned int ) sfSoundBuffer_getSampleRate( soundBuffer ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// unsigned int sfSoundBuffer_getChannelCount(const sfSoundBuffer* soundBuffer);
HB_FUNC( SFSOUNDBUFFER_GETCHANNELCOUNT )
{
   sfSoundBuffer* soundBuffer = hb_sfSoundBuffer_param( 1 );

   if( soundBuffer )
   {
      hb_retni( ( unsigned int ) sfSoundBuffer_getChannelCount( soundBuffer ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfTime sfSoundBuffer_getDuration(const sfSoundBuffer* soundBuffer);
HB_FUNC( SFSOUNDBUFFER_GETDURATION )
{
   sfSoundBuffer* soundBuffer = hb_sfSoundBuffer_param( 1 );

   if( soundBuffer )
   {
      sfTime duration = sfSoundBuffer_getDuration( soundBuffer );

      PHB_ITEM pDurationArray = hb_itemArrayNew( 1 );

      hb_arraySetNLL( pDurationArray, 1, duration.microseconds );

      hb_itemReturnRelease( pDurationArray );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}
