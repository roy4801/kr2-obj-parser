# Test Data Directory

This directory contains OBJ test files for the kr2-obj-parser test suite.

## Files

### bunny.obj
- **Description**: Real-world model of a Stanford bunny
- **Properties**: 2503 vertices, 4968 faces (all triangles)
- **Features**: Vertices only, no texture coordinates or normals
- **Use**: Testing performance and basic parsing functionality

### test_pyramid.obj
- **Description**: Hand-crafted pyramid model
- **Properties**: 5 vertices, 5 faces (4 triangles + 1 quad)
- **Features**: Vertices, texture coordinates, and normals
- **Use**: Testing complete OBJ format support including v/vt/vn indices

### cube.obj
- **Description**: Simple cube model
- **Properties**: 8 vertices, 6 faces (all quads)
- **Features**: Vertices only
- **Use**: Testing quad face parsing

### triangle.obj
- **Description**: Minimal triangle model
- **Properties**: 3 vertices, 1 face (triangle)
- **Features**: Vertices only
- **Use**: Testing basic parsing functionality

## Usage

These files are referenced in the test suite located at `test/test_parser.cpp`. The parser is tested with various combinations of vertex data, face types, and optional features like texture coordinates and normals.