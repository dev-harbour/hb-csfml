/*
 * CSFML library: Rect.c
 * version 2.5.1
 *
 * Copyright 2021 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hbcsfml.h"

// sfBool sfFloatRect_contains(const sfFloatRect* rect, float x, float y);
HB_FUNC( SFFLOATRECT_CONTAINS )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 &&
                 hb_param( 2, HB_IT_NUMERIC ) != NULL &&
                 hb_param( 3, HB_IT_NUMERIC ) != NULL )
   {
   sfFloatRect rect;

   rect.left   = ( float ) hb_arrayGetND( pItem, 1 );
   rect.top    = ( float ) hb_arrayGetND( pItem, 2 );
   rect.width  = ( float ) hb_arrayGetND( pItem, 3 );
   rect.height = ( float ) hb_arrayGetND( pItem, 4 );

      hb_retl( sfFloatRect_contains( &rect, ( float ) hb_parnd( 2 ), ( float ) hb_parnd( 3 ) ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfBool sfIntRect_contains(const sfIntRect* rect, int x, int y);
HB_FUNC( SFINTRECT_CONTAINS )
{
   PHB_ITEM pItem;

   if( ( pItem = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 &&
                 hb_param( 2, HB_IT_INTEGER ) != NULL &&
                 hb_param( 3, HB_IT_INTEGER ) != NULL )
   {
    sfIntRect rect;

   rect.left   = hb_arrayGetNI( pItem, 1 );
   rect.top    = hb_arrayGetNI( pItem, 2 );
   rect.width  = hb_arrayGetNI( pItem, 3 );
   rect.height = hb_arrayGetNI( pItem, 4 );

      hb_retl( sfIntRect_contains( &rect, hb_parni( 2 ), hb_parni( 3 ) ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfBool sfFloatRect_intersects(const sfFloatRect* rect1, const sfFloatRect* rect2, sfFloatRect* intersection);
HB_FUNC( SFFLOATRECT_INTERSECTS )
{
   PHB_ITEM pItem1, pItem2, pItem3;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 4 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 &&
       ( pItem3 = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 4 )
   {
   sfFloatRect rect1;

   rect1.left   = ( float ) hb_arrayGetND( pItem1, 1 );
   rect1.top    = ( float ) hb_arrayGetND( pItem1, 2 );
   rect1.width  = ( float ) hb_arrayGetND( pItem1, 3 );
   rect1.height = ( float ) hb_arrayGetND( pItem1, 4 );

   sfFloatRect rect2;

   rect2.left   = ( float ) hb_arrayGetND( pItem2, 1 );
   rect2.top    = ( float ) hb_arrayGetND( pItem2, 2 );
   rect2.width  = ( float ) hb_arrayGetND( pItem2, 3 );
   rect2.height = ( float ) hb_arrayGetND( pItem2, 4 );

   sfFloatRect intersection;

   intersection.left   = ( float ) hb_arrayGetND( pItem3, 1 );
   intersection.top    = ( float ) hb_arrayGetND( pItem3, 2 );
   intersection.width  = ( float ) hb_arrayGetND( pItem3, 3 );
   intersection.height = ( float ) hb_arrayGetND( pItem3, 4 );

      hb_retl( sfFloatRect_intersects( &rect1, &rect2, &intersection ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfBool sfIntRect_intersects(const sfIntRect* rect1, const sfIntRect* rect2, sfIntRect* intersection);
HB_FUNC( SFINTRECT_INTERSECTS )
{
   PHB_ITEM pItem1, pItem2, pItem3;

   if( ( pItem1 = hb_param( 1, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem1 ) == 4 &&
       ( pItem2 = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem2 ) == 4 &&
       ( pItem3 = hb_param( 3, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem3 ) == 4 )
   {
   sfIntRect rect1;

   rect1.left   = hb_arrayGetNI( pItem1, 1 );
   rect1.top    = hb_arrayGetNI( pItem1, 2 );
   rect1.width  = hb_arrayGetNI( pItem1, 3 );
   rect1.height = hb_arrayGetNI( pItem1, 4 );

   sfIntRect rect2;

   rect2.left   = hb_arrayGetNI( pItem2, 1 );
   rect2.top    = hb_arrayGetNI( pItem2, 2 );
   rect2.width  = hb_arrayGetNI( pItem2, 3 );
   rect2.height = hb_arrayGetNI( pItem2, 4 );

   sfIntRect intersection;

   intersection.left   = hb_arrayGetNI( pItem3, 1 );
   intersection.top    = hb_arrayGetNI( pItem3, 2 );
   intersection.width  = hb_arrayGetNI( pItem3, 3 );
   intersection.height = hb_arrayGetNI( pItem3, 4 );

      hb_retl( sfIntRect_intersects( &rect1, &rect2, &intersection ) );
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}
