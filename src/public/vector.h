#pragma once

#include <cmath>
#include <iostream>
#include <string>


// Forward declarations of template classes
template<typename T = int>
class vec4;

template<typename T = int>
class vec3;

template<typename T = int>
class vec2;

// Typedefs for different vector types
using vec4_f = vec4<float>;
using vec4_i = vec4<int>;
using vec3_f = vec3<float>;
using vec2_f = vec2<float>;
using vec2_i = vec2<int>;   
using vec3_i = vec3<int>;   

// vec4 class template
template<typename T = int>
class vec4 {
public:
    T x, y, z, w;

    vec4();
    vec4(T a);
    vec4(T e0, T e1, T e2, T e3);

    ~vec4() = default;

    void fromString(const std::string& s, char comma = ',');

    vec4 operator-() const;
    vec4& operator+=(const vec4& v);
    vec4& operator-=(const vec4& v);
    vec4& operator*=(const vec4& v);
    vec4& operator/=(const vec4& v);
    vec4& operator*=(T t);
    vec4& operator/=(T t);
    vec4& operator+=(T t);
    vec4& operator-=(T t);

    float length() const;
    T length_squared() const;
    vec4 normalise() const;
    void normalise();
};

// vec3 class template
template<typename T = int>
class vec3 {
public:
    T x, y, z;

    vec3();
    vec3(T a);
    vec3(T e0, T e1, T e2);

    ~vec3() = default;

    void fromString(const std::string& s, char comma = ',');

    vec3 operator-() const;
    vec3& operator+=(const vec3& v);
    vec3& operator-=(const vec3& v);
    vec3& operator*=(const vec3& v);
    vec3& operator/=(const vec3& v);
    vec3& operator*=(T t);
    vec3& operator/=(T t);
    vec3& operator+=(T t);
    vec3& operator-=(T t);

    float length() const;
    T length_squared() const;
    vec3 normalise() const;
    void normalise();

    void RotateInX(float angle);
    void RotateInY(float angle);
    void RotateInZ(float angle);
};

// vec2 class template
template<typename T = int>
class vec2 {
public:
    T x, y;

    vec2();
    vec2(T a);
    vec2(T a, T b);

    void fromString(const std::string& s, char comma = ',');

    vec2& operator+=(T f);
    vec2& operator-=(T f);
    vec2& operator*=(T f);
    vec2& operator/=(T f);
    vec2& operator+=(const vec2& v);
    vec2& operator-=(const vec2& v);
    vec2& operator*=(const vec2& v);
    vec2& operator/=(const vec2& v);

    float length() const;
    T length_squared() const;
    vec2 normalise() const;
    void normalise();
    T rad() const;
};

// Template function declarations
// Output stream overloads
template<typename T>
std::ostream& operator<<(std::ostream& out, const vec4<T>& v) 
{
    return out << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const vec3<T>& v) 
{
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const vec2<T>& v) 
{
    return out << v.x << ' ' << v.y;
}

// String extraction functions
template<typename T>
void ExtractVectorfromString(vec2<T>& v, const std::string& s, char comma) 
{
    std::stringstream ss(s);
    T x, y;
    ss >> x >> comma >> y;
    v.x = x;
    v.y = y;
}

template<typename T>
void ExtractVectorfromString(vec3<T>& v, const std::string& s, char comma) 
{
    std::stringstream ss(s);
    T x, y, z;
    ss >> x >> comma >> y >> comma >> z;
    v.x = x;
    v.y = y;
    v.z = z;
}

template<typename T>
void ExtractVectorfromString(vec4<T>& v, const std::string& s, char comma) 
{
    std::stringstream ss(s);
    T x, y, z, w;
    ss >> x >> comma >> y >> comma >> z >> comma >> w;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
}

