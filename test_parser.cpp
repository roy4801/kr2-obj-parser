#include "parser.h"
#include <gtest/gtest.h>
#include <cmath>

class OBJParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Test files should be available in the working directory
    }

    void TearDown() override {
        // Clean up if needed
    }
};

// Test bunny.obj parsing
TEST_F(OBJParserTest, BunnyObjParsing) {
    ObjParser parser("test_data/bunny.obj");
    
    EXPECT_FALSE(parser.isEmpty()) << "Failed to parse bunny.obj or file is empty";
    
    if (!parser.isEmpty()) {
        EXPECT_GT(parser.getVertexCount(), 0) << "No vertices found in bunny.obj";
        EXPECT_GT(parser.getFaceCount(), 0) << "No faces found in bunny.obj";
        
        // Check specific expected values from bunny.obj
        EXPECT_EQ(parser.getVertexCount(), 2503) << "Expected 2503 vertices in bunny.obj";
        EXPECT_EQ(parser.getFaceCount(), 4968) << "Expected 4968 faces in bunny.obj";
        
        // Check that all faces are triangles
        size_t triangleCount = parser.getTriangleCount();
        EXPECT_EQ(triangleCount, parser.getFaceCount()) << "All faces should be triangles";
        
        // Check that there are no texture coordinates or normals
        EXPECT_FALSE(parser.hasTextures()) << "bunny.obj should not have texture coordinates";
        EXPECT_FALSE(parser.hasNormals()) << "bunny.obj should not have normals";
    }
}

// Test getter methods with bunny.obj
TEST_F(OBJParserTest, GetterMethods) {
    ObjParser parser("test_data/bunny.obj");
    
    ASSERT_FALSE(parser.isEmpty()) << "Failed to parse bunny.obj";
    
    // Test vertex getter
    const auto& vertices = parser.getVertices();
    EXPECT_FALSE(vertices.empty()) << "Vertices should not be empty";
    
    // Test first vertex coordinates
    const auto& firstVertex = vertices[0];
    EXPECT_NO_THROW(firstVertex.getX()) << "Should be able to get X coordinate";
    EXPECT_NO_THROW(firstVertex.getY()) << "Should be able to get Y coordinate";
    EXPECT_NO_THROW(firstVertex.getZ()) << "Should be able to get Z coordinate";
    
    // Test faces getter
    const auto& faces = parser.getFaces();
    EXPECT_FALSE(faces.empty()) << "Faces should not be empty";
    
    // Test first face properties
    const auto& firstFace = faces[0];
    EXPECT_TRUE(firstFace.isTriangle()) << "First face should be a triangle";
    EXPECT_EQ(firstFace.getVertexCount(), 3) << "Triangle should have 3 vertices";
    
    // Test vertex indices
    const auto& vertexIndices = firstFace.getVertexIndices();
    EXPECT_EQ(vertexIndices.size(), 3) << "Triangle should have 3 vertex indices";
    
    // All indices should be valid (1-based, so > 0 and <= vertex count)
    for (int idx : vertexIndices) {
        EXPECT_GT(idx, 0) << "Vertex index should be positive (1-based)";
        EXPECT_LE(idx, static_cast<int>(parser.getVertexCount())) << "Vertex index should not exceed vertex count";
    }
}

// Test pyramid.obj parsing with texture coordinates and normals
TEST_F(OBJParserTest, PyramidObjParsing) {
    ObjParser parser("test_data/test_pyramid.obj");
    
    EXPECT_FALSE(parser.isEmpty()) << "Failed to parse test_pyramid.obj or file is empty";
    
    if (!parser.isEmpty()) {
        EXPECT_GT(parser.getVertexCount(), 0) << "No vertices found in test_pyramid.obj";
        EXPECT_GT(parser.getFaceCount(), 0) << "No faces found in test_pyramid.obj";
        
        // Check specific expected values from test_pyramid.obj
        EXPECT_EQ(parser.getVertexCount(), 5) << "Expected 5 vertices in test_pyramid.obj";
        EXPECT_EQ(parser.getFaceCount(), 5) << "Expected 5 faces in test_pyramid.obj";
        
        // Check texture coordinates and normals
        EXPECT_TRUE(parser.hasTextures()) << "test_pyramid.obj should have texture coordinates";
        EXPECT_TRUE(parser.hasNormals()) << "test_pyramid.obj should have normals";
        EXPECT_EQ(parser.getTextureCoordCount(), 5) << "Expected 5 texture coordinates";
        EXPECT_EQ(parser.getNormalCount(), 5) << "Expected 5 normals";
        
        // Check triangle and quad counts
        size_t triangleCount = parser.getTriangleCount();
        size_t quadCount = parser.getQuadCount();
        EXPECT_EQ(triangleCount, 4) << "Expected 4 triangles";
        EXPECT_EQ(quadCount, 1) << "Expected 1 quad";
        EXPECT_EQ(triangleCount + quadCount, parser.getFaceCount()) << "Triangle + quad count should equal total face count";
    }
}

