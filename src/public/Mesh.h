#pragma once

#include <vector>

#include "vector.h"
#include "fstream"
#include "sstream"

template<typename T>
class Triangle
{
public:
	Triangle() {
		points[0] = T();
		points[1] = T();
		points[2] = T();
	}

	// Constructor to initialize with specific points
	Triangle(const T& p0, const T& p1, const T& p2) {
		points[0] = p0;
		points[1] = p1;
		points[2] = p2;
	}

	T points[3];
};

class Mesh
{
public:
	Mesh() = default;
	~Mesh() = default;

	Mesh(const Mesh&) = delete; // Delete Copy constructer

	Mesh(Mesh&& other) noexcept :
		vertices(std::move(other.vertices)),
		faces(std::move(other.faces)),
		rotation(std::move(other.rotation))
	{}

	void loadObjFileDate(const char* filePath);

public:
	std::vector<vec3_f> vertices;
	std::vector<vec3_i> faces;
	std::vector<vec3_i> texture;
	std::vector<vec3_i> normal;
	vec3_f rotation;
};