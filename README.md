# hb-sfml

Harbour module implementing bindings to [SFML 2.5.1](https://www.sfml-dev.org/index.php).

### Getting Started

Installing hb-sfml requires sfml including its headers. For more info see [getting started](examples/README.md).

## Building

- Build static library:

   ```
   hbmk2 hbsfml.hbp
   ```

- Build and run sample and test code:

   ```
   hbmk2 short_example.prg
   ./short_example.prg
   ```

``` harbour
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

   pWindow := sfRenderWindow_create( aMode, "Hello! Harbour", sfResize + sfClose, aContextSettings )
   IF pWindow == NIL
      RETURN
   ENDIF

   pTexture := sfTexture_createFromFile( "../../../docs/assets/img/harbour_sfml.png", { 0, 0, 0, 0 } )
   IF pTexture == NIL
      RETURN
   ENDIF

   pSprite := sfSprite_create()
   sfSprite_setTexture( pSprite, pTexture, .T. )

   pFont := sfFont_createFromFile( "../../../docs/assets/fonts/Merienda/Merienda-Regular.ttf" )
   IF pFont == NIL
      RETURN
   ENDIF

   pText := sfText_create()
   sfText_setString( pText, "Hello! Harbour .AND. CSFML" )
   sfText_setFont( pText, pFont )
   sfText_setCharacterSize( pText, 48 )

   pMusic := sfMusic_createFromFile( "../../../docs/assets/melody/Jieese.ogg" )
   IF pMusic == NIL
      RETURN
   ENDIF

   sfMusic_play( pMusic )

   DO WHILE sfRenderWindow_isOpen( pWindow )

      DO WHILE sfRenderWindow_pollEvent( pWindow, @nEventType )

         IF nEventType == sfEvtClosed
            sfRenderWindow_close( pWindow )
         ENDIF

      ENDDO

      sfRenderWindow_clear( pWindow, { 235, 235, 255, 0 } )
      sfRenderWindow_drawSprite( pWindow, pSprite )
      sfRenderWindow_drawText( pWindow, pText )
      sfRenderWindow_display( pWindow )

   ENDDO

   sfMusic_destroy( pMusic )
   sfText_destroy( pText )
   sfFont_destroy( pFont )
   sfSprite_destroy( pSprite )
   sfTexture_destroy( pTexture )
   sfRenderWindow_destroy( pWindow )

   RETURN
```

[License.](LICENSE)
