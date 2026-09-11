# uFR Readers Tool

A wxWidgets GUI for exercising the uFR / uFR Zero series NFC/RFID reader SDK
(`ufr-lib/`, vendored from Digital Logic).

The repository's `uFR_Readers_tool.cbp` is a Code::Blocks project hard-wired
for Windows/MinGW (links `libwxmsw30u.a`, `kernel32.a`, etc.). The
application code itself has no Windows-only dependencies, so it also builds
natively on macOS via the `Makefile` in this directory, against wxWidgets
(Cocoa) and the macOS uFCoder library already bundled under
`ufr-lib/macos/`.

## macOS: prerequisites

1. **Xcode Command Line Tools** (provides `clang++` and the macOS SDK):

   ```sh
   xcode-select --install
   ```

2. **Homebrew** — see <https://brew.sh> if not already installed.

3. **wxWidgets 3.2**:

   ```sh
   brew install wxwidgets@3.2
   ```

   This formula is keg-only, so it will not be linked onto your `PATH` as
   plain `wx-config`. The `Makefile` looks for `wx-config-3.2` first and
   falls back to `wx-config`, so no extra linking or `PATH` changes are
   needed.

No other dependencies are required: the uFCoder reader library ships
prebuilt for macOS (universal arm64 + x86_64) at
`ufr-lib/macos/universal/libuFCoder-macos.dylib`, and the build links
against it directly.

## Build

From the repository root:

```sh
make
```

This compiles `uFR_Readers_toolApp.cpp` and `uFR_Readers_toolMain.cpp` and
links them against wxWidgets and `libuFCoder-macos.dylib`, producing
`bin/macos/uFR_Readers_tool`. The binary is linked with an rpath relative to
its own location (`@executable_path/../../ufr-lib/macos/universal`), so as
long as you keep the repo's directory layout intact, it will find the
`.dylib` without any environment variables or manual copying.

## Run

```sh
make run
```

or directly:

```sh
./bin/macos/uFR_Readers_tool
```

A wxWidgets window should open. To exercise reader functions (`Reader
open`, `Reader Open Ex`, etc.) you need a physical uFR/uFR Zero reader
connected via USB — the macOS library talks to it through IOKit.

## Clean

```sh
make clean
```

Removes `bin/macos/` (build output only; nothing else is touched).

## Notes

- `Sleep(200)` calls in `uFR_Readers_toolMain.cpp` are Win32 API calls with
  no direct macOS/Linux equivalent; a small `#ifndef _WIN32` shim
  (`usleep`-based) was added near the top of the file so the same source
  builds on both platforms. The Windows build path is unaffected.
- `image.c` and `resource.rc` are Windows-project artifacts not referenced
  by the macOS build (or even by the `.cbp` project's unit list) — they can
  be ignored on macOS.
- The `Makefile` targets macOS specifically (Cocoa frameworks via
  `wx-config --libs`). It is not used for the Windows build, which remains
  the `.cbp` / Code::Blocks project.
