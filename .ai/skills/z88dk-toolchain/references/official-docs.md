# Z88DK official docs — read these when in doubt

The skill body tells you HOW this project uses z88dk. These docs explain WHY the flags behave the way they do. Read them before changing toolchain behavior.

## Pragma include and the pragma file

- [pragma.md](https://github.com/z88dk/z88dk/blob/master/doc/pragma.md) — how `-pragma-include:` is resolved and which pragmas exist.
- [ZXSpectrumZSDCCnewlib_06_SomeDetails.md](https://github.com/z88dk/z88dk/blob/master/doc/ZXSpectrumZSDCCnewlib_06_SomeDetails.md) — `CRT_ORG_CODE`, `CRT_HEAP_AMALLOC`, and newlib-specific caveats (already cited in `zpragma.inc`).

## App generator (TAP / SNA output)

- [appmake.md](https://github.com/z88dk/z88dk/blob/master/doc/appmake.md) — `-create-app`, `-Cz`, and the SNA/TAP format options.

## Target

- [target-zx.md](https://github.com/z88dk/z88dk/blob/master/doc/target-zx.md) — what `+zx` enables and which Spectrum-specific helpers exist.

## CLIB

- The default empty `CLIB_FLAG` selects the **newlib (SDCC)** library. Override with `CLIB=classic` for the classic clib; see [clibs.md](https://github.com/z88dk/z88dk/blob/master/doc/clibs.md).

## CRT

- [CRT.md](https://github.com/z88dk/z88dk/blob/master/doc/CRT.md) — what CRT files do, and how `CRT=0` differs from the default.