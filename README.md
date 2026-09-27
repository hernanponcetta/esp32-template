# esp32-template

Reusable ESP32 development environment for **ESP32-C6**, built around **Zed** and
the **eim** (Espressif IDF Manager) install. No Docker required.

## Layout

```
.
├── CMakeLists.txt            # ESP-IDF project root
├── sdkconfig.defaults        # esp32c6 target, 8MB flash
├── main/                     # Application source
│   ├── CMakeLists.txt
│   └── app_main.c
├── scripts/
│   ├── idf                   # wrapper: eim run v6.1 -- idf.py <args>
│   ├── idf-flash             # auto-detects USB port + flashes
│   └── idf-monitor           # auto-detects USB port + opens monitor
└── .zed/
    ├── settings.json         # clangd → esp-clangd, IntelliSense config
    └── tasks.json            # build / flash / monitor / menuconfig / size
```

## Prerequisites

- **eim** (Espressif IDF Manager) with ESP-IDF **v6.1** installed and selected:

  ```bash
  eim list   # should show v6.1 (selected)
  ```

- **esp-clangd** (bundled by eim at
  `~/.espressif/tools/esp-clangd/<version>/esp-clangd/bin/clangd`).

  `.zed/settings.json` also references two paths under `~/.espressif/tools`:
  - `--resource-dir`: esp-clangd ships without its builtin headers, so clangd
    is pointed at **esp-clang**'s `lib/clang/<ver>` directory instead.
  - `--query-driver`: lets clangd query the actual ESP32 GCC to resolve the
    picolibc system headers (`_mbstate_t`, etc.).

  If you upgrade ESP-IDF versions, update these two paths to match. To find the
  current resource dir: `ls ~/.espressif/tools/esp-clang/*/esp-clang/lib/clang/`.

- **Zed** editor (works out of the box with the bundled clangd).

## Usage

### First build (required for IntelliSense)

ESP-IDF generates `build/compile_commands.json`, which clangd needs. Build once
from Zed **Tasks** panel (`idf: build`) or terminal:

```bash
./scripts/idf build
```

### From Zed

Open the project, then run tasks via the Tasks panel / `cmd+shift+P` → "Tasks":

| Task | Action |
|---|---|
| `idf: build` | Compile firmware |
| `idf: clean (fullclean)` | Wipe build artifacts |
| `idf: flash` | Flash to detected USB port |
| `idf: monitor` | Open serial monitor on detected port |
| `idf: menuconfig` | Configure project (Kconfig) |
| `idf: size` | Show firmware size |

### From terminal

```bash
./scripts/idf build                  # build
./scripts/idf-flash                  # flash (auto port)
./scripts/idf-monitor                # monitor (auto port)
./scripts/idf -p /dev/tty.usbmodem1234 flash monitor   # explicit port
```

Ports are auto-detected from `/dev/tty.usbmodem*` / `/dev/tty.usbserial*`.
Override with `IDF_PORT=/dev/... ./scripts/idf-flash` or the `-p` flag.

### Swap target chip

```bash
./scripts/idf set-target esp32s3   # e.g. for an ESP32-S3 board
./scripts/idf menuconfig           # adjust flash size etc. if needed
```

## Notes

- `sdkconfig` is generated from `sdkconfig.defaults` on first build and is gitignored.
- Flash size defaults to 8MB (ESP32-C6-DevKitC-1 N8). For 4MB boards, set
  `CONFIG_ESPTOOLPY_FLASHSIZE_4MB=y` in `sdkconfig.defaults` and rebuild.