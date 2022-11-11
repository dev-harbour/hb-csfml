/*
 * Language bindings to CSFML library: SoundStream.c
 * version 2.5.1
 *
 * Copyright Rafał Jopek ( rafaljopek at hotmail com )
 * created: 2021-03-22
 * updated: 2021-11-18
 *
 */

#include "hbcsfml.h"

/* Audio/sfSoundStream */
static HB_GARBAGE_FUNC( hb_sfSoundStream_destructor )
{
   sfSoundStream ** ppSfSoundStream = ( sfSoundStream ** ) Cargo;

   if( *ppSfSoundStream )
   {
      sfSoundStream_destroy( *ppSfSoundStream );
      *ppSfSoundStream = NULL;
   }
}

static const HB_GC_FUNCS s_gcSfSoundStreamFuncs =
{
   hb_sfSoundStream_destructor,
   hb_gcDummyMark
};

PHB_ITEM hb_sfSoundStreamItemPut( PHB_ITEM pItem, sfSoundStream * pSfSoundStream )
{
   sfSoundStream ** ppSfSoundStream = ( sfSoundStream ** ) hb_gcAllocate( sizeof( sfSoundStream * ), &s_gcSfSoundStreamFuncs );

   *ppSfSoundStream = pSfSoundStream;
   return hb_itemPutPtrGC( pItem, ppSfSoundStream );
}

sfSoundStream * hb_sfSoundStream_param( int iParam )
{
   sfSoundStream ** ppSfSoundStream = ( sfSoundStream ** ) hb_parptrGC( &s_gcSfSoundStreamFuncs, iParam );

   if( ppSfSoundStream && *ppSfSoundStream )
   {
      return *ppSfSoundStream;
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
      return NULL;
   }
}

void hb_sfSoundStream_ret( sfSoundStream * pSfSoundStream )
{
   hb_sfSoundStreamItemPut( hb_stackReturnItem(), pSfSoundStream );
}

// typedef sfBool (*sfSoundStreamGetDataCallback)(sfSoundStreamChunk*, void*); ///< Type of the callback used to get a sound stream data
// typedef void   (*sfSoundStreamSeekCallback)(sfTime, void*);                 ///< Type of the callback used to seek in a sound stream

// sfSoundStream* sfSoundStream_create(sfSoundStreamGetDataCallback onGetData, sfSoundStreamSeekCallback onSeek, unsigned int channelCount, unsigned int sampleRate, void* userData);

