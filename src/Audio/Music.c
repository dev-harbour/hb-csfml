/*
 * Language bindings to CSFML library: Music.c
 * version 2.5.1
 *
 * Copyright Rafał Jopek ( rafaljopek at hotmail com )
 * created: 2021-03-22
 * updated: 2021-11-14
 *
 */

#include "hbcsfml.h"

/* Audio/sfMusic */
static HB_GARBAGE_FUNC( hb_sfMusic_destructor )
{
   sfMusic ** ppSfMusic = ( sfMusic ** ) Cargo;

   if( *ppSfMusic )
   {
      sfMusic_destroy( *ppSfMusic );
      *ppSfMusic = NULL;
   }
}

static const HB_GC_FUNCS s_gcSfMusicFuncs =
{
   hb_sfMusic_destructor,
   hb_gcDummyMark
};

PHB_ITEM hb_sfMusicItemPut( PHB_ITEM pItem, sfMusic * pSfMusic )
{
   sfMusic ** ppSfMusic = ( sfMusic ** ) hb_gcAllocate( sizeof( sfMusic * ), &s_gcSfMusicFuncs );

   *ppSfMusic = pSfMusic;
   return hb_itemPutPtrGC( pItem, ppSfMusic );
}

sfMusic * hb_sfMusic_param( int iParam )
{
   sfMusic ** ppSfMusic = ( sfMusic ** ) hb_parptrGC( &s_gcSfMusicFuncs, iParam );

   if( ppSfMusic && *ppSfMusic )
   {
      return *ppSfMusic;
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
      return NULL;
   }
}

void hb_sfMusic_ret( sfMusic * pSfMusic )
{
   hb_sfMusicItemPut( hb_stackReturnItem(), pSfMusic );
}

