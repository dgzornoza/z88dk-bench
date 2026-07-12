#ifndef __DGZ_IO_H__
#define __DGZ_IO_H__

/** INFRASTRUCTURE */
// -----------------------------------------------------------------------------

/** Font control codes, should be equal to control_chars -> 'FontControlCodeRoutines'
 * See src/lib/io/control_chars.asm
 * example: print_string(FONT_CONTROL_CRLF "Hello" FONT_CONTROL_CRLF);
 */
#define FONT_CONTROL_EOS "\x00"
#define FONT_CONTROL_SET_X "\x02"
#define FONT_CONTROL_SET_Y "\x03"
#define FONT_CONTROL_LF "\x0A"
#define FONT_CONTROL_CRLF "\x0B"
#define FONT_CONTROL_BLANK "\x0C"
#define FONT_CONTROL_CR "\x0D"
#define FONT_CONTROL_BACKSPACE "\x0E"
#define FONT_CONTROL_TAB "\x0F"
#define FONT_CONTROL_INC_X "\x10"

/** FUNCTIONS */
// -----------------------------------------------------------------------------

/**
 * Print string in screen
 * @param string string to print
 */
extern void print_string(char *string) __z88dk_fastcall;

#endif
