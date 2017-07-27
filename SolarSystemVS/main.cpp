// SolarSystemVS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL/glut.h>
#include "solarsystem.hpp"
#include <windows.h> 
#include <iostream>

//#pragma comment(linker,"/subsystem:\"Windows\" /ENTRY:\"mainCRTStartup\"")

// set window frame needed defines
#define WIDTH 800
#define HEIGHT 600

SolarSystem solarsystem;

int timeLastFrame = 0;

//register for glut callback
void onDisplay(void)
{
	solarsystem.onDisplay();
}
void onUpdate(void)
{	
	/*show fps*/
	int time = 0;
	time = glutGet(GLUT_ELAPSED_TIME);
	int msThisFrame = time - timeLastFrame;
	std::cout << "Frame is: " << 1000 / msThisFrame << std::endl;
	timeLastFrame = time;
	solarsystem.onUpdate(msThisFrame);
}
void onKeyboard(unsigned char key, int x, int y)
{
	solarsystem.onKeyboard(key, x, y);
}

int main(int argc, char* argv[]) {


	int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	//Initialize glut
	glutInit(&argc, argv);

	//This function specified that use RGBA color mode or color-index mode
	//In addition to specified that use double buffer or single buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	//Set the initial window position on screen(?)
	glutInitWindowPosition((screenWidth - WIDTH)/2, (screenHeight - HEIGHT) / 2);

	//Set the initial window size
	glutInitWindowSize(WIDTH, HEIGHT);

	//Create a window and give it a title
	glutCreateWindow("Solar system");

	// glutDisplayFunc �ĺ���ԭ��Ϊ glutDisplayFunc(void (*func)(void))
	// ����һ���ص�������ÿ�� GLUT ȷ��һ�����ڵ�������Ҫ������ʾ��ʱ��,
	// glutDisplayFunc ע��Ļص������ͻᱻִ��.
	//
	// glutIdleFunc(void (*func)(void)) ��ָ��һ�����������ڴ����¼�ѭ��
	// ���ڿ��е�ʱ�򣬾�ִ���������������ص���������һ������ָ����Ϊ����Ψһ����
	//
	// glutKeyboardFunc(void (*func)(unsigned char key, int x, int y))
	// �Ὣ�����ϵļ���һ������������������������»����ͷ�ʱ�������ͻ����
	//
	// ������������ʵ���������� GLUT ע��ؼ��������ص�����
	glutDisplayFunc(onDisplay);
	glutIdleFunc(onUpdate);
	glutKeyboardFunc(onKeyboard);
	glutMainLoop();
	return 0;

}