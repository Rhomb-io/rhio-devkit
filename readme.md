# rhio-devkit

This is a base project for the development of rhomb.io C++ libraries. It is based on VSCode + Platformio.

The repository contains a Platformio Project and a set de git submodules with rhomb.io libraries.

## Target Audience

This repository is for developers, not suitable for production. Your collaboration is greatly appreciated. Please follow the indications below to participate in the development.

## Download and Install

1. Clone the repo with the libraries:

```bash
git submodule add git@github.com:Rhomb-io/rhio-state-machine.git
git submodule update --remote --merge
```

2. Add a main.cpp file. The repository does not contain a main.cpp file by default, you should add it. Each library inside `lib` directory has a custom `main-x.cpp.back` file inside src directory. Duplicate (not remove) the file but naming it as `main.cpp`.

> IMPORTANT do not remove any main-x.cpp file from the src directory or you will delete it from the repository.

3. Compile the code

### Download VSCode + Platfomio

Download VSCode and install PlatformIO as a plugin.

### Recommended VSCode extensions

The following extensions will help you to integrate better with the development:

* Editorcofig (editorconfig.editorconfig)
* Todo Tree (gruntfuggly.todo-tree)

Use the extension manager inside VSCode to install it.

## Code Style

All the C++ code is written using the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html). The directory `.vscode` (hidden dir on the repo root) contains a `settings.json` with this configuration.

Also we use _Editorconfig_ to keep the indentation in 2 spaces with trailing whitespaces and final new line.

## Update libraries

Rhio libraries are located in separated repositories and linked here using git submodules. Use this command to update all the libraries to the latest version:

```
git submodule update --remote --merge
```

## Unit Testing

Some libraries have implemented unit testing using [Platformio Unit Tesing](https://docs.platformio.org/en/latest/plus/unit-testing.html) franework.

Unit test are located inside the `test` directory and may run using the Platformio command `Test`.

Please consider writing test code whenever possible.

## Contact

Main mainteiner @jenguidanos. Please feel free to post an issue.
