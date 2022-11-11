/*
 * Language bindings to CSFML library: Listener.c
 * version 2.5.1
 *
 * Copyright Rafał Jopek ( rafaljopek at hotmail com )
 * created: 2021-03-22
 * updated: 2021-11-14
 *
 */

#include "hbcsfml.h"

// void sfListener_setGlobalVolume(float volume);
HB_FUNC( SFLISTENER_SETGLOBALVOLUME )
{
   if( hb_param( 1, HB_IT_NUMERIC ) != NULL )
   {
      sfListener_setGlobalVolume( ( float ) hb_parnd( 1 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// float sfListener_getGlobalVolume(void);
HB_FUNC( SFLISTENER_GETGLOBALVOLUME )
{
   hb_retnd( ( float ) sfListener_getGlobalVolume() );
}

// void sfListener_setPosition(sfVector3f position);
HB_FUNC( SFLISTENER_SETPOSITION )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 3 )
   {
      sfVector3f position;

      position.x = ( float ) hb_arrayGetND( pItem, 1 );
      position.y = ( float ) hb_arrayGetND( pItem, 2 );
      position.z = ( float ) hb_arrayGetND( pItem, 3 );

      sfListener_setPosition( position );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfVector3f sfListener_getPosition();
HB_FUNC( SFLISTENER_GETPOSITION )
{
   sfVector3f position = sfListener_getPosition();

   PHB_ITEM pPositionArray = hb_itemArrayNew( 3 );

   hb_arraySetND( pPositionArray, 1, ( float ) position.x );
   hb_arraySetND( pPositionArray, 2, ( float ) position.y );
   hb_arraySetND( pPositionArray, 3, ( float ) position.z );

   hb_itemReturnRelease( pPositionArray );
}

// void sfListener_setDirection(sfVector3f direction);
HB_FUNC( SFLISTENER_SETDIRECTION )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 3 )
   {
      sfVector3f direction;

      direction.x = ( float ) hb_arrayGetND( pItem, 1 );
      direction.y = ( float ) hb_arrayGetND( pItem, 2 );
      direction.z = ( float ) hb_arrayGetND( pItem, 3 );

      sfListener_setDirection( direction );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfVector3f sfListener_getDirection();
HB_FUNC( SFLISTENER_GETDIRECTION )
{
   sfVector3f direction = sfListener_getDirection( ( unsigned int ) hb_parni( 1 ) );

   PHB_ITEM pDirectionArray = hb_itemArrayNew( 3 );

   hb_arraySetND( pDirectionArray, 1, ( float ) direction.x );
   hb_arraySetND( pDirectionArray, 2, ( float ) direction.y );
   hb_arraySetND( pDirectionArray, 3, ( float ) direction.z );

   hb_itemReturnRelease( pDirectionArray );
}

// void sfListener_setUpVector(sfVector3f upVector);
HB_FUNC( SFLISTENER_SETUPVECTOR )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 3 )
   {
      sfVector3f upVector;

      upVector.x = ( float ) hb_arrayGetND( pItem, 1 );
      upVector.y = ( float ) hb_arrayGetND( pItem, 2 );
      upVector.z = ( float ) hb_arrayGetND( pItem, 3 );

      sfListener_setUpVector( upVector );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfVector3f sfListener_getUpVector();
HB_FUNC( SFLISTENER_GETUPVECTOR )
{
   sfVector3f upvector = sfListener_getUpVector( ( unsigned int ) hb_parni( 1 ) );

   PHB_ITEM pUpVectorArray = hb_itemArrayNew( 3 );

   hb_arraySetND( pUpVectorArray, 1, ( float ) upvector.x );
   hb_arraySetND( pUpVectorArray, 2, ( float ) upvector.y );
   hb_arraySetND( pUpVectorArray, 3, ( float ) upvector.z );

   hb_itemReturnRelease( pUpVectorArray );
}
