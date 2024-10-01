#pragma once

#include <cmath>
#include <iostream>
#include <string>

class vec3;
class vec2;

class vec3 {
public:
    float x, y, z;

    vec3();
    vec3(float a);
    vec3(float e0, float e1, float e2);

    void fromString(const std::string& s, char comma = ',');

    vec3 operator-() const;
    vec3& operator+=(const vec3& v);
    vec3& operator-=(const vec3& v);
    vec3& operator*=(const vec3& v);
    vec3& operator/=(const vec3& v);
    vec3& operator*=(float t);
    vec3& operator/=(float t);
    vec3& operator+=(float t);
    vec3& operator-=(float t);

    float length() const;
    float length_squared() const;
    vec3 normalise() const;
    void normalise();

    void RotateInX(float angle);
    void RotateInY(float angle);
    void RotateInZ(float angle);
};

class vec2 {
public:
    float x, y;

    vec2();
    vec2(float a);
    vec2(float a, float b);

    void fromString(const std::string& s, char comma = ',');

    vec2& operator+=(float f);
    vec2& operator-=(float f);
    vec2& operator*=(float f);
    vec2& operator/=(float f);
    vec2& operator+=(vec2& v);
    vec2& operator-=(vec2& v);
    vec2& operator*=(vec2& v);
    vec2& operator/=(vec2& v);

    float length() const;
    float length_squared() const;
    vec2 normalise() const;
    void normalise();
    float rad() const;
};

using point2 = vec2;
using point3 = vec3;
using color3 = vec3;
using face3 = vec3;

std::ostream& operator<<(std::ostream& out, const vec3& v);
std::ostream& operator<<(std::ostream& out, const vec2& v);
void ExtractVectorfromString(vec2& v, const std::string& s, char comma = ',');
void ExtractVectorfromString(vec3& v, const std::string& s, char comma = ',');

vec3 operator+(const vec3& u, const vec3& v);
vec2 operator+(const vec2& u, const vec2& v);
vec3 operator-(const vec3& u, const vec3& v);
vec2 operator-(const vec2& u, const vec2& v);
vec3 operator*(const vec3& u, const vec3& v);
vec2 operator*(const vec2& u, const vec2& v);
vec3 operator/(const vec3& u, const vec3& v);
vec2 operator/(const vec2& u, vec2& v);

vec3 operator*(float t, const vec3& v);
vec3 operator*(const vec3& v, float t);
vec3 operator/(float t, const vec3& v);
vec3 operator/(const vec3& v, float t);
vec2 operator/(float t, const vec2& v);
vec2 operator/(const vec2& v, float t);

float dot(const vec3& u, const vec3& v);
float dot(const vec2& u, const vec2& v);
vec3 cross(const vec3& u, const vec3& v);
float cross(const vec2& u, const vec2& v);

vec3 unit_vector(const vec3& v);
vec2 unit_vector(const vec2& v);
vec2 lerp(const vec2& v, const vec2& u, float t);
vec3 lerp(const vec3& v, const vec3& u, float t);
float absolute(float a);
float distance(const vec2& v, const vec2& u);
float distance(const vec3& v, const vec3& u);


void rotateVecInX(vec3& v, float angle);
void rotateVecInY(vec3& v, float angle);
void rotateVecInZ(vec3& v, float angle);
