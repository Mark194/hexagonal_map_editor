# Hexagonal Map Editor

A hexagonal map editor for creating game boards, strategy maps, and visualizations. This program allows you to create, edit, and save maps composed of hexagonal cells with extensive customization options.

## 🌟 Key Features

### 🎨 Map Creation and Editing

- Intuitive drawing of hexagonal grids of various sizes

- Select and change the color of individual cells

- Place building icons on cells

- Change the display style of hexagons

### 🎭 Custom Styles

- Create your own cell appearance styles

- Save styles to separate files for reuse

- Load previously created styles

- Configure visual parameters: borders, fill, effects

### 💾 File Management

- Save maps to files for future editing

- Load previously created maps

- Export maps to various formats

- Manage a style library

🛠 Additional Features 
- Map zooming and panning

- Batch cell editing

- Undo/Redo actions

## 🛠 Technology used

- Qt 5 - Cross-platform framework for GUI development
- QtSvg - Vector graphics and icon handling

- C++17 - Modern C++ standard for high performance

- CMake - Project build system

- QtConcurrent - Multithreaded operations for processing large maps

## ⬇️ Install

- Requirements

- CMake 3.10 or higher
- Qt 5.15.2 or higher
- Compiler with C++17 support (GCC 7+, Clang 5+, MSVC 2017+)

## 👨‍💻 Build from Source

```commandline

# Clone the repository
git clone https://github.com/yourusername/hexagonal-map-editor.git
cd hexagonal-map-editor

# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the project
cmake --build . --config Release

# Run the application
./HexagonalMapEditor
```

## 📦 Pre-built Binaries

Pre-built binaries for Windows, Linux, and macOS are available in the [Releases section](https://github.com/Mark194/hexagonal_map_editor/releases).
