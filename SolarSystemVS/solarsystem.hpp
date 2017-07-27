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

	void OnDisplay();
	void OnUpdate(GLfloat DeltaTime);
	void OnKeyboard(unsigned char key, int x, int y);

	void MoveCameraRight(GLfloat Axis);
	void MoveCameraUp(GLfloat Axis);
	void RotateCamera(GLfloat DeltaAngle);

private:
	class Star *Stars[STARS_NUM];

	//define view parameters
	GLdouble viewX, viewY, viewZ;
	GLdouble centerX, centerY, centerZ;
	GLdouble upX, upY, upZ;

};

#endif