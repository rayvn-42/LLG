# Contributing to LLG

Thank you for taking the time to contribute to LLG. Every contribution — whether it's a bug fix, a new feature, or an improvement to the docs — makes the library better for everyone.

---

## Table of Contents

- [Getting Started](#getting-started)
- [What You Can Contribute](#what-you-can-contribute)
- [Code Style](#code-style)
- [Commit Messages](#commit-messages)
- [Pull Request Guidelines](#pull-request-guidelines)
- [Reporting Bugs](#reporting-bugs)
- [Suggesting Features](#suggesting-features)

---

## Getting Started

1. **Fork** this repository
2. **Clone** your fork locally
   ```bash
   git clone https://github.com/rayvn-42/LLG.git
   cd llg
   ```
3. **Create a branch** for your change — never work directly on `main`
   ```bash
   git checkout -b fix/my-bug-fix
   # or
   git checkout -b feature/my-new-feature
   ```
4. **Make your changes**, following the code style guidelines below
5. **Run the tests** to make sure nothing is broken
   ```bash
   make test
   make test_context
   make test_window
   make test_color
   make test_frame
   make test_event
   ```
6. **Commit and push** your branch
   ```bash
   git push origin fix/my-bug-fix
   ```
7. **Open a pull request** against `main` and I'll review it as soon as possible

---

## What You Can Contribute

**Bug Fixes**
If you find a bug, fix it and open a PR. If you're not sure how to fix it, open an issue instead so it can be tracked.

**Code Improvements**
Refactoring, optimization, and cleanup are all welcome. If you're making a larger structural change, open an issue first to discuss the approach before writing code — this avoids wasted effort if the direction isn't right.

**New Features**
Before implementing a new feature, open an issue describing what you'd like to add and why. This ensures it fits the scope and direction of the library and avoids duplicate work.

**Documentation**
Improvements to the README, this file, inline code comments, or adding new examples are always appreciated.

**Tests**
Adding test cases for untested behavior, or improving existing tests to be more robust, is a great way to contribute even without touching library code.

---

## Code Style

LLG follows a consistent style throughout. Please match it in any code you contribute.

**Naming conventions**
- Public functions: `LLG_camelCase` — e.g. `LLG_drawRect`
- Private/internal functions: `LLG__camelCase` (double underscore) — e.g. `LLG__colorToPixel`
- Structs and types: `LLGPascalCase` — e.g. `LLGContext`, `LLGDrawState`
- Enum values: `LLG_SCREAMING_SNAKE` — e.g. `LLG_ERR_BADARG`
- Macros: `LLG_SCREAMING_SNAKE` — e.g. `LLG_RGB`

**Error handling**
- Every public function must NULL-guard its context parameter
- Bad arguments must dispatch `LLG_ERR_BADARG` before returning
- Never silently fail — if something goes wrong, set an error

**Headers**
- Public headers go in `include/LLG/` and must never include `src/internal.h` or any `X11/` headers
- Source files include their own public header first, then `internal.h`

**File placement**
- New public functions go in the appropriate existing `.c` file (see the file map in the README)
- New source files must be added to `OBJ` in the Makefile

**Comments**
- Functions should have a short comment block listing parameters and return value
- Non-obvious logic should have inline comments explaining *why*, not just *what*

---

## Commit Messages

Use clear, present-tense imperative commit messages:

```
add LLG_drawArc implementation
fix NULL dereference in LLG_resize
refactor LLG__colorToPixel error handling
remove unused pval variable in color.c
```

Not:
```
fixed stuff
updated file
changes
WIP
```

For larger changes, add a short body after a blank line:
```
fix backbuffer mismatch after failed LLG_resize

Previously ctx->width and ctx->height were updated before the
new Pixmap was created. If XCreatePixmap failed, the context
dimensions no longer matched the actual backbuffer size.
Now dimensions are only updated after successful allocation.
```

---

## Pull Request Guidelines

- Keep PRs focused — one fix or one feature per PR. Large mixed PRs are hard to review, unless you want to torture me :).
- If your PR fixes an open issue, reference it in the PR description: `Fixes #12`
- Make sure the project compiles cleanly with no new warnings under `-Wall -Wextra`
- Make sure all existing tests still pass
- If you're adding new functionality, add tests for it in the appropriate `tests/test_*.c` file

---

## Reporting Bugs

Open a GitHub issue and include:

- A minimal code example that reproduces the problem
- What you expected to happen
- What actually happened
- Your OS, display server, and compiler version (`gcc --version`)

---

## Suggesting Features

Open a GitHub issue with:

- What you want to add and why
- How you'd expect it to look from the user's side (ideally a short code snippet)
- Whether you'd like to implement it yourself or just flag the idea

---

## Questions

If you're unsure about anything before opening a PR, just open an issue and ask. It's always better to check first.