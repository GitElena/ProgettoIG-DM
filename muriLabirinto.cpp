
#include <GL/glut.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string>
using namespace std;

GLfloat poscamx = 0.0, poscamy = 0.0, posfx = 1.0, posfy = 0, poscamz=1.0,posfz=1.0;
bool alto=false;

void init(void) {
	glClearColor(1.0, 1.0, 0, 0);

	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

}

const int dim = 20;
GLfloat delta_alpha = 3, alpha = 0, pgreco = 3.14159;
int labirinto[dim][dim]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						  {0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						  {0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0},
						  {0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
						  {0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0},
						  {0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
					      {0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
						  {0,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,0,0,0,0},
						  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
						  {0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
					      {0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
						  {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
						  {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
						  {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
						  {0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
						  {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						  {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						  {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};


struct Vertice {
	GLfloat x, y;
	bool muro;
};

Vertice vertici[dim][dim] = { 0.0 };

GLfloat l = 1;
int indiceX(float x){
	float diff=(x+10)-(int)(x+10);

	if(diff>0.5)
		return (int)((x+10))+1;
	else
		return (int)((x+10));
}
int indiceY(float y){
	float diff=(y+10)-(int)(y+10);

		if(diff>0.5)
			return (int)((y+10))+1;
		else
			return (int)((y+10));
}


double nextX(){
	return ((poscamx + 0.1 * cos((alpha * pgreco) / 180)));
}
double nextY(){
	return (poscamy + 0.1 * sin((alpha * pgreco) / 180));
}

bool collisioneCuboF(){
	if(labirinto[indiceY(nextY())][indiceY(nextX())]==1)
		return true;
	return false;
}
bool collisioneCuboD(){
	if(labirinto[indiceY(nextY()+l/2)][indiceX(nextX()+l/2)]==1)
		return true;
	return false;
}
bool collisioneCuboS(){
	if(labirinto[indiceY(nextY()+l/2)][indiceX(nextX()-l/2)]==1)
		return true;
	return false;
}


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

	for(int i=0;i<dim;i++){
				for(int j=0;j<dim;j++){
					cout<<vertici[i][j].y<<" "<<vertici[i][j].x<<" "<<i<<" "<<j<<"|";
				}
				cout<<endl;
			}


}

void disegnaPiano(string tipo) {
	GLfloat z;
	((tipo == "tetto") ? z = 5.0 : z = 0.0);
	glBegin(GL_QUADS);
	glVertex3f(vertici[0][0].x, vertici[0][0].y, z);
	glVertex3f(vertici[0][dim - 1].x, vertici[0][dim - 1].y, z);
	glVertex3f(vertici[dim - 1][dim - 1].x, vertici[dim - 1][dim - 1].y, z);
	glVertex3f(vertici[dim - 1][0].x, vertici[dim - 1][0].y, z);
	glEnd();
}

void disegnaParete(int a1, int a2,int b, string parete) {

	if(parete=="v"){
		glBegin(GL_QUADS);
			glVertex3f(vertici[a1][b].x, vertici[a1][b].y, 0.0);
			glVertex3f(vertici[a1][b].x, vertici[a1][b].y, 5.0);
			glVertex3f(vertici[a2][b].x, vertici[a2][b].y, 5.0);
			glVertex3f(vertici[a2][b].x, vertici[a2][b].y, 0.0);

		glEnd();
		for(int i=a1;i<=a2;i++)
			vertici[i][b].muro=true;

		}
	else {
		glBegin(GL_QUADS);
			glVertex3f(vertici[b][a1].x, vertici[b][a1].y, 0.0);
			glVertex3f(vertici[b][a1].x, vertici[b][a1].y, 5.0);
			glVertex3f(vertici[b][a2].x, vertici[b][a2].y, 5.0);
			glVertex3f(vertici[b][a2].x, vertici[b][a2].y, 0.0);

		glEnd();
		for(int i=a1;i<=a2;i++)
					vertici[b][i].muro=true;

	}

}

void disengnaLabirinto()
{
	unsigned int rigaVertice,colonnaVertice1,colonnaVertice2;
	for(unsigned int i=0;i<dim-1;i++)
	{
		for(unsigned int j=1;j<dim;j++)
		{
			rigaVertice=i;
			if(labirinto[i][j]==1)
			{

				colonnaVertice1=j;
				while(labirinto[i][j]==1 && j<dim)
				{

					colonnaVertice2=j;
					j++;
				}
				if (colonnaVertice1==colonnaVertice2)
					colonnaVertice2+=1;

			disegnaParete(colonnaVertice1,colonnaVertice2,rigaVertice,"o");
			disegnaParete(colonnaVertice1,colonnaVertice2,i+1,"o");
			disegnaParete(i,i+1,colonnaVertice1,"v");
			disegnaParete(i,i+1,colonnaVertice2,"v");

			glBegin(GL_QUADS);
				glVertex3f(vertici[i][colonnaVertice1].x, vertici[i][colonnaVertice1].y, 5.0);
				glVertex3f(vertici[i][colonnaVertice2].x, vertici[i][colonnaVertice2].y, 5.0);
				glVertex3f(vertici[i+1][colonnaVertice2].x, vertici[i+1][colonnaVertice2].y, 5.0);
				glVertex3f(vertici[i+1][colonnaVertice1].x, vertici[i+1][colonnaVertice1].y, 5.0);
			glEnd();



			}
		}

	}
}
void disegnaStanza() {



	glColor3f(1, 0, 0);
	if(!alto)
	disegnaPiano("tetto");
	disegnaPiano("pavimento");
	glColor3f(1, 1, 0);
	disegnaParete(0,dim-1, 0, "v");	//d_s indica parete destra e sinistra
	glColor3f(1, 1, 1);
	disegnaParete(0,dim - 1, dim-1, "v");
	glColor3f(0, 1, 1);
	disegnaParete(0, dim-1 ,0, "o");
	glColor3f(1, 0, 1);
	disegnaParete(0, dim - 1,dim-1, "o");


	glColor3f(0,0,0);
	disengnaLabirinto();

}

bool controlloY(){


	if(vertici[indiceY(poscamy)+1][indiceX(poscamx)].muro && nextY()>poscamy)
			return false;
		if(vertici[indiceY(poscamy)-1][indiceX(poscamy)].muro&&nextY()<poscamy)
			return false;
		return true;}

bool controlloX(){


	if(vertici[indiceY(poscamy)][indiceX(poscamx)+1].muro&&nextX()>poscamx)
		return false;
	if(vertici[indiceY(poscamy)][indiceX(poscamx)-1].muro&&nextX()<poscamx)
		return false;
return true;}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

			gluLookAt(poscamx, poscamy, poscamz, posfx, posfy, posfz, 0.0, 0.0,
					1.0);

disegnaStanza();

	glPopMatrix();

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'd':

		alpha -= delta_alpha;
		posfx = poscamx + cos((alpha * pgreco) / 180);
		posfy = poscamy + sin((alpha * pgreco) / 180);

		glutPostRedisplay();

		break;
	case 'a':
		alpha += delta_alpha;
		posfx = poscamx + cos((alpha * pgreco) / 180);
		posfy = poscamy + sin((alpha * pgreco) / 180);

		glutPostRedisplay();

		break;

	case 'w':
		//cout<<indiceY()<<" "<<indiceX()<<" "<<poscamy<<" "<<poscamx<<endl;

		if (controlloX()&&controlloY()) {
			poscamx=nextX();
			poscamy = nextY();


		} else {
			if(!controlloX()){
				poscamy = nextY();
		}
			else if(!controlloY()){
			poscamx = poscamx + 0.1 * cos((alpha * pgreco) / 180);
		}


		}

		posfx = poscamx + cos((alpha * pgreco) / 180);
		posfy = poscamy + sin((alpha * pgreco) / 180);

		glutPostRedisplay();
		break;
	case 's':
		if ((((poscamx + 0.1 * cos((alpha * pgreco) / 180))
				> (vertici[0][0].x - 0.5))
				&& ((poscamy + 0.1 * sin((alpha * pgreco) / 180))
						> vertici[0][0].y - 0.5))
				&& (((poscamy + 0.1 * sin((alpha * pgreco) / 180))
						< (vertici[dim - 1][dim - 1].y - 0.5))
						&& ((poscamx + 0.1 * cos((alpha * pgreco) / 180))
								< (vertici[dim - 1][dim - 1].x - 0.5)))) {
			poscamx = poscamx - 0.1 * cos((alpha * pgreco) / 180);
			poscamy = poscamy - 0.1 * sin((alpha * pgreco) / 180);


			posfx = poscamx + cos((alpha * pgreco) / 180);
			posfy = poscamy + sin((alpha * pgreco) / 180);
		}
		glutPostRedisplay();
		break;
	case 't':
		alto=true;
		poscamz=22.0;
				posfz=0.0;
				glutPostRedisplay();

		break;

	case 'n':
		alto=false;
		poscamz=2.0;
				posfz=2.0;
				glutPostRedisplay();

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
	glutInitWindowSize(1350, 710);
	glutCreateWindow("la PERFEZIONE FATTA PIANO");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}





