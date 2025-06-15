# Project generated with [Templi](https://github.com/RickaPrincy/Templi)

# rcli :wrench:

rcli is a powerful C++ library that simplifies the creation of CLI applications. It provides convenient user `input functions` and efficiently manages command-line `options` and `subcommands`. 

# Installation :seedling:

- Archlinux

```bash
yay -Sy rcli 
```
For the moment, you have to build rcli to use it if you use another system (not archlinux)

- Dependancies

    - CMake (Version 3.27 or later)
    - C++ Compiler with C++17 support

```bash
bash <(curl -s https://raw.githubusercontent.com/RickaPrincy/rcli/main/install.sh)
```

- Build manually

```bash
git clone -b v1.5.2 https://github.com/RickaPrincy/rcli.git

cd rcli

mkdir build

cd build

cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .

sudo make install

cd ../..

rm -rf rcli 
```
#### :warning: If some libs are not found after building manually

Identify the installation path of the missing library. For example, let's assume the library is installed in `/usr/local/lib` (on linux it should be there).

If you are using Linux, add the following code to your `~/.zshrc` or `~/.bashrc` based on what you use (replacing `/usr/local/lib` with the actual installation path):

```bash
export LD_LIBRARY_PATH=/usr/local/lib:\$LD_LIBRARY_PATH
```

- You can also simply use rcli as a submodule.


# Gettting started

### Step 1: Include rcli in your Project

Include the rcli library in your project by adding the following include statements at the beginning of your source file:

```cpp
#include <rcli/rcli.hpp>
#include <iostream>
```

### Step 2: Create and Configure Your CLI Application

Create an instance of the App class, specifying the application name, version, and a brief description.

```cpp
int main(int argc, const char *argv[]){
    app example("example", "1.9.5", "cool application");
    // ...
    // (Your application logic will be added in the following steps)
    return example.run(argc, argv);
}
```
### Step 3: Define Commands and Options

Define commands and options within your application. For example, you can create an "init" command and a "hello" command. Specify options for user input, such as the file name and user's name:

```cpp
command init("init", "Initialize a new project", [](command* _init){
    std::cout << "File value: " << _init->get_option_value("file") << "\n";
});

init.add_option("-f,--file", "Specify file name", "file");

command hello("hello", "Say hello", [&](command* _hello){
    std::string name = _hello->get_option_value("name");
    std::cout << "Hello, " << name << "!" << "\n";
});

hello.add_option("-n,--name", "Specify your name", "name");
```

### Step 4: Run Your CLI Application

Add the commands to your App object, and run your CLI application by calling the run method:

```cpp
templi.add_subcommand(&init);
templi.add_subcommand(&hello);
templi.run(argc, argv);
```

# Another features 

## Automatically Added Options :bulb:

rcli automatically adds help options `(-h and --help)` to all commands, and version options `(-v and --version)` to the main App object. Users can use these options to get information about your application.

# Preview

![Example0](./images/default_color.png)

# License 

This project is licensed under the [MIT License](LICENSE).
