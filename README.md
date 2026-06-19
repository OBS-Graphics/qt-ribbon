# Nedrysoft Ribbon

![ribbon image](https://user-images.githubusercontent.com/55795671/100941548-b5652700-34f1-11eb-975d-5bf284852590.png)

The ribbon library provides a simple ribbon bar implementation for Qt-based applications.

## Features

* Cross-platform and tested under macOS, Windows and Linux
* RibbonWidget is the main ribbon widget.
* RibbonGroup is a container for sub controls.
* RibbonPushButton is a push-button styled for the ribbon.
* RibbonDropButton is a push button with a drop-down button to allow multiple actions.
* RibbonComboBox is a combo box styled for the ribbon.
* RibbonCheckBox is a checkbox styled for the ribbon.
* RibbonLineEdit is a line edit styled for the ribbon.
* RibbonSlider is a slider styled for the ribbon.
* RibbonToolButton is a tool button styled for the ribbon.

You can build the designer plugin, which allows the layout of ribbon bars in Designer or Qt Creator.

## Requirements

* Qt 6.5+
* CMake 3.21+
* C++20-capable compiler

## Using via CPM

The easiest way to consume this library is through [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake):

```cmake
CPMAddPackage("gh:obs-graphics/qt-ribbon@1.0.0")
target_link_libraries(MyTarget PRIVATE Ribbon::Ribbon)
```

The library has no external dependencies — only Qt 6.5+ is required.

## Building standalone

To build the library, invoke CMake or open the `CMakeLists.txt` file in your preferred IDE.

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### CMake options

| Variable | Default | Description |
|---|---|---|
| `NEDRYSOFT_RIBBON_BUILD_DESIGNER_PLUGIN` | `OFF` | Build the Qt Designer plugin |

# License

This project is open source and released under the GPLv3 licence.

Distributed as-is; no warranty is given.
