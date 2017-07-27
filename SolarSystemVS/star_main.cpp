#include "stdafx.h"
#include "star_main.hpp"
#include <cmath>

#define PI 3.1415926535

Star::Star(GLfloat radius, GLfloat distance,
		GLfloat speed, GLfloat selfSpeed,
		Star* parentStar)
{
	this->radius = radius;
	this->distance = distance;
	this->selfSpeed = selfSpeed;
	this->alphaSelf = this->alpha = 0;
	this->parentStar = parentStar;

	for (int i = 0; i < 4; i++)
	{
		this->rgbaColor[i] = 1.f;
	}

	if (speed > 0)
	{
		this->speed = 360.0f/speed;
	}
	else
	{
		this->speed = 0.f;
	}
}


/*glMattrix()这个函数接受三个不同的模式：GL_PROJECTION 投影, GL_MODELVIEW 模型视图, GL_TEXTURE 纹理。

GL_PROJECTION 会向 OpenGL 声明将进行投影操作，会把物体头银到一个平面上。开启这个模式后要使用glLoadIdentity()把矩阵设置为单位矩阵，而后的操作如可以通过 gluPerspective 设置视景（在下面介绍完 OpenGL 中视角的概念后我们再详细说明这个函数的功能）。

GL_MODELVIEW 会向 OpenGL 声明接下来的语句将描绘一个以模型为基础的操作，比如设置摄像机视角，开启后同样需要设置 OpenGL 的矩阵模式为单位矩阵。

GL_TEXTURE 则是进行纹理相关的操作，我们暂时用不到。

如果对矩阵的概念不熟悉，可以直接将 glMatrixMode 理解为针对 OpenGL 申明接下来要做的事情。我们在绘制、旋转对象之前，一定要通过 glPushMatrix 保存当前的矩阵环境，否则会出现莫名其妙的绘制错误。*/

/*glEnable(GLenum cap): 这个函数用于激活 OpenGL 中提供的各种功能，传入的参数 cap 是OpenGL 内部的宏，提供诸如光源、雾化、抖动等效果；

glPushMatrix() 和 glPopMatrix(): 将当前矩阵保存到堆栈栈顶（保存当前矩阵）；

glRotatef(alpha, x, y, z): 表示当前图形沿 (x,y,z) 逆时针旋转 alpha 度;

glTranslatef(distance, x, y): 表示当前图形沿 (x,y) 方向平移 distance 距离;

glutSolidSphere(GLdouble radius , GLint slices , GLint stacks): 绘制球体， radius 为半径，slices 为经线条数, stacks 为纬线条数;

glBegin() 和 glEnd()：当我们要进行图形绘制时，需要在开始回之前和绘制完成后调用这两个函数，glBegin()指定了绘制图形的类型，例如 GL_POINTS 表示绘制点、 GL_LINES 表示绘制依次画出的点及他们之间的连线、GL_TRIANGLES 则是在每绘制的三个点中完成一个三角形、GL_POLYGON 则是绘制一个从第一个点到第 n 个点的多边形，等等。例如当我们需要绘制一个圆时可以边很多的多边形来模拟：*/
void Star::drawStar()
{
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);

	int drawLines = radius * 500;

	// 保存 OpenGL 当前的矩阵环境
	glPushMatrix();
	{
		// 公转

        // 如果是行星，且距离不为0，那么 且向原点平移一个半径
        // 这部分用于处理卫星

		if (parentStar != 0 && parentStar->distance > 0)
		{
			//将绘制的图形沿 z 轴旋转 alpha
			glRotatef(parentStar->alpha, 0, 0, 1);
			// x 轴方向上平移 distance , y,z 方向不变
			glTranslatef(parentStar->distance, 0, 0);
		}
		glBegin(GL_LINES);
		for (int i = 0; i < drawLines; i++)
		{
			glVertex2f(distance * cos(2 * PI * i / drawLines),
						distance * sin(2 * PI * i / drawLines));
		}
		glEnd();
		glRotatef(alpha, 0, 0, 1);
		glTranslatef(distance, 0, 0);

		glRotatef(alphaSelf, 0, 0, 1);

		glColor3f(rgbaColor[0], rgbaColor[1], rgbaColor[2]);
		glutSolidSphere(radius, 40, 32);
	}
	glPopMatrix();
}

void Star::update(long timeSpan)
{
	alpha += timeSpan * speed; // 更新角度
	alphaSelf += selfSpeed; // 更新自转角度
}

Planet::Planet(GLfloat radius, GLfloat distance,
		GLfloat speed, GLfloat selfSpeed,
		Star* parentStar, GLfloat rgbColor[3]):
Star(radius, distance, speed, selfSpeed, parentStar)
{
	rgbaColor[0] = rgbColor[0];
    rgbaColor[1] = rgbColor[1];
    rgbaColor[2] = rgbColor[2];
    rgbaColor[3] = 1.0f;
}

void Planet::drawPlanet()
{
	GLfloat mat_ambient[]  = {0.0f, 0.0f, 0.5f, 1.0f};
    GLfloat mat_diffuse[]  = {0.0f, 0.0f, 0.5f, 1.0f};
    GLfloat mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
    GLfloat mat_emission[] = {rgbaColor[0], rgbaColor[1], rgbaColor[2], rgbaColor[3]};
    GLfloat mat_shininess  = 90.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,  mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, mat_shininess);
}

LightPlanet::LightPlanet(GLfloat radius, GLfloat distance,
		GLfloat speed, GLfloat selfSpeed,
		Star* parentStar, GLfloat rgbColor[3]):
Planet(radius, distance, speed, selfSpeed, parentStar, rgbColor)
{
	//TODO
}

void LightPlanet::drawLightPlanet()
{
	/*这里的位置由四个值来表示，(x,y,z,w) 其中当 w为0时，表示该光源位于无限远，而 x,y,z 便指定了这个无限远光源的方向；
	当 w 不为0时，表示 位置性光源，其位置为 (x/w, y/w, z/w) 。*/
	GLfloat light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
	/*环境光*/
    GLfloat light_ambient[]  = {0.0f, 0.0f, 0.0f, 1.0f};
	/*漫反射光*/
    GLfloat light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
	/*镜面反射光*/
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}