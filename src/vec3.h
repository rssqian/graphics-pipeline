#ifndef _VEC3_H_
#define _VEC3_H_

class vec3 {
public:
	vec3(): x(0), y(0), z(0) {}
	vec3(float v): x(v), y(v), z(v) {}
	vec3(float x0, float y0, float z0): x(x0), y(y0), z(z0) {}
	~vec3() {}
	float x;
	float y;
	float z;
};



#endif