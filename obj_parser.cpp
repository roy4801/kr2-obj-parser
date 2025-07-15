#include "parser.h"
#include <fstream>
#include <sstream>

#define STR_LENG 256

ObjParser::ObjParser(std::string path) {
	ParseObjFile(path);
}

ObjParser::~ObjParser() {
	// Default destructor
}

ObjParser::Vertex ObjParser::ParseVertex(std::string input) {
	// parse vertex (x, y, z [,w])
	double x, y, z, w = 1.0;
	std::stringstream ss(input);
	ss >> x >> y >> z >> w;

	ObjParser::Vertex tmp_point(x, y, z, w);

	return tmp_point;
}

ObjParser::Face ObjParser::ParseFace(std::string input) {
	// parse face (v1[/vt1[/vn1]] v2[/vt2[/vn2]] v3[/vt3[/vn3]] ...)
	std::vector<int> vertex_indices;
	std::vector<int> texture_indices;
	std::vector<int> normal_indices;
	
	std::stringstream ss(input);
	std::string token;
	
	while (ss >> token) {
		if (token.empty()) continue;
		
		// Split by '/'
		std::stringstream vertex_ss(token);
		std::string part;
		std::vector<std::string> parts;
		
		while (std::getline(vertex_ss, part, '/')) {
			parts.push_back(part);
		}
		
		if (!parts.empty() && !parts[0].empty()) {
			vertex_indices.push_back(std::stoi(parts[0]));
		}
		
		if (parts.size() > 1 && !parts[1].empty()) {
			texture_indices.push_back(std::stoi(parts[1]));
		}
		
		if (parts.size() > 2 && !parts[2].empty()) {
			normal_indices.push_back(std::stoi(parts[2]));
		}
	}
	
	return ObjParser::Face(vertex_indices, texture_indices, normal_indices);
}

ObjParser::Vertex ObjParser::ParseTextureCoord(std::string input) {
	// parse texture coordinate (u, v [,w])
	double u, v, w = 0.0;
	std::stringstream ss(input);
	ss >> u >> v >> w;
	
	return ObjParser::Vertex(u, v, w, 1.0);
}

ObjParser::Vertex ObjParser::ParseNormal(std::string input) {
	// parse normal (x, y, z)
	double x, y, z;
	std::stringstream ss(input);
	ss >> x >> y >> z;
	
	return ObjParser::Vertex(x, y, z, 0.0);
}

void ObjParser::ParseObjFile(std::string path) {
	std::ifstream fin(path);

#ifdef VERBOSE
	std::cout << "Open file: " << path << "\n";
#endif

	if(!fin) {
		std::cout << "Cannot open file failed: " << path << "\n";
		return ;
	}

	std::string line;
	int lineNumber = 0;
	while(std::getline(fin, line)) {
		lineNumber++;
		
		if(line.empty() || line[0] == '#') {
			continue; // Skip empty lines and comments
		}
		
		std::stringstream ss(line);
		std::string prefix;
		ss >> prefix;
		
		try {
			if(prefix == "v") {
				// Vertex
				std::string remaining;
				std::getline(ss, remaining);
				vertexes.emplace_back(ParseVertex(remaining));
			}
			else if(prefix == "vt") {
				// Texture coordinate
				std::string remaining;
				std::getline(ss, remaining);
				texture_coords.emplace_back(ParseTextureCoord(remaining));
			}
			else if(prefix == "vn") {
				// Normal
				std::string remaining;
				std::getline(ss, remaining);
				normals.emplace_back(ParseNormal(remaining));
			}
			else if(prefix == "f") {
				// Face
				std::string remaining;
				std::getline(ss, remaining);
				faces.emplace_back(ParseFace(remaining));
			}
			// Ignore other elements like materials (mtllib, usemtl), groups (g), etc.
		}
		catch(const std::exception& e) {
			std::cout << "Error parsing line " << lineNumber << ": " << line << std::endl;
			std::cout << "  Error: " << e.what() << std::endl;
		}
	}
}

void ObjParser::PrintVertexes() {
	int cnt = 0;
	for(Vertex vertex : vertexes) {
		std::cout << cnt++ << " " << vertex;
	}
}

void ObjParser::PrintFaces() {
	int cnt = 0;
	for(Face face : faces) {
		std::cout << cnt++ << " " << face;
	}
}

void ObjParser::PrintStatistics() const {
	std::cout << "OBJ Parser Statistics:" << std::endl;
	std::cout << "  Vertices: " << getVertexCount() << std::endl;
	std::cout << "  Faces: " << getFaceCount() << std::endl;
	std::cout << "  Texture Coordinates: " << getTextureCoordCount() << std::endl;
	std::cout << "  Normals: " << getNormalCount() << std::endl;
	std::cout << "  Triangles: " << getTriangleCount() << std::endl;
	std::cout << "  Quads: " << getQuadCount() << std::endl;
	std::cout << "  Has Textures: " << (hasTextures() ? "Yes" : "No") << std::endl;
	std::cout << "  Has Normals: " << (hasNormals() ? "Yes" : "No") << std::endl;
}

size_t ObjParser::getTriangleCount() const {
	size_t count = 0;
	for(const Face& face : faces) {
		if(face.isTriangle()) {
			count++;
		}
	}
	return count;
}

size_t ObjParser::getQuadCount() const {
	size_t count = 0;
	for(const Face& face : faces) {
		if(face.isQuad()) {
			count++;
		}
	}
	return count;
}
