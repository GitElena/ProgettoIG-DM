#include <GL/glut.h>
#include <GL/glext.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <fstream>
#include "tga.h"
using namespace std;

//DIMENSIONE OGGETTI
GLfloat dimInizialeT = 1, dimensioneSferaT = 0, dimensioneFantasma = 0.5,
		dimCuboTroll = 1;
GLfloat xL = 0, zL = 0; //schermata di lose
const int dim = 40; //Dimensione labirinto
const int numTex = 10;
const int tempTot = 60;
int tempRimanente = tempTot;
GLfloat lunghezzaBarra = 17.0;
GLfloat l = 1;

//SPOSTAMENTI
GLfloat poscamx = 0.0, poscamy = 0.0, posfx = 1.0, posfy = 0, poscamz = 1.0,
		posfz = 1.0; //look at
GLfloat traslazionex = 0.0, traslazioney = 0.0; //2d
GLfloat varianza = -10.0;
GLfloat delta_alpha = 3, alpha = 0, pgreco = 3.14159, alphaCubo = 0,
		delta_alpha_cubo = 1, dimMuriLose = 4.0;
unsigned int labx, laby; //collisioni 2d
GLfloat velocita = 0.1;
int rotate = 0;
GLfloat decrementoBarra = (lunghezzaBarra / tempTot) * 2;

//POSIZIONI
int posOsservatoreX, posOsservatoreY, posTargetX, posTargetY, posTrollX = 6, posTrollY = 6, posTrollCubeX,
		posTrollCubeY;
int posFantasmaX[4]={3,3,37,20};
int posFantasmaY[4]={3,37,3,20};

//CONTROLLI STATO DI GIOCO
bool alto = false, modalitaSemplice = false, win = false, trolla = false, ing =
		false;
bool gioco = true, presoFantasma = false, loser = false, mostraLoser = false;

int labirinto[dim][dim] = { 3 };
GLuint textures[numTex];
const char *textureFile[numTex] = { "src\\erba1.tga", "src\\muroGrigio.tga",
		"src\\cielo.tga", "src\\cassa.tga", "src\\cubo3.tga", "src\\occhio.tga",
		"src\\vittori.tga", "src\\troll.tga", "src\\TimerLungo.tga",
		"src\\youLose.tga" };

