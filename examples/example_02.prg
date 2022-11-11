/*
 *
 */

#include "hbsfml.ch"

PROCEDURE Main()

   LOCAL pWindow
   LOCAL aMode := { 720, 450, 32 }
   LOCAL aContextSettings := { 0, 0, 0, 4, 5, 0, .F. }
   LOCAL nEvent

   pWindow := sfWindow_create( aMode, "Example 02 ą, ć, ę, ł, ń, ó, ś, ź, ż.", hb_bitOr( sfResize, sfClose ), aContextSettings )
   IF( pWindow == NIL )
      RETURN
   ENDIF

   DO WHILE sfWindow_isOpen( pWindow )

      DO WHILE sfWindow_pollEvent( pWindow, @nEvent )

         SWITCH( nEvent )

         CASE sfEvtClosed
            sfWindow_close( pWindow )
            EXIT

         CASE sfEvtResized

         ENDSWITCH

      ENDDO

      sfWindow_display( pWindow )

   ENDDO

   sfWindow_destroy( pWindow )

   RETURN