// void sfSoundStream_destroy(sfSoundStream* soundStream);
HB_FUNC( SFSOUNDSTREAM_DESTROY )
{
   sfSoundStream ** ppSfSoundStream = ( sfSoundStream ** ) hb_parptrGC( &s_gcSfSoundStreamFuncs, 1 );

   if( ppSfSoundStream && *ppSfSoundStream )
   {
      sfSoundStream_destroy( *ppSfSoundStream );
      *ppSfSoundStream = NULL;
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSoundStream_play(sfSoundStream* soundStream);
HB_FUNC( SFSOUNDSTREAM_PLAY )
{
   sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream )
   {
      sfSoundStream_play( soundStream );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSoundStream_pause(sfSoundStream* soundStream);
HB_FUNC( SFSOUNDSTREAM_PAUSE )
{
   sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream )
   {
      sfSoundStream_pause( soundStream );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSoundStream_stop(sfSoundStream* soundStream);
HB_FUNC( SFSOUNDSTREAM_STOP )
{
   sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream )
   {
      sfSoundStream_stop( soundStream );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfSoundStatus sfSoundStream_getStatus(const sfSoundStream* soundStream);
HB_FUNC( SFSOUNDSTREAM_GETSTATUS )
{
   sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream )
   {
      hb_retni( sfSoundStream_getStatus( soundStream ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// unsigned int sfSoundStream_getChannelCount(const sfSoundStream* soundStream);
HB_FUNC( SFSOUNDSTREAM_GETCHANNELCOUNT )
{
   const sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream )
   {
      hb_retni( ( unsigned int ) sfSoundStream_getChannelCount( soundStream ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// unsigned int sfSoundStream_getSampleRate(const sfSoundStream* soundStream);
HB_FUNC( SFSOUNDSTREAM_GETSAMPLERATE )
{
   const sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream )
   {
      hb_retni( ( unsigned int ) sfSoundStream_getSampleRate( soundStream ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSoundStream_setPitch(sfSoundStream* soundStream, float pitch);
HB_FUNC( SFSOUNDSTREAM_SETPITCH )
{
   sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      sfSoundStream_setPitch( soundStream, ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSoundStream_setVolume(sfSoundStream* soundStream, float volume);
HB_FUNC( SFSOUNDSTREAM_SETVOLUME )
{
   sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      sfSoundStream_setVolume( soundStream, ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSoundStream_setPosition(sfSoundStream* soundStream, sfVector3f position);
HB_FUNC( SFSOUNDSTREAM_SETPOSITION )
{
   sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );
   PHB_ITEM pItem;

   if( soundStream && ( pItem = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 3 )
   {
      sfVector3f position;

      position.x = ( float ) hb_arrayGetNI( pItem, 1 );
      position.y = ( float ) hb_arrayGetNI( pItem, 2 );
      position.z = ( float ) hb_arrayGetNI( pItem, 3 );

      sfSoundStream_setPosition( soundStream, position );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSoundStream_setRelativeToListener(sfSoundStream* soundStream, sfBool relative);
HB_FUNC( SFSOUNDSTREAM_SETRELATIVETOLISTENER )
{
   sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream && hb_param( 2, HB_IT_LOGICAL ) != NULL )
   {
      sfSoundStream_setRelativeToListener( soundStream, hb_parl( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSoundStream_setMinDistance(sfSoundStream* soundStream, float distance);
HB_FUNC( SFSOUNDSTREAM_SETMINDISTANCE )
{
   sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      sfSoundStream_setMinDistance( soundStream, ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSoundStream_setAttenuation(sfSoundStream* soundStream, float attenuation);
HB_FUNC( SFSOUNDSTREAM_SETATTENUATION )
{
   sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      sfSoundStream_setAttenuation( soundStream, ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSoundStream_setPlayingOffset(sfSoundStream* soundStream, sfTime timeOffset);
HB_FUNC( SFSOUNDSTREAM_SETPLAYINGOFFSET )
{
   sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );
   PHB_ITEM pItem;

   if( soundStream && ( pItem = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 1 )
   {
      sfTime timeOffset;

      timeOffset.microseconds = hb_arrayGetNLL( pItem, 1 );

      sfSoundStream_setPlayingOffset( soundStream, timeOffset );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSoundStream_setLoop(sfSoundStream* soundStream, sfBool loop);
HB_FUNC( SFSOUNDSTREAM_SETLOOP )
{
   sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream && hb_param( 2, HB_IT_LOGICAL ) != NULL )
   {
      sfSoundStream_setLoop( soundStream, hb_parl( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// float sfSoundStream_getPitch(const sfSoundStream* soundStream);
HB_FUNC( SFSOUNDSTREAM_GETPITCH )
{
   const sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream )
   {
      sfSoundStream_getPitch( soundStream );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// float sfSoundStream_getVolume(const sfSoundStream* soundStream);
HB_FUNC( SFSOUNDSTREAM_GETVOLUME )
{
   const sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream )
   {
      hb_retnd( ( float ) sfSoundStream_getVolume( soundStream ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfVector3f sfSoundStream_getPosition(const sfSoundStream* soundStream);
HB_FUNC( SFSOUNDSTREAM_GETPOSITION )
{
   const sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream )
   {
      sfVector3f position = sfSoundStream_getPosition( soundStream );

      PHB_ITEM pPositionArray = hb_itemArrayNew( 3 );

      hb_arraySetND( pPositionArray, 1, ( float ) position.x );
      hb_arraySetND( pPositionArray, 2, ( float ) position.y );
      hb_arraySetND( pPositionArray, 3, ( float ) position.z );

      hb_itemReturnRelease( pPositionArray );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfBool sfSoundStream_isRelativeToListener(const sfSoundStream* soundStream);
HB_FUNC( SFSOUNDSTREAM_ISRELATIVETOLISTENER )
{
   const sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream )
   {
      hb_retl( sfSoundStream_isRelativeToListener( soundStream ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// float sfSoundStream_getMinDistance(const sfSoundStream* soundStream);
HB_FUNC( SFSOUNDSTREAM_GETMINDISTANCE )
{
   const sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream )
   {
      hb_retnd( ( float ) sfSoundStream_getMinDistance( soundStream ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// float sfSoundStream_getAttenuation(const sfSoundStream* soundStream);
HB_FUNC( SFSOUNDSTREAM_GETATTENUATION )
{
   const sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream )
   {
      hb_retnd( ( float ) sfSoundStream_getAttenuation( soundStream ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfBool sfSoundStream_getLoop(const sfSoundStream* soundStream);
HB_FUNC( SFSOUNDSTREAM_GETLOOP )
{
   const sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream )
   {
      hb_retl( sfSoundStream_getLoop( soundStream ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfTime sfSoundStream_getPlayingOffset(const sfSoundStream* soundStream);
HB_FUNC( SFSOUNDSTREAM_GETPLAYINGOFFSET )
{
   const sfSoundStream* soundStream = hb_sfSoundStream_param( 1 );

   if( soundStream )
   {
      sfTime playingoffset = sfSoundStream_getPlayingOffset( soundStream );

      PHB_ITEM pPlayingOffsetArray = hb_itemArrayNew( 1 );

      hb_arraySetNLL( pPlayingOffsetArray, 1, playingoffset.microseconds );

      hb_itemReturnRelease( pPlayingOffsetArray );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}
