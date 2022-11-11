/*
 * CSFML library: Text.c
 * version 2.5.1
 *
 * Copyright 2021 Rafał Jopek ( rafaljopek at hotmail com )
 *
 */

#include "hbcsfml.h"

/* Graphics/sfText */
static HB_GARBAGE_FUNC( hb_sfText_destructor )
{
   sfText ** ppSfText = ( sfText ** ) Cargo;

   if( *ppSfText )
   {
      sfText_destroy( *ppSfText );
      *ppSfText = NULL;
   }
}

static const HB_GC_FUNCS s_gcSfTextFuncs =
{
   hb_sfText_destructor,
   hb_gcDummyMark
};

PHB_ITEM hb_sfTextItemPut( PHB_ITEM pItem, sfText * pSfText )
{
   sfText ** ppSfText = ( sfText ** ) hb_gcAllocate( sizeof( sfText * ), &s_gcSfTextFuncs );

   *ppSfText = pSfText;
   return hb_itemPutPtrGC( pItem, ppSfText );
}

sfText * hb_sfText_param( int iParam )
{
   sfText ** ppSfText = ( sfText ** ) hb_parptrGC( &s_gcSfTextFuncs, iParam );

   if( ppSfText && *ppSfText )
   {
      return *ppSfText;
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
      return NULL;
   }
}

void hb_sfText_ret( sfText * pSfText )
{
   hb_sfTextItemPut( hb_stackReturnItem(), pSfText );
}

// sfText* sfText_create(void);
HB_FUNC( SFTEXT_CREATE )
{
   hb_sfText_ret( sfText_create() );
}

// sfText* sfText_copy(const sfText* text);

