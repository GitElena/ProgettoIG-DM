//============================================================================
// Name        : MakkaPakka.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <GL/glut.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace std;


GLfloat poscamx=0.0,poscamy=0.0,posfx=1.0,posfy=0,velocita=0.1,xmax=0,ymax=0,xmin=0,ymin=0;

void init(void) {
	glClearColor(1.0, 1.0, 0, 0);

	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

}

const int dim = 20;
GLfloat delta_alpha = 5,alpha = 0,pgreco=3.14159 ;

struct Vertice {
	GLfloat x, y;
};

Vertice vertici[dim][dim]={0.0};

GLfloat l = 1.3;


void Inizializza() {
	GLfloat y = -10.0, x = -10.0;

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			vertici[i][j].x += x;

			vertici[i][j].y += y;


			x = vertici[i][j].x + l;
		}
		y = vertici[i][0].y + l;
		x = -10.0;
	}

	xmax=vertici[dim-1][dim-1].x;
	ymax=vertici[dim-1][dim-1].y;
	xmin=vertici[0][0].x;
	ymin=vertici[0][0].y;

}

void disegnaPiano(string tipo)
{
	GLfloat z;
	((tipo=="tetto")?z=3.0:z=0.0);
	glBegin(GL_QUADS);
	glVertex3f(vertici[0][0].x, vertici[0][0].y, z);
	glVertex3f(vertici[0][dim-1].x, vertici[0][dim-1].y, z);
	glVertex3f(vertici[dim-1][dim-1].x, vertici[dim-1][dim-1].y,z);
	glVertex3f(vertici[dim-1][0].x, vertici[dim-1][0].y,z);
	glEnd();
}



int quadrante()
{
		if(poscamx>0 && poscamy>0)
			return 1;
		else if(poscamx>0 && poscamy<0)
				return 2;
		else if(poscamx<0 && poscamy<0)
				return 3;
		else if (poscamx<0 && poscamy>0)
				return 4;
		return 0;
	}

void incrementoQ1(GLfloat proxX,GLfloat proxY)
{	cout<<"quadrante 1"<<endl;
	if(proxX>xmax-0.7)
	{	cout<<"la x è maggiore"<<endl;
		if(proxY<=ymax-0.7)
			poscamy=proxY;
		else

			 if(((proxY-poscamy)>0 || (proxY-poscamy)<0) && (poscamy+(proxY-poscamy)<=ymax))
			 {	cout<<"entra nell'if della differenza"<<endl;
				poscamy=poscamy+(proxY-poscamy);

			 }

	}
	else
		if(proxY>ymax-0.7)
		{cout<<"la y è maggiore"<<endl;
			if(proxX<=xmax-0.7)
			{
				poscamx=proxX;
			}
			else
				if(((proxX-poscamx)< 0 || (proxX-poscamx)> 0) && (poscamx+(proxX-poscamx)<=xmax) )
				{cout<<"entra nell'if della differenza"<<endl;
					poscamx=poscamx+(proxX-poscamx);
				}
		}

}

void incrementoQ2(GLfloat proxX,GLfloat proxY)
{	cout<<"quadrante 2"<<endl;
	if(proxX>xmax-0.7)
	{cout<<"la x è maggiore"<<endl;
		if(proxY>=ymin+0.7)
			poscamy=proxY;
		else
			 if(((proxY-poscamy)<0 || (proxY-poscamy)>0) && (poscamy+(proxY-poscamy)>=ymin))
			 {
				 cout<<"entra nell'if della differenza"<<endl;
				poscamy=poscamy+(proxY-poscamy);
			 }
	}
	else
		if(proxY<ymin+0.7)
		{	cout<<"la y è minore"<<endl;
			if(proxX<=xmax-0.7)
			{
				poscamx=proxX;
			}
			else
				if(((proxX-poscamx)<0 ||(proxX-poscamx)>0)&& poscamx+(proxX-poscamx)<=xmax)
				{
					cout<<"entra nell'if della differenza"<<endl;
					poscamx=poscamx+(proxX-poscamx);
				}
		}

}


void incrementoQ3(GLfloat proxX,GLfloat proxY)
{
	cout<<"terzo quadrante"<<endl;
	if(proxX<xmin+0.7)
	{cout<<"è più piccola la x"<<endl;
		if(proxY >= ymin+0.7)
			poscamy=proxY;
		else
			 if(((proxY-poscamy)<0 || (proxY-poscamy)>0)&& poscamy+(proxY-poscamy)>=ymin)
			 {cout<<"entra nell'if della differenza"<<endl;
				poscamy=poscamy+(proxY-poscamy);
			 }
	}
	else
		if(proxY<ymin+0.7)
		{cout<<"è più piccola la y"<<endl;
			if(proxX>=xmin+0.7)
			{
				poscamx=proxX;
			}
			else
				if(((proxX-poscamx)<0 || (proxX-poscamx)>0) && poscamx+(proxX-poscamx)>=xmin)
				{
					cout<<"entra nell'if della differenza"<<endl;
					poscamx=poscamx+(proxX-poscamx);
				}
		}

}

void incrementoQ4(GLfloat proxX,GLfloat proxY)
{cout<<"quarto quadrante"<<endl;
	if(proxX<xmin+0.7)
	{ cout<<"è più piccola la x"<<endl;
		if(proxY<=ymax-0.7)
			poscamy=proxY;
		else
			 if(((proxY-poscamy)<0 || (proxY-poscamy)>0) && poscamy+(proxY-poscamy)<=ymax)
			 {
				 cout<<"entra nell'if della differenza"<<endl;
				poscamy=poscamy+(proxY-poscamy);
			 }
	}
	else
		if(proxY>ymax-0.7)
		{cout<<"è più grande la y"<<endl;
			if(proxX>=xmin+0.7)
			{
				poscamx=proxX;
			}
			else
				if(((proxX-poscamx)<0 || (proxX-poscamx)>0)&&poscamx+(proxX-poscamx)>=xmin)
				{
					cout<<"entra nell'if della differenza"<<endl;
					poscamx=poscamx+(proxX-poscamx);
				}
		}

}

