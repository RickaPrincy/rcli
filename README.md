# rcli :wrench:

A **header-only**, dependency-free C++17 library to build command line applications: commands, subcommands,
options, flags, automatic `--help` and `--version`.

```c++
#include <rcli/rcli.hpp>
#include <iostream>

auto main(int argc, const char *argv[]) -> int
{
	rcli::app app("greet", "Say hello", "1.0.0");

	rcli::command hello("hello", "Say hello to someone", [](rcli::command *cmd)
	{ std::cout << "Hello " << cmd->get_option_value("name") << "!\n"; });
	hello.add_option("-n,--name", "Your name", "name");

	app.add_subcommand(&hello);
	return app.run(argc, argv);
}
```

```console
$ ./greet hello --name Ricka
Hello Ricka!
```

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Getting started](#getting-started)
- [Options](#options)
- [Commands and subcommands](#commands-and-subcommands)
- [Help and version](#help-and-version)
- [Exit codes](#exit-codes)
- [API reference](#api-reference)
- [Building the tests and the example](#building-the-tests-and-the-example)
- [Releasing](#releasing)
- [License](#license)

## Features

- Header only: download **one file** and `#include` it, nothing to build, install or link (CMake supported too)
- Nested commands and subcommands
- Options with values (`-f value`, `--file value`, `--file=value`), flags (`--force`), undeclared options
- Automatic `-h,--help` on every command and `-v,--version` on the application
- Colors only when writing to a terminal (disabled with `NO_COLOR`)
- Linux, macOS and Windows

## Installation

Requirements: a C++17 compiler. That's all.

### Option 1: download the single header (simplest)

The whole library is also available as one self-contained file:
[`single_include/rcli/rcli.hpp`](./single_include/rcli/rcli.hpp).

```bash
# latest release
curl -LO https://github.com/RickaPrincy/rcli/releases/latest/download/rcli.hpp
# or the current main branch
curl -LO https://raw.githubusercontent.com/RickaPrincy/rcli/main/single_include/rcli/rcli.hpp
```

```c++
#include "rcli.hpp"
```

```bash
g++ -std=c++17 main.cpp -o app   # no flags, no libraries
```

The single header and the modular headers of `include/` provide exactly the same API. Placed in an `rcli/` folder
of your include path, it can also be included as `<rcli/rcli.hpp>`, so you can switch to any of the options below
without changing your code.

### Option 2: CMake `FetchContent`

```cmake
include(FetchContent)
FetchContent_Declare(
  rcli
  GIT_REPOSITORY https://github.com/RickaPrincy/rcli.git
  GIT_TAG v2.1.0)
FetchContent_MakeAvailable(rcli)

target_link_libraries(your_target PRIVATE rcli::rcli)
```

### Option 3: git submodule

```bash
git submodule add https://github.com/RickaPrincy/rcli.git external/rcli
```

```cmake
add_subdirectory(external/rcli)
target_link_libraries(your_target PRIVATE rcli::rcli)
```

Tests and examples are only built when rcli is the top-level project.

### Option 4: install it system-wide

```bash
# Arch Linux (AUR)
yay -S rcli

# anywhere else
git clone -b v2.1.0 https://github.com/RickaPrincy/rcli
cmake -S rcli -B rcli/build -DRCLI_BUILD_TESTS=OFF -DRCLI_BUILD_EXAMPLES=OFF
sudo cmake --install rcli/build
```

```cmake
find_package(rcli 2.1 REQUIRED)
target_link_libraries(your_target PRIVATE rcli::rcli)
```

Without building anything: each [release](https://github.com/RickaPrincy/rcli/releases) also ships
`rcli-<version>.tar.gz` / `.zip`, an already installed layout (`include/` + `share/cmake/`). Extract it anywhere and
pass `-DCMAKE_PREFIX_PATH=/path/to/rcli-<version>` to CMake.

> Upgrading from rcli 2.0: rcli is now header-only, but the API did not change. `target_link_libraries(... rcli)`
> keeps working next to the new `rcli::rcli`, and `#include <rcli/rcli_config.hpp>` still provides `RCLI_VERSION`.

### Option 5: copy the modular headers

Copy the `include/rcli` folder into your project and add its parent to the include path.

## Getting started

### 1. Create the application

```c++
#include <rcli/rcli.hpp>
#include <iostream>

using namespace rcli;

auto main(int argc, const char *argv[]) -> int
{
	//  name       description                 version
	app example("example", "Generate cool application", "1.9.5");
	example.add_informations({ { "Author", "RickaPrincy" } });  // shown by --version

	// ... commands, see below

	return example.run(argc, argv);
}
```

`run` also accepts `char *argv[]`, so `int main(int argc, char *argv[])` works too.

### 2. Define commands and their options

The callback of a command receives the command itself, to read the option values:

```c++
command init("init", "Initialize a new project", [](command *cmd)
{
	std::cout << "file: " << cmd->get_option_value("file") << "\n";
	if (cmd->has_option("force"))
	{
		std::cout << "overwriting\n";
	}
});
init.add_option("-f,--file", "Specify file name", "file");
init.add_flag("--force", "Overwrite existing files", "force");

command hello("hello", "Say hello", [](command *cmd)
{ std::cout << "Hello " << cmd->get_option_value("name") << "!\n"; });
hello.add_option("-n,--name", "Specify your name", "name");
```

### 3. Add them to the application

```c++
example.add_subcommand(&init);
example.add_subcommand(&hello);
return example.run(argc, argv);
```

```console
$ ./example init --file main.cpp --force
file: main.cpp
overwriting
```

A complete example lives in [example/main.cpp](./example/main.cpp).

## Options

| Declared with                                    | Command line                                       | `get_option_value(key)`  |
|--------------------------------------------------|----------------------------------------------------|--------------------------|
| `add_option("-f,--file", "desc", "file")`        | `-f a.txt`, `--file a.txt`, `--file=a.txt`         | `"a.txt"`                |
| `add_flag("-V,--verbose", "desc", "verbose")`    | `-V`, `--verbose` (`--verbose=false` also works)   | `"true"`                 |
| nothing (undeclared option)                      | `-author me`, `--author me`, `--author=me`         | `"me"` under `"author"`  |

- An absent option gives `""`; use `has_option(key)` to distinguish absent from empty.
- Undeclared options are stored under their name without the leading dashes. It lets you accept dynamic options, for
  example one per template placeholder.
- An option can be declared once and added to several commands: `add_option(&shared_option)` copies it.
- When an option is repeated, the last value wins.

## Commands and subcommands

Commands can be nested at any depth: `tool remote add --name origin`.

```c++
command remote("remote", "Manage remotes", nullptr);  // no callback: prints its help
command add("add", "Add a remote", [](command *cmd) { /* ... */ });
remote.add_subcommand(&add);
app.add_subcommand(&remote);
```

`add_subcommand(command *)` stores a **copy**: add options and subcommands to a command *before* adding it to its
parent. To keep modifying it afterwards, pass a `std::shared_ptr<command>` instead, which is stored as is.

Options written before a subcommand belong to the parent: in `tool -g x remote add`, `g` is an option of `tool`.

## Help and version

- `-h` / `--help` prints the help of the command it follows (`./example init --help`), with its usage, description,
  options and subcommands. The same help is printed on invalid input.
- `-v` / `--version` (alone) prints the name, version, description and informations of the application.
- An application run without arguments prints its help.

Override `print_help()` or `print_version()` in a subclass to customize them.

## Exit codes

`app::run` returns `0` on success (including `--help` / `--version`) and `1` on invalid input (unknown command,
option without value, unexpected argument), after printing the help. Return it from `main`.

## API reference

```c++
namespace rcli
{
	using callback = std::function<void(command *)>;

	class option
	{
		option(std::string names, std::string description, std::string key_name, bool is_flag = false);
		get_base_name(), get_names(), get_description(), get_key_name(), is_flag(), matches(name)
	};

	class command
	{
		command(std::string name, std::string description, callback on_run);

		add_option(std::string names, std::string description, std::string key_name);
		add_option(option *);
		add_flag(std::string names, std::string description, std::string key_name);
		add_subcommand(command *);                  // copy
		add_subcommand(std::shared_ptr<command>);   // shared
		add_informations(std::map<std::string, std::string>);

		get_option_value(key) -> std::string;       // "" when absent
		has_option(key) -> bool;
		get_options_values() -> const std::map<std::string, std::string> &;
		get_name(), get_description(), get_options(), get_subcommands()
		virtual print_help();
	};

	class app : public command
	{
		app(std::string name, std::string description, std::string version);
		run(int argc, const char *argv[]) -> int;   // also char *argv[]
		get_version();
		virtual print_version();
	};
}
```

`RCLI_VERSION` (e.g. `"2.1.0"`), `RCLI_VERSION_MAJOR`, `RCLI_VERSION_MINOR` and `RCLI_VERSION_PATCH` give the library
version.

## Building the tests and the example

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure   # tests, run against include/ and single_include/
                                             # (doctest is downloaded automatically)
./build/bin/example --help

cmake --build build --target amalgamate      # regenerate the single header after editing include/
cmake --build build --target format          # clang-format
cmake --build build --target lint            # clang-tidy
```

| CMake option          | Default           |
|-----------------------|-------------------|
| `RCLI_BUILD_TESTS`    | ON when top-level |
| `RCLI_BUILD_EXAMPLES` | ON when top-level |
| `RCLI_INSTALL`        | ON when top-level |

## Releasing

1. Bump the version in [`include/rcli/version.hpp`](./include/rcli/version.hpp) (CMake reads it from there),
   run `python3 tools/amalgamate.py`, update `pkgver` in the `PKGBUILD`, commit and push.
2. Actions > **release** > **Run workflow** (or push the tag `v<version>`). The workflow runs the tests, builds the release
   files with `tools/package_release.sh` and publishes the GitHub release:

   | File                          | Content                                          |
   |-------------------------------|--------------------------------------------------|
   | `rcli.hpp`                    | the single header                                |
   | `rcli-<v>-single-header.zip`  | the single header + license                      |
   | `rcli-<v>.tar.gz` / `.zip`    | installed layout for `find_package`              |
   | `SHA256SUMS`                  | checksums                                        |

3. Arch Linux: run `updpkgsums` on the `PKGBUILD`, commit, push, then run the **aur-publish** workflow.

## License

This project is licensed under the MIT License. See the [LICENSE](License.txt) file for details.
