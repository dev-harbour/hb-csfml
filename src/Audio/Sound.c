/*
 * Language bindings to CSFML library: Sound.c
 * version 2.5.1
 *
 * Copyright Rafał Jopek ( rafaljopek at hotmail com )
 * created: 2021-03-22
 * updated: 2021-11-14
 *
 */

#include "hbcsfml.h"

/* Audio/sfSound */
static HB_GARBAGE_FUNC( hb_sfSound_destructor )
{
   sfSound ** ppSfSound = ( sfSound ** ) Cargo;

   if( *ppSfSound )
   {
      sfSound_destroy( *ppSfSound );
      *ppSfSound = NULL;
   }
}

static const HB_GC_FUNCS s_gcSfSoundFuncs =
{
   hb_sfSound_destructor,
   hb_gcDummyMark
};

PHB_ITEM hb_sfSoundItemPut( PHB_ITEM pItem, sfSound * pSfSound )
{
   sfSound ** ppSfSound = ( sfSound ** ) hb_gcAllocate( sizeof( sfSound * ), &s_gcSfSoundFuncs );

   *ppSfSound = pSfSound;
   return hb_itemPutPtrGC( pItem, ppSfSound );
}

sfSound * hb_sfSound_param( int iParam )
{
   sfSound ** ppSfSound = ( sfSound ** ) hb_parptrGC( &s_gcSfSoundFuncs, iParam );

   if( ppSfSound && *ppSfSound )
   {
      return *ppSfSound;
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
      return NULL;
   }
}

void hb_sfSound_ret( sfSound * pSfSound )
{
   hb_sfSoundItemPut( hb_stackReturnItem(), pSfSound );
}

// sfSound* sfSound_create(void);
HB_FUNC( SFSOUND_CREATE )
{
   hb_sfSound_ret( sfSound_create() );
}

