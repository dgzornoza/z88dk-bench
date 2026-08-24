; ASM I/O primitive template.
;
; Drop a new .asm under src/lib/io/ — Makefile auto-discovers it via `find src`.
; Declare the prototype in src/lib/io.h.

SECTION code_user

PUBLIC my_asm_routine

; External symbols you call:
; EXTERN some_c_symbol

my_asm_routine:
    ; TODO: Z80 implementation here.
    ; Preserve BC/DE/HL if the caller relies on them across the call.
    ret