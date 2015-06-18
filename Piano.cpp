#include <GL/glut.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace std;


GLfloat poscamx=0.0,poscamy=0.0,posfx=1.0,posfy=0;

void init(void) {
	glClearColor(0.0, 1.0, 0.5, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	GLfloat ambientLight[]= { 0.3f , 0.3f , 0.3f , 1.0f};
		GLfloat diffuseLight[]= { 0.7f , 0.7f , 0.7f , 1.0f };
		// Enable l i g h t i n g
		glEnable ( GL_LIGHTING ) ;
		// Setup and enable l i g h t 0
		glLightfv( GL_LIGHT0 , GL_AMBIENT , ambientLight);
		glLightfv( GL_LIGHT0 , GL_DIFFUSE , diffuseLight);
		glEnable( GL_LIGHT0 );

		// Enable c o l o r t r a c k i n g
		glEnable(GL_COLOR_MATERIAL) ;
		// Set M a t e r i a l p r o p e r t i e s t o f o l l o w g l C o l o r v a l u e s
		glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE ) ;

		GLfloat lightPos[]={0.0f,0.0f,1.0f};
		glLightfv(GL_LIGHT1,GL_POSITION,lightPos);
		GLfloat specularLight[] = { 0.2f , 0.2f , 0.2f , 1.0f };
		glLightfv( GL_LIGHT1 , GL_SPECULAR, specularLight) ;
		glEnable( GL_LIGHT1 ) ;
		GLfloat specular[]={0.0f,0.0f,1.0f};

		glLightfv( GL_LIGHT2 , GL_SPECULAR, specular) ;
		glLightfv( GL_LIGHT2 , GL_POSITION , lightPos ) ;
		//spotdirectionis(0 ,0 , −1) by d e f a u l t
		GLfloat spotDir[]={0.0,0.0,1.0};
		glLightfv( GL_LIGHT2 , GL_SPOT_DIRECTION , spotDir ) ;
		// Cut o f f angle i s 50 degrees
		glLightf( GL_LIGHT2 , GL_SPOT_CUTOFF, 50.0f ) ;
		// Enable t h i s l i g h t i n p a r t i c u l a r
		glEnable ( GL_LIGHT2 ) ;
}

int dim = 20;
GLfloat delta_alpha = 3,alpha = 0,pgreco=3.14159 ;

struct Vertice {
	GLfloat x, y, z;
} vertici[20][20] = { 0 };

GLfloat l = 1.3;


void Inizializza() {
	GLfloat y = -10.0, x = -10.0, z = 0.0;

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			vertici[i][j].x += x;
			vertici[i][j].y += y;
			vertici[i][j].z = z;
			x = vertici[i][j].x + l;
		}
		y = vertici[i][0].y + l;
		x = -10.0;
	}

	cout<<"v1 "<<vertici[0][0].x<<vertici[0][0].y<<endl;
	cout<<"v2 "<<vertici[0][dim-1].x<<vertici[0][dim-1].y<<endl;
	cout<<"v3 "<<vertici[dim-1][dim-1].x<<vertici[dim-1][dim-1].y<<endl;
	cout<<"v4 "<<vertici[dim-1][0].x<<vertici[dim-1][0].y<<endl;

}

void disegnaPiano() {
	int b = 0;

	glBegin(GL_QUADS);

	for (int i = 0; i < dim - 1; i++) {
		if (i % 2 == 0)
			b = 0;
		else
			b = 1;

		for (int j = 0; j < dim - 1; j++) {
			if (j % 2 == b)
				glColor3f(1, 1, 1);
			else
				glColor3f(0, 0, 0);

			glVertex3f(vertici[i][j].x, vertici[i][j].y, vertici[i][j].z);
			glVertex3f(vertici[i][j + 1].x, vertici[i][j].y, vertici[i][j].z);
			glVertex3f(vertici[i][j + 1].x, vertici[i + 1][j].y,vertici[i + 1][j].z);
			glVertex3f(vertici[i][j].x, vertici[i + 1][j].y,vertici[i + 1][j].z);

		}

		}

	/*glColor3f(1, 1, 1);
	glVertex3f(-10, -10, 0);
	glVertex3f( 10, -10, 0);
	glVertex3f( 10,  10, 0);
	glVertex3f(-10,  10, 0);*/

	glEnd();

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	gluLookAt(poscamx, poscamy, 1.0,
		  posfx,   posfy,   1.0,
		  0,       0,       1.0);

	disegnaPiano();

	glPopMatrix();


	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':

		alpha-=delta_alpha;
		posfx=poscamx+cos((alpha*pgreco)/180);
		posfy=poscamy+sin((alpha*pgreco)/180);



		glutPostRedisplay();

		break;
	case 'a':
		alpha += delta_alpha;
		posfx=poscamx+cos((alpha*pgreco)/180);
		posfy=poscamy+sin((alpha*pgreco)/180);

		glutPostRedisplay();

		break;

	case 'w':
		if( (( ( poscamx+0.5*cos((alpha*pgreco)/180) ) >-10 ) && ((poscamy+0.5*sin((alpha*pgreco)/180)) >-10) ) &&
				(( ( poscamy+0.5*sin((alpha*pgreco)/180) ) < 14.5 ) && ( ( poscamx+0.5*cos((alpha*pgreco)/180) )<14.5))    )
		{poscamx=poscamx+0.5*cos((alpha*pgreco)/180);
		poscamy=poscamy+0.5*sin((alpha*pgreco)/180);
		posfx=poscamx+cos((alpha*pgreco)/180);
		posfy=poscamy+sin((alpha*pgreco)/180);}
		glutPostRedisplay();
		break;
	case's':
		poscamx=poscamx-0.5*cos((alpha*pgreco)/180);
				poscamy=poscamy-0.5*sin((alpha*pgreco)/180);
				posfx=poscamx+cos((alpha*pgreco)/180);
				posfy=poscamy+sin((alpha*pgreco)/180);
		glutPostRedisplay();
		break;


	default:
		break;

	}
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}

int main(int argc, char** argv) {
	Inizializza();
	srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1500, 1500);
	glutCreateWindow("LA PERFEZIONE FATTA PIANO");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}




