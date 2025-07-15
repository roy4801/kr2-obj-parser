#include "parser.h"

objParser::Vertex::Vertex() : x(0.0), y(0.0), z(0.0), w(1.0) {}

objParser::Vertex::Vertex(double x, double y, double z, double w) 
						  : x(x), y(y), z(z), w(w) {}

void objParser::Vertex::set(double x, double y, double z, double w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

std::ostream& operator<<(std::ostream& os, const objParser::Vertex& p) {
	os << p.x << " " << p.y << " " << p.z << " " << p.w << "\n";
	return os;
}