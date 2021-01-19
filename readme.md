# rhio-devkit

This is a base project for the development of rhomb.io C++ libraries. It is based on VSCode + PlatformIO.

The repository contains a PlatformIO Project and a set de git submodules with rhomb.io libraries.

## Target Audience

This repository is for developers, not suitable for production. Your collaboration is greatly appreciated. Please follow the indications below to participate in the development.

## Download and Install

### 1. Clone the repository

Using this command that also uncludes all the lib dependencies

```bash
git clone --recurse-submodules -j8 git@github.com:Rhomb-io/rhio-devkit.git
```

### 2. Add a main.cpp file

The repository does not contain a main.cpp file by default, you should add it. Each library inside `lib` directory has a custom `main-x.cpp.back` file inside src directory. Duplicate (not remove) the file but naming it as `main.cpp`.

### 3. Add a platformio.ini file

There is a sample file called platformio.sample.ini, in the same way as main-x.cpp, duplicate the file removing the "sample" extension.

> IMPORTANT do not remove any main-x.cpp or "sample" file from the src directory or you will also remove it from the repository.

### 4. Compile the code

Finally, use platformio toolbar to upload and flash the microcontroller

## Recommended VSCode extensions

The following extensions will help you to integrate better with the development:

* [Editorcofig](https://editorconfig.org/) (editorconfig.editorconfig)
* Todo Tree (gruntfuggly.todo-tree)

Use the extension manager inside VSCode to install it.

## Code Style

All the C++ code is written using the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html). The directory `.vscode` (hidden dir on the repo root) contains a `settings.json` with this configuration.

Also we use [_Editorconfig_](https://editorconfig.org/) to keep the indentation in 2 spaces with trailing whitespaces and final new line.

## Libraries

Current list of libraries (inside lib directory)

| Library                                                                      | Description                                                                                                       |
| :--------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------- |
| [rhio-flash](https://github.com/Rhomb-io/rhio-flash)                         | Read/Write on the SPI Flash Memory on Halley PCB                                                                  |
| [rhio-ioexpander](https://gitlab.com/rhombio/rhio-libraries/rhio-ioexpander) | Manage the IOExpander of Halley and Hydra                                                                         |
| [rhio-pinmap](https://github.com/Rhomb-io/rhio-pinmap)                       | Pinmap for the rhomb.io standard                                                                                  |
| [rhio-puf](https://github.com/Rhomb-io/rhio-puf)                             | Portable event driven development library                                                                         |
| [rhio-state-machine](https://github.com/Rhomb-io/rhio-state-machine)         | Portable State Machine library                                                                                    |
| [rhio-sync](https://github.com/Rhomb-io/rhio-sync)                           | Some portable libraries implementing multiple paradigms like concurrency, parallelism, callback management... etc |

## Update libraries

Rhio libraries are located in separated repositories and linked here using [git submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules). Use this command to update all the libraries to the latest version:

```bash
# update all recursively
git submodule update --remote --merge

# or update only one library:
git submodule update --recursive lib/rhio-flash
```

## Unit Testing

Some libraries have implemented unit testing using [PlatformIO Unit Tesing](https://docs.platformio.org/en/latest/plus/unit-testing.html) framework.

Unit test are located inside the `test` directory and may run using the PlatformIO command `Test`.

Please consider writing test code whenever possible.

### Enable/Disable test modules

Each library has its own tests, by default all tests will be executed, but through the `platformio.ini` file we can limit which tests will run each time.

Currently this are the available test:

| Macro                   | Description                                                                          |
| ----------------------- | ------------------------------------------------------------------------------------ |
| RHIO_TEST_ALL           | Enable all test (will invalidate other macros)                                       |
| RHIO_TEST_PUF           | Enable test for [rhio-puf](https://github.com/Rhomb-io/rhio-puf)                     |
| RHIO_TEST_STATE_MACHINE | Enable test for [rhio-state-machine](https://github.com/Rhomb-io/rhio-state-machine) |
| RHIO_TEST_FLASH         | Enable test for [rhio-flash](https://github.com/Rhomb-io/rhio-flash)                 |

To change the test settings, open the platformio.ini file and modify the macros:

```ini
build_flags =
  -DRHIO_TEST_ALL=1
  -DRHIO_TEST_PUF=1
  -DRHIO_TEST_STATE_MACHINE=1
  -DRHIO_TEST_FLASH=1
```

## Contact

Main maintainer @jenguidanos. Please feel free to post an issue.
