#ifndef solarsystem_hpp
#define solarsystem_hpp

#include <GL/glut.h>

#define TIMEPAST 1
#define SELFROTATE 3

#define STARS_NUM 10

enum STARS{
	Sun,
	Mercury,
	Venus,
	Earth,
	Moon,
	Mars,
	Jupiter,
	Saturn,
	Uranus,
	Neptune
};

class SolarSystem 
{
public:
	SolarSystem();
	~SolarSystem();

	void onDisplay();
	void onUpdate(int deltaMs);
	void onKeyboard(unsigned char key, int x, int y);

private:
	class Star *stars[STARS_NUM];

	//define view parameters
	GLdouble viewX, viewY, viewZ;
	GLdouble centerX, centerY, centerZ;
	GLdouble upX, upY, upZ;

};

#endif