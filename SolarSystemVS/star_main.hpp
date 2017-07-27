#ifndef star_main_hpp
#define star_main_hpp

#include <GL/glut.h>

class Star
{
public:
	//Star radius
	GLfloat radius;
	//Orbital period speed, and self period speed
	GLfloat speed;
	GLfloat selfSpeed;
	//Orbital period radius
	GLfloat distance;
	//Star color
	GLfloat rgbaColor[4];

	//Pointer of parent star
	Star* parentStar;

	//Constructor function 
	//Offer Necessary values to construct a planet
	Star(GLfloat radius, GLfloat distance,
		GLfloat speed, GLfloat selfSpeed,
		Star* parentStar);

	//Draw movement and rotation of a star
	void drawStar();

	//Set a default implementation of a star
	virtual void draw(){ drawStar(); }

	//parameter 'timeSpan' is the time between every screen refresh
	virtual void update(long timeSpan);

protected:
	GLfloat alphaSelf, alpha;
};

class Planet : public Star
{
public:
	//Constructor
	Planet(GLfloat radius, GLfloat distance,
		GLfloat speed, GLfloat selfSpeed,
		Star* parentStar, GLfloat rgbColot[3]);

	void drawPlanet();

	virtual void draw() {drawPlanet(); drawStar(); }
};

class LightPlanet : public Planet 
{
public: 
	LightPlanet(GLfloat radius, GLfloat distance,
		GLfloat speed, GLfloat selfSpeed,
		Star* parentStar, GLfloat rgbColot[3]);

	void drawLightPlanet();
	virtual void draw() {drawLightPlanet(); drawPlanet(); drawStar(); }
};

#endif