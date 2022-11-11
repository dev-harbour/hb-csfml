/*
 *
 */

#include "hbsfml.ch"

PROCEDURE Main()

   LOCAL pWindow
   LOCAL aMode := { 720, 450, 32 }
   LOCAL aContextSettings := { 0, 0, 0, 4, 5, 0, .F. }
   LOCAL pTexture
   LOCAL pSprite
   LOCAL pFont
   LOCAL pText
   LOCAL pMusic
   LOCAL nEventType

   pWindow := sfRenderWindow_create( aMode, "Hello! Harbour ą, ć, ę, ł, ń, ó, ś, ź, ż.", sfResize + sfClose, aContextSettings )
   IF( pWindow == NIL )
      RETURN
   ENDIF

   pFont := sfFont_createFromFile( "../../../docs/assets/fonts/Merienda/Merienda-Regular.ttf" )
   IF pFont == NIL
      RETURN
   ENDIF

   pText := sfText_create()
   sfText_setString( pText, "Hello! Harbour .AND. CSFML" )
   sfText_setFont( pText, pFont )
   sfText_setCharacterSize( pText, 48 )


   DO WHILE sfRenderWindow_isOpen( pWindow )


      DO WHILE sfRenderWindow_pollEvent( pWindow, @nEventType )


         IF nEventType == sfEvtClosed
            sfRenderWindow_close( pWindow )
         ENDIF

      ENDDO

      /* Clear the screen */
      sfRenderWindow_clear( pWindow, { 235, 235, 255, 0 } )

      /* Draw the sprite */
      sfRenderWindow_drawSprite( pWindow, pSprite )

      /* Draw the text */
      sfRenderWindow_drawText( pWindow, pText )

      /* Update the window */
      sfRenderWindow_display( pWindow )

   ENDDO

   /* Cleanup resources */
   sfMusic_destroy( pMusic )
   sfText_destroy( pText )
   sfFont_destroy( pFont )
   sfSprite_destroy( pSprite )
   sfTexture_destroy( pTexture )
   sfRenderWindow_destroy( pWindow )

   RETURN
