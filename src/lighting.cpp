#include "lighting.h"

#include <glm/glm.hpp>

/*glm::vec3 lighting(glm::vec3 normal,Material* mtl,glm::vec3& ambient_c,glm::vec3& diffuse_c,glm::vec3& specular_c)     //input 3 triangle vertex
{
	//ambient
	float ambient_light_intensity =  1;
	glm::vec3 ambient_reflection_coefficient = mtl->Ka;
	glm::vec3 ambient = ambient_light_intensity * ambient_reflection_coefficient;
	ambient.x *= ambient_c.x;
	ambient.y *= ambient_c.y;
	ambient.z *= ambient_c.z;

	//diffuse
	float point_light_attenuation = 1;
	float point_light_intensity = 1;
	glm::vec3 diffuse_reflection_coefficient = mtl->Kd;

	normal = glm::normalize(normal);
	glm::vec3 light_direction(1.f,1.f,1.f);
	light_direction = glm::normalize(light_direction);
	glm::vec3 diffuse = point_light_attenuation * point_light_intensity * diffuse_reflection_coefficient * glm::dot(normal,light_direction);
	diffuse.x *= diffuse_c.x;
	diffuse.y *= diffuse_c.y;
	diffuse.z *= diffuse_c.z;

	//specular
	glm::vec3 specular_reflection_coefficient = mtl->Ks;
	float specular_reflection_exponent = mtl->Ns;
	glm::vec3 specular(0.f,0.f,0.f);	//sum ()

	//glm::vec3 intensity = ambient + diffuse + specular;
	glm::vec3 c;
	c.x = ambient.x + diffuse.x + specular.x;
	c.y = ambient.y + diffuse.y + specular.y;
	c.z = ambient.z + diffuse.z + specular.z;
	return c;
}*/

vec3 lighting(glm::vec3 normal)     //input 3 triangle vertex
{
	//ambient
	float ambient_light_intensity =  1;
	float ambient_reflection_coefficient = 0.2;
	float ambient = ambient_light_intensity * ambient_reflection_coefficient;
	//diffuse
	float point_light_attenuation = 1;
	float point_light_intensity = 1;
	float diffuse_reflection_coefficient = 0.8;

	normal = glm::normalize(normal);
	glm::vec3 light_direction(1.f,1.f,1.f);
	light_direction = glm::normalize(light_direction);
	float diffuse = point_light_attenuation * point_light_intensity * diffuse_reflection_coefficient * glm::dot(normal,light_direction);
	//specular
	float specular_reflection_coefficient = 0.3;
	float specular_reflection_exponent = 3;

	float specular = 0; //sum ()
	float intensity = ambient + diffuse + specular;
	vec3 c = color;
	c.x *= intensity;
	c.y *= intensity;
	c.z *= intensity;
	return c;
}