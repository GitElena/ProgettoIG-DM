
#include <GL/glut.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <fstream>
using namespace std;

GLfloat poscamx = 0.0, poscamy = 0.0, posfx = 1.0, posfy = 0, poscamz = 1.0,
		posfz = 1.0, traslazionex = 0.0, traslazioney = 0.0, varianza = -10.0;
bool alto = false, modalitaSemplice = false, prima = false, seconda = false,win=false;
unsigned int labx, laby, posOsservatoreX, posOsservatoreY, posTargetX,
		posTargetY;
void init(void) {
	glClearColor(1.0, 1.0, 0, 0);

	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

}

const int dim = 40;
GLfloat delta_alpha = 3, alpha = 0, pgreco = 3.14159;
int labirinto[dim][dim] = { 3 };

struct Vertice {
	GLfloat x, y;
	bool muro;
};

Vertice verticiGrandi[dim][dim] = { 0.0 }, verticiPiccoli[dim][dim] = { 0.0 };

GLfloat l = 1;

int indiceX(float x) {
	float diff = (x - varianza) - (int) (x - varianza);

	if (diff > 0.5)
		return ((int) ((x - varianza))) + 1;
	else
		return (int) ((x - varianza));
}
int indiceY(float y) {
	float diff = (y - varianza) - (int) (y - varianza);

	if (diff > 0.5)
		return ((int) ((y - varianza))) + 1;
	else
		return (int) ((y - varianza));
}
GLdouble coordinate(int x){
	return x+varianza;
}

double nextX() {
	return ((poscamx + 0.1 * cos((alpha * pgreco) / 180)));
}
double nextY() {
	return (poscamy + 0.1 * sin((alpha * pgreco) / 180));
}
double lastX() {
	return ((poscamx - 0.1 * cos((alpha * pgreco) / 180)));
}
double lastY() {
	return (poscamy - 0.1 * sin((alpha * pgreco) / 180));
}

bool collisioneCuboF() {
	if (labirinto[indiceY(nextY())][indiceX(nextX())] == 1)
		return true;
	return false;
}
bool collisioneCuboC() {
	if (labirinto[indiceY(lastY())][indiceX(lastX())] == 1)
		return true;
	return false;
}
bool collisioneCuboDA() {
	if (labirinto[indiceY(poscamy + l)][indiceX(poscamx + (l))] == 1)
		return true;
	return false;
}
bool collisioneCuboSA() {
	if (labirinto[indiceY(poscamy + (l))][indiceX(poscamx - (l))] == 1)
		return true;
	return false;
}
bool collisioneCuboDB() {
	if (labirinto[indiceY(poscamy - (l))][indiceX(poscamx + (l))] == 1)
		return true;
	return false;
}
bool collisioneCuboSB() {
	if (labirinto[indiceY(poscamy - (l))][indiceX(poscamx - (l))] == 1)
		return true;
	return false;
}

bool collisioneCuboW() {

	if (nextX() >= poscamx && nextY() < poscamy) {
		return collisioneCuboDB();
	}

	if (nextY() < poscamy && nextX() < poscamx) {
		return collisioneCuboSB();
	}

	if (nextY() >= poscamy && nextX() < poscamx) {
		return collisioneCuboSA();
	}

	if (nextX() >= poscamx && nextY() > poscamy) {
		return collisioneCuboDA();
	}

	return false;

}
bool collisioneCuboS() {

	if (lastX() >= poscamx && lastY() < poscamy) {
		return collisioneCuboDB();
	}

	if (lastY() < poscamy && lastX() < poscamx) {
		return collisioneCuboSB();
	}

	if (lastY() >= poscamy && lastX() < poscamx) {
		return collisioneCuboSA();
	}

	if (lastX() >= poscamx && lastY() > poscamy) {
		return collisioneCuboDA();
	}

	return false;

}
bool collisioneCuboLaterale() {

//	return collisioneCuboDA()||collisioneCuboSA()||collisioneCuboDB()||collisioneCuboSB();

	return collisioneCuboW();
}
void posizionaCamera(unsigned int i, unsigned int j) {

	poscamx = verticiGrandi[i][j].x;
	poscamy = verticiGrandi[i][j].y;
	posfy = poscamy;
	posfy = poscamx + 1;
}