// void sfText_destroy(sfText* text);
HB_FUNC( SFTEXT_DESTROY )
{
   sfText ** ppSfText = ( sfText ** ) hb_parptrGC( &s_gcSfTextFuncs, 1 );

   if( ppSfText && *ppSfText )
   {
      sfText_destroy( *ppSfText );
      *ppSfText = NULL;
   }
   else
   {
      hb_errRT_BASE( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfText_setPosition(sfText* text, sfVector2f position);

// void sfText_setRotation(sfText* text, float angle);

// void sfText_setScale(sfText* text, sfVector2f scale);

// void sfText_setOrigin(sfText* text, sfVector2f origin);

// sfVector2f sfText_getPosition(const sfText* text);

// float sfText_getRotation(const sfText* text);

// sfVector2f sfText_getScale(const sfText* text);

// sfVector2f sfText_getOrigin(const sfText* text);

// void sfText_move(sfText* text, sfVector2f offset);

// void sfText_rotate(sfText* text, float angle);

// void sfText_scale(sfText* text, sfVector2f factors);

// sfTransform sfText_getTransform(const sfText* text);

// sfTransform sfText_getInverseTransform(const sfText* text);

// void sfText_setString(sfText* text, const char* string);
HB_FUNC( SFTEXT_SETSTRING )
{
   sfText* text = hb_sfText_param( 1 );

   if( text && hb_param( 2, HB_IT_STRING ) != NULL )
   {
      sfText_setString( text, hb_parc( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfText_setUnicodeString(sfText* text, const sfUint32* string);

// void sfText_setFont(sfText* text, const sfFont* font);
HB_FUNC( SFTEXT_SETFONT )
{
   sfText* text = hb_sfText_param( 1 );
   sfFont* font = hb_sfFont_param( 2 );

   if( text && font )
   {
      sfText_setFont( text, font );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfText_setCharacterSize(sfText* text, unsigned int size);
HB_FUNC( SFTEXT_SETCHARACTERSIZE )
{
   sfText* text = hb_sfText_param( 1 );

   if( text && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {
      sfText_setCharacterSize( text, ( unsigned int ) hb_parni( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfText_setLineSpacing(sfText* text, float spacingFactor);
HB_FUNC( SFTEXT_SETLINESPACING )
{
   sfText* text = hb_sfText_param( 1 );

   if( text && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {

      sfText_setLineSpacing( text, ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfText_setLetterSpacing(sfText* text, float spacingFactor);
HB_FUNC( SFTEXT_SETLETTERSPACING )
{
   sfText* text = hb_sfText_param( 1 );

   if( text && hb_param( 2, HB_IT_NUMERIC ) != NULL )
   {

      sfText_setLetterSpacing( text, ( float ) hb_parnd( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfText_setStyle(sfText* text, sfUint32 style);
HB_FUNC( SFTEXT_SETSTYLE )
{
   sfText* text = hb_sfText_param( 1 );

   if( text && hb_param( 2, HB_IT_INTEGER ) != NULL )
   {

      sfText_setStyle( text, ( sfUint32 ) hb_parni( 2 ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfText_setColor(sfText* text, sfColor color);
HB_FUNC( SFTEXT_SETCOLOR )
{
   sfText* text = hb_sfText_param( 1 );
   PHB_ITEM pItem;

   if( text && ( pItem = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 )
   {
      sfColor color;

      color.r = ( sfUint8 ) hb_arrayGetNI( pItem, 1 );
      color.g = ( sfUint8 ) hb_arrayGetNI( pItem, 2 );
      color.b = ( sfUint8 ) hb_arrayGetNI( pItem, 3 );
      color.a = ( sfUint8 ) hb_arrayGetNI( pItem, 4 );

      sfText_setColor( text, color );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfText_setFillColor(sfText* text, sfColor color);
HB_FUNC( SFTEXT_SETFILLCOLOR )
{
   sfText* text = hb_sfText_param( 1 );
   PHB_ITEM pItem;

   if( text && ( pItem = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 )
   {
      sfColor color;

      color.r =  hb_arrayGetNI( pItem, 1 );
      color.g =  hb_arrayGetNI( pItem, 2 );
      color.b =  hb_arrayGetNI( pItem, 3 );
      color.a =  hb_arrayGetNI( pItem, 4 );

      sfText_setFillColor( text, color );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfText_setOutlineColor(sfText* text, sfColor color);
HB_FUNC( SFTEXT_SETOUTLINECOLOR )
{
   sfText* text = hb_sfText_param( 1 );
   PHB_ITEM pItem;

   if( text && ( pItem = hb_param( 2, HB_IT_ARRAY ) ) != NULL && hb_arrayLen( pItem ) == 4 )
   {
      sfColor color;

      color.r = ( sfUint8 ) hb_arrayGetNI( pItem, 1 );
      color.g = ( sfUint8 ) hb_arrayGetNI( pItem, 2 );
      color.b = ( sfUint8 ) hb_arrayGetNI( pItem, 3 );
      color.a = ( sfUint8 ) hb_arrayGetNI( pItem, 4 );

      sfText_setOutlineColor( text, color );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// void sfText_setOutlineThickness(sfText* text, float thickness);

// const char* sfText_getString(const sfText* text);

// const sfUint32* sfText_getUnicodeString(const sfText* text);

// const sfFont* sfText_getFont(const sfText* text);

// unsigned int sfText_getCharacterSize(const sfText* text);

// float sfText_getLetterSpacing(const sfText* text);

// float sfText_getLineSpacing(const sfText* text);

// sfUint32 sfText_getStyle(const sfText* text);

// sfColor sfText_getColor(const sfText* text);
HB_FUNC( SFTEXT_GETCOLOR )
{
   sfText* text = hb_sfText_param( 1 );

   if( text )
   {
      sfColor color = sfText_getColor( text );

      PHB_ITEM pColorArray = hb_itemArrayNew( 4 );

      hb_arraySetNI( pColorArray, 1, ( sfUint8 ) color.r );
      hb_arraySetNI( pColorArray, 2, ( sfUint8 ) color.g );
      hb_arraySetNI( pColorArray, 3, ( sfUint8 ) color.b );
      hb_arraySetNI( pColorArray, 4, ( sfUint8 ) color.a );

      hb_itemReturnRelease( pColorArray );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfColor sfText_getFillColor(const sfText* text);
HB_FUNC( SFTEXT_GETFILLCOLOR )
{
   sfText* text = hb_sfText_param( 1 );

   if( text )
   {
      sfColor color = sfText_getFillColor( text );

      PHB_ITEM pColorArray = hb_itemArrayNew( 4 );

      hb_arraySetNI( pColorArray, 1, ( sfUint8 ) color.r );
      hb_arraySetNI( pColorArray, 2, ( sfUint8 ) color.g );
      hb_arraySetNI( pColorArray, 3, ( sfUint8 ) color.b );
      hb_arraySetNI( pColorArray, 4, ( sfUint8 ) color.a );

      hb_itemReturnRelease( pColorArray );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfColor sfText_getOutlineColor(const sfText* text);
HB_FUNC( SFTEXT_GETOUTLINECOLOR )
{
   sfText* text = hb_sfText_param( 1 );

   if( text )
   {
      sfColor color = sfText_getOutlineColor( text );

      PHB_ITEM pColorArray = hb_itemArrayNew( 4 );

      hb_arraySetNI( pColorArray, 1, ( sfUint8 ) color.r );
      hb_arraySetNI( pColorArray, 2, ( sfUint8 ) color.g );
      hb_arraySetNI( pColorArray, 3, ( sfUint8 ) color.b );
      hb_arraySetNI( pColorArray, 4, ( sfUint8 ) color.a );

      hb_itemReturnRelease( pColorArray );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// float sfText_getOutlineThickness(const sfText* text);
HB_FUNC( SFTEXT_GETOUTLINETHICKNESS )
{
   sfText* text = hb_sfText_param( 1 );

   if( text )
   {
      hb_retnd( ( float ) sfText_getOutlineThickness( text ) );
   }
   else
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, HB_ERR_FUNCNAME, HB_ERR_ARGS_BASEPARAMS );
   }
}

// sfVector2f sfText_findCharacterPos(const sfText* text, size_t index);

// sfFloatRect sfText_getLocalBounds(const sfText* text);

// sfFloatRect sfText_getGlobalBounds(const sfText* text);
