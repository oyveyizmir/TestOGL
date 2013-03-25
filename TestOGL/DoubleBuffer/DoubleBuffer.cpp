// DoubleBuffer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using std::cout;

static GLfloat spin = 0.0;
int display_count = 0;

int start_time; //in ms
bool is_rotating = false;

int get_time_ms()
{
	SYSTEMTIME time;
	GetSystemTime(&time);
	int time_ms = (((time.wHour * 60) + time.wMinute) * 60 + time.wSecond) * 1000 + time.wMilliseconds;
	return time_ms;
}

void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 1.0);
	glColor3f(0.5, 1.0, 1.0);
	glRectf(-25.0, -25.0, 25.0, 25.0);
	glPopMatrix();
	glutSwapBuffers();

	if (is_rotating)
	{
		display_count++;

		if (display_count % 100 == 0)
		{
			int time = get_time_ms();
			if (time - start_time >= 1000)
			{
				double fps = (double)1000 * display_count / (time - start_time);
				std::cout << fps << std::endl;
				display_count = 0;
				start_time = time;
			}
		}
	}
}

void spinDisplay(void)
{
	spin = spin + 0.01f;
	if (spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y) 
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			is_rotating = true;
			display_count = 0;
			start_time = get_time_ms();
			glutIdleFunc(spinDisplay);
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)
		{
			is_rotating = false;
			glutIdleFunc(NULL);
		}
		break;
	default:
		break;
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (250, 250); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape); 
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}

