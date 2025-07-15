# Test Directory

This directory contains the test suite for the kr2-obj-parser project.

## Structure

### test_parser.cpp
Main test file containing Google Test test cases for the OBJ parser functionality.

### data/
Directory containing OBJ test files used by the test suite.

## Running Tests

Build and run the tests using CMake:

```bash
mkdir build
cd build
cmake -DBUILD_GRAPHICS=OFF ..
make test_parser
./test_parser
```

Or run specific tests:

```bash
ctest -R "BunnyObjParsing"
ctest -R "PyramidObjParsing"
```

## Test Coverage

The test suite covers:
- Basic OBJ parsing (vertices, faces)
- Texture coordinate and normal parsing
- Face type detection (triangles, quads)
- Error handling and edge cases
- Data access methods
- Statistics functionality