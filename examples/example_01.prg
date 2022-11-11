/*
 *
 */

#include "hbsfml.ch"

PROCEDURE Main()

   LOCAL pWindow
   LOCAL aContextSettings := { 0, 0, 0, 4, 5, 0, .F. }
   LOCAL aMode := { 800, 600, 24 }
   LOCAL nEvent

   pWindow := sfWindow_createUnicode( aMode, hb_UTF8ToStr( "Example 01" ), hb_bitOr( sfResize, sfClose ), aContextSettings )

   DO WHILE( sfWindow_isOpen( pWindow ) )

      DO WHILE( sfWindow_pollEvent( pWindow, @nEvent ) )

         SWITCH( nEvent )

         CASE sfEvtClosed
            sfWindow_close( pWindow )
            EXIT

         ENDSWITCH

      ENDDO

   ENDDO

   sfWindow_destroy( pWindow )

   RETURN
