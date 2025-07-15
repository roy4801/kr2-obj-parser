#include "parser.h"
#include <iostream>

int main() {
    std::cout << "Testing OBJ parser..." << std::endl;
    
    // Test parsing the bunny.obj file
    std::cout << "\n=== Testing bunny.obj ===" << std::endl;
    objParser parser("bunny.obj");
    
    if (!parser.isEmpty()) {
        parser.printStatistics();
        
        // Test getter methods
        std::cout << "\nTesting getter methods:" << std::endl;
        std::cout << "First vertex: (" << parser.getVertices()[0].getX() << ", " 
                  << parser.getVertices()[0].getY() << ", " << parser.getVertices()[0].getZ() << ")" << std::endl;
        
        std::cout << "First face vertex count: " << parser.getFaces()[0].getVertexCount() << std::endl;
        std::cout << "First face is triangle: " << (parser.getFaces()[0].isTriangle() ? "Yes" : "No") << std::endl;
        
        // Show first few face vertex indices
        const auto& firstFace = parser.getFaces()[0];
        std::cout << "First face vertex indices: ";
        for (int idx : firstFace.getVertexIndices()) {
            std::cout << idx << " ";
        }
        std::cout << std::endl;
        
    } else {
        std::cout << "Failed to parse OBJ file or file is empty." << std::endl;
    }
    
    // Test the pyramid file with texture coordinates and normals
    std::cout << "\n=== Testing test_pyramid.obj ===" << std::endl;
    objParser pyramid("test_pyramid.obj");
    
    if (!pyramid.isEmpty()) {
        pyramid.printStatistics();
        
        // Test face with texture and normal indices
        const auto& face = pyramid.getFaces()[0];
        std::cout << "\nFirst face details:" << std::endl;
        std::cout << "  Vertex indices: ";
        for (int idx : face.getVertexIndices()) {
            std::cout << idx << " ";
        }
        std::cout << std::endl;
        
        if (face.hasTextureCoords()) {
            std::cout << "  Texture indices: ";
            for (int idx : face.getTextureIndices()) {
                std::cout << idx << " ";
            }
            std::cout << std::endl;
        }
        
        if (face.hasNormals()) {
            std::cout << "  Normal indices: ";
            for (int idx : face.getNormalIndices()) {
                std::cout << idx << " ";
            }
            std::cout << std::endl;
        }
        
    } else {
        std::cout << "Failed to parse pyramid OBJ file or file is empty." << std::endl;
    }
    
    return 0;
}