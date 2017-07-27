#include "stdafx.h"
#include "solarsystem.hpp"
#include "star_main.hpp"
#include <stdlib.h>
#include <iostream>

#define REST 700
#define REST_Z (REST)
#define REST_Y 1000

void SolarSystem::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.7f, 0.7f, 0.7f, 0.1f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*gluPerspective(GLdouble fov,GLdouble aspect,GLdouble zNear,GLdouble zFar)
	1.第一个参数为视角的大小

	2.第二个参数为实际窗口的横纵比，如图中 aspect=w/h

	3.第三个参数为近平面距离

	4.第四个参数则为远平面距离*/
	GLfloat windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	GLfloat windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(75.0f, windowWidth / windowHeight, 1.0f, 40000000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(viewX, viewY, viewZ, centerX, centerY, centerZ, upX, upY, upZ);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < STARS_NUM; ++i)
	{
		Stars[i]->Draw();
	}
	glutSwapBuffers();
}


#define TIMEPAST 1
void SolarSystem::OnUpdate(GLfloat deltaTime)
{
	for (int i = 0; i < STARS_NUM; ++i)
	{
		Stars[i]->Update(deltaTime);
	}
	this->OnDisplay();
	std::cout << "ViewX: " << viewX << ", ViewY: " << viewY << ", ViewZ: " << viewZ << std::endl;
	std::cout << "CenterX: " << centerX << ", CenterY: " << centerY << ", CenterZ: " << centerZ << std::endl;
	std::cout << "UpX: " << upX << ", UpY: " << upY << ", UpZ: " << upZ << std::endl;
}

#define OFFSET 20
void SolarSystem::OnKeyboard(unsigned char key, int x, int y)
{
	switch(key) 
	{
		case 'w': viewY += OFFSET; break;
		case 's': viewY -= OFFSET; break;
		//case 'S': viewZ -= OFFSET; break;
		case 'a': viewX -= OFFSET; break;
		case 'd': viewX += OFFSET; break;
		case 'q': RotateCamera(1); break;
		case 'e': RotateCamera(-1); break;
		case 'r':
			viewX = 0; viewY = 0; viewZ = 1000;
			centerX = centerY = centerZ = 0;
			upX = upZ = 0; upY = 1;
			break;
		/*Esc to exit*/
		case 27: exit(0); break;
		default: break;	
	}
}

void SolarSystem::MoveCameraRight(GLfloat Axis)
{
	GLfloat CameraDist = sqrt(viewX * viewX + viewY * viewY + viewZ * viewZ);
}

void SolarSystem::MoveCameraUp(GLfloat Axis)
{

}

GLfloat CurrentAngle = 90;
void SolarSystem::RotateCamera(GLfloat DeltaAngle)
{
	CurrentAngle += DeltaAngle;
	upX = cos(CurrentAngle);
	upY = sin(CurrentAngle);
}

#define SUN_RADIUS 48.74
#define MER_RADIUS  7.32
#define VEN_RADIUS 18.15
#define EAR_RADIUS 19.13
#define MOO_RADIUS  6.15
#define MAR_RADIUS 10.19
#define JUP_RADIUS 42.90
#define SAT_RADIUS 36.16
#define URA_RADIUS 25.56
#define NEP_RADIUS 24.78

#define MER_DIS   62.06
#define VEN_DIS  115.56
#define EAR_DIS  168.00
#define MOO_DIS   26.01
#define MAR_DIS  228.00
#define JUP_DIS  333.40
#define SAT_DIS  428.10
#define URA_DIS 848.00
#define NEP_DIS 949.10

#define MER_SPEED   8.70
#define VEN_SPEED  22.50
#define EAR_SPEED  36.50
#define MOO_SPEED   3.00
#define MAR_SPEED  68.70
#define JUP_SPEED 129.84
#define SAT_SPEED 322.56
#define URA_SPEED 306.64
#define NEP_SPEED 601.48

#define SELFROTATE 3

#define SET_VALUE_3(name, value0, value1, value2) \
                   ((name)[0])=(value0), ((name)[1])=(value1), ((name)[2])=(value2)

SolarSystem::SolarSystem()
{
	viewX = 0;
    viewY = 0;
    viewZ = 1000;
    centerX = centerY = centerZ = 0;
    upX = upZ = 0;
    upY = 1;

    GLfloat rgbColor[3] = {1, 0, 0};
    Stars[Sun]     = new LightPlanet(SUN_RADIUS, 0, 0, SELFROTATE, 0, rgbColor);

    SET_VALUE_3(rgbColor, .2, .2, .5);
    Stars[Mercury] = new Planet(MER_RADIUS, MER_DIS, MER_SPEED, SELFROTATE, Stars[Sun], rgbColor);

    SET_VALUE_3(rgbColor, 1, .7, 0);
    Stars[Venus]   = new Planet(VEN_RADIUS, VEN_DIS, VEN_SPEED, SELFROTATE, Stars[Sun], rgbColor);

    SET_VALUE_3(rgbColor, 0, 1, 0);
    Stars[Earth]   = new Planet(EAR_RADIUS, EAR_DIS, EAR_SPEED, SELFROTATE, Stars[Sun], rgbColor);

    SET_VALUE_3(rgbColor, 1, 1, 0);
    Stars[Moon]    = new Planet(MOO_RADIUS, MOO_DIS, MOO_SPEED, SELFROTATE, Stars[Earth], rgbColor);

    SET_VALUE_3(rgbColor, 1, .5, .5);
    Stars[Mars]    = new Planet(MAR_RADIUS, MAR_DIS, MAR_SPEED, SELFROTATE, Stars[Sun], rgbColor);

    SET_VALUE_3(rgbColor, 1, 1, .5);
    Stars[Jupiter] = new Planet(JUP_RADIUS, JUP_DIS, JUP_SPEED, SELFROTATE, Stars[Sun], rgbColor);

    SET_VALUE_3(rgbColor, .5, 1, .5);
    Stars[Saturn]  = new Planet(SAT_RADIUS, SAT_DIS, SAT_SPEED, SELFROTATE, Stars[Sun], rgbColor);

    SET_VALUE_3(rgbColor, .4, .4, .4);
    Stars[Uranus]  = new Planet(URA_RADIUS, URA_DIS, URA_SPEED, SELFROTATE, Stars[Sun], rgbColor);

    SET_VALUE_3(rgbColor, .5, .5, 1);
    Stars[Neptune] = new Planet(NEP_RADIUS, NEP_DIS, NEP_SPEED, SELFROTATE, Stars[Sun], rgbColor);
}

SolarSystem::~SolarSystem()
{
	for (int i = 0; i < STARS_NUM; ++i)
	{
		delete Stars[i];
	}
}