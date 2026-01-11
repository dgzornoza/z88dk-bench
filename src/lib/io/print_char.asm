SECTION code_user

PUBLIC asm_print_char

;;; FONT VARIABLES
_ROM_CHARSET:       equ $3C00

_FONT_ATTRIBUTES:    equ 56     ; font attributes bits (8 flash, 7 bright, 6-4 paper, 3-1 ink)


EXTERN _GLOBAL_FONT_X


;-------------------------------------------------------------------------------
;	Name:		   internal asm_print_char
;	Description:   print 8x8 pixels char from charset.
;	Input:		   A = ASCII char to print
;	Output: 	      --
;	Clobbers: 	   DE, BC, HL
;  Remarks:       _GLOBAL_FONT_CHARSET define charset memory address to use.
;                 _GLOBAL_FONT_X              = X Coordinate in low-res (0-31)
;                 _GLOBAL_FONT_Y              = Y Coordinate in low-res (0-23)
;                 _GLOBAL_FONT_STYLE          = Font style to use.
; This routine don't preserve registers (only internal use)
;-------------------------------------------------------------------------------
asm_print_char:

   ld bc, (_GLOBAL_FONT_X)          ; B = Y,  C = X
   ex af, af'                       ; store char in A'

   ;;; calculate destination screen coordinates in DE.
   ld a, b
   and $18
   add a, $40
   ld d, a
   ld a, b
   and 7
   rrca
   rrca
   rrca
   add a, c
   ld e, a                 ; DE contains destination address.

   ;;; calculate origin position (array sprites) in HL: adress = base_sprites + (num_sprite * 8)
   ex af, af'              ; get char to print in A'
   ld bc, _ROM_CHARSET
   ld h, 0
   ld l, a
   add hl, hl
   add hl, hl
   add hl, hl
   add hl, bc              ; HL = BC + HL = _ROM_CHARSET + (A * 8)

   ex de, hl               ; exchange DE y HL (DE=origin, HL=destination)

;;;;;; DRAW CHAR ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
   ld B, 8                       ; 8 scanlines to draw
.drawchar_loop_normal:
   ld a, (de)                    ; get char data
   ld (hl), a                    ; set value in video memory
   inc de
   inc h
   djnz drawchar_loop_normal
   jr print_attribute            ; jupm to print attributes

   ;;; print attributes ........................................................
.print_attribute:

   ld a, h                       ; get HL initial value
   sub 8                         ; substract 8 advanced scanlines

   ;;; calculate attributes area position in DE (currently A = H)
   rrca                          ; shift A 3 times (A = A >> 3)
   rrca
   rrca
   and 3                         ; A = A AND 00000011 = 2 high bits from row
   or $58
   ld d, a
   ld e, l

   ;;; draw attibute in memory
   ld a, _FONT_ATTRIBUTES
   ld (de), a                    ;  draw attibute in memory
   ret

