#include "parser.h"

ObjParser::Face::Face() {}

ObjParser::Face::Face(const std::vector<int>& vertices) 
    : vertex_indices(vertices) {}

ObjParser::Face::Face(const std::vector<int>& vertices, const std::vector<int>& textures, const std::vector<int>& normals)
    : vertex_indices(vertices), texture_indices(textures), normal_indices(normals) {}

std::ostream& operator<<(std::ostream& os, const ObjParser::Face& f) {
    os << "f ";
    for (size_t i = 0; i < f.vertex_indices.size(); ++i) {
        if (i > 0) os << " ";
        os << f.vertex_indices[i];
        if (!f.texture_indices.empty() && i < f.texture_indices.size()) {
            os << "/" << f.texture_indices[i];
        }
        if (!f.normal_indices.empty() && i < f.normal_indices.size()) {
            if (f.texture_indices.empty()) os << "/";
            os << "/" << f.normal_indices[i];
        }
    }
    os << "\n";
    return os;
}