//LUCI & COLORI
GLfloat coloreLuceAmbiente[] = { 0.1, 0.1, 0.1, 1.0f };
GLfloat luceDiffusa[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat luceSpeculare[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat rouge[] = { 0.5, 0.1, 0.0, 1.0 };
GLfloat coloreNebbia[] = { 0.4, 0.4, 0.4, 0 };
GLfloat PosLuceAmbiente[] = { 10, 10, 10, 1.0 };
GLfloat coloreLuceAmbienteTicToc[] = { -0.5, -0.5, 1, 1.0 };

void ingFantasma();
void collisioneFantasma(int);
void preso(); //porta il giocatore al punto di partenza
void disegnaCubo(int, GLfloat);
bool vicinoCubo(int, int); //verifica vittoria
void disegnaParete(float, float, float, string, GLfloat, int);
GLdouble coordinate(int); //calcola le coordinate a partire da un indice della matrice

struct Vertice {
	GLfloat x, y;
	bool muro;
};
Vertice vertici[dim][dim] = { 0.0 };

void init(void) {
	glClearColor(0.4, 0.4, 0.4, 0);

	glEnable(GL_LIGHTING);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glLightfv(GL_LIGHT0, GL_AMBIENT, coloreLuceAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luceDiffusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luceSpeculare);
	glLightfv(GL_LIGHT0, GL_POSITION, PosLuceAmbiente);

	glEnable(GL_LIGHT0);

	glFogfv(GL_FOG_COLOR, coloreNebbia);
	glFogf(GL_FOG_START, -2);
	glFogf(GL_FOG_END, 11);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glEnable(GL_FOG);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

}

void texture() {
	GLbyte *pBytes;
	GLint iWidth, iHeight, iComponents;
	GLenum eFormat;
	GLubyte i;

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glGenTextures(numTex, textures);

	// Carica texture
	for (i = 0; i < numTex; i++) {

		glBindTexture(GL_TEXTURE_2D, textures[i]);



		pBytes = gltLoadTGA(textureFile[i], &iWidth, &iHeight, &iComponents,
				&eFormat);
		glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat,
				GL_UNSIGNED_BYTE, pBytes);

		free(pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}

}

void schermataLose() {



	GLfloat rigaSchermata = coordinate(dim / 2), colonnaSchermata = coordinate(5), zSchermata = 1.5;

	glPushMatrix();
	glTranslatef(colonnaSchermata, rigaSchermata, zSchermata);
	if (zL < 1.3) {

		glRotatef(GLfloat(rotate), 0.1, 0.0, 0.0);

	}
	glBindTexture(GL_TEXTURE_2D, textures[9]);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0, -xL, -zL);
	glTexCoord2f(0, 0);
	glVertex3f(0, +xL, -zL);
	glTexCoord2f(0, 1);
	glVertex3f(0, +xL, +zL);
	glTexCoord2f(1, 1);
	glVertex3f(0, -xL, +zL);
	glEnd();
	glPopMatrix();
	glutPostRedisplay();

}

void Timer(int sec) {
	if (!win) {
		if (tempRimanente > 0) {
			tempRimanente--;
			lunghezzaBarra -= decrementoBarra;
		} else {
			gioco = false;
			loser = true;
		}

		if (tempRimanente == 30) {
			glLightfv(GL_LIGHT0, GL_AMBIENT, coloreLuceAmbienteTicToc);

			glFogfv(GL_FOG_COLOR, rouge);
			glClearColor(0.5, 0.1, 0.0, 1.0);
		}
	}
	glutTimerFunc(sec, Timer, sec);
}

void abbassaMuri(int sec) {
	if (loser) {
		if (dimMuriLose > 0) {
			dimMuriLose--;


			if (dimMuriLose == 0) {
				poscamx = coordinate(1);
				poscamy = coordinate(dim / 2);
				alpha = 0;
				posfx = poscamx + cos((alpha * pgreco) / 180);
				posfy = poscamy + sin((alpha * pgreco) / 180);

			}
		} else {
			mostraLoser = true;

			if (zL < 1.3) {
				xL += 0.2;
				zL += 0.2;
			}


		}
	}
	glutTimerFunc(sec, abbassaMuri, sec);
}

void muoviFantasma(int i) {
	int mov = rand() % 8;

	switch (mov) {
	case 0:
		if (labirinto[posFantasmaY[i] + 1][posFantasmaX[i] + 1] == 0) {
			posFantasmaY[i]++;
			posFantasmaX[i]++;
		}
		break;
	case 1:
		if (labirinto[posFantasmaY[i]][posFantasmaX[i] + 1] == 0)
			posFantasmaX[i]++;
		break;
	case 2:
		if (labirinto[posFantasmaY[i] + 1][posFantasmaX[i]] == 0)
			posFantasmaY[i]++;
		break;
	case 3:
		if (labirinto[posFantasmaY[i] - 1][posFantasmaX[i] - 1] == 0) {
			posFantasmaY[i]--;
			posFantasmaX[i]--;
		}
		break;
	case 4:
		if (labirinto[posFantasmaY[i]][posFantasmaX[i] - 1] == 0)
			posFantasmaX[i]--;
		break;
	case 5:
		if (labirinto[posFantasmaY[i] - 1][posFantasmaX[i]] == 0)
			posFantasmaY[i]--;
		break;
	case 6:
		if (labirinto[posFantasmaY[i] + 1][posFantasmaX[i] - 1] == 0) {
			posFantasmaY[i]++;
			posFantasmaX[i]--;
		}
		break;
	case 7:
		if (labirinto[posFantasmaY[i] - 1][posFantasmaX[i] + 1] == 0) {
			posFantasmaY[i]--;
			posFantasmaX[i]++;
		}
		break;
	default:
		break;

	}

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
GLfloat nextnextX() {
	return ((poscamx + 10 * (velocita * cos((alpha * pgreco) / 180))));
}
GLfloat nextnextY() {
	return (poscamy + 10 * (velocita * sin((alpha * pgreco) / 180)));
}
bool collisioneCuboF() {

	if (labirinto[indice(nextnextY())][indice(nextnextX())] == 1)
		return true;
	if (labirinto[indice(nextnextY())][indice(nextnextX() + l / 2)] == 1)
		return true;
	if (labirinto[indice(nextnextY() + l / 2)][indice(nextnextX())] == 1)
		return true;
	if (labirinto[indice(nextnextY() - l / 2)][indice(nextnextX())] == 1)
		return true;
	if (labirinto[indice(nextnextY())][indice(nextnextX() - l / 2)] == 1)
		return true;

	return false;
}
bool collisioneCuboC() {
	if (labirinto[indice(lastY())][indice(lastX())] == 1)
		return true;
	return false;
}
bool collisione45Gradi() {
	if (indice(poscamx + velocita) == indice(nextX())) {
		if (indice(poscamy + velocita) == indice(nextY())) {
			if (labirinto[indice(poscamy + velocita)][indice(poscamx + velocita)]
					== 1)
				return true;
		}
		if (indice(poscamy - velocita) == indice(nextY())) {
			if (labirinto[indice(poscamy - velocita)][indice(poscamx + velocita)]
					== 1) {
				return true;
			}
		}
	}
	if (indice(poscamx - velocita) == indice(nextX())) {
		if (indice(poscamy + velocita) == indice(nextY())) {
			if (labirinto[indice(poscamy + velocita)][indice(poscamx - velocita)]
					== 1)
				return true;
		}
		if (indice(poscamy - velocita) == indice(nextY())) {
			if (labirinto[indice(poscamy - velocita)][indice(poscamx - velocita)]
					== 1)
				return true;

		}
	}

	return false;
}
bool collisioneCuboDA() {
	if (labirinto[indice(nextY() + l)][indice(nextX() + (l))] == 1)
		return true;

	return false;
}
bool collisioneCuboSA() {
	if (labirinto[indice(nextY() + (l))][indice(nextX() - (l))] == 1)
		return true;

	return false;
}
bool collisioneCuboDB() {
	if (labirinto[indice(nextY() - (l))][indice(nextX() + (l))] == 1)
		return true;
	return false;
}
bool collisioneCuboSB() {
	if (labirinto[indice(nextY() - (l))][indice(nextX() - (l))] == 1)
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

void rimpFantasma() {
	for(int i=0;i<4;i++)
	{
	if (dimensioneFantasma > 0.2) {
		dimensioneFantasma -= 0.005;


	} else {
		muoviFantasma(i);
		ing = true;
	}
	}

}

void setIngFalse(int sec) {
	ing = false;
	glutTimerFunc(sec, setIngFalse, sec);
}

void stampaFantasma(int i) {

	glPushMatrix();



	glTranslatef(vertici[posFantasmaY[i]][posFantasmaX[i]].x,
			vertici[posFantasmaY[i]][posFantasmaX[i]].y, l);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glRotatef(GLfloat(rotate), 0.0, 0.0, 0.1);
	GLUquadric * q = gluNewQuadric();
	gluQuadricTexture(q, true);
	gluSphere(q, dimensioneFantasma, 200, 200);

	if (!ing)
		rimpFantasma();
	else {

		ingFantasma();
	}

	glPopMatrix();

}
void ingFantasma() {
	if (dimensioneFantasma < l / 2) {
		dimensioneFantasma += 0.005;


	} else {
		if (presoFantasma)
			preso();
		else
			{for(int i=0;i<4;i++)
			collisioneFantasma(i);}

	}
}
void preso() {
	if (!(indice(poscamy) == posOsservatoreY
			&& indice(poscamx) == posOsservatoreX)) {
		if (indice(poscamy) < posOsservatoreY
				&& (indice(poscamy) != posOsservatoreY))
			poscamy = vertici[indice(poscamy) + 1][0].y;

		else if ((indice(poscamy) != posOsservatoreY))
			poscamy = vertici[indice(poscamy) - 1][0].y;

		if (indice(poscamx) < posOsservatoreX
				&& (indice(poscamx) != posOsservatoreX))
			poscamx = vertici[0][indice(poscamx) + 1].x;

		else if ((indice(poscamx) != posOsservatoreX))
			poscamx = vertici[0][indice(poscamx) - 1].x;

		presoFantasma = true;
	} else {
		presoFantasma = false;
		gioco = true;

		posfx = poscamx + cos((alpha * pgreco) / 180);
		posfy = poscamy + sin((alpha * pgreco) / 180);
		if (alto) {
			traslazionex = vertici[indice(poscamy)][indice(poscamx)].x;
			traslazioney = vertici[indice(poscamy)][indice(poscamx)].y;
			labx = indice(traslazionex);
			laby = indice(traslazioney);
		}
		if (tempRimanente > 30)
			glFogfv(GL_FOG_COLOR, coloreNebbia);

	}

}
void collisioneFantasma(int i) {
	if (!alto) {
		if (posFantasmaX[i] - (indice(poscamx)) <= 1
				&& posFantasmaX[i] - indice(poscamx) >= -1
				&& (posFantasmaY[i] - indice(poscamy) <= 1
						&& posFantasmaY[i] - indice(poscamy) >= -1)) {
			gioco = false;
			glFogfv(GL_FOG_COLOR, rouge);
			preso();
		}
	} else {
		if (posFantasmaX[i] - (indice(poscamx)) <= 0.7
				&& posFantasmaX[i] - indice(poscamx) >= -0.7
				&& (posFantasmaY[i] - indice(poscamy) <= 0.7
						&& posFantasmaY[i] - indice(poscamy) >= -0.7)) {
			gioco = false;
			preso();
		}
	}


}

void Inizializza() {
	GLfloat y = -10, x = -10;

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			vertici[i][j].x += x;

			vertici[i][j].y += y;

			x = vertici[i][j].x + l;
		}
		y = vertici[i][0].y + l;
		x = -10;
	}

}

void disegnaPiano(string tipo) {
	GLfloat z;
	int g;
	((tipo == "tetto") ? z = 4.0 : z = 0.0);
	((tipo == "tetto") ? g = 2 : g = 0);
	glBindTexture(GL_TEXTURE_2D, textures[g]);

	int i;
	((z > 0) ? i = -1 : i = 1);
	for (int q = 0; q < dim; q++) {
		for (int p = 0; p < dim; p++) {
			if (labirinto[q][p] != 1 || loser) {
				glBegin(GL_QUADS);
				glNormal3f(0, 0, i);
				glTexCoord2f(0, 0);
				glVertex3f(vertici[q][p].x - l / 2, vertici[q][p].y - l / 2, z);
				glTexCoord2f(1, 0);
				glVertex3f(vertici[q][p].x + l / 2, vertici[q][p].y - l / 2, z);
				glTexCoord2f(1, 1);
				glVertex3f(vertici[q][p].x + l / 2, vertici[q][p].y + l / 2, z);
				glTexCoord2f(0, 1);
				glVertex3f(vertici[q][p].x - l / 2, vertici[q][p].y + l / 2, z);

				glEnd();



			}
		}
	}

}



void disegnaParete(float a1, float a2, float b, string parete, GLfloat z,
		int i) {

	if (parete == "o") {
		glBegin(GL_QUADS);
		glNormal3f(0, i, 0);
		glTexCoord2f(0, 1);
		glVertex3f(a1, b, z + l);
		glTexCoord2f(1, 1);
		glVertex3f(a2, b, z + l);
		glTexCoord2f(1, 0);
		glVertex3f(a2, b, z);
		glTexCoord2f(0, 0);
		glVertex3f(a1, b, z);

		glEnd();


	} else {

		glBegin(GL_QUADS);
		glNormal3f(i, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3f(b, a1, z);
		glTexCoord2f(0, 1);
		glVertex3f(b, a1, z + l);
		glTexCoord2f(1, 1);
		glVertex3f(b, a2, z + l);
		glTexCoord2f(1, 0);
		glVertex3f(b, a2, z);

		glEnd();


	}

}

void tappi(int z, int k, int o) {
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);

	glVertex3f(vertici[k][o].x - l / 2, vertici[k][o].y - l / 2, z);
	glTexCoord2f(1, 0);
	glVertex3f(vertici[k][o].x + l / 2, vertici[k][o].y - l / 2, z);
	glTexCoord2f(1, 1);
	glVertex3f(vertici[k][o].x + l / 2, vertici[k][o].y + l / 2, z);
	glTexCoord2f(0, 1);
	glVertex3f(vertici[k][o].x - l / 2, vertici[k][o].y + l / 2, z);

	glEnd();

}

void disengnaLabirinto() {

	int z = 0;
	int zmax;
	((alto) ? zmax = 1 : zmax = 4);
	if (loser) {
		zmax = dimMuriLose;
	}
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	for (unsigned int k = 0; k < dim; k++)
		for (unsigned int o = 0; o < dim; o++) {
			if (labirinto[k][o] == 1) {

				while (z < zmax) {

					disegnaParete(vertici[k][o].x - l / 2,
							vertici[k][o].x + l / 2, vertici[k][o].y + l / 2,
							"o", z, +1);
					disegnaParete(vertici[k][o].x - l / 2,
							vertici[k][o].x + l / 2, vertici[k][o].y - l / 2,
							"o", z, -1);
					disegnaParete(vertici[k][o].y + l / 2,
							vertici[k][o].y - l / 2, vertici[k][o].x - l / 2,
							"v", z, -1);
					disegnaParete(vertici[k][o].y + l / 2,
							vertici[k][o].y - l / 2, vertici[k][o].x + l / 2,
							"v", z, +1);

					z += l;
				}
				tappi(z, k, o);
				z = 0.0;
				tappi(z, k, o);

			}

		}

	if (loser)
		glutPostRedisplay();


}


void disegnaStanza() {



	if (!alto)
		disegnaPiano("tetto");

	disegnaPiano("pavimento");



	disengnaLabirinto();

}



void TempoRotazione(int secondi) {
	rotate = (rotate + 2) % 360;

	glutTimerFunc(secondi, TempoRotazione, secondi);
}

bool vicinoTroll() {
	if (indice(poscamx) <= posTrollCubeX + 2
			&& indice(poscamx) >= posTrollCubeX - 2
			&& indice(poscamy) <= posTrollCubeY + 2
			&& indice(poscamy) >= posTrollCubeY - 2)
		return true;
	return false;
}

void trollCube() {

	glPushMatrix();
	glTranslatef(coordinate(posTrollCubeX), coordinate(posTrollCubeY), 0);
	glRotatef(GLfloat(rotate), 0.0, 0.0, 0.1);

	if (!vicinoTroll() && !trolla)
		disegnaCubo(3, dimCuboTroll);
	else {
		if (!trolla) {
			disegnaCubo(3, dimCuboTroll);
			dimCuboTroll -= 0.004;
			gioco = false;
			if (dimCuboTroll <= 0.2) {
				trolla = true;
				dimCuboTroll = 1;
				gioco = true;
			}

		}
		if (trolla) {

			disegnaCubo(7, dimCuboTroll);


		}
	}
	glPopMatrix();
}

void disegnaCubo(int i, GLfloat p) {

	GLfloat h = l / 2;
	GLfloat x1 = h * p;
	GLfloat yh1 = (-1 * h) * p;
	GLfloat x2 = (-1 * h) * p;
	GLfloat yh2 = (h) * p;
	GLfloat x3 = (-1 * h) * p;
	GLfloat yh3 = (-1 * h) * p;
	GLfloat x4 = h * p;
	GLfloat yh4 = h * p;
	GLfloat l1 = l - (h * p);
	GLfloat l2 = l + (h * p);
	glBindTexture(GL_TEXTURE_2D, textures[i]);

	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(x1, yh1, l1);
	glTexCoord2f(1, 1);
	glVertex3f(x1, yh1, l2);
	glTexCoord2f(0, 1);
	glVertex3f(x3, yh3, l2);
	glTexCoord2f(0, 0);
	glVertex3f(x3, yh3, l1);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(x3, yh3, l1);
	glTexCoord2f(1, 1);
	glVertex3f(x3, yh3, l2);
	glTexCoord2f(0, 1);
	glVertex3f(x2, yh2, l2);
	glTexCoord2f(0, 0);
	glVertex3f(x2, yh2, l1);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(x2, yh2, l1);
	glTexCoord2f(0, 1);
	glVertex3f(x2, yh2, l2);
	glTexCoord2f(1, 1);
	glVertex3f(x4, yh4, l2);
	glTexCoord2f(1, 0);
	glVertex3f(x4, yh4, l1);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(x4, yh4, l1);
	glTexCoord2f(0, 1);
	glVertex3f(x4, yh4, l2);
	glTexCoord2f(1, 1);
	glVertex3f(x1, yh1, l2);
	glTexCoord2f(1, 0);
	glVertex3f(x1, yh1, l1);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(x1, yh1, l2);
	glTexCoord2f(0, 1);
	glVertex3f(x3, yh3, l2);
	glTexCoord2f(1, 1);
	glVertex3f(x2, yh2, l2);
	glTexCoord2f(1, 0);
	glVertex3f(x4, yh4, l2);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 0);
	glVertex3f(x1, yh1, l1);
	glTexCoord2f(0, 1);
	glVertex3f(x3, yh3, l1);
	glTexCoord2f(1, 1);
	glVertex3f(x2, yh2, l1);
	glTexCoord2f(1, 0);
	glVertex3f(x4, yh4, l1);
	glEnd();
}

