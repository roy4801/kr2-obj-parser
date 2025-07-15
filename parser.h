#include <iostream>
#include <string>
#include <vector>

class objParser {
public:
	struct Vertex {
private:
		double x, y, z, w;
public:
		// Constructor
		Vertex();
		Vertex(double x, double y, double z, double w);

		// Print
		friend std::ostream& operator<<(std::ostream& os, const Vertex& p);
		
		// Set funciton
		void set(double x, double y, double z, double w);
	};

	struct Face {
		std::vector<int> vertex_indices;
		std::vector<int> texture_indices;
		std::vector<int> normal_indices;
		
		// Constructor
		Face();
		Face(const std::vector<int>& vertices);
		Face(const std::vector<int>& vertices, const std::vector<int>& textures, const std::vector<int>& normals);
		
		// Print
		friend std::ostream& operator<<(std::ostream& os, const Face& f);
	};

	objParser(std::string path);
	~objParser();

	void printVertexes();
	void printFaces();

	// vertexes
	std::vector<Vertex> vertexes;
	
	// faces
	std::vector<Face> faces;

	// texture coordinates
	std::vector<Vertex> texture_coords;
	
	// normals
	std::vector<Vertex> normals;

private:
	// Vertex parser
	Vertex parseVertex(std::string input);
	
	// Face parser
	Face parseFace(std::string input);
	
	// Texture coordinate parser
	Vertex parseTextureCoord(std::string input);
	
	// Normal parser
	Vertex parseNormal(std::string input);

	// Parser handler
	void parseObjFile(std::string path);
	
};