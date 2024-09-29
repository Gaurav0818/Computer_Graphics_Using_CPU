#include "vector.h"
#include <sstream>


vec3::vec3() : x(0), y(0), z(0) {}
vec3::vec3(float a) : x(a), y(a), z(a) {}
vec3::vec3(float e0, float e1, float e2) : x(e0), y(e1), z(e2) {}

vec3 vec3::operator-() const { return vec3(-x, -y, -z); }

void vec3::fromString(const std::string& s, char comma) {
    ExtractVectorfromString(*this, s, comma);
}

vec3& vec3::operator+=(const vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

vec3& vec3::operator-=(const vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

vec3& vec3::operator*=(const vec3& v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

vec3& vec3::operator/=(const vec3& v) {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

vec3& vec3::operator*=(float t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

vec3& vec3::operator/=(float t) {
    return *this *= 1 / t;
}

vec3& vec3::operator+=(float t) {
    x += t;
    y += t;
    z += t;
    return *this;
}

vec3& vec3::operator-=(float t) {
    x -= t;
    y -= t;
    z -= t;
    return *this;
}

float vec3::length() const {
    return std::sqrt(length_squared());
}

float vec3::length_squared() const {
    return x * x + y * y + z * z;
}

vec3 vec3::normalise() const {
    float l = length();
    return vec3(x / l, y / l, z / l);
}

void vec3::normalise() {
    float l = length();
    x /= l;
    y /= l;
    z /= l;
}

void vec3::RotateInX(float angle)
{
    float posY = y;
    float posz = z;

    x = x;
    y = posY * cos(angle) - posz * sin(angle);
    z = posY * sin(angle) + posz * cos(angle);
}

void vec3::RotateInY(float angle)
{
    float posX = x;
    float posZ = z;

    x = posX * cos(angle) - posZ * sin(angle);
    y = y;
    z = posX * sin(angle) + posZ * cos(angle);
}

void vec3::RotateInZ(float angle)
{
    float posX = x;
    float posY = y;

    x = posX * cos(angle) - posY * sin(angle);
    y = posX * sin(angle) + posY * cos(angle);
    z = z;
}

vec2::vec2() : x(0), y(0) {}
vec2::vec2(float a) : x(a), y(a) {}
vec2::vec2(float a, float b) : x(a), y(b) {}

void vec2::fromString(const std::string& s, char comma) {
    ExtractVectorfromString(*this, s, comma);
}

vec2& vec2::operator+=(float f) {
    x += f;
    y += f;
    return *this;
}

vec2& vec2::operator-=(float f) {
    x -= f;
    y -= f;
    return *this;
}

vec2& vec2::operator*=(float f) {
    x *= f;
    y *= f;
    return *this;
}

vec2& vec2::operator/=(float f) {
    x /= f;
    y /= f;
    return *this;
}

vec2& vec2::operator+=(vec2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

vec2& vec2::operator-=(vec2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

vec2& vec2::operator*=(vec2& v) {
    x *= v.x;
    y *= v.y;
    return *this;
}

vec2& vec2::operator/=(vec2& v) {
    x /= v.x;
    y /= v.y;
    return *this;
}

float vec2::length() const {
    return std::sqrt(length_squared());
}

float vec2::length_squared() const {
    return x * x + y * y;
}

vec2 vec2::normalise() const {
    float l = length();
    return vec2(x / l, y / l);
}

void vec2::normalise() {
    float l = length();
    x /= l;
    y /= l;
}

float vec2::rad() const {
    return std::atan2(y, x);
}

std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

std::ostream& operator<<(std::ostream& out, const vec2& v) {
    return out << v.x << ' ' << v.y;
}

void ExtractVectorfromString(vec2& v, const std::string& s, char comma) {
    std::stringstream ss(s);
    float x, y;
    ss >> x >> comma >> y;
    v.x = x;
    v.y = y;
}

void ExtractVectorfromString(vec3& v, const std::string& s, char comma) {
    std::stringstream ss(s);
    float x, y, z;
    ss >> x >> comma >> y >> comma >> z;
    v.x = x;
    v.y = y;
    v.z = z;
}

vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

vec2 operator+(const vec2& u, const vec2& v) {
    return vec2(u.x + v.x, u.y + v.y);
}

vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

vec2 operator-(const vec2& u, const vec2& v) {
    return vec2(u.x - v.x, u.y - v.y);
}

vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

vec2 operator*(const vec2& u, const vec2& v) {
    return vec2(u.x * v.x, u.y * v.y);
}

vec3 operator/(const vec3& u, const vec3& v) {
    return vec3(u.x / v.x, u.y / v.y, u.z / v.z);
}

vec2 operator/(const vec2& u, vec2& v) {
    return vec2(u.x / v.x, u.y / v.y);
}

vec3 operator*(float t, const vec3& v) {
    return vec3(t * v.x, t * v.y, t * v.z);
}

vec3 operator*(const vec3& v, float t) {
    return t * v;
}

vec3 operator/(float t, const vec3& v) {
    return vec3(t / v.x, t / v.y, t / v.z);
}

vec3 operator/(const vec3& v, float t) {
    return vec3(v.x / t, v.y / t, v.z / t);
}

vec2 operator/(float t, const vec2& v) {
    return vec2(t / v.x, t / v.y);
}

vec2 operator/(const vec2& v, float t) {
    return vec2(v.x / t, v.y / t);
}


float dot(const vec3& u, const vec3& v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

float dot(const vec2& u, const vec2& v) {
    return u.x * v.x + u.y * v.y;
}

vec3 cross(const vec3& u, const vec3& v) {
    return vec3(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

float cross(const vec2& u, const vec2& v) {
    return u.x * v.y - u.y * v.x;
}

vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

vec2 unit_vector(const vec2& v) {
    return v / v.length();
}

vec2 lerp(const vec2& v, const vec2& u, float t) {
    return v * t + u * (1 - t);
}

vec3 lerp(const vec3& v, const vec3& u, float t) {
    return v * t + u * (1 - t);
}

float absolute(float a) {
    return a < 0 ? -a : a;
}

float distance(const vec2& v, const vec2& u) {
    return std::sqrt((v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y));
}

float distance(const vec3& v, const vec3& u) {
    return std::sqrt(
        (v.x - u.x) * (v.x - u.x) +
        (v.y - u.y) * (v.y - u.y) +
        (v.z - u.z) * (v.z - u.z)
    );
}

void rotateVecInX(vec3& v, float angle)
{
    v.RotateInX(angle);
}

void rotateVecInY(vec3& v, float angle)
{
    v.RotateInY(angle);
}

void rotateVecInZ(vec3& v, float angle)
{
    v.RotateInZ(angle);
}