void rimp() {
	if (dimInizialeT > 0.2) {
		dimInizialeT -= 0.005;
		disegnaCubo(3, dimInizialeT);

		dimensioneSferaT = dimInizialeT;
	} else {
		if (dimensioneSferaT < 0.8)
			dimensioneSferaT += 0.005;
		glBindTexture(GL_TEXTURE_2D, textures[6]);

		glTranslatef(0, 0, 1);


		GLUquadric * q = gluNewQuadric();
		gluQuadricTexture(q, true);
		gluSphere(q, dimensioneSferaT, 200, 200);

	}
}


void gestisciCubo() {
	glPushMatrix();

	glTranslatef((coordinate(posTargetX)), (coordinate(posTargetY)), 0);
	glRotatef(GLfloat(rotate), 0.0, 0.0, -0.1);

	if (win) {
		rimp();

	} else {

		disegnaCubo(3, dimInizialeT);


	}

	glPopMatrix();

	glutPostRedisplay();

}

void disegnaBarra(){
	glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, textures[4]);
			glTranslatef(poscamx, poscamy, 1);
			GLUquadric * q = gluNewQuadric();
			gluQuadricTexture(q, true);
			gluSphere(q, 0.5, 200, 200);

			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-8.1, -16, l * 2);
			glTexCoord2f(1, 0);
			glVertex3f(-8.1, -15, l * 2);
			glTexCoord2f(1, 1);
			glVertex3f((lunghezzaBarra / 2) + 0.5, -15, l * 2);
			glTexCoord2f(0, 1);

			glVertex3f((lunghezzaBarra / 2) + 0.5, -16, l * 2);

			glEnd();

			glBindTexture(GL_TEXTURE_2D, textures[8]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 1);
			glVertex3f(-9, -17, l * 2);
			glTexCoord2f(1, 1);
			glVertex3f(-9, -14, l * 2);
			glTexCoord2f(1, 0);
			glVertex3f(-8, -14, l * 2);
			glTexCoord2f(0, 0);

			glVertex3f(-8, -17, l * 2);
			glEnd();


			glPopMatrix();
}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glPushMatrix();

	if (loser) {
		alto = false;
		glEnable(GL_FOG);

	}

	if (!alto) {
		gluLookAt(poscamx, poscamy, poscamz, posfx, posfy, posfz, 0.0, 0.0,
				1.0);

	} else
		gluLookAt(poscamx, poscamy, 19.5, poscamx + 0.1, poscamy, poscamz, 0.0,
				0.0, -1.0);
	disegnaStanza();
	if(!loser){


	gestisciCubo();
	for(int i=0;i<4;i++)
	stampaFantasma(i);
	trollCube();}

	if (mostraLoser)
		schermataLose();

	if (alto) {
			disegnaBarra();}

