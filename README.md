# Z88dk-Bench

![Licencia](https://img.shields.io/badge/Licencia-MIT-green.svg)

```txt
███████╗ █████╗  █████╗ ██████╗ ██╗  ██╗     ██████╗ ███████╗███╗   ██╗ ██████╗██╗  ██╗
╚══███╔╝██╔══██╗██╔══██╗██╔══██╗██║ ██╔╝     ██╔══██╗██╔════╝████╗  ██║██╔════╝██║  ██║
  ███╔╝ ╚█████╔╝╚█████╔╝██║  ██║█████╔╝█████╗██████╔╝█████╗  ██╔██╗ ██║██║     ███████║
 ███╔╝  ██╔══██╗██╔══██╗██║  ██║██╔═██╗╚════╝██╔══██╗██╔══╝  ██║╚██╗██║██║     ██╔══██║
███████╗╚█████╔╝╚█████╔╝██████╔╝██║  ██╗     ██████╔╝███████╗██║ ╚████║╚██████╗██║  ██║
╚══════╝ ╚════╝  ╚════╝ ╚═════╝ ╚═╝  ╚═╝     ╚═════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝╚═╝  ╚═╝
```

## Features

- **Modular benchmark harness**: `bench_start(name)` / `bench_end()` wrap any workload with consistent timing and a printed result.
- **Seven built-in benchmarks**:
  - `add` — integer arithmetic loop
  - `call` — function-call overhead
  - `coremark` — CoreMark-derived workload
  - `fpmark` — floating-point workload
  - `memcpy` — block memory copy
  - `memset` — block memory fill
  - `malloc` — dynamic allocation
- **Four build configurations** to compare toolchain and library choices side by side:
  - `sdcc` + classic clib
  - `sdcc` + `sdcc_iy` new clib
  - `sccz80` + classic clib
  - `sccz80` + new clib
- **Dual output**: every build emits a `.sna` (emulator-friendly snapshot) and a `.tap` (tape image for real hardware or tape-loading emulators).
- **ZX Spectrum timing**: results are measured against the 50 Hz frame counter (1 tick = 20 ms), so no extra hardware is required.
- **Ready-to-use devcontainer** with the `dgzornoza.zxide` extension, DeZog, full Z80 tooling, and Makefile support preinstalled.
- **Three debug targets** preconfigured in `launch.json`:
  - `Internal Simulator` — DeZog's built-in `zsim`, no external emulator needed
  - `ZEsarUX` — external emulator over ZRCP
  - `CSpect` — external emulator

## Requirements

- VsCode [https://code.visualstudio.com/](https://code.visualstudio.com/)
- Installed visual studio code dev-container extension:
  [https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers](vscode-remote.remote-containers)

- Docker environment
  - Windows: [https://docs.docker.com/docker-for-windows/install/](https://docs.docker.com/docker-for-windows/install/)
  - Mac: [https://docs.docker.com/docker-for-mac/install/](https://docs.docker.com/docker-for-mac/install/)
  - Linux: [https://docs.docker.com/engine/install/](https://docs.docker.com/engine/install/)

## Usage

The project ships with a devcontainer that already includes the Z88DK toolchain, the `dgzornoza.zxide` extension, and DeZog. Open the folder in VS Code and reopen it inside the container when prompted.

### 1. Build

Open the Command Palette and run **Tasks: Run Task**, then pick one of:

- `Build sdcc-classic-lib`
- `Build sdcc-new-lib`
- `Build sccz80-classic-lib`
- `Build sccz80-new-lib`

Each task runs `make` with the matching `COMPILER`, `CLIB`, `CRT`, and optimization flags, and produces `build/z88dk-bench.sna` and `build/z88dk-bench.tap`.

If you prefer the command line, the exact arguments each task passes live in `.vscode/tasks.json` and can be forwarded to `make` directly.

### 2. Run

Press **F5** in VS Code to launch the active configuration against the built `.sna`. The default launch target is **Internal Simulator** (DeZog's built-in `zsim`), so no external emulator needs to be installed.

`launch.json` also defines `ZEsarUX` and `CSpect` targets — pick the one you have running on your host from the Run and Debug panel. Both expect the emulators to be reachable over `host.docker.internal` on the configured ports.

You can also load `build/z88dk-bench.tap` or `build/z88dk-bench.sna` directly in any ZX Spectrum emulator (Fuse, Retro Virtual Machine, etc.) or transfer the `.tap` to real hardware.

### 3. Read the results

Each benchmark announces itself with `bench-<name>:` and prints its elapsed time in milliseconds when it finishes. Typical output looks like:

```text
bench-coremark: 1820 ms
bench-fpmark: 3140 ms
bench-add: 220 ms
bench-call: 540 ms
bench-memcpy: 880 ms
bench-memset: 760 ms
bench-malloc: 1320 ms

All benchmarks completed.
```

Record the numbers in `benchmarks.xlsx` to compare toolchain configurations side by side.

### 4. Add a new benchmark

1. Create `src/benchmarks/bench_<name>.c` and `bench_<name>.h`. Implement `void bench_<name>(unsigned long iterations)` and wrap the workload between `bench_start("bench_<name>")` and `bench_end()`.
2. Include the new header from `src/main.c` and call `bench_<name>(BENCH_<NAME>_ITERATIONS)` inside `main()`.
3. Add a `BENCH_<NAME>_ITERATIONS` macro next to the existing ones in `src/main.c`.
4. Re-run your build task — `make` auto-discovers any `*.c` / `*.asm` under `src/`, so no Makefile or task changes are required.

## License

This project is licensed under the **MIT license**. This means you can use, copy, modify, and distribute this code, always including the copyright notice and the permission notice. For more details, see the [LICENSE](./LICENSE) file or visit the [MIT License](https://opensource.org/licenses/MIT) page.

## Contact

Any questions or suggestions, please contact me at [dgzornoza@dgzornoza.com](mailto:dgzornoza@dgzornoza.com).
