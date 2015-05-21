#include "lighting.h"

vec3 lighting(vec3 normal)     //input 3 triangle vertex
{
	//ambient
	float ambient_light_intensity =  1;
	float ambient_reflection_coefficient = 0.2;
	float ambient = ambient_light_intensity * ambient_reflection_coefficient;
	//diffuse
	float point_light_attenuation = 1;
	float point_light_intensity = 1;
	float diffuse_reflection_coefficient = 0.8;

	normalize(normal);
	vec3 light_direction(1.f,1.f,-2.f);
	normalize(light_direction);
	float diffuse = point_light_attenuation * point_light_intensity * diffuse_reflection_coefficient * dotProduct(normal,light_direction);
	//specular
	float specular = 0; //sum ()
	float intensity = ambient + diffuse + specular;
	vec3 c = color;
	c.x *= intensity;
	c.y *= intensity;
	c.z *= intensity;
	return c;
}
