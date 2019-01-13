#pragma once

constexpr float PI = 3.14159265f;

inline float degToRad(float deg) { return deg * PI / 180.0f; }
inline float radToDeg(float rad) { return rad * 180.0f / PI; }