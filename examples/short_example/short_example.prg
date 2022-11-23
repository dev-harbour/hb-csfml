/*
 *
 */

#include "hbcsfml.ch"

PROCEDURE Main()

   LOCAL pWindow
   LOCAL aMode := { 700, 564, 32 }
   LOCAL aContextSettings := { 0, 0, 0, 4, 5, 0, .F. }
   LOCAL pTexture
   LOCAL pSprite
   LOCAL pFont
   LOCAL pText
   LOCAL pMusic
   LOCAL nEventType

   /* Create the main window */
   pWindow := sfRenderWindow_create( aMode, "Hello! Harbour", sfResize + sfClose, aContextSettings )
   IF pWindow == NIL
      RETURN
   ENDIF

   /* Load a sprite to display */
   pTexture := sfTexture_createFromFile( "../../docs/assets/img/harbour_sfml.png", { 0, 0, 0, 0 } )
   IF pTexture == NIL
      RETURN
   ENDIF

   pSprite := sfSprite_create()
   sfSprite_setTexture( pSprite, pTexture, .T. )

   /* Create a graphical text to display */
   pFont := sfFont_createFromFile( "../../docs/assets/fonts/Merienda/Merienda-Regular.ttf" )
   IF pFont == NIL
      RETURN
   ENDIF

   pText := sfText_create()
   sfText_setString( pText, "Hello! Harbour .AND. CSFML" )
   sfText_setFont( pText, pFont )
   sfText_setCharacterSize( pText, 48 )

   /* Load a music to play */
   pMusic := sfMusic_createFromFile( "../../docs/assets/melody/Jieese.ogg" )
   IF pMusic == NIL
      RETURN
   ENDIF

   /* Play the music */
   sfMusic_play( pMusic )

   /* Start the game loop */
   DO WHILE sfRenderWindow_isOpen( pWindow )

      /* Process events */
      DO WHILE sfRenderWindow_pollEvent( pWindow, @nEventType )

         /* Close window : exit */
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
