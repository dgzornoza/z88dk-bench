---
name: z88dk-toolchain
description: "Trigger: z88dk, zcc, +zx, Z80, ZX Spectrum, clib, CRT, pragma. Use zcc correctly for this ZX Spectrum benchmarking suite."
license: MIT
metadata:
  author: "dgzornoza"
  version: "1.0"
---

## Activation Contract

Load this skill before:

- Editing `Makefile`, `zpragma.inc`, or any `src/**/*.c` / `src/**/*.asm`
- Adding a benchmark, ASM I/O routine, or new shared pragma
- Changing the build target (`+zx`), clib, CRT, or compiler backend
- Debugging link errors, missing pragmas, or wrong output artifacts

Do NOT load for documentation-only edits or pure `.lis` inspection.

## Hard Rules

1. **All shared pragmas live in `zpragma.inc`** — never inline `#pragma` in `.c` / `.asm`.
2. **`-pragma-include:zpragma.inc` MUST appear on both the C compile line AND the link line.** It is NOT added to the ASM compile line. Forgetting it on the link step silently drops shared pragmas.
3. **`--list` and `--c-code-in-asm` are mandatory on C compile.** They produce the per-TU `.lis` files that `build/z88dk-bench.source.lis` joins, and interleave C source with generated Z80. Do NOT drop them.
4. **Default heap is `amalloc`/`afree`, not `malloc`/`free`.** `zpragma.inc` sets `CRT_HEAP_AMALLOC=1`.
5. **Code load address is hardcoded to `24500`** via `CRT_ORG_CODE`. Any new data > ~6 KiB is a latent bug.
6. **`main()` MUST call `enable_ei()` first** — `zx_clock` depends on interrupts for all timing-based benchmarks.
7. **`CRT_FLAG` is link-time only.** Never pass it on a per-TU compile command.
8. **Link order**: objects first (alphabetical, from `find src`), then `$(CRT_FLAG)`, then `-o output.bin -create-app`. Do NOT place `-o` between objects.
9. **`C_OPT_FLAGS` and `LINKER_FLAGS` are NOT defaulted in the Makefile.** A bare `make all` compiles unoptimized. Use a VSCode build task from `.vscode/tasks.json` (which sets them) or pass them explicitly on the `make` command line.

## Decision Gates

| Need                                   | Action                                                       |
| -------------------------------------- | ------------------------------------------------------------ |
| Standard build (human-driven)          | Run the VSCode task for the target compiler/clib (e.g. `Build sccz80-new-lib`) — see the table in `agents.md` |
| Standard build (headless / sub-agent)  | Replicate the task args as `make COMPILER=... CLIB=... CRT=... C_OPT_FLAGS=... LINKER_FLAGS=... CREATE_SNA=true CREATE_TAP=true all` — copy verbatim from the matching task in `.vscode/tasks.json` |
| Real Spectrum or tape-loading emulator | Any build task — every task produces both `.sna` and `.tap`   |
| Modern emulator                        | Any build task — every task produces both formats            |
| Clean all artifacts                    | VSCode task `Clean All` (runs `make clean_all`)              |
| Profile Z80 cycles / inspect asm       | Open `build/z88dk-bench.source.lis` (joined per-TU listings) |
| Try a CRT not in tasks.json            | `make CRT=<n> all` directly (link-time only)                 |

Canonical build configurations live in `.vscode/tasks.json` — read it before changing or adding a build configuration.

## Execution Steps

### Add a new benchmark

1. Create `src/benchmarks/bench_<name>.{c,h}` exporting `void bench_<name>(unsigned int iterations)`.
2. Use `volatile unsigned int accumulator` + `(void)accumulator;` to defeat dead-code elimination. See `assets/bench_template.c`.
3. In `src/main.c`:
   - Add `#include "benchmarks/bench_<name>.h"`.
   - Add a block: `bench_start("<name>"); bench_<name>(ITER_<NAME>); bench_end();`.
4. The Makefile auto-discovers sources via `find src` — no Makefile edit needed.
5. Rebuild via the matching VSCode task (or `make` with the task args copied verbatim from `.vscode/tasks.json`) and load `build/z88dk-bench.sna` in an emulator.

### Add a new shared pragma

1. Edit `zpragma.inc`. Append the directive at the bottom with a one-line `# why` comment.
2. Update `assets/zpragma.inc.stub` so the stub stays in sync.
3. Rebuild — no flag change needed; `-pragma-include` already pulls it in.

### Add an ASM I/O primitive

1. Drop a new `.asm` under `src/lib/io/` (Makefile auto-discovers).
2. Use `SECTION code_user` + `PUBLIC <name>` + declare any `EXTERN` symbols you call.
3. Declare the prototype in `src/lib/io.h`.
4. See `assets/io_asm_template.asm`.

### Build a release artifact

1. Run the VSCode task that matches your target compiler/clib (e.g. `Build sccz80-new-lib`) via `Tasks: Run Task`, or invoke `make` directly with the exact args copied from `.vscode/tasks.json`.
2. Verify `build/z88dk-bench.tap` and `build/z88dk-bench.sna` exist and load in an emulator.

## Output Contract

When you finish a z88dk-related change, return:

- Files created or modified (with paths)
- Build command actually run and its result (pass/fail)
- For benchmark additions: the `ITER_<NAME>` macro used
- For pragma additions: a one-line note on what it enables and any heap/address impact
- For Makefile changes: which override variable (`COMPILER`, `CLIB`, `CRT`, `CREATE_SNA`, `CREATE_TAP`, `C_OPT_FLAGS`, `LINKER_FLAGS`) you touched and why
- For VSCode task changes (`/.vscode/tasks.json`): the task label and the args you changed

## References

- `references/official-docs.md` — links to the z88dk doc pages that explain `-pragma-include`, `-create-app`, `+zx`, and CRT semantics.
- `assets/zpragma.inc.stub` — pragma file stub mirroring the two directives in use.
- `assets/bench_template.{c,h}` — minimal benchmark skeleton.
- `assets/io_asm_template.asm` — bare ASM I/O skeleton.
- `assets/Makefile.override.snippet` — copy-paste override examples.