// sfMusic* sfMusic_createFromFile(const char* filename);
HB_FUNC( SFMUSIC_CREATEFROMFILE )
{
   if( hb_param( 1, HB_IT_STRING )  != NULL )
   {
      hb_sfMusic_ret( sfMusic_createFromFile( hb_parc( 1 ) ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfMusic* sfMusic_createFromMemory(const void* data, size_t sizeInBytes);
HB_FUNC( SFMUSIC_CREATEFROMMEMORY )
{
}

// sfMusic* sfMusic_createFromStream(sfInputStream* stream);
HB_FUNC( SFMUSIC_CREATEFROMSTREAM )
{
   sfInputStream* stream = hb_parptr( 1 );

   if( hb_param( 1, HB_IT_INTEGER ) != NULL )
   {
      hb_sfMusic_ret( sfMusic_createFromStream( stream ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfMusic_destroy(sfMusic* music);
HB_FUNC( SFMUSIC_DESTROY )
{
   sfMusic ** ppSfMusic = ( sfMusic ** ) hb_parptrGC( &s_gcSfMusicFuncs, 1 );

   if( ppSfMusic && *ppSfMusic )
   {
      sfMusic_destroy( *ppSfMusic );
      *ppSfMusic = NULL;
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfMusic_setLoop(sfMusic* music, sfBool loop);
HB_FUNC( SFMUSIC_SETLOOP )
{
   sfMusic* music = hb_sfMusic_param( 1 );

   if( music && hb_param( 2, HB_IT_LOGICAL ) != NULL )
   {
      sfMusic_setLoop( music, hb_parl( 2 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfBool sfMusic_getLoop(const sfMusic* music);
HB_FUNC( SFMUSIC_GETLOOP )
{
   const sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      hb_retl( sfMusic_getLoop( music ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfTime sfMusic_getDuration(const sfMusic* music);
HB_FUNC( SFMUSIC_GETDURATION )
{
   const sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      sfTime duration = sfMusic_getDuration( music );

      PHB_ITEM pDurationArray = hb_itemArrayNew( 1 );

      hb_arraySetNLL( pDurationArray, 1, duration.microseconds );

      hb_itemReturnRelease( pDurationArray );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfTimeSpan sfMusic_getLoopPoints(const sfMusic* music);
HB_FUNC( SFMUSIC_GETLOOPPOINTS )
{
   const sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      sfTimeSpan looppoints = sfMusic_getLoopPoints( music );

      PHB_ITEM pLoopPointsArray = hb_itemArrayNew( 2 );

         // sfTime offset
         PHB_ITEM pSubarrayTime1 = hb_arrayGetItemPtr( pLoopPointsArray, 1 );

         hb_arrayNew( pSubarrayTime1, 1 );
         hb_arraySetNLL( pSubarrayTime1, 1, looppoints.offset.microseconds );

         // sfTime length
         PHB_ITEM pSubarrayTime2 = hb_arrayGetItemPtr( pLoopPointsArray, 2 );

         hb_arrayNew( pSubarrayTime2, 1 );
         hb_arraySetNLL( pSubarrayTime2, 1, looppoints.length.microseconds );

      hb_itemReturnRelease( pLoopPointsArray );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfMusic_setLoopPoints(sfMusic* music, sfTimeSpan timePoints);
HB_FUNC( SFMUSIC_SETLOOPPOINTS )
{
   PHB_ITEM pItem;

   sfMusic* music = hb_sfMusic_param( 1 );

   if( music && ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 2 )
   {
      sfTimeSpan timePoints;

      // sfTime offset
      PHB_ITEM pSubarrayTime1 = hb_arrayGetItemPtr( pItem, 1 );

      timePoints.offset.microseconds = hb_arrayGetNLL( pSubarrayTime1, 1 );

      // sfTime length
      PHB_ITEM pSubarrayTime2 = hb_arrayGetItemPtr( pItem, 2 );

      timePoints.length.microseconds = hb_arrayGetNLL( pSubarrayTime2, 1 );

      sfMusic_setLoopPoints( music, timePoints );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfMusic_play(sfMusic* music);
HB_FUNC( SFMUSIC_PLAY )
{
   sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      sfMusic_play( music );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfMusic_pause(sfMusic* music);
HB_FUNC( SFMUSIC_PAUSE )
{
   sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      sfMusic_pause( music );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfMusic_stop(sfMusic* music);
HB_FUNC( SFMUSIC_STOP )
{
   sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      sfMusic_stop( music );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// unsigned int sfMusic_getChannelCount(const sfMusic* music);
HB_FUNC( SFMUSIC_GETCHANNELCOUNT )
{
   const sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      hb_retni( ( unsigned int ) sfMusic_getChannelCount( music ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// unsigned int sfMusic_getSampleRate(const sfMusic* music);
HB_FUNC( SFMUSIC_GETSAMPLERATE )
{
   const sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      hb_retni( ( unsigned int ) sfMusic_getSampleRate( music ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfSoundStatus sfMusic_getStatus(const sfMusic* music);
HB_FUNC( SFMUSIC_GETSTATUS )
{
   const sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      hb_retni( ( sfSoundStatus ) sfMusic_getStatus( music ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfTime sfMusic_getPlayingOffset(const sfMusic* music);
HB_FUNC( SFMUSIC_GETPLAYINGOFFSET )
{
   const sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      sfTime playingoffset = sfMusic_getPlayingOffset( music );

      PHB_ITEM pPlayingOffsetArray = hb_itemArrayNew( 1 );

      hb_arraySetNLL( pPlayingOffsetArray, 1, playingoffset.microseconds );

      hb_itemReturnRelease( pPlayingOffsetArray );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfMusic_setPitch(sfMusic* music, float pitch);
HB_FUNC( SFMUSIC_SETPITCH )
{
   sfMusic* music = hb_sfMusic_param( 1 );

   if( music && hb_param( 1, HB_IT_NUMERIC ) != NULL )
   {
      sfMusic_setPitch( music, ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfMusic_setVolume(sfMusic* music, float volume);
HB_FUNC( SFMUSIC_SETVOLUME )
{
   sfMusic* music = hb_sfMusic_param( 1 );

   if( music && hb_param( 1, HB_IT_NUMERIC ) != NULL )
   {
      sfMusic_setVolume( music, ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfMusic_setPosition(sfMusic* music, sfVector3f position);
HB_FUNC( SFMUSIC_SETPOSITION )
{
   sfMusic* music = hb_sfMusic_param( 1 );
   PHB_ITEM pItem;

   if( music && ( pItem = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 3 )
   {
      sfVector3f position;

      position.x = ( float ) hb_arrayGetNI( pItem, 1 );
      position.y = ( float ) hb_arrayGetNI( pItem, 2 );
      position.z = ( float ) hb_arrayGetNI( pItem, 3 );

      sfMusic_setPosition( music, position );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfMusic_setRelativeToListener(sfMusic* music, sfBool relative);
HB_FUNC( SFMUSIC_SETRELATIVETOLISTENER )
{
   sfMusic* music = hb_sfMusic_param( 1 );

   if( music && hb_param( 2, HB_IT_LOGICAL ) != NULL )
   {
      sfMusic_setRelativeToListener( music, hb_parl( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfMusic_setMinDistance(sfMusic* music, float distance);
HB_FUNC( SFMUSIC_SETMINDISTANCE )
{
   sfMusic* music = hb_sfMusic_param( 1 );

   if( music && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      sfMusic_setMinDistance( music, ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfMusic_setAttenuation(sfMusic* music, float attenuation);
HB_FUNC( SFMUSIC_SETATTENUATION )
{
   sfMusic* music = hb_sfMusic_param( 1 );

   if( music && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      sfMusic_setAttenuation( music, ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfMusic_setPlayingOffset(sfMusic* music, sfTime timeOffset);
HB_FUNC( SFMUSIC_SETPLAYINGOFFSET )
{
   sfMusic* music = hb_sfMusic_param( 1 );
   PHB_ITEM pItem;

   if( music && ( pItem = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 1 )
   {
      sfTime timeOffset;

      timeOffset.microseconds = hb_arrayGetNLL( pItem, 1 );

      sfMusic_setPlayingOffset( music, timeOffset );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// float sfMusic_getPitch(const sfMusic* music);
HB_FUNC( SFMUSIC_GETPITCH )
{
   const sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      hb_retnd( ( float ) sfMusic_getPitch( music ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// float sfMusic_getVolume(const sfMusic* music);
HB_FUNC( SFMUSIC_GETVOLUME )
{
   const sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      hb_retnd( ( float ) sfMusic_getVolume( music ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfVector3f sfMusic_getPosition(const sfMusic* music);
HB_FUNC( SFMUSIC_GETPOSITION )
{
   const sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      sfVector3f position = sfMusic_getPosition( music );

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

// sfBool sfMusic_isRelativeToListener(const sfMusic* music);
HB_FUNC( SFMUSIC_ISRELATIVETOLISTENER )
{
   const sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      hb_retl( sfMusic_isRelativeToListener( music ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// float sfMusic_getMinDistance(const sfMusic* music);
HB_FUNC( SFMUSIC_GETMINDISTANCE )
{
   const sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      hb_retnd( ( float ) sfMusic_getMinDistance( music ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// float sfMusic_getAttenuation(const sfMusic* music);
HB_FUNC( SFMUSIC_GETATTENUATION )
{
   const sfMusic* music = hb_sfMusic_param( 1 );

   if( music )
   {
      hb_retnd( ( float ) sfMusic_getAttenuation( music ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}
