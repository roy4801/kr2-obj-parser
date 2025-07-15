#include "parser.h"
#include <iostream>

int main() {
    std::cout << "Testing OBJ parser..." << std::endl;
    
    // Test parsing the bunny.obj file
    objParser parser("bunny.obj");
    
    std::cout << "Vertices: " << parser.vertexes.size() << std::endl;
    std::cout << "Faces: " << parser.faces.size() << std::endl;
    std::cout << "Texture coords: " << parser.texture_coords.size() << std::endl;
    std::cout << "Normals: " << parser.normals.size() << std::endl;
    
    // Print first few vertices and faces
    std::cout << "\nFirst 5 vertices:" << std::endl;
    for(int i = 0; i < 5 && i < parser.vertexes.size(); ++i) {
        std::cout << "v" << i << ": " << parser.vertexes[i];
    }
    
    std::cout << "\nFirst 5 faces:" << std::endl;
    for(int i = 0; i < 5 && i < parser.faces.size(); ++i) {
        std::cout << "f" << i << ": " << parser.faces[i];
    }
    
    return 0;
}