void disegnaParete(int a,int b,string parete)
{
	int c;
	((parete=="d_s")?c=b:c=a);
	glBegin(GL_QUADS);
	glVertex3f(vertici[a][b].x,vertici[a][b].y,0.0);
	glVertex3f(vertici[a][b].x,vertici[a][b].y,3.0);
	glVertex3f(vertici[c][c].x,vertici[c][c].y,3.0);
	glVertex3f(vertici[c][c].x,vertici[c][c].y,0.0);


	glEnd();
}
void disegnaStanza() {


	glColor3f(1, 0, 0);
	disegnaPiano("tetto");
	disegnaPiano("pavimento");
	glColor3f(1, 1, 0);
	disegnaParete(0,dim-1,"d_s");//d_s indica parete destra e sinistra
	glColor3f(1, 1, 1);
	disegnaParete(dim-1,0,"d_s");
	glColor3f(0, 1, 1);
	disegnaParete(dim-1,0,"s_i");
	glColor3f(1, 0, 1);
	disegnaParete(0,dim-1,"s_i");

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	gluLookAt(poscamx, poscamy, 1.0,
		      posfx,   posfy,   1.0,
		      0.0,       0.0,   1.0);

	disegnaStanza();


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
		GLdouble proxX;
		proxX=poscamx + velocita * cos((alpha * pgreco) / 180);
		GLdouble proxY;
		proxY=poscamy + velocita * sin((alpha * pgreco) / 180);
		if (((proxX > (vertici[0][0].x +0.7 )) && (proxY > vertici[0][0].y +0.7))
			&& ((proxY < (vertici[dim - 1][dim - 1].y-0.7)) && (proxX < (vertici[dim - 1][dim - 1].x -0.7))))
						{
							poscamx = proxX;
							poscamy = proxY;
						}
		else
			{
				if(quadrante()==1)
				{
					incrementoQ1(proxX,proxY);
				}
				else if(quadrante()==2)
					{
						incrementoQ2(proxX,proxY);
					}

				else if(quadrante()==3)
						{
							incrementoQ3(proxX,proxY);
						}

				else if(quadrante()==4)
							{
								incrementoQ4(proxX,proxY);
							}
			}

				posfx = poscamx + cos((alpha * pgreco) / 180);
				posfy = poscamy + sin((alpha * pgreco) / 180);

				glutPostRedisplay();

		/*if( (( ( poscamx+0.1*cos((alpha*pgreco)/180) ) >(vertici[0][0].x-0.5) ) && ((poscamy+0.1*sin((alpha*pgreco)/180)) >vertici[0][0].y-0.5) ) &&
				(( ( poscamy+0.1*sin((alpha*pgreco)/180) ) < (vertici[dim-1][dim-1].y-0.5)) && ( ( poscamx+0.1*cos((alpha*pgreco)/180) )<(vertici[dim-1][dim-1].x-0.5)))    )
		{poscamx=poscamx+0.1*cos((alpha*pgreco)/180);
		poscamy=poscamy+0.1*sin((alpha*pgreco)/180);
		posfx=poscamx+cos((alpha*pgreco)/180);
		posfy=poscamy+sin((alpha*pgreco)/180);}
		else if( poscamx+((poscamx-0.1*cos(alpha*pgreco)/180)-poscamx)*cos((alpha*pgreco)/180)>0 ){
			poscamx=poscamx+((poscamx-0.1*cos(alpha*pgreco)/180)-poscamx)*cos((alpha*pgreco)/180);
			poscamy=poscamy+((poscamy-0.1*sin((alpha*pgreco)/180))-poscamy)*sin((alpha*pgreco)/180);

			posfx=poscamx+cos((alpha*pgreco)/180);
			posfy=poscamy+sin((alpha*pgreco)/180);

		}


		glutPostRedisplay();*/
		break;
	case's':
		if( (( ( poscamx-0.5*cos((alpha*pgreco)/180) ) >-9.5 ) && ((poscamy-0.5*sin((alpha*pgreco)/180)) >-9.5) ) &&
						(( ( poscamy-0.5*sin((alpha*pgreco)/180) ) < 14 ) && ( ( poscamx-0.5*cos((alpha*pgreco)/180) )<14))    )
		{poscamx=poscamx-0.5*cos((alpha*pgreco)/180);
				poscamy=poscamy-0.5*sin((alpha*pgreco)/180);
				posfx=poscamx+cos((alpha*pgreco)/180);
				posfy=poscamy+sin((alpha*pgreco)/180);}
		glutPostRedisplay();
		break;


	default:
		break;

	}
	cout<<"posizione x camera "<<poscamx<<endl;
	cout<<"posizione y camera "<<poscamy<<endl;
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
	glutInitWindowSize(1350, 710);
	glutCreateWindow("LA PERFEZIONE FATTA PIANO");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	/*cout<<"x 0 0 e y 0 0 "<<vertici[0][0].x<<" "<<vertici[0][0].y<<endl;
	cout<<"x dim dim y "<<vertici[dim-1][dim-1].x<<" "<<vertici[dim-1][dim-1].y<<endl;
	cout<<"x 0 dim y "<<vertici[0][dim-1].x<<" "<<vertici[0][dim-1].y<<endl;
	cout<<"x dim 0 y "<<vertici[dim-1][0].x<<" "<<vertici[dim-1][0].y<<endl;*/
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}