void Inizializza() {
	GLfloat y = -10, x = -10, xp = -5, yp = -5;

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			verticiGrandi[i][j].x += x;
			verticiPiccoli[i][j].x += xp;

			verticiGrandi[i][j].y += y;
			verticiPiccoli[i][j].y += yp;

			x = verticiGrandi[i][j].x + l;
			xp = verticiPiccoli[i][j].x + l / 2;
		}
		y = verticiGrandi[i][0].y + l;
		yp = verticiPiccoli[i][0].y + l / 2;
		x = -10;
		xp = -5;
	}

//	for(int i=0;i<dim;i++){
//				for(int j=0;j<dim;j++){
//					cout<<verticiGrandi[i][j].y<<" "<<verticiGrandi[i][j].x<<" "<<i<<" "<<j<<"|";
//				}
//				cout<<endl;
//			}
	//generaLab();
poscamx=coordinate(posOsservatoreX);
poscamy=coordinate(posOsservatoreY);
posfx = poscamx + cos((alpha * pgreco) / 180);
		posfy = poscamy + sin((alpha * pgreco) / 180);
cout<<poscamx;
}

void disegnaPiano(string tipo) {
	GLfloat z;
	((tipo == "tetto") ? z = 5.0 : z = 0.0);
	glBegin(GL_QUADS);
	glVertex3f(verticiGrandi[0][0].x, verticiGrandi[0][0].y, z);
	glVertex3f(verticiGrandi[0][dim - 1].x, verticiGrandi[0][dim - 1].y, z);
	glVertex3f(verticiGrandi[dim - 1][dim - 1].x,
			verticiGrandi[dim - 1][dim - 1].y, z);
	glVertex3f(verticiGrandi[dim - 1][0].x, verticiGrandi[dim - 1][0].y, z);
	glEnd();
}

void disegnaParete(int a1, int a2, int b, string parete) {

	if (parete == "v") {
		glBegin(GL_QUADS);
		glVertex3f(verticiGrandi[a1][b].x, verticiGrandi[a1][b].y, 0.0);
		glVertex3f(verticiGrandi[a1][b].x, verticiGrandi[a1][b].y, 5.0);
		glVertex3f(verticiGrandi[a2][b].x, verticiGrandi[a2][b].y, 5.0);
		glVertex3f(verticiGrandi[a2][b].x, verticiGrandi[a2][b].y, 0.0);

		glEnd();
		for (int i = a1; i <= a2; i++)
			verticiGrandi[i][b].muro = true;

	} else {
		glBegin(GL_QUADS);
		glVertex3f(verticiGrandi[b][a1].x, verticiGrandi[b][a1].y, 0.0);
		glVertex3f(verticiGrandi[b][a1].x, verticiGrandi[b][a1].y, 5.0);
		glVertex3f(verticiGrandi[b][a2].x, verticiGrandi[b][a2].y, 5.0);
		glVertex3f(verticiGrandi[b][a2].x, verticiGrandi[b][a2].y, 0.0);

		glEnd();
		for (int i = a1; i <= a2; i++)
			verticiGrandi[b][i].muro = true;

	}

}

void disengnaLabirinto(Vertice vertici[][dim]) {

	for (unsigned int i = 0; i < dim; i++) {
		for (unsigned int j = 0; j < dim; j++) {
			if (labirinto[i][j] == 1) {
				GLfloat z = l / 2;
				for (unsigned int k = 0; k < 4; k++) {
					glPushMatrix();
					glTranslatef(vertici[i][j].x, vertici[i][j].y, z);
					glutSolidCube(l);
					glPopMatrix();
					z += l;
				}
			}
		}
	}

}
void disegnaStanza() {

	glColor3f(1, 0, 0);
	if (!alto)
		disegnaPiano("tetto");
	disegnaPiano("pavimento");

	glColor3f(0, 0, 0);
	if (alto)
		disengnaLabirinto(verticiPiccoli);
	else
		disengnaLabirinto(verticiGrandi);

}
void vinto(){
	cout<<indiceX(nextX()+1)<<" "<<indiceY(nextY()+1)<<" ";
	if((&labirinto[indiceY(nextY())][indiceX(nextX())]==&labirinto[posTargetY][posTargetX])||
				(&labirinto[indiceY(lastY())][indiceX(lastX())]==&labirinto[posTargetY][posTargetX])){

		win= true;
	}
}
bool controlloY() {

	if (verticiGrandi[indiceY(poscamy) + 1][indiceX(poscamx)].muro
			&& nextY() > poscamy)
		return false;
	if (verticiGrandi[indiceY(poscamy) - 1][indiceX(poscamy)].muro
			&& nextY() < poscamy)
		return false;
	return true;
}

bool controlloX() {

	if (verticiGrandi[indiceY(poscamy)][indiceX(poscamx) + 1].muro
			&& nextX() > poscamx)
		return false;
	if (verticiGrandi[indiceY(poscamy)][indiceX(poscamx) - 1].muro
			&& nextX() < poscamx)
		return false;
	return true;
}
void disegnaCubo() {
vinto();
	glPushMatrix();
	glColor3f(1, 0, 0.2);
	glTranslatef( (coordinate(posTargetX)),(coordinate(posTargetY)), 1);
	if(win)
		glutSolidSphere(0.2, 200, 200);
	else
		glutSolidCube(1);
	glPopMatrix();
}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	if (!alto) {
		gluLookAt(poscamx, poscamy, poscamz, posfx, posfy, posfz, 0.0, 0.0,
				1.0);
	} else
		gluLookAt(5.1, 5.0, 20.5, 5.0, 5.0, 0.0, 0, -1, 1.0);
//	if(alto && prima)
//				{cout<<"entra";
//
//					if(prima)
//					ridimensionaMatrice();
//					prima=false;// per non inizializzare sempre la matrice quando è dall'alto;
//					}
//			else if(seconda)
//			{
//				seconda=false;
//				Inizializza(); // per non inizializzare sempre la matrice quando è dall'alto;
//			}
////		gluLookAt(4.0, 4.0, 22.0, 4.0, 4.5, 0.0, 3.0, 2.0, 1.0);

	disegnaStanza();

		disegnaCubo();

	if (alto) {
		glPushMatrix();
		glColor3f(1, 0, 1);
		glTranslatef(traslazionex, traslazioney, 1);
		glutSolidSphere(0.2, 200, 200);
		glPopMatrix();
	/*	glPushMatrix();
		glTranslated((coordinate(posTargetY)), (coordinate(posTargetX)), 1);
		glutSolidCube(0.5);
		glPopMatrix();*/
		}

	glPopMatrix();

	glutSwapBuffers();

}

bool muro(unsigned int i, unsigned int j) {

	if (labirinto[i][j] == 1) {
		return true;
	}
	return false;
}

bool vicinoCubo() {
	if (labx <= posTargetX + 2 && labx >= posTargetX - 2
			&& laby <= posTargetY + 2 && laby >= posTargetY - 2)
		return true;
	return false;
}

void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'd':
		if (!alto) {
			alpha -= delta_alpha;
		} else if (modalitaSemplice) {

			if (labx - 1 >= 0 && !muro(laby, labx - 1)) {
				labx--;
				poscamx -= 0.5;
				traslazionex = poscamx;
				traslazioney = poscamy;
				if (vicinoCubo()) {
					alto = false;
					seconda = true;
					varianza = -10;
					l = 1;
					poscamx = verticiGrandi[laby][labx].x;
					poscamy = verticiGrandi[laby][labx].y;
				}
			}

		}
		posfx = poscamx + cos((alpha * pgreco) / 180);
		posfy = poscamy + sin((alpha * pgreco) / 180);

		glutPostRedisplay();

		break;
	case 'a':
		if (!alto)
			alpha += delta_alpha;
		else if (modalitaSemplice) {

			if (labx + 1 < dim && !muro(laby, labx + 1)) {
				labx++;
				poscamx += 0.5;
				traslazionex = poscamx;
				traslazioney = poscamy;
				if (vicinoCubo()) {
					alto = false;
					seconda = true;
					varianza = -10;
					l = 1;
					poscamx = verticiGrandi[laby][labx].x;
					poscamy = verticiGrandi[laby][labx].y;
				}
			}

		}
		posfx = poscamx + cos((alpha * pgreco) / 180);
		posfy = poscamy + sin((alpha * pgreco) / 180);

		glutPostRedisplay();

		break;

	case 'w':
		if (!alto) {
			if ((!collisioneCuboF()) && (!collisioneCuboW())) {
				poscamx = nextX();
				poscamy = nextY();
				traslazionex = poscamx - 0.5;
				traslazioney = poscamy - 0.5;

			} else {
				if (!controlloX()) {
					poscamy = nextY();
				} else if (!controlloY()) {
					poscamx = poscamx + 0.1 * cos((alpha * pgreco) / 180);
				}

			}

		} else if (modalitaSemplice) {

			if (laby - 1 >= 0 && !muro(laby - 1, labx)) {
				poscamy -= 0.5;
				laby--;
				traslazionex = poscamx;
				traslazioney = poscamy;
				if (vicinoCubo()) {
					alto = false;
					seconda = true;
					varianza = -10;
					l = 1;
					poscamx = verticiGrandi[laby + 1][labx].x;
					poscamy = verticiGrandi[laby + 1][labx].y;
				}

			}
		}
		posfx = poscamx + cos((alpha * pgreco) / 180);
		posfy = poscamy + sin((alpha * pgreco) / 180);
		glutPostRedisplay();
		break;
	case 's':
		if (!alto) {
			if ((!collisioneCuboC()) && (!collisioneCuboS())) {
				poscamx = lastX();
				poscamy = lastY();
			}
		} else if (modalitaSemplice) {

			if (laby + 1 < dim && !muro(laby + 1, labx)) {
				poscamy += 0.5;
				laby++;
				traslazionex = poscamx;
				traslazioney = poscamy;
				if (vicinoCubo()) {
					alto = false;
					seconda = true;
					varianza = -10;
					l = 1;
					poscamx = verticiGrandi[laby][labx].x;
					poscamy = verticiGrandi[laby][labx].y;
				}
			}

		}

		posfx = poscamx + cos((alpha * pgreco) / 180);
		posfy = poscamy + sin((alpha * pgreco) / 180);

		glutPostRedisplay();
		break;
	case 't':
		alto = true;
		prima = true;
		traslazionex = verticiPiccoli[indiceY(poscamy)][indiceX(poscamx)].x;
		traslazioney = verticiPiccoli[indiceY(poscamy)][indiceX(poscamx)].y;
		labx = indiceX(traslazionex);
		laby = indiceY(traslazioney);
		varianza = -5;
		l = 0.5;
		glutPostRedisplay();
		break;

	case 'n':
		if (!modalitaSemplice) {
			alto = false;
			seconda = true;
			varianza = -10;
			l = 1;
		}
		glutPostRedisplay();
		break;

	case 'v':
		modalitaSemplice = true;
		if (!alto) {
			alto = true;

			prima = true;
			traslazionex = verticiPiccoli[indiceY(poscamy)][indiceX(poscamx)].x;
			traslazioney = verticiPiccoli[indiceY(poscamy)][indiceX(poscamx)].y;
			labx = indiceX(traslazionex);
			laby = indiceY(traslazioney);
			varianza = -5;
			l = 0.5;
		}
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

void leggiMatrice() {
	ifstream file("src\\lab.txt");

	string tipo;
	file >> tipo;
	if (tipo == "Osservatore") {
		file >> posOsservatoreY;
		file >> posOsservatoreX;
		file >> tipo;
		file >> posTargetY;
		file >> posTargetX;
	} else if (tipo == "Target") {
		file >> posTargetY;
		file >> posTargetX;
		file >> tipo;
		file >> posOsservatoreY;
		file >> posOsservatoreX;
	}

	for (unsigned int i = 0; i < dim; i++) {
		for (unsigned int j = 0; j < dim; j++) {
			file >> labirinto[i][j];
		}
	}

	file.close();
	cout << "oss" << posOsservatoreY << posOsservatoreX;
	cout << "Targ" << posTargetY << posTargetX;
	for (unsigned int i = 0; i < dim; i++) {
		for (unsigned int j = 0; j < dim; j++) {
			cout << labirinto[i][j];
		}
		cout << endl;
	}

}

int main(int argc, char** argv) {


	leggiMatrice();
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

