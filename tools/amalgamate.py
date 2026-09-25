#!/usr/bin/env python3
"""Merges include/rcli/*.hpp into the single header single_include/rcli/rcli.hpp.

Usage:
    python3 tools/amalgamate.py          # (re)generate the single header
    python3 tools/amalgamate.py --check  # fail if the committed single header is outdated
"""

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SOURCE_DIR = ROOT / "include" / "rcli"
ENTRY = SOURCE_DIR / "rcli.hpp"
OUTPUT = ROOT / "single_include" / "rcli" / "rcli.hpp"

LOCAL_INCLUDE = re.compile(r'^\s*#\s*include\s+(?:"([^"]+)"|<rcli/([^>]+)>)\s*$')
PRAGMA_ONCE = re.compile(r"^\s*#\s*pragma\s+once\s*$")
VERSION_PART = re.compile(r"^#define RCLI_VERSION_(MAJOR|MINOR|PATCH) (\d+)$", re.MULTILINE)


def expand(path: Path, visited: set) -> list:
    """Returns the lines of `path` with its local includes inlined (each file only once)."""
    if path in visited:
        return []
    visited.add(path)

    lines = [f"// ----- begin {path.name} -----\n"]
    for line in path.read_text(encoding="utf-8").splitlines(keepends=True):
        if PRAGMA_ONCE.match(line):
            continue
        match = LOCAL_INCLUDE.match(line)
        if match:
            lines.extend(expand((path.parent / (match.group(1) or match.group(2))).resolve(), visited))
            continue
        lines.append(line)
    lines.append(f"// ----- end {path.name} -----\n")
    return lines


def generate() -> str:
    parts = dict(VERSION_PART.findall((SOURCE_DIR / "version.hpp").read_text(encoding="utf-8")))
    version = f"{parts['MAJOR']}.{parts['MINOR']}.{parts['PATCH']}"

    header = (
        "// rcli v" + version + " - single header version\n"
        "// Header-only library to build command line applications in C++17.\n"
        "// https://github.com/RickaPrincy/rcli - MIT License\n"
        "//\n"
        "// GENERATED FILE, DO NOT EDIT: run `python3 tools/amalgamate.py` after changing include/.\n"
        "#pragma once\n"
        "\n"
    )
    body = "".join(expand(ENTRY.resolve(), set()))
    # collapse the blank lines left by removed includes / pragmas
    body = re.sub(r"\n{3,}", "\n\n", body)
    return header + body


def main() -> int:
    content = generate()
    if "--check" in sys.argv[1:]:
        current = OUTPUT.read_text(encoding="utf-8") if OUTPUT.exists() else ""
        if current != content:
            print(f"{OUTPUT.relative_to(ROOT)} is outdated: run `python3 tools/amalgamate.py`")
            return 1
        print(f"{OUTPUT.relative_to(ROOT)} is up to date")
        return 0

    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    OUTPUT.write_text(content, encoding="utf-8")
    print(f"generated {OUTPUT.relative_to(ROOT)} ({content.count(chr(10))} lines)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
