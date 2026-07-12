// compile: zcc +zx -c -compiler=sdcc --list --c-code-in-asm test.c

#include <stdint.h>

uint8_t rubbish8, rubbish8_2, rubbish8_3;
uint16_t rubbish16, rubbish16_2;
uint32_t rubbish32;

void fun_8( uint8_t p ) {
    rubbish8 = p;
}

void fun_8_fastcall( uint8_t p ) __z88dk_fastcall {
    rubbish8 = p;
}

void fun_16_fastcall( uint16_t p ) __z88dk_fastcall {
    rubbish16 = p;
}

void fun_32_fastcall( uint32_t p ) __z88dk_fastcall {
    rubbish32 = p;
}

// does not work, "error 222: invalid number of parameters for __z88dk_fastcall"
// void fun_8_8_fastcall( uint8_t p1, uint8_t p2 ) __z88dk_fastcall {
//     rubbish8 = p1;
//     rubbish8_2 = p2;
// }

void fun_8_8_sdcccall( uint8_t p1, uint8_t p2 ) __sdcccall(1) {
    rubbish8 = p1;
    rubbish8_2 = p2;
}

void fun_8_16_sdcccall( uint8_t p1, uint16_t p2 ) __sdcccall(1) {
    rubbish8 = p1;
    rubbish16 = p2;
}

void fun_16_8_sdcccall( uint16_t p1, uint8_t p2 ) __sdcccall(1) {
    rubbish16 = p1;
    rubbish8 = p2;
}

void fun_16_8_8_sdcccall( uint16_t p1, uint8_t p2, uint8_t p3 ) __sdcccall(1) {
    rubbish16 = p1;
    rubbish8 = p2;
    rubbish8_2 = p3;
}

void fun_8_16_8_8_sdcccall( uint8_t p1, uint16_t p2, uint8_t p3, uint8_t p4 ) __sdcccall(1) {
    rubbish8 = p1;
    rubbish16 = p2;
    rubbish8_2 = p3;
    rubbish8_3 = p4;
}

void fun_16_8_16_sdcccall( uint16_t p1, uint8_t p2, uint16_t p3 ) __sdcccall(1) {
    rubbish16 = p1;
    rubbish8 = p2;
    rubbish16_2 = p3;
}

void main( void ) {
    fun_8( 0x17 );
    fun_8_fastcall( 0x18 );
    fun_16_fastcall( 0x0019 );
    fun_32_fastcall( 0x00000020 );
    fun_8_8_sdcccall( 0x21, 0x22 );
    fun_8_16_sdcccall( 0x23, 0x0024 );
    fun_16_8_sdcccall( 0x0025, 0x26 );
    fun_16_8_8_sdcccall( 0x0027, 0x28, 0x29 );
    fun_8_16_8_8_sdcccall( 0x30, 0x0031, 0x32, 0x33 );
    fun_16_8_16_sdcccall( 0x0034, 0x35, 0x0036 );
}