// Test face properties with texture and normal indices
TEST_F(OBJParserTest, FacePropertiesWithTexNormals) {
    ObjParser parser("test_data/test_pyramid.obj");
    
    ASSERT_FALSE(parser.isEmpty()) << "Failed to parse test_pyramid.obj";
    
    const auto& faces = parser.getFaces();
    ASSERT_FALSE(faces.empty()) << "Faces should not be empty";
    
    // Test first face (should be a triangle)
    const auto& firstFace = faces[0];
    EXPECT_TRUE(firstFace.isTriangle()) << "First face should be a triangle";
    EXPECT_FALSE(firstFace.isQuad()) << "First face should not be a quad";
    
    // Test texture coordinate indices
    EXPECT_TRUE(firstFace.hasTextureCoords()) << "First face should have texture coordinates";
    const auto& texIndices = firstFace.getTextureIndices();
    EXPECT_EQ(texIndices.size(), 3) << "Triangle should have 3 texture indices";
    
    // Test normal indices
    EXPECT_TRUE(firstFace.hasNormals()) << "First face should have normals";
    const auto& normalIndices = firstFace.getNormalIndices();
    EXPECT_EQ(normalIndices.size(), 3) << "Triangle should have 3 normal indices";
    
    // Test vertex indices
    const auto& vertexIndices = firstFace.getVertexIndices();
    EXPECT_EQ(vertexIndices.size(), 3) << "Triangle should have 3 vertex indices";
    
    // Test last face (should be a quad)
    const auto& lastFace = faces[faces.size() - 1];
    EXPECT_TRUE(lastFace.isQuad()) << "Last face should be a quad";
    EXPECT_FALSE(lastFace.isTriangle()) << "Last face should not be a triangle";
    EXPECT_EQ(lastFace.getVertexCount(), 4) << "Quad should have 4 vertices";
}

// Test empty or invalid file handling
TEST_F(OBJParserTest, InvalidFileHandling) {
    ObjParser parser("nonexistent.obj");
    
    EXPECT_TRUE(parser.isEmpty()) << "Parser should be empty for non-existent file";
    EXPECT_EQ(parser.getVertexCount(), 0) << "Vertex count should be 0 for invalid file";
    EXPECT_EQ(parser.getFaceCount(), 0) << "Face count should be 0 for invalid file";
    EXPECT_FALSE(parser.hasTextures()) << "Should not have textures for invalid file";
    EXPECT_FALSE(parser.hasNormals()) << "Should not have normals for invalid file";
}

// Test statistics functionality
TEST_F(OBJParserTest, Statistics) {
    ObjParser parser("test_data/bunny.obj");
    
    ASSERT_FALSE(parser.isEmpty()) << "Failed to parse bunny.obj";
    
    // Test triangle/quad counting
    size_t triangleCount = parser.getTriangleCount();
    size_t quadCount = parser.getQuadCount();
    
    EXPECT_GT(triangleCount, 0) << "Should have some triangles";
    EXPECT_EQ(triangleCount + quadCount, parser.getFaceCount()) << "Triangle + quad count should equal total face count";
    
    // Test data presence checks
    EXPECT_FALSE(parser.hasTextures()) << "bunny.obj should not have textures";
    EXPECT_FALSE(parser.hasNormals()) << "bunny.obj should not have normals";
    EXPECT_FALSE(parser.isEmpty()) << "Parser should not be empty";
}

// Test vertex constructor and methods
TEST_F(OBJParserTest, VertexFunctionality) {
    ObjParser parser("test_data/bunny.obj");
    
    ASSERT_FALSE(parser.isEmpty()) << "Failed to parse bunny.obj";
    
    const auto& vertices = parser.getVertices();
    ASSERT_FALSE(vertices.empty()) << "Vertices should not be empty";
    
    // Test vertex getters
    const auto& vertex = vertices[0];
    double x = vertex.getX();
    double y = vertex.getY();
    double z = vertex.getZ();
    
    // Values should be finite
    EXPECT_TRUE(std::isfinite(x)) << "X coordinate should be finite";
    EXPECT_TRUE(std::isfinite(y)) << "Y coordinate should be finite";
    EXPECT_TRUE(std::isfinite(z)) << "Z coordinate should be finite";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}