SECTION code_user

PUBLIC _print_string    ; export C decl "extern void print_string(char *string) __z88dk_fastcall;"

EXTERN asm_print_char
EXTERN asm_font_inc_x
EXTERN FontControlCodeRoutines

;-------------------------------------------------------------------------------
;  Name:		    public _print_string
;  Description:	    print string with optional control codes in screen
;  Input:		    HL = string to print
;  Output: 	        --
;  Clobbers: 	    HL
;  Remarks:         FontCharset define charset memory address to use.
;-------------------------------------------------------------------------------
_print_string:
   push bc                    ; store stack
   push de

.string_loop:
   ld a, (hl)                 ; Get char from string
   inc hl                     ; pointer to next char

   cp 32                      ; id control code? (char < 32)
   jp c,  string_control_code ; jump if is control code

   push hl                    ; store HL
   call asm_print_char        ; print char
   pop hl                     ; restore HL

   ;;; increment cursor using font_blanck, increment x and update x and y if need
   call asm_font_inc_x        ; increment X
   jr string_loop             ; continue with next char in string

.string_control_code:
   or a
   jp nz, process_control_code      ; if control code is eos (end of string), exit, else call process_control_code
   pop de
   pop bc
   ret

.process_control_code:
   ;;; get control code routine and call it.
   ex de, hl
   ld hl, FontControlCodeRoutines
   rlca                             ; a = a * 2 = control code * 2 (routines addresses are 2 bytes)
   ld c, a
   ld b, 0                          ; bc = a * 2
   add hl, bc                       ; hl = dir FontControlCodeRoutines + (control code routine address)
   ld c, (hl)                       ; read low register in C...
   inc hl                           ; ... for no broken HL and read ...
   ld h, (hl)                       ; ... hight register from h ...
   ld l, c                          ; can't use A register because is used in CP

   ;;; if control > 0 y control < 10 -> get first parameter and jump to routine
   ;;; if control > 9 y ccontrol < 32 -> jump to routine withouth parameter
   cp 18                            ; control < 10 ((control - 1) * 2 < 18 )
   jp nc, string_call_routine       ; if is < 10, jump withouth param

   ;;; if control < 10 -> get parameter:
   ld a, (de)                       ; get parameter from string
   inc de                           ; pointer to next char

   ;;; code for call control code routine
.string_call_routine:
   ld bc, string_end_call_routine   ; store return address
   push bc
   jp (hl)                          ; jump to routine for manage control code

   ;;; end code for control code routine
.string_end_call_routine:
   ex de, hl                        ; set in HL string pointer
   jr string_loop                   ; continue loop


