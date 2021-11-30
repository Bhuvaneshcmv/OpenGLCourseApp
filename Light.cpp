#include "Light.h"

Light::Light()
{
	colour = glm::vec3(1, 1, 1);
	ambientIntensity = 1;

	direction = glm::vec3(0, -1, 0);
	diffuseIntensity = 1;
}
Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
	GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity)
{
	colour = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;

	direction = glm::vec3(xDir, yDir, zDir);
	diffuseIntensity = dIntensity;
}

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
	GLfloat diffuseIntensityLocation, GLfloat directionLocation)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	
	glUniform3f(directionLocation,direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}



Light:: ~Light()
{

}