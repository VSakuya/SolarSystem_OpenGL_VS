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

	// glutDisplayFunc 的函数原型为 glutDisplayFunc(void (*func)(void))
	// 这是一个回调函数，每当 GLUT 确定一个窗口的内容需要更新显示的时候,
	// glutDisplayFunc 注册的回调函数就会被执行.
	//
	// glutIdleFunc(void (*func)(void)) 将指定一个函数，用于处理当事件循环
	// 处于空闲的时候，就执行这个函数。这个回调函数接受一个函数指针作为它的唯一参数
	//
	// glutKeyboardFunc(void (*func)(unsigned char key, int x, int y))
	// 会将键盘上的键与一个函数关联，当这个键被按下或者释放时，函数就会调用
	//
	// 因此下面的三行实际上是在向 GLUT 注册关键的三个回调函数
	glutDisplayFunc(onDisplay);
	glutIdleFunc(onUpdate);
	glutKeyboardFunc(onKeyboard);
	glutMainLoop();
	return 0;

}