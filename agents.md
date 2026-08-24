# Z88DK-Bench — AI Governance Entry Point

This file is the **single entry point** for AI agents working on the z88dk-bench project. Read it before any non-trivial task.

## Project Context

`z88dk-bench` is a benchmarking suite for the **Z88DK** C/Assembly toolchain targeting the **Z80 / ZX Spectrum** platform.

- **Language**: C, Z80 Assembly
- **Toolchain**: `zcc` (Z88DK compiler) with `+zx` target
- **Build system**: GNU Make, with build tasks defined in `.vscode/tasks.json`
- **Container**: devcontainer (Docker)
- **Output artifacts**: `.bin`, `.tap`, `.sna` (Spectrum snapshots), `.lis` (joined listing for asm debug)

## Repository Layout

```text
src/                C and Z80 Assembly sources (compiled by Makefile)
obj/                Object files (generated, ignored by git)
build/              Final binaries + joined .lis (ignored by git)
.vscode/            VSCode workspace config (tasks.json, launch.json, settings.json)
doc/                Project documentation
zpragma.inc         Z88DK pragma include (shared compiler pragmas)
benchmarks.xlsx     Benchmark results spreadsheet
LICENSE             MIT license
Makefile            Build orchestration
README.md           User-facing readme
agents.md           This file (AI entry point)
.ai/                Project-specific AI governance (manual, curated)
```

## Build Configurations

All build configurations are defined in `.vscode/tasks.json`. That file is the **single source of truth** for which compiler, clib, CRT, optimization flags, and output formats each build uses.

Use VSCode's `Tasks: Run Task` command, or invoke the underlying `make` command directly with the same arguments shown in each task definition (useful for sub-agents or headless builds).

| VSCode Task Label         | Compiler | CLIB     | CRT | Optimization flags         | Output        |
| ---                       | ---      | ---      | --- | ---                        | ---           |
| `Build sdcc-classic-lib`  | sdcc     | (default) | (default) | `-SO3 --opt-code-size` | SNA + TAP     |
| `Build sdcc-new-lib`      | sdcc     | `sdcc_iy` | 31  | `-SO3 --opt-code-size`     | SNA + TAP     |
| `Build sccz80-classic-lib`| sccz80   | (default) | (default) | `-O3`                | SNA + TAP     |
| `Build sccz80-new-lib`    | sccz80   | `new`     | 31  | `-O3`                      | SNA + TAP     |
| `Clean All`               | —        | —        | —   | —                          | runs `make clean_all` |

Every build task sets both `CREATE_SNA=true` and `CREATE_TAP=true`, so each run produces a `.sna` (for emulators) and a `.tap` (for real hardware or tape-loading emulators).

To add or modify a build configuration, edit `.vscode/tasks.json`. Do **not** add a new `make` recipe to the `Makefile` without also adding a matching VSCode task.

## AI Governance Structure

The project uses a single project-specific AI folder:

| Folder | Purpose | Maintained by |
| ---    | ---    | ---           |
| `.ai/` | Project-specific governance (skills, instructions, templates) | Authored manually |

All project-specific AI artifacts (skills, instructions, templates) live under `.ai/`. See `.ai/README.md` for the index.

## Conventions

- **Language**: English in code, comments, commit messages, README, and all AI artifacts.
- **Commits**: Conventional Commits format. No `Co-Authored-By` lines or AI attribution.
- **Toolchain targets**: ZX Spectrum (`+zx`) is the default. Only change `TARGET` in `Makefile` after explicit confirmation.
- **Object and build directories** are gitignored — never commit them.

## When to Load Skills

Before any non-trivial work:

1. Read this `agents.md` fully.
2. Check `.ai/skills/` for project-specific skills relevant to the task.
3. Pass matching skill paths to any sub-agent under `## Skills to load before work`.

For Z88DK, Z80 assembly, or Makefile-rule questions, project-specific skills in `.ai/skills/` take precedence over generic engineering skills.