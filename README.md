# rcli :wrench:

rcli is a powerful C++ library that simplifies the creation of CLI applications. It provides convenient user `input functions` and efficiently manages command-line `options` and `subcommands`. 

With rcli, you can effortlessly handle user interactions, process input, and implement features like help commands (your_cli -h).

For the color, rcli use [TColor](http://github.com/RickaPrincy/TColor)

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
    ColorConfig::key = TColor::B_RED; // rcli use TColor
    App example("example", "1.9.5", "cool application");
    // ...
    // (Your application logic will be added in the following steps)
    example.run(argc, argv);
    return 0;
}
```
### Step 3: Define Commands and Options

Define commands and options within your application. For example, you can create an "init" command and a "hello" command. Specify options for user input, such as the file name and user's name:

```cpp
Command init("init", "Initialize a new project", [](Command* _init){
    std::cout << "File value: " << _init->get_option_value("file") << std::endl;
});

init.add_option("-f,--file", "Specify file name", "file");

Command hello("hello", "Say hello", [&](Command* _hello){
    std::string name = _hello->get_option_value("name");
    if (name.empty()) {
        // If name is not provided as an option, ask the user for input
        name = ask_input_value("What is your name");
    }
    std::cout << "Hello, " << name << "!" << std::endl;
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

### Automatically Added Options :bulb:

rcli automatically adds help options `(-h and --help)` to all commands, and version options `(-v and --version)` to the main App object. Users can use these options to get information about your application.

### Use Various Input Types in rcli :jack_o_lantern:

rcli provides various input types:

```cpp
#ifndef __RCLI_INPUTS__
#define __RCLI_INPUTS__
    
    #include <vector>
    #include <string>

    namespace rcli {

        // one simple value
        std::string ask_input_value(InputConfig config);

        // multiples values
        std::vector<std::string> ask_inputs_values(std::vector<InputConfig> configs);

        // ask the value in list without showing the list
        std::string ask_value_in_list(InputConfig config, std::vector<std::string> options, bool ignore_case = false);

        // ask single one boolean
        bool ask_boolean(std::string text, bool default_value = true);

        // ask in value list of options
        std::string ask_value_in_list_as_number(std::string text, std::vector<std::string> options);

    } // namespace rcli

#endif
```

# Default color

![Example0](./images/default_color.png)

# Customized_color

![Example1](./images/customized_color.png)

# Some output

![Example2](./images/version.png)

![Example1](./images/command.png)

![Example2](./images/input.png)
 
# License 

This project is licensed under the [MIT License](LICENSE).
