# Test Data

This directory contains test data files used by the OBJ parser tests.

## Files

### bunny.obj
- **Description**: Stanford bunny model with only vertices and faces
- **Statistics**: 2,503 vertices, 4,968 triangular faces
- **Features**: Vertices (v), faces (f)
- **No texture coordinates or normals**
- **Use**: Tests basic vertex and face parsing functionality

### test_pyramid.obj
- **Description**: Simple pyramid model with complete OBJ format features
- **Statistics**: 5 vertices, 5 faces (4 triangles + 1 quad), 5 texture coordinates, 5 normals
- **Features**: Vertices (v), texture coordinates (vt), normals (vn), faces (f) with v/vt/vn indices
- **Use**: Tests parsing of texture coordinates, normals, and mixed triangle/quad faces

## Test Coverage

The test files collectively cover:
- ✅ Basic vertex parsing
- ✅ Face parsing (triangles and quads)  
- ✅ Texture coordinate parsing
- ✅ Normal vector parsing
- ✅ Complex face format (v/vt/vn indices)
- ✅ Real-world model testing
- ✅ Edge case handling (empty/invalid files)