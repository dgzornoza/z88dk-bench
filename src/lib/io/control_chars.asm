SECTION code_user

; NOTE FontX and FontY should be togheter on this order for use in pair registers, don't change
; ------------------------------------------------------------------------------------------------
PUBLIC _GLOBAL_FONT_X
    _GLOBAL_FONT_X:             db 0
PUBLIC _GLOBAL_FONT_Y
    _GLOBAL_FONT_Y:             db 0
; ------------------------------------------------------------------------------------------------

EXTERN _print_string
EXTERN asm_print_char

_SYS_LOWRES_SCR_WIDTH       equ 32 ; Low-Resolution width
_SYS_LOWRES_SCR_HEIGHT      equ 24; Low-Resolution height


;-------------------------------------------------------------------------------
;	Name:		      internal asm_font_set_x
;	Description:	set screen X cursor coordinate
;	Input:		   A = X coordinate
;	Output: 	      --
;-------------------------------------------------------------------------------
PUBLIC asm_font_set_x
asm_font_set_x:
   ld (_GLOBAL_FONT_X), a
   ret


;-------------------------------------------------------------------------------
;	Name:		      internal asm_font_set_y
;	Description:	set screen Y cursor coordinate
;	Input:		   A = Y coordinate
;	Output: 	      --
;-------------------------------------------------------------------------------
PUBLIC asm_font_set_y
asm_font_set_y:
   ld (_GLOBAL_FONT_Y), a
   ret

;-------------------------------------------------------------------------------
;	Name:		      internal asm_font_blank
;	Description:	print space, override current position in cursor and increment X (updating y if need)
;	Clobbers: 	   AF, BC', DE', HL'
;-------------------------------------------------------------------------------
PUBLIC asm_font_blank
asm_font_blank:
   ld a, ' '               ; set char space
   exx
   call asm_print_char     ; print char
   exx
   call asm_font_inc_x     ; increment x coord
   ret



;-------------------------------------------------------------------------------
;	Name:		      internal asm_font_inc_x
;	Description:	increments x coordinate by 1 taking into account the edge on the screen (updating Y accordingly).
;	Clobbers: 	   AF
;-------------------------------------------------------------------------------
PUBLIC asm_font_inc_x
asm_font_inc_x:
   ld a, (_GLOBAL_FONT_X)           ; increment x
   inc a
   cp _SYS_LOWRES_SCR_WIDTH         ; Compare with right border (x > 32)
   jr c, update_x                   ; jump if not is in right border
   call asm_font_crlf
   ret

update_x:
   ld (_GLOBAL_FONT_X), a           ; store X coordinate in var
   ret


;-------------------------------------------------------------------------------
;	Name:		      internal asm_font_lf
;	Description:	Generate un linefeed (increment Y by 1).
;                 Takes into account the height variables of the screen.
;	Clobbers: 	   AF
;-------------------------------------------------------------------------------
PUBLIC asm_font_lf
asm_font_lf:
   ld a, (_GLOBAL_FONT_Y)           ; get Y coordinate
   cp _SYS_LOWRES_SCR_HEIGHT - 1    ; Compare with bottom border (y > 23)
   jr nc, update_y                  ; jump if (y = 23)
   inc a                            ; (y < 23), increment Y
   ld (_GLOBAL_FONT_Y), a           ; store Y coordinate in var

update_y:
   ret


;-------------------------------------------------------------------------------
;	Name:		      internal asm_font_cr
;	Description:	Generate carriage return (CR) => x=0.
;	Clobbers: 	   AF
;-------------------------------------------------------------------------------
PUBLIC asm_font_cr
asm_font_cr:
   xor a
   ld (_GLOBAL_FONT_X), a
   ret


;-------------------------------------------------------------------------------
;	Name:		      internal asm_font_crlf
;	Description:	Generate linefeed and Carriage return (lf+cr).
;	Clobbers: 	   AF
;-------------------------------------------------------------------------------
PUBLIC asm_font_crlf
asm_font_crlf:
   call asm_font_lf
   call asm_font_cr
   ret


;-------------------------------------------------------------------------------
;	Name:		      internal asm_font_tab
;	Description:	print tabulator (3 spaces) using printstring
;	Clobbers: 	   AF
;-------------------------------------------------------------------------------
PUBLIC asm_font_tab
asm_font_tab:
   push hl
   ld hl, FontTabString
   call _print_string      ; print 3 spaces
   pop hl
   ret


;-------------------------------------------------------------------------------
;	Name:		      internal asm_font_dec_x
;	Description:	decrement X cursor coordinate withouth delete char
;	Clobbers: 	   AF
;-------------------------------------------------------------------------------
PUBLIC asm_font_dec_x
asm_font_dec_x:
   ld a, (_GLOBAL_FONT_X)     ; get X coordinate
   or a
   ret z             ; if is Zero, exit
   dec a             ; decrement and store in var
   ld (_GLOBAL_FONT_X), a
   ret               ; exit


;-------------------------------------------------------------------------------
;	Name:		      internal asm_font_backspace
;	Description:	decrement X cursor, deleting char backspace)
;                 delete char printing space.
;	Clobbers: 	   AF, BC', DE', HL'
;-------------------------------------------------------------------------------
PUBLIC asm_font_backspace
asm_font_backspace:
   call asm_font_dec_x
   ld a, ' '               ; space to print
   exx
   call asm_print_char     ; override char with space
   exx
   ret                     ; exit


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; VARIABLES
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;-------------------------------------------------------------
; Table with 16 control code routines adresses.
; some routine is empty for expand if need.
;-------------------------------------------------------------
PUBLIC FontControlCodeRoutines
   FontControlCodeRoutines:
      dw 0000, 0000, asm_font_set_x, asm_font_set_y
      dw 0000, 0000, 0000, 0000, 0000, 0000
      dw asm_font_lf, asm_font_crlf, asm_font_blank
      dw asm_font_cr, asm_font_backspace, asm_font_tab, asm_font_inc_x

.FontTabString       db  "   ", 0