// Arithmetic operators for vec4
template<typename T>
vec4<T> operator+(const vec4<T>& u, const vec4<T>& v) 
{
    return vec4<T>(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}

template<typename T>
vec4<T> operator+(const vec4<T>& v, T t) 
{
    return vec4<T>(v.x + t, v.y + t, v.z + t, v.w + t);
}

template<typename T>
vec4<T> operator+(T t, const vec4<T>& v) 
{
    return vec4<T>(t + v.x, t + v.y, t + v.z, t + v.w);
}

template<typename T>
vec4<T> operator-(const vec4<T>& u, const vec4<T>& v) 
{
    return vec4<T>(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);
}

template<typename T>
vec4<T> operator-(const vec4<T>& v, T t) 
{
    return vec4<T>(v.x - t, v.y - t, v.z - t, v.w - t);
}

template<typename T>
vec4<T> operator-(T t, const vec4<T>& v) 
{
    return vec4<T>(t - v.x, t - v.y, t - v.z, t - v.w);
}

template<typename T>
vec4<T> operator*(const vec4<T>& u, const vec4<T>& v) 
{
    return vec4<T>(u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w);
}

template<typename T>
vec4<T> operator*(const vec4<T>& v, T t) 
{
    return vec4<T>(v.x * t, v.y * t, v.z * t, v.w * t);
}

template<typename T>
vec4<T> operator*(T t, const vec4<T>& v) 
{
    return vec4<T>(t * v.x, t * v.y, t * v.z, t * v.w);
}

template<typename T>
vec4<T> operator/(const vec4<T>& u, const vec4<T>& v) 
{
    return vec4<T>(u.x / v.x, u.y / v.y, u.z / v.z, u.w / v.w);
}

template<typename T>
vec4<T> operator/(const vec4<T>& v, T t) 
{
    return vec4<T>(v.x / t, v.y / t, v.z / t, v.w / t);
}

template<typename T>
vec4<T> operator/(T t, const vec4<T>& v) 
{
    return vec4<T>(t / v.x, t / v.y, t / v.z, t / v.w);
}

// Arithmetic operators for vec3
template<typename T>
vec3<T> operator+(const vec3<T>& u, const vec3<T>& v) 
{
    return vec3<T>(u.x + v.x, u.y + v.y, u.z + v.z);
}

template<typename T>
vec3<T> operator+(const vec3<T>& v, T t) 
{
    return vec3<T>(v.x + t, v.y + t, v.z + t);
}

template<typename T>
vec3<T> operator+(T t, const vec3<T>& v) 
{
    return vec3<T>(t + v.x, t + v.y, t + v.z);
}

template<typename T>
vec3<T> operator-(const vec3<T>& u, const vec3<T>& v) 
{
    return vec3<T>(u.x - v.x, u.y - v.y, u.z - v.z);
}

template<typename T>
vec3<T> operator-(const vec3<T>& v, T t) 
{
    return vec3<T>(v.x - t, v.y - t, v.z - t);
}

template<typename T>
vec3<T> operator-(T t, const vec3<T>& v) 
{
    return vec3<T>(t - v.x, t - v.y, t - v.z);
}

template<typename T>
vec3<T> operator*(const vec3<T>& u, const vec3<T>& v) 
{
    return vec3<T>(u.x * v.x, u.y * v.y, u.z * v.z);
}

template<typename T>
vec3<T> operator*(const vec3<T>& v, T t) 
{
    return vec3<T>(v.x * t, v.y * t, v.z * t);
}

template<typename T>
vec3<T> operator*(T t, const vec3<T>& v) 
{
    return vec3<T>(t * v.x, t * v.y, t * v.z);
}

template<typename T>
vec3<T> operator/(const vec3<T>& u, const vec3<T>& v) 
{
    return vec3<T>(u.x / v.x, u.y / v.y, u.z / v.z);
}

template<typename T>
vec3<T> operator/(const vec3<T>& v, T t) 
{
    return vec3<T>(v.x / t, v.y / t, v.z / t);
}

template<typename T>
vec3<T> operator/(T t, const vec3<T>& v) 
{
    return vec3<T>(t / v.x, t / v.y, t / v.z);
}

// Arithmetic operators for vec2
template<typename T>
vec2<T> operator+(const vec2<T>& u, const vec2<T>& v) 
{
    return vec2<T>(u.x + v.x, u.y + v.y);
}

template<typename T>
vec2<T> operator+(const vec2<T>& v, T t) 
{
    return vec2<T>(v.x + t, v.y + t);
}

template<typename T>
vec2<T> operator+(T t, const vec2<T>& v) 
{
    return vec2<T>(t + v.x, t + v.y);
}

template<typename T>
vec2<T> operator-(const vec2<T>& u, const vec2<T>& v) 
{
    return vec2<T>(u.x - v.x, u.y - v.y);
}

template<typename T>
vec2<T> operator-(const vec2<T>& v, T t) 
{
    return vec2<T>(v.x - t, v.y - t);
}

template<typename T>
vec2<T> operator-(T t, const vec2<T>& v) {
    return vec2<T>(t - v.x, t - v.y);
}

template<typename T>
vec2<T> operator*(const vec2<T>& u, const vec2<T>& v) 
{
    return vec2<T>(u.x * v.x, u.y * v.y);
}

template<typename T>
vec2<T> operator*(const vec2<T>& v, T t) 
{
    return vec2<T>(v.x * t, v.y * t);
}

template<typename T>
vec2<T> operator*(T t, const vec2<T>& v) 
{
    return vec2<T>(t * v.x, t * v.y);
}

template<typename T>
vec2<T> operator/(const vec2<T>& u, const vec2<T>& v) 
{
    return vec2<T>(u.x / v.x, u.y / v.y);
}

template<typename T>
vec2<T> operator/(const vec2<T>& v, T t) 
{
    return vec2<T>(v.x / t, v.y / t);
}

template<typename T>
vec2<T> operator/(T t, const vec2<T>& v) 
{
    return vec2<T>(t / v.x, t / v.y);
}

// Dot and cross product functions
template<typename T>
T dot(const vec3<T>& u, const vec3<T>& v) 
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

template<typename T>
T dot(const vec2<T>& u, const vec2<T>& v) 
{
    return u.x * v.x + u.y * v.y;
}

template<typename T>
vec3<T> cross(const vec3<T>& u, const vec3<T>& v) 
{
    return vec3<T>(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

template<typename T>
T cross(const vec2<T>& u, const vec2<T>& v) 
{
    return u.x * v.y - u.y * v.x;
}

// Utility functions
template<typename T>
vec4<T> unit_vector(const vec4<T>& v) 
{
    return v / v.length();
}

template<typename T>
T distance(const vec4<T>& v, const vec4<T>& u) 
{
    return std::sqrt(
        (v.x - u.x) * (v.x - u.x) +
        (v.y - u.y) * (v.y - u.y) +
        (v.z - u.z) * (v.z - u.z) +
        (v.w - u.w) * (v.w - u.w)
    );
}
template<typename T>
vec3<T> unit_vector(const vec3<T>& v) 
{
    return v / v.length();
}

template<typename T>
vec2<T> unit_vector(const vec2<T>& v) 
{
    return v / v.length();
}

template<typename T>
vec2<T> lerp(const vec2<T>& v, const vec2<T>& u, T t) 
{
    return v * t + u * (1 - t);
}

template<typename T>
vec3<T> lerp(const vec3<T>& v, const vec3<T>& u, T t) 
{
    return v * t + u * (1 - t);
}

template<typename T>
T absolute(T a) 
{
    return a < 0 ? -a : a;
}

template<typename T>
T distance(const vec2<T>& v, const vec2<T>& u) 
{
    return std::sqrt((v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y));
}

template<typename T>
T distance(const vec3<T>& v, const vec3<T>& u) 
{
    return std::sqrt(
        (v.x - u.x) * (v.x - u.x) +
        (v.y - u.y) * (v.y - u.y) +
        (v.z - u.z) * (v.z - u.z)
    );
}

// Rotation functions
template<typename T>
void rotateVecInX(vec3<T>& v, float angle) 
{
    v.RotateInX(angle);
}

template<typename T>
void rotateVecInY(vec3<T>& v, float angle) 
{
    v.RotateInY(angle);
}

template<typename T>
void rotateVecInZ(vec3<T>& v, float angle) 
{
    v.RotateInZ(angle);
}

template<typename T>
float getAngle(vec2<T>& v1, vec2<T>& v2)
{
    return acos(dot(v1, v2) / (v1.length * v2.length));
}

template<typename T>
float getAngle(vec3<T>& v1, vec3<T>& v2)
{
    return acos(dot(v1, v2) / (v1.length * v2.length));
}