// sfSound* sfSound_copy(const sfSound* sound);
HB_FUNC( SFSOUND_COPY )
{
   const sfSound* sound = hb_sfSound_param( 1 );

   if( sound )
   {
      hb_sfSound_ret( sfSound_copy( sound ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSound_destroy(sfSound* sound);
HB_FUNC( SFSOUND_DESTROY )
{
   sfSound ** ppSfSound = ( sfSound ** ) hb_parptrGC( &s_gcSfSoundFuncs, 1 );

   if( ppSfSound && *ppSfSound )
   {
      sfSound_destroy( *ppSfSound );
      *ppSfSound = NULL;
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSound_play(sfSound* sound);
HB_FUNC( SFSOUND_PLAY )
{
   sfSound* sound = hb_sfSound_param( 1 );

   if( sound )
   {
      sfSound_play( sound );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSound_pause(sfSound* sound);
HB_FUNC( SFSOUND_PAUSE )
{
   sfSound* sound = hb_sfSound_param( 1 );

   if( sound )
   {
      sfSound_pause( sound );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSound_stop(sfSound* sound);
HB_FUNC( SFSOUND_STOP )
{
   sfSound* sound = hb_sfSound_param( 1 );

   if( sound )
   {
      sfSound_stop( sound );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSound_setBuffer(sfSound* sound, const sfSoundBuffer* buffer);
HB_FUNC( SFSOUND_SETBUFFER )
{
   sfSound* sound = hb_sfSound_param( 1 );
   const sfSoundBuffer* buffer = hb_sfSoundBuffer_param( 2 );

   if( sound && buffer )
   {
      sfSound_setBuffer( sound, buffer );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// const sfSoundBuffer* sfSound_getBuffer(const sfSound* sound);
HB_FUNC( SFSOUND_GETBUFFER )
{
   const sfSound* sound = hb_sfSound_param( 1 );

   if( sound )
   {
      hb_sfSoundBuffer_ret( ( sfSoundBuffer* ) sfSound_getBuffer( sound ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSound_setLoop(sfSound* sound, sfBool loop);
HB_FUNC( SFSOUND_SETLOOP )
{
   sfSound* sound = hb_sfSound_param( 1 );

   if( sound && hb_param( 3, HB_IT_LOGICAL ) != NULL )
   {
      sfSound_setLoop( sound, hb_parl( 2 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfBool sfSound_getLoop(const sfSound* sound);
HB_FUNC( SFSOUND_GETLOOP )
{
   const sfSound* sound = hb_sfSound_param( 1 );

   if( sound )
   {
      sfSound_getLoop( sound );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfSoundStatus sfSound_getStatus(const sfSound* sound);
HB_FUNC( SFSOUND_GETSTATUS )
{
   const sfSound* sound = hb_sfSound_param( 1 );

   if( sound )
   {
      hb_retni( sfSound_getStatus( sound ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSound_setPitch(sfSound* sound, float pitch);
HB_FUNC( SFSOUND_SETPITCH )
{
   sfSound* sound = hb_sfSound_param( 1 );

   if( sound && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      sfSound_setPitch( sound, ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSound_setVolume(sfSound* sound, float volume);
HB_FUNC( SFSOUND_SETVOLUME )
{
   sfSound* sound = hb_sfSound_param( 1 );

   if( sound && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      sfSound_setVolume( sound, ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSound_setPosition(sfSound* sound, sfVector3f position);
HB_FUNC( SFSOUND_SETPOSITION )
{
   sfSound* sound = hb_sfSound_param( 1 );
   PHB_ITEM pItem;

   if( sound && ( pItem = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 3 )
   {
      sfVector3f position;

      position.x = ( float ) hb_arrayGetNI( pItem, 1 );
      position.y = ( float ) hb_arrayGetNI( pItem, 2 );
      position.z = ( float ) hb_arrayGetNI( pItem, 3 );

      sfSound_setPosition( sound, position );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSound_setRelativeToListener(sfSound* sound, sfBool relative);
HB_FUNC( SFSOUND_SETRELATIVETOLISTENER )
{
   sfSound* sound = hb_sfSound_param( 1 );

   if( sound && hb_param( 2, HB_IT_LOGICAL ) != NULL )
   {
      sfSound_setRelativeToListener( sound, hb_parl( 2 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSound_setMinDistance(sfSound* sound, float distance);
HB_FUNC( SFSOUND_SETMINDISTANCE )
{
   sfSound* sound = hb_sfSound_param( 1 );

   if( sound && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      sfSound_setMinDistance( sound, ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSound_setAttenuation(sfSound* sound, float attenuation);
HB_FUNC( SFSOUND_SETATTENUATION )
{
   sfSound* sound = hb_sfSound_param( 1 );

   if( sound && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {
      sfSound_setAttenuation( sound, ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfSound_setPlayingOffset(sfSound* sound, sfTime timeOffset);
HB_FUNC( SFSOUND_SETPLAYINGOFFSET )
{
   sfSound* sound = hb_sfSound_param( 1 );
   PHB_ITEM pItem;

   if( sound && ( pItem = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 1 )
   {
      sfTime timeOffset;

      timeOffset.microseconds = hb_arrayGetNLL( pItem, 1 );

      sfSound_setPlayingOffset( sound, timeOffset );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}


// float sfSound_getPitch(const sfSound* sound);
HB_FUNC( SFSOUND_GETPITCH )
{
   const sfSound* sound = hb_sfSound_param( 1 );

   if( sound )
   {
      hb_retnd( ( float ) sfSound_getPitch( sound ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// float sfSound_getVolume(const sfSound* sound);
HB_FUNC( SFSOUND_GETVOLUME )
{
   const sfSound* sound = hb_sfSound_param( 1 );

   if( sound )
   {
      hb_retnd( ( float ) sfSound_getVolume( sound ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfVector3f sfSound_getPosition(const sfSound* sound);
HB_FUNC( SFSOUND_GETPOSITION )
{
   const sfSound* sound = hb_sfSound_param( 1 );

   if( sound )
   {
      sfVector3f position = sfSound_getPosition( sound );

      PHB_ITEM pPositionArray = hb_itemArrayNew( 3 );

      hb_arraySetND( pPositionArray, 1, ( float ) position.x );
      hb_arraySetND( pPositionArray, 2, ( float ) position.y );
      hb_arraySetND( pPositionArray, 3, ( float ) position.z );

      hb_itemReturnRelease( pPositionArray );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfBool sfSound_isRelativeToListener(const sfSound* sound);
HB_FUNC( SFSOUND_ISRELATIVETOLISTENER )
{
   const sfSound* sound = hb_sfSound_param( 1 );

   if( sound )
   {
      hb_retl( ( float ) sfSound_isRelativeToListener( sound ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// float sfSound_getMinDistance(const sfSound* sound);
HB_FUNC( SFSOUND_GETMINDISTANCE )
{
   const sfSound* sound = hb_sfSound_param( 1 );

   if( sound )
   {
      hb_retnd( ( float ) sfSound_getMinDistance( sound ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// float sfSound_getAttenuation(const sfSound* sound);
HB_FUNC( SFSOUND_GETATTENUATION )
{
   const sfSound* sound = hb_sfSound_param( 1 );

   if( sound )
   {
      hb_retnd( ( float ) sfSound_getAttenuation( sound ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfTime sfSound_getPlayingOffset(const sfSound* sound);
HB_FUNC( SFSOUND_GETPLAYINGOFFSET )
{
   const sfSound* sound = hb_sfSound_param( 1 );

   if( sound )
   {
      sfTime playingoffset = sfSound_getPlayingOffset( sound );

      PHB_ITEM pPlayingOffsetArray = hb_itemArrayNew( 1 );

      hb_arraySetNLL( pPlayingOffsetArray, 1, playingoffset.microseconds );

      hb_itemReturnRelease( pPlayingOffsetArray );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}
