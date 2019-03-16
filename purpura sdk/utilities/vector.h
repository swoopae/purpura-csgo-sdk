#pragma once

class vec2_t {
public:
	using vec_t = float;
	vec_t x, y;

	vec2_t(vec_t x = 0, vec_t y = 0) : x(x), y(y) {}
};

using vec2_t = vec2_t;

class vec3_t {
public:
	using vec_t = float;
	vec_t x, y, z;

	vec_t operator[](size_t i) const;
	vec_t& operator[](size_t i);
};

class q_angle : vec3_t {
public:
	vec_t pitch();
	vec_t yaw();
	vec_t roll();
};