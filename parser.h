#include <iostream>
#include <string>
#include <vector>

class ObjParser {
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
		
		// Set function
		void set(double x, double y, double z, double w);
		
		// Getter methods
		double getX() const { return x; }
		double getY() const { return y; }
		double getZ() const { return z; }
		double getW() const { return w; }
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
		
		// Getter methods
		const std::vector<int>& getVertexIndices() const { return vertex_indices; }
		const std::vector<int>& getTextureIndices() const { return texture_indices; }
		const std::vector<int>& getNormalIndices() const { return normal_indices; }
		
		// Utility methods
		size_t getVertexCount() const { return vertex_indices.size(); }
		bool hasTextureCoords() const { return !texture_indices.empty(); }
		bool hasNormals() const { return !normal_indices.empty(); }
		bool isTriangle() const { return vertex_indices.size() == 3; }
		bool isQuad() const { return vertex_indices.size() == 4; }
	};

	ObjParser(std::string path);
	~ObjParser();

	void PrintVertexes();
	void PrintFaces();
	
	// Getter methods
	size_t getVertexCount() const { return vertexes.size(); }
	size_t getFaceCount() const { return faces.size(); }
	size_t getTextureCoordCount() const { return texture_coords.size(); }
	size_t getNormalCount() const { return normals.size(); }
	
	// Access methods
	const std::vector<Vertex>& getVertices() const { return vertexes; }
	const std::vector<Face>& getFaces() const { return faces; }
	const std::vector<Vertex>& getTextureCoords() const { return texture_coords; }
	const std::vector<Vertex>& getNormals() const { return normals; }
	
	// Validation methods  
	bool hasTextures() const { return !texture_coords.empty(); }
	bool hasNormals() const { return !normals.empty(); }
	bool isEmpty() const { return vertexes.empty() && faces.empty(); }
	
	// Statistics methods
	void PrintStatistics() const;
	size_t getTriangleCount() const;
	size_t getQuadCount() const;

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
	Vertex ParseVertex(std::string input);
	
	// Face parser
	Face ParseFace(std::string input);
	
	// Texture coordinate parser
	Vertex ParseTextureCoord(std::string input);
	
	// Normal parser
	Vertex ParseNormal(std::string input);

	// Parser handler
	void ParseObjFile(std::string path);
	
};