//

	glPopMatrix();

	glutSwapBuffers();
}

bool muro(unsigned int i, unsigned int j) {

	if (labirinto[i][j] == 1) {
		return true;
	}
	return false;
}

bool vicinoCubo(int intx, int inty) {

	if (intx <= posTargetX + 2 && intx >= posTargetX - 2
			&& inty <= posTargetY + 2 && inty >= posTargetY - 2) {
		gioco = false;
		win = true;
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, PosLuceAmbiente);
		glFogfv(GL_FOG_COLOR, coloreNebbia);
		glutPostRedisplay();
		return true;

	}
	return false;
}

void spostaInAvanti3D() {
	if ((!collisioneCuboF()) && (!collisioneCuboW())) {

		poscamx = nextX();
		poscamy = nextY();
		vicinoCubo(indice(poscamx), indice(poscamy));

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

			varianza = -10;
			l = 1;
			poscamx = vertici[laby][labx].x;
			poscamy = vertici[laby][labx].y;
		}
	}
}

void vaiDietro3D() {
	if (!collisioneCuboS() && !collisioneCuboC()) {
		poscamx = lastX();
		poscamy = lastY();
		vicinoCubo(indice(poscamx), indice(poscamy));

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
			varianza = -10;
			l = 1;
			poscamx = vertici[laby][labx].x;
			poscamy = vertici[laby][labx].y;
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

			varianza = -10;
			l = 1;
			poscamx = vertici[laby][labx].x;
			poscamy = vertici[laby][labx].y;
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

			varianza = -10;
			l = 1;
			poscamx = vertici[laby + 1][labx].x;
			poscamy = vertici[laby + 1][labx].y;
		}

	}
}

