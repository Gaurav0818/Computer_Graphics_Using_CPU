#include "vector.h"
#include <sstream>

// Explicit template instantiation
template class vec2<int>;
template class vec2<float>;
template class vec3<int>;
template class vec3<float>;
template class vec4<int>;
template class vec4<float>;

// vec4 member functions
template<typename T>
vec4<T>::vec4() : x(0), y(0), z(0), w(0) {}

template<typename T>
vec4<T>::vec4(T a) : x(a), y(a), z(a), w(a) {}

template<typename T>
vec4<T>::vec4(T e0, T e1, T e2, T e3) : x(e0), y(e1), z(e2), w(e3) {}

template<typename T>
vec4<T> vec4<T>::operator-() const 
{
    return vec4(-x, -y, -z, -w);
}

template<typename T>
void vec4<T>::fromString(const std::string& s, char comma) 
{
    ExtractVectorfromString(*this, s, comma);
}

template<typename T>
vec4<T>& vec4<T>::operator+=(const vec4& v) 
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

template<typename T>
vec4<T>& vec4<T>::operator-=(const vec4& v) 
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}

template<typename T>
vec4<T>& vec4<T>::operator*=(const vec4& v) 
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
}

template<typename T>
vec4<T>& vec4<T>::operator/=(const vec4& v) 
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
    return *this;
}

template<typename T>
vec4<T>& vec4<T>::operator*=(T t) 
{
    x *= t;
    y *= t;
    z *= t;
    w *= t;
    return *this;
}

template<typename T>
vec4<T>& vec4<T>::operator/=(T t) 
{
    return *this *= 1 / t;
}

template<typename T>
vec4<T>& vec4<T>::operator+=(T t) 
{
    x += t;
    y += t;
    z += t;
    w += t;
    return *this;
}

template<typename T>
vec4<T>& vec4<T>::operator-=(T t) 
{
    x -= t;
    y -= t;
    z -= t;
    w -= t;
    return *this;
}

template<typename T>
float vec4<T>::length() const 
{
    return std::sqrt(length_squared());
}

template<typename T>
T vec4<T>::length_squared() const 
{
    return x * x + y * y + z * z + w * w;
}

template<typename T>
vec4<T> vec4<T>::normalise() const 
{
    float l = length();
    return vec4(x / l, y / l, z / l, w / l);
}

template<typename T>
void vec4<T>::normalise() 
{
    float l = length();
    x /= l;
    y /= l;
    z /= l;
    w /= l;
}

// vec3 member functions
template<typename T>
vec3<T>::vec3() : x(0), y(0), z(0) {}

template<typename T>
vec3<T>::vec3(T a) : x(a), y(a), z(a) {}

template<typename T>
vec3<T>::vec3(T e0, T e1, T e2) : x(e0), y(e1), z(e2) {}

template<typename T>
vec3<T> vec3<T>::operator-() const 
{
    return vec3(-x, -y, -z);
}

template<typename T>
void vec3<T>::fromString(const std::string& s, char comma) 
{
    ExtractVectorfromString(*this, s, comma);
}

template<typename T>
vec3<T>& vec3<T>::operator+=(const vec3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

template<typename T>
vec3<T>& vec3<T>::operator-=(const vec3& v) 
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

template<typename T>
vec3<T>& vec3<T>::operator*=(const vec3& v) 
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

template<typename T>
vec3<T>& vec3<T>::operator/=(const vec3& v) 
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

template<typename T>
vec3<T>& vec3<T>::operator*=(T t) 
{
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

template<typename T>
vec3<T>& vec3<T>::operator/=(T t) 
{
    return *this *= 1 / t;
}

template<typename T>
vec3<T>& vec3<T>::operator+=(T t) 
{
    x += t;
    y += t;
    z += t;
    return *this;
}

template<typename T>
vec3<T>& vec3<T>::operator-=(T t) 
{
    x -= t;
    y -= t;
    z -= t;
    return *this;
}

template<typename T>
float vec3<T>::length() const 
{
    return std::sqrt(length_squared());
}

template<typename T>
T vec3<T>::length_squared() const 
{
    return x * x + y * y + z * z;
}

template<typename T>
vec3<T> vec3<T>::normalise() const 
{
    float l = length();
    return vec3(x / l, y / l, z / l);
}

template<typename T>
void vec3<T>::normalise() 
{
    float l = length();
    x /= l;
    y /= l;
    z /= l;
}

template<typename T>
void vec3<T>::RotateInX(float angle) 
{
    T posY = y;
    T posz = z;
    y = posY * cos(angle) - posz * sin(angle);
    z = posY * sin(angle) + posz * cos(angle);
}

template<typename T>
void vec3<T>::RotateInY(float angle) 
{
    T posX = x;
    T posZ = z;
    x = posX * cos(angle) - posZ * sin(angle);
    z = posX * sin(angle) + posZ * cos(angle);
}

template<typename T>
void vec3<T>::RotateInZ(float angle) 
{
    T posX = x;
    T posY = y;
    x = posX * cos(angle) - posY * sin(angle);
    y = posX * sin(angle) + posY * cos(angle);
}

// vec2 member functions
template<typename T>
vec2<T>::vec2() : x(0), y(0) {}

template<typename T>
vec2<T>::vec2(T a) : x(a), y(a) {}

template<typename T>
vec2<T>::vec2(T a, T b) : x(a), y(b) {}

template<typename T>
void vec2<T>::fromString(const std::string& s, char comma) 
{
    ExtractVectorfromString(*this, s, comma);
}

template<typename T>
vec2<T>& vec2<T>::operator+=(T f) 
{
    x += f;
    y += f;
    return *this;
}

template<typename T>
vec2<T>& vec2<T>::operator-=(T f) 
{
    x -= f;
    y -= f;
    return *this;
}

template<typename T>
vec2<T>& vec2<T>::operator*=(T f) 
{
    x *= f;
    y *= f;
    return *this;
}

template<typename T>
vec2<T>& vec2<T>::operator/=(T f) 
{
    x /= f;
    y /= f;
    return *this;
}

template<typename T>
vec2<T>& vec2<T>::operator+=(const vec2& v) 
{
    x += v.x;
    y += v.y;
    return *this;
}

template<typename T>
vec2<T>& vec2<T>::operator-=(const vec2& v) 
{
    x -= v.x;
    y -= v.y;
    return *this;
}

template<typename T>
vec2<T>& vec2<T>::operator*=(const vec2& v) 
{
    x *= v.x;
    y *= v.y;
    return *this;
}

template<typename T>
vec2<T>& vec2<T>::operator/=(const vec2& v) 
{
    x /= v.x;
    y /= v.y;
    return *this;
}

template<typename T>
float vec2<T>::length() const 
{
    return std::sqrt(length_squared());
}

template<typename T>
T vec2<T>::length_squared() const 
{
    return x * x + y * y;
}

template<typename T>
vec2<T> vec2<T>::normalise() const 
{
    float l = length();
    return vec2(x / l, y / l);
}

template<typename T>
void vec2<T>::normalise() 
{
    float l = length();
    x /= l;
    y /= l;
}

template<typename T>
T vec2<T>::rad() const 
{
    return std::atan2(y, x);
}
