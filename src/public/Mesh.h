#pragma once

#include <vector>

#include "vector.h"

#define N_MESH_VERTICES 8
#define N_MESH_FACES (6 * 2)	// 6 cube faces, 2 Tri each per face


class Mesh
{
public:
	Mesh() ;
	~Mesh() = default;


	std::vector<vec3> meshVertices = { 0 };
	std::vector<face3> meshFaces = { 0 };
};

class Triangle
{
public:
	vec2 points[3] = { 0 };
};