void keyboard(unsigned char key, int x, int y) {
	if (gioco) {
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
				posfx = vertici[posTargetY][posTargetX].x;
				posfy = vertici[posTargetY][posTargetX].y;
			}

			glutPostRedisplay();

			break;
		case 'f':
			glutFullScreen();
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
				posfx = vertici[posTargetY][posTargetX].x;
				posfy = vertici[posTargetY][posTargetX].y;
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
				posfx = vertici[posTargetY][posTargetX].x;
				posfy = vertici[posTargetY][posTargetX].y;
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
				posfx = vertici[posTargetY][posTargetX].x;
				posfy = vertici[posTargetY][posTargetX].y;
			}

			glutPostRedisplay();
			break;
		case 'm':
			alto = true;

			glDisable(GL_FOG);

			traslazionex = vertici[indice(poscamy)][indice(poscamx)].x;
			traslazioney = vertici[indice(poscamy)][indice(poscamx)].y;
			labx = indice(traslazionex);
			laby = indice(traslazioney);

			glutPostRedisplay();
			break;

		case 'n':
			if (!modalitaSemplice) {
				alto = false;

				glEnable(GL_FOG);

			}
			glutPostRedisplay();
			break;

		case 'v':
			modalitaSemplice = true;
			if (!alto) {
				alto = true;

				glDisable(GL_FOG);
				traslazionex = vertici[indice(poscamy)][indice(poscamx)].x;
				traslazioney = vertici[indice(poscamy)][indice(poscamx)].y;
				labx = indice(traslazionex);
				laby = indice(traslazioney);

			}
			glutPostRedisplay();
			break;

		default:
			break;

		}
	}
	if (key == 27)
		exit(0);



}
void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void leggiMatrice(string nomeFile) {
	ifstream file(&nomeFile[0]);

	file >> posOsservatoreY;
	file >> posOsservatoreX;

	file >> posTargetY;
	file >> posTargetX;

	file >> posTrollCubeY;
	file >> posTrollCubeX;

	for (unsigned int i = 0; i < dim; i++) {
		for (unsigned int j = 0; j < dim; j++) {
			file >> labirinto[i][j];
		}
	}

	file.close();


	poscamx = vertici[posOsservatoreY][posOsservatoreX].x;
	poscamy = vertici[posOsservatoreY][posOsservatoreX].y;
	posfx = poscamx + cos((alpha * pgreco) / 180);
	posfy = poscamy + sin((alpha * pgreco) / 180);

}

void scegliLab() {
	int lab=rand()%4;

	switch (lab) {
		case 0:
			leggiMatrice("src\\lab.txt");

			break;
		case 1:
			leggiMatrice("src\\lab3.txt");
			break;
		case 2:
			leggiMatrice("src\\lab4.txt");
		break;
		case 3:
					leggiMatrice("src\\lab2.txt");
				break;
		default:
			leggiMatrice("src\\lab3.txt");
			break;
	}


}

int main(int argc, char** argv) {
	srand(time(0));
	Inizializza();
	scegliLab();


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1450,800);
	glutCreateWindow("Progetto IG DM");
	init();

	abbassaMuri(1000);
	TempoRotazione(25);
	Timer(1000);
	setIngFalse(7000);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutReshapeFunc(reshape);
	texture();
	glutMainLoop();
	glDeleteTextures(numTex, textures);

	return 0;
}

