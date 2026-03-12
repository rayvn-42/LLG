# LLG — Lightweight Linux Graphics

<div align="center">

![LLG Banner](docs/images/banner.png)

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Build Status](https://img.shields.io/github/actions/workflow/status/rayvn-42/LLG/build.yml?branch=main&label=build)](https://github.com/rayvn-42/LLG/actions)
[![Version](https://img.shields.io/github/v/tag/rayvn-42/LLG?label=version)](https://github.com/rayvn-42/LLG/tags)
[![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)](https://github.com/rayvn-42/LLG)
[![Language](https://img.shields.io/badge/language-C-orange.svg)](https://github.com/rayvn-42/LLG)
[![X11](https://img.shields.io/badge/backend-X11-informational.svg)](https://www.x.org)

A lightweight 2D graphics library for Linux, built as a clean abstraction over XLib.  
No extra dependencies. Designed to be simple to use, simple to read, and simple to build.

</div>

---

## Table of Contents

- [Quick Look](#quick-look)
- [Features](#features)
- [Requirements](#requirements)
- [Building](#building)
- [Running the Tests](#running-the-tests)
- [API Overview](#api-overview)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

---

## Quick Look

```c
#include <LLG/llg.h>

int main(void) {
    LLGContext *ctx = LLG_init("My Window", 800, 600);
    LLGEvent ev;

    LLG_setBackground(ctx, LLG_RGB(20, 20, 20));
    LLG_setFpsCap(ctx, 60);

    while (LLG_isRunning(ctx)) {
        while (LLG_pollEvent(ctx, &ev))
            if (ev.type == LLG_EVENT_CLOSE) LLG_quit(ctx);

        LLG_clear(ctx);

        LLG_setFill(ctx, LLG_RGB(255, 80, 0));
        LLG_setStroke(ctx, LLG_RGB(255, 255, 255));
        LLG_setStrokeWidth(ctx, 2);
        LLG_circle(ctx, 400, 300, 80);

        LLG_present(ctx);
    }

    LLG_destroy(ctx);
    return 0;
}
```

<div align="center">

![LLG Demo Screenshot](docs/images/demo.png)

</div>

---

## Features

- Simple one-call window creation and lifecycle management
- Double buffered rendering - no tearing, no flickering
- Drawing primitives - pixels, lines, rectangles, circles, ellipses, polygons, arcs
- Fill and stroke draw state, similar to Processing / p5.js
- Keyboard and mouse event handling with both polling and blocking modes
- Live input state queries - `LLG_keyDown`, `LLG_mouseDown`, `LLG_mousePos`
- Delta time and FPS cap for frame-rate independent logic
- Image loading and blitting
- Text rendering via XLib fonts
- Clean error handling via error codes with descriptive strings
- No dependencies beyond X11

---

## Requirements

| Requirement | Notes |
|---|---|
| Linux with X11 | Wayland not currently supported |
| GCC or Clang | Any version supporting C99 or later |
| `libx11-dev` | X11 development headers |
| Make | For the build system |

Install X11 development headers on:

### Debian/Ubuntu/Linux Mint:

```bash
sudo apt install libx11-dev make git
```

### Fedora:

```bash
sudo dnf install libx11-devel make git
```

### CentOS/RHEL 7:

```bash
sudo yum install libx11-devel make git
```

### Arch Linux/Manjaro:

```bash
sudo pacman -S libx11 make git
```

### openSUSE:

```bash
sudo zypper install libx11-devel make git
```

---

## Building

Clone and build the static library:

```bash
git clone https://github.com/rayvn-42/LLG.git
cd LLG
make install
```

This builds the library and copies headers to `/usr/local/include/LLG/` and the library to `/usr/local/lib/`.

#### To include:
```bash
gcc program.c -o program $(pkg-config --cflags --libs llg)
```

---

## Running the Tests

LLG has a test suite covering all current functionality. Start with the basic test, then run individual files:

```bash
make test           # basic test — run this first
make test_context   # lifecycle: init, destroy, quit, isRunning
make test_window    # window properties: size, title, resize, resizable
make test_color     # draw state: fill, stroke, color, background
make test_frame     # frame control: clear, present, fps cap, delta time
make test_event     # event handling — interactive, requires manual input
```

A passing basic test looks like this:

![Test Output](docs/images/test_output.png)

---

## API Overview

### Lifecycle

| Function | Description |
|---|---|
| `LLG_init(title, w, h)` | Open display, create window, return context |
| `LLG_destroy(ctx)` | Free all resources and close display |
| `LLG_isRunning(ctx)` | Returns 1 while window is active |
| `LLG_quit(ctx)` | Signal the loop to stop |

### Window

| Function | Description |
|---|---|
| `LLG_getWidth(ctx)` | Get current window width |
| `LLG_getHeight(ctx)` | Get current window height |
| `LLG_setTitle(ctx, title)` | Update the window title bar |
| `LLG_resize(ctx, w, h)` | Resize window and recreate backbuffer |
| `LLG_setResizable(ctx, flag)` | Lock or unlock window resizing |

### Frame

| Function | Description |
|---|---|
| `LLG_clear(ctx)` | Fill backbuffer with background color |
| `LLG_present(ctx)` | Flip backbuffer to screen |
| `LLG_setFpsCap(ctx, fps)` | Cap the frame rate |
| `LLG_deltaTime(ctx)` | Seconds elapsed since last frame |
| `LLG_time()` | Monotonic time in seconds |

### Draw State

| Function | Description |
|---|---|
| `LLG_setColor(ctx, color)` | Set fill and stroke to the same color |
| `LLG_setFill(ctx, color)` | Set fill color and enable fill |
| `LLG_setStroke(ctx, color)` | Set stroke color and enable stroke |
| `LLG_noFill(ctx)` | Disable fill |
| `LLG_noStroke(ctx)` | Disable stroke |
| `LLG_setStrokeWidth(ctx, w)` | Set stroke line width |
| `LLG_setBackground(ctx, color)` | Set the background clear color |

### Drawing

| Function | Description |
|---|---|
| `LLG_drawPixel(ctx, x, y)` | Draw a single pixel |
| `LLG_drawLine(ctx, x1, y1, x2, y2)` | Draw a line |
| `LLG_drawRect / LLG_fillRect` | Outline or filled rectangle |
| `LLG_drawCircle / LLG_fillCircle` | Outline or filled circle |
| `LLG_drawEllipse / LLG_fillEllipse` | Outline or filled ellipse |
| `LLG_drawPolygon / LLG_fillPolygon` | Outline or filled polygon |
| `LLG_drawArc / LLG_fillArc` | Outline or filled arc |
| `LLG_rect / LLG_circle / LLG_ellipse` | Honors both fill and stroke state |

### Events

| Function | Description |
|---|---|
| `LLG_pollEvent(ctx, ev)` | Non-blocking — returns 0 if nothing pending |
| `LLG_waitEvent(ctx, ev)` | Blocking — waits until an event arrives |
| `LLG_keyDown(ctx, key)` | Returns 1 if key is currently held |
| `LLG_mouseDown(ctx, button)` | Returns 1 if mouse button is held |
| `LLG_mousePos(ctx, x, y)` | Get current cursor position |

### Errors

| Function | Description |
|---|---|
| `LLG_getError()` | Get and clear the last error |
| `LLG_clearError()` | Clear the error state |
| `LLG_errorStr(err)` | Human-readable error description |

---

## Contributing

Contributions are welcome. Please read [CONTRIBUTING.md](CONTRIBUTING.md) before opening a pull request — it covers branching, code style, commit message format, and the PR process.

---

## License

LLG is licensed under the MIT License. See [LICENSE](LICENSE) for the full text.