#include <GL/glut.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <fstream>
using namespace std;
int h = 0;
GLfloat poscamx = 0.0, poscamy = 0.0, posfx = 1.0, posfy = 0, poscamz = 1.0,
		posfz = 1.0; //look at
GLfloat di = 1, dis = 0;
GLfloat traslazionex = 0.0, traslazioney = 0.0; //2d
GLfloat varianza = -10.0; //matrice grande
bool alto = false, modalitaSemplice = false, prima = false, seconda = false,
		win = false;
unsigned int labx, laby; //collisioni 2d
unsigned int posOsservatoreX, posOsservatoreY, posTargetX, posTargetY;
const int dim = 40;
GLfloat delta_alpha = 3, alpha = 0, pgreco = 3.14159;
int labirinto[dim][dim] = { 3 };
GLfloat velocita = 0.1;
int rotate = 0;
struct Vertice {
	GLfloat x, y;
	bool muro;
};

Vertice verticiGrandi[dim][dim] = { 0.0 };

GLfloat l = 1;

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

}

GLdouble coordinate(int x) {
	return x + varianza;
}

int indice(float x) {
	float diff = (x - varianza) - (int) (x - varianza);

	if (diff > 0.5)
		return (int) ((x - varianza)) + 1;
	else
		return (int) ((x - varianza));
}

double nextX() {
	return ((poscamx + velocita * cos((alpha * pgreco) / 180)));
}
double nextY() {
	return (poscamy + velocita * sin((alpha * pgreco) / 180));
}
double lastX() {
	return ((poscamx - velocita * cos((alpha * pgreco) / 180)));
}
double lastY() {
	return (poscamy - velocita * sin((alpha * pgreco) / 180));
}

bool collisioneCuboF() {

	if (labirinto[indice(nextY())][indice(nextX())] == 1) {
		float hxmax = verticiGrandi[indice(nextY())][indice(nextX())].x + l / 2;
		float hymax = verticiGrandi[indice(nextY())][indice(nextX())].y + l / 2;

		float hxmin = verticiGrandi[indice(nextY())][indice(nextX())].x - l / 2;
		float hymin = verticiGrandi[indice(nextY())][indice(nextX())].y - l / 2;
		if ((nextY() > hymin && nextY() < hymax)
				&& (nextX() > hxmin && nextX() < hxmax))
			return true;
	}
	return false;
//
//	((nextY()<poscamy)?vary=+1:vary=-1);
//	if(nextY()==poscamy) vary=0;
//	((nextX()<poscamx)?varx=+1:varx=-1);
//		if(nextX()==poscamx) varx=0;

//	if (labirinto[(indice(poscamy)+vary)][(indice(poscamx)+varx)] == 1)
//		return true;
//	return false;
}
bool collisioneCuboC() {
	if (labirinto[indice(lastY())][indice(lastX())] == 1)
		return true;
	return false;
}
bool collisioneCuboDA() {
	if (labirinto[indice(lastY() + l)][indice(nextX() + (l))] == 1)
		return true;
	return false;
}
bool collisioneCuboSA() {
	if (labirinto[indice(lastY() + (l))][indice(nextX() - (l))] == 1)
		return true;
	return false;
}
bool collisioneCuboDB() {
	if (labirinto[indice(lastY() - (l))][indice(nextX() + (l))] == 1)
		return true;
	return false;
}
bool collisioneCuboSB() {
	if (labirinto[indice(lastY() - (l))][indice(nextX() - (l))] == 1)
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

	return collisioneCuboDA() || collisioneCuboSA() || collisioneCuboDB()
			|| collisioneCuboSB();

}

void Inizializza() {
	GLfloat y = -10, x = -10;

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			verticiGrandi[i][j].x += x;

			verticiGrandi[i][j].y += y;

			x = verticiGrandi[i][j].x + l;
		}
		y = verticiGrandi[i][0].y + l;
		x = -10;
	}

//	for(int i=0;i<dim;i++){
//				for(int j=0;j<dim;j++){
//					cout<<verticiGrandi[i][j].y<<" "<<verticiGrandi[i][j].x<<" "<<i<<" "<<j<<"|";
//				}
//				cout<<endl;
//			}
	//generaLab();

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

void disengnaLabirinto(Vertice vertici[][dim]) {

	unsigned int h = 0;
	((alto) ? h = 1 : h = 5);
	for (unsigned int i = 0; i < dim; i++) {
		for (unsigned int j = 0; j < dim; j++) {
			if (labirinto[i][j] == 1) {
				GLfloat z = l / 2;
				for (unsigned int k = 0; k < h; k++) {
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

	disengnaLabirinto(verticiGrandi);

}

//
//
//void glutTimerFunc(unsigned int msec,,0){
//
//}
void rotCube(int secondi) {
	rotate = (rotate + 1) % 360;
	glPushMatrix();
	glTranslatef(posfx, posfy, 1);
	glRotatef((GLfloat) rotate, 0.0, 0.0, 0.1);

	glutSolidCube(3);

	glPopMatrix();
	glutPostRedisplay();
	glutTimerFunc(secondi, rotCube, secondi);

}

void rimp() {
	if (di > 0.2) {
		di -= 0.001;
		glutSolidCube(di);
		glutPostRedisplay();
		dis = di;
	} else {
		if (dis < 0.8)
			dis += 0.001;
		glutSolidSphere(dis, 200, 200);
		glutPostRedisplay();
	}
}
void disegnaCubo() {
//vinto();
	glPushMatrix();
	glColor3f(1, 1, 1);

	if (h == 4) {
		rotate = (rotate + 1) % 360;
		h = 0;
	}
	glTranslatef((coordinate(posTargetX)), (coordinate(posTargetY)), 1);
	glRotatef((GLfloat) rotate, 0.0, 0.0, 0.1);
	if (win) {
		rimp();

	} else
		glutSolidCube(1);
	glPopMatrix();

	glutPostRedisplay();
	h++;
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	if (!alto) {
		//gluLookAt(5,9,19.9,5, 9,0, -1.0, 0.0,-1.0);
		gluLookAt(poscamx, poscamy, poscamz, posfx, posfy, posfz, 0.0, 0.0,
				1.0);

	} else
		gluLookAt(poscamx, poscamy, 19.5, poscamx + 0.1, poscamy, poscamz, 0.0,
				0.0, -1.0);

	disegnaStanza();

	disegnaCubo();
	if (alto) {
		glColor3f(1, 0, 1);
		if (!alto)
			glPushMatrix();
		glTranslatef(poscamx, poscamy, 1);
		glutSolidSphere(1, 200, 200);
		glPopMatrix();
		glPushMatrix();
		//glTranslatef(coordinate(posTargetX),coordinate(posTargetY),1);
		glTranslatef(verticiGrandi[posTargetY][posTargetX].x,
				verticiGrandi[posTargetY][posTargetX].y, 1);

		glutSolidCube(1);
		glPopMatrix();

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

bool vicinoCubo(unsigned int intx, unsigned int inty) {
	if (intx <= posTargetX + 2 && intx >= posTargetX - 2
			&& inty <= posTargetY + 2 && inty >= posTargetY - 2)
		return true;
	return false;
}

void spostaInAvanti3D() {
	if ((!collisioneCuboF()) && (!collisioneCuboW())) {
		cout << collisioneCuboF() << endl;
		poscamx = nextX();
		poscamy = nextY();
		if (vicinoCubo(indice(poscamx), indice(poscamy)))
			win = true;
	}
}

void vaiAvanti2D() {
	if (labx - 1 >= 0 && !muro(laby, labx - 1)) {
		labx--;
		poscamx -= l;
		traslazionex = poscamx;
		traslazioney = poscamy;
		if (vicinoCubo(labx, laby)) {
			alto = false;
			seconda = true;
			varianza = -10;
			l = 1;
			poscamx = verticiGrandi[laby][labx].x;
			poscamy = verticiGrandi[laby][labx].y;
		}
	}
}

void vaiDietro3D() {
	if (!collisioneCuboF() && !collisioneCuboS()) {
		poscamx = lastX();
		poscamy = lastY();
		if (vicinoCubo(indice(poscamx), indice(poscamy)))
			win = true;
	}
}

void vaiDietro2D() {
	if (labx + 1 < dim && !muro(laby, labx + 1)) {
		labx++;
		poscamx += l;
		traslazionex = poscamx;
		traslazioney = poscamy;
		if (vicinoCubo(labx, laby)) {
			alto = false;
			seconda = true;
			varianza = -10;
			l = 1;
			poscamx = verticiGrandi[laby][labx].x;
			poscamy = verticiGrandi[laby][labx].y;
		}
	}

}
void vaiDestra2D() {
	if (laby + 1 < dim && !muro(laby + 1, labx)) {
		poscamy += l;
		laby++;
		traslazionex = poscamx;
		traslazioney = poscamy;
		if (vicinoCubo(labx, laby)) {
			alto = false;
			seconda = true;
			varianza = -10;
			l = 1;
			poscamx = verticiGrandi[laby][labx].x;
			poscamy = verticiGrandi[laby][labx].y;
		}
	}
}

void vaiSinistra2D() {
	if (laby - 1 >= 0 && !muro(laby - 1, labx)) {
		poscamy -= l;
		laby--;
		traslazionex = poscamx;
		traslazioney = poscamy;
		if (vicinoCubo(labx, laby)) {
			alto = false;
			seconda = true;
			varianza = -10;
			l = 1;
			poscamx = verticiGrandi[laby + 1][labx].x;
			poscamy = verticiGrandi[laby + 1][labx].y;
		}

	}
}

void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'd':
		if (!alto) {
			alpha -= delta_alpha;
		} else if (modalitaSemplice) {
			vaiDestra2D();

		}

		if (!vicinoCubo(labx, laby)) {
			posfx = poscamx + cos((alpha * pgreco) / 180);
			posfy = poscamy + sin((alpha * pgreco) / 180);
		} else {
			posfx = verticiGrandi[posTargetY][posTargetX].x;
			posfy = verticiGrandi[posTargetY][posTargetX].y;
		}

		glutPostRedisplay();

		break;
	case 'a':

		if (!alto)
			alpha += delta_alpha;
		else if (modalitaSemplice) {

			vaiSinistra2D();
		}
		if (!vicinoCubo(labx, laby)) {
			posfx = poscamx + cos((alpha * pgreco) / 180);
			posfy = poscamy + sin((alpha * pgreco) / 180);
		} else {
			posfx = verticiGrandi[posTargetY][posTargetX].x;
			posfy = verticiGrandi[posTargetY][posTargetX].y;
		}

		glutPostRedisplay();

		break;

	case 'w':

		if (!alto)
			spostaInAvanti3D();

		else if (modalitaSemplice)
			vaiAvanti2D();

		if (!vicinoCubo(labx, laby)) {
			posfx = poscamx + cos((alpha * pgreco) / 180);
			posfy = poscamy + sin((alpha * pgreco) / 180);
		} else {
			posfx = verticiGrandi[posTargetY][posTargetX].x;
			posfy = verticiGrandi[posTargetY][posTargetX].y;
		}
		glutPostRedisplay();
		break;
	case 's':
		if (!alto) {
			vaiDietro3D();
		} else if (modalitaSemplice)
			vaiDietro2D();

		if (!vicinoCubo(labx, laby)) {

			posfx = poscamx + cos((alpha * pgreco) / 180);
			posfy = poscamy + sin((alpha * pgreco) / 180);
		} else {
			posfx = verticiGrandi[posTargetY][posTargetX].x;
			posfy = verticiGrandi[posTargetY][posTargetX].y;
		}

		glutPostRedisplay();
		break;
	case 'm':
		alto = true;
		prima = true;


		traslazionex = verticiGrandi[indice(poscamy)][indice(poscamx)].x;
		traslazioney = verticiGrandi[indice(poscamy)][indice(poscamx)].y;
		labx = indice(traslazionex);
		laby = indice(traslazioney);

		glutPostRedisplay();
		break;

	case 'n':
		if (!modalitaSemplice) {
			alto = false;
			seconda = true;


		}
		glutPostRedisplay();
		break;

	case 'v':
		modalitaSemplice = true;
		if (!alto) {
			alto = true;
			prima = true;

			traslazionex = verticiGrandi[indice(poscamy)][indice(poscamx)].x;
			traslazioney = verticiGrandi[indice(poscamy)][indice(poscamx)].y;
			labx = indice(traslazionex);
			laby = indice(traslazioney);

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

	Inizializza();
	leggiMatrice();

	srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1300, 710);
	glutCreateWindow("la PERFEZIONE FATTA PIANO");
	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutReshapeFunc(reshape);
//rotCube(25);
	glutMainLoop();

	return 0;
}

