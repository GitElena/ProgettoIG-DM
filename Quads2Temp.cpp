//============================================================================
// Name        : grrrr.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//============================================================================
// Name        : InvioNiellow.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <GL/glut.h>

#define GL_GLEXT_LEGACY      //should prevent old glext.h from being included
#define GL_GLEXT_PROTOTYPES  //should make glActiveTexture be defined
#define GL_ACTIVE_TEXTURE                 0x84E0
#include <GL/glext.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <fstream>
#include "tga.h"
using namespace std;
int h = 0;
GLfloat poscamx = 0.0, poscamy = 0.0, posfx = 1.0, posfy = 0, poscamz = 1.0,
		posfz = 1.0; //look at
GLfloat di = 1, dis = 0,dif=0.5;
GLfloat traslazionex = 0.0, traslazioney = 0.0; //2d
GLfloat varianza = -10.0; //matrice grande
bool alto = false, modalitaSemplice = false, prima = false, seconda = false,
		win = false;
unsigned int labx, laby; //collisioni 2d
int posOsservatoreX, posOsservatoreY, posTargetX, posTargetY,posFantasmaX=3,posFantasmaY=3;
const int dim = 40;
GLfloat delta_alpha = 3, alpha = 0, pgreco = 3.14159, alphaCubo=0,delta_alpha_cubo=1,zloser=4.0;
int labirinto[dim][dim] = { 3 };
GLfloat velocita = 0.1;
int rotate = 0;
bool ing=false;
const int numTex=7;
GLuint  textures[numTex];
const char *textureFile[numTex] = { "src\\erba1.tga", "src\\muroGrigio.tga","src\\stella.tga","src\\cassa.tga","src\\cubo3.tga","src\\Fantasmino2.tga","src\\vittori.tga"};
const int tempTot=300;
int tempRimanente=tempTot;
GLfloat lunghezzaBarra=18.0;
GLfloat decrementoBarra=(lunghezzaBarra/tempTot)*2;
bool gioco=true,presoFantasma=false,loser=false;

GLfloat x1=0,x2=0,x3=0,x4=0;

GLfloat yh1=0,yh2=0,yh3=0,yh4=0;

GLfloat coloreLuceAmbiente[] = { 0.1, 0.1, 0.1, 1.0f };
//GLfloat coloreLuceAmbiente[] = { 0.0, 0.0, 0.0, 0.5f };
GLfloat luceDiffusa[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat luceSpeculare[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat reflex[] = { 0.0 };
GLfloat grigioBello[] = { 0.2, 0.2, 0.2, 1.0 };
//GLfloat marrone[]= { 0.2, 0.2, 0.0, 1.0 };
//GLfloat senape[]= { 0.4, 0.4, 0.0, 1.0 };
GLfloat rouge[]= { 0.5, 0.1, 0.0, 1.0 };
GLfloat Speculare[] = { 0, 0, 0, 1.0 };
GLfloat nero[] = { 0, 0, 0, 1 };
GLfloat bianco[] = { 1, 1, 1, 1 };
GLfloat verde[] = { 0, 1, 0, 1 };
//GLfloat grigio[] = { 1, 0, 1, 1 };
//GLfloat coloreNebbia[] = { 0.3, 0.3, 0.3, 1 };
GLfloat coloreNebbia[] = { 0.4, 0.4, 0.4, 0 };
GLfloat PosLuceAmbiente[] = {10, 10,10, 1.0 };


GLfloat coloreLuceAmbienteTicToc[] = {-0.5, -0.5,1, 1.0 };
GLfloat PosLuceAmbiente2[] = { 40, 40,10, 1.0 };
void ingFantasma();
void collisioneFantasma();
void preso();



struct Vertice {
	GLfloat x, y;
	bool muro;
};

Vertice verticiGrandi[dim][dim] = { 0.0 };

GLfloat l = 1;

void init(void) {
	glClearColor(0.4, 0.4, 0.4, 0);

	glEnable(GL_LIGHTING);

	glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glLightfv(GL_LIGHT0, GL_AMBIENT, coloreLuceAmbiente);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, luceDiffusa);
		glLightfv(GL_LIGHT0, GL_SPECULAR, luceSpeculare);
//		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, PosLuceAmbiente);
		glLightfv(GL_LIGHT0, GL_POSITION, PosLuceAmbiente);

		glEnable(GL_LIGHT0);

//		glLightfv(GL_LIGHT1, GL_DIFFUSE, luceDiffusa);
//		glLightfv(GL_LIGHT1, GL_SPECULAR, luceSpeculare);
//		glEnable(GL_LIGHT1);


		glFogfv(GL_FOG_COLOR, coloreNebbia);
		glFogf(GL_FOG_START,-2);
		glFogf(GL_FOG_END, 11);
		glFogi(GL_FOG_MODE, GL_LINEAR);
		//glEnable(GL_FOG);

		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);

}

void texture()
{
			GLbyte *pBytes;
		    GLint iWidth, iHeight, iComponents;
		    GLenum eFormat;
		    GLubyte i;

		   	glEnable(GL_TEXTURE_2D);
		   	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		    glGenTextures(numTex, textures);

		    	// Load texture
		    	for ( i= 0; i < numTex; i++)
		    	{

		    		//glActiveTexture(GL_TEXTURE0);
		    		glBindTexture(GL_TEXTURE_2D, textures[i]);

		    		// glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		    		pBytes = gltLoadTGA(textureFile[i], &iWidth, &iHeight, &iComponents, &eFormat);
		    		glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);

		    		free(pBytes);
		    		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		    		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT);

		    	}




}

void Timer(int sec)
{

	if(tempRimanente>0)
	{	tempRimanente--;
	lunghezzaBarra-=decrementoBarra;}
	else
		{gioco=false;
		loser=true;}

	if(tempRimanente==30)
	{
		glLightfv(GL_LIGHT0, GL_AMBIENT, coloreLuceAmbienteTicToc);
			//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, PosLuceAmbienteF);
				glFogfv(GL_FOG_COLOR, rouge);
	}
	glutTimerFunc(sec,Timer,sec);
}

void abbassaMuri(int sec )
{	if(loser)
		if(zloser>0)
			zloser--;

	glutTimerFunc(sec,abbassaMuri,sec);
}

void muoviFantasma()
{
	int mov=rand()%8;

	switch (mov) {
		case 0:
			if(labirinto[posFantasmaY+1][posFantasmaX+1]==0)
							{cout<<mov<<endl;
								posFantasmaY++;
								posFantasmaX++;
							}
			break;
		case 1:
			 if(labirinto[posFantasmaY][posFantasmaX+1]==0)
						posFantasmaX++;
			break;
		case 2:
			if(labirinto[posFantasmaY+1][posFantasmaX]==0)
						posFantasmaY++;
			break;
		case 3:
			if(labirinto[posFantasmaY-1][posFantasmaX-1]==0)
						{
							posFantasmaY--;
							posFantasmaX--;
						}
					break;
		case 4:
			if(labirinto[posFantasmaY][posFantasmaX-1]==0)
								posFantasmaX--;
					break;
		case 5:
			if(labirinto[posFantasmaY-1][posFantasmaX]==0)
								posFantasmaY--;
					break;
		case 6:
					if(labirinto[posFantasmaY+1][posFantasmaX-1]==0){
										posFantasmaY++;
										posFantasmaX--;
					}
							break;
		case 7:
					if(labirinto[posFantasmaY-1][posFantasmaX+1]==0){
										posFantasmaY--;
										posFantasmaX++;
					}break;
		default:
			break;


	}
//	if(!labirinto[posFantasmaY+1][posFantasmaX+1])
//	{
//		posFantasmaY++;
//		posFantasmaX++;
//	}
//	else if(!labirinto[posFantasmaY][posFantasmaX+1])
//			posFantasmaX++;
//	else if(!labirinto[posFantasmaY+1][posFantasmaX])
//			posFantasmaY++;
//	else
//		if(!labirinto[posFantasmaY-1][posFantasmaX-1])
//			{
//				posFantasmaY--;
//				posFantasmaX--;
//			}
//			else if(!labirinto[posFantasmaY][posFantasmaX-1])
//					posFantasmaX--;
//			else if(!labirinto[posFantasmaY-1][posFantasmaX])
//					posFantasmaY--;
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
GLfloat nextnextX(){
	return ((poscamx + 10*(velocita * cos((alpha * pgreco) / 180))));
}
GLfloat nextnextY(){
	return (poscamy + 10*(velocita * sin((alpha * pgreco) / 180)));
}
bool collisioneCuboF() {
//	GLfloat vary=0,varx=0;
//
//	((nextY()<poscamy)?vary=-0.7:vary=+0.7);
//	if(nextY()==poscamy)
//		vary=0;
//	((nextX()<poscamx)?varx=-0.7:varx=+0.7);
//	if(nextX()==poscamx)
//			varx=0;
	//cout<<labirinto[indice(nextnextY())][indice(nextnextX())]<<endl;
	if (labirinto[indice(nextnextY())][indice(nextnextX())] == 1)
		return true;
	if (labirinto[indice(nextnextY())][indice(nextnextX()+l/2)] == 1)
			return true;
	if (labirinto[indice(nextnextY()+l/2)][indice(nextnextX())] == 1)
			return true;
	if (labirinto[indice(nextnextY()-l/2)][indice(nextnextX())] == 1)
			return true;
	if (labirinto[indice(nextnextY())][indice(nextnextX()-l/2)] == 1)
			return true;
//	if(labirinto[indice(nextY()+vary)][indice(nextX()+varx)]==1)
//		return true;
	return false;
}
bool collisioneCuboC() {
	if (labirinto[indice(lastY())][indice(lastX())] == 1)
		return true;
	return false;
}
bool collisione45Gradi(){
	if(indice(poscamx+velocita)==indice(nextX())){
		if(indice(poscamy+velocita)==indice(nextY())){
			if(labirinto[indice(poscamy+velocita)][indice(poscamx+velocita)]==1)
				return true;
		}
		if(indice(poscamy-velocita)==indice(nextY())){
			if(labirinto[indice(poscamy-velocita)][indice(poscamx+velocita)]==1){
				return true;
			}
		}
	}
	if(indice(poscamx-velocita)==indice(nextX())){
			if(indice(poscamy+velocita)==indice(nextY())){
				if(labirinto[indice(poscamy+velocita)][indice(poscamx-velocita)]==1)
					return true;
			}
			if(indice(poscamy-velocita)==indice(nextY())){
				if(labirinto[indice(poscamy-velocita)][indice(poscamx-velocita)]==1)
			       return true;


			}
		}

return false;}
bool collisioneCuboDA() {
	if (labirinto[indice(nextY() + l)][indice(nextX() + (l))] == 1)
		return true;
//	if (labirinto[indice(nextY() + l-l/3)][indice(nextX() + (l))] == 1)
//			return true;
//	if (labirinto[indice(nextY() + l)][indice(nextX() + (l)-l/3)] == 1)
//			return true;
//	if (labirinto[indice(nextY() + l)][indice(nextX() + (l)+l/3)] == 1)
//			return true;
//	if (labirinto[indice(nextY() + l+l/3)][indice(nextX() + (l))] == 1)
//			return true;
	return false;
}
bool collisioneCuboSA() {
	if (labirinto[indice(nextY() + (l))][indice(nextX() - (l))] == 1)
		return true;
//	if (labirinto[indice(nextY() + (l)+l/3)][indice(nextX() - (l))] == 1)
//			return true;
//	if (labirinto[indice(nextY() + (l))][indice(nextX() - (l)+l/3)] == 1)
//			return true;
//	if (labirinto[indice(nextY() + (l)-l/3)][indice(nextX() - (l))] == 1)
//			return true;
//	if (labirinto[indice(nextY() + (l))][indice(nextX() - (l)-l/3)] == 1)
//			return true;
	return false;
}
bool collisioneCuboDB() {
	if (labirinto[indice(nextY() - (l))][indice(nextX() + (l))] == 1)
		return true;
//	if (labirinto[indice(nextY() - (l))][indice(nextX() + (l)+l/3)] == 1)
//			return true;
//	if (labirinto[indice(nextY() - (l)-l/3)][indice(nextX() + (l))] == 1)
//			return true;
//	if (labirinto[indice(nextY() - (l))][indice(nextX() + (l)-l/3)] == 1)
//			return true;
//	if (labirinto[indice(nextY() - (l)+l/3)][indice(nextX() + (l))] == 1)
//			return true;
	return false;
}
bool collisioneCuboSB() {
	if (labirinto[indice(nextY() - (l))][indice(nextX() - (l))] == 1)
		return true;
//	if (labirinto[indice(nextY() - (l)+l/3)][indice(nextX() - (l))] == 1)
//			return true;
//	if (labirinto[indice(nextY() - (l))][indice(nextX() - (l)+l/3)] == 1)
//			return true;
//	if (labirinto[indice(nextY() - (l))][indice(nextX() - (l)-l/3)] == 1)
//			return true;
//	if (labirinto[indice(nextY() - (l)-l/3)][indice(nextX() - (l))] == 1)
//			return true;
	return false;
}



bool collisioneCuboW() {


//
//	if (nextX() >= poscamx && nextY() < poscamy) {
//		return ((collisioneCuboDB()|| collisioneCuboDA()) && (collisioneCuboDB() || collisioneCuboSB())
//				&& (collisioneCuboDA() || collisioneCuboSB()));
//	}
//
//	if (nextY() < poscamy && nextX() < poscamx) {
//		//return collisioneCuboSB()||collisioneCuboDB()||collisioneCuboSA();
//		return ((collisioneCuboSB()||collisioneCuboDB())&&(collisioneCuboSB()||collisioneCuboSA())&&
//				(collisioneCuboDB()||collisioneCuboSA()));
//	}
//
//	if (nextY() >= poscamy && nextX() < poscamx) {
//		//return collisioneCuboSA()||collisioneCuboDA()||collisioneCuboSB();
//		return ((collisioneCuboSA()||collisioneCuboDA())&&(collisioneCuboSA()||collisioneCuboSB())&&
//				(collisioneCuboDA()||collisioneCuboSB()));
//
//	}
//
//	if (nextX() >= poscamx && nextY() > poscamy) {
//		//return collisioneCuboDA()||collisioneCuboDB()||collisioneCuboSA();
//		return ((collisioneCuboDA()||collisioneCuboDB())&& (collisioneCuboDA()||collisioneCuboSA())&&
//				(collisioneCuboDB()||collisioneCuboSA()));
//	}
//	if (nextX() >= poscamx && nextY() < poscamy) {
//		return ((collisioneCuboDB() && collisioneCuboDA()) || (collisioneCuboDB() && collisioneCuboSB())
//				|| (collisioneCuboDA() && collisioneCuboSB()));
//	}
//
//	if (nextY() < poscamy && nextX() < poscamx) {
//		//return collisioneCuboSB()||collisioneCuboDB()||collisioneCuboSA();
//		return ((collisioneCuboSB()&&collisioneCuboDB())||(collisioneCuboSB()&&collisioneCuboSA())||
//				(collisioneCuboDB()&&collisioneCuboSA()));
//	}
//
//	if (nextY() >= poscamy && nextX() < poscamx) {
//		//return collisioneCuboSA()||collisioneCuboDA()||collisioneCuboSB();
//		return ((collisioneCuboSA()&&collisioneCuboDA())||(collisioneCuboSA()&&collisioneCuboSB())||
//				(collisioneCuboDA()&&collisioneCuboSB()));
//
//	}
//
//	if (nextX() >= poscamx && nextY() > poscamy) {
//		//return collisioneCuboDA()||collisioneCuboDB()||collisioneCuboSA();
//		return ((collisioneCuboDA()&&collisioneCuboDB())|| (collisioneCuboDA()&&collisioneCuboSA())||
//				(collisioneCuboDB()&&collisioneCuboSA()));
//	}




//	if (nextX() >= poscamx && nextY() < poscamy) {
//		return collisioneCuboDB()||collisioneCuboDA()||collisioneCuboSB();
//	}
//
//	if (nextY() < poscamy && nextX() < poscamx) {
//		return collisioneCuboSB()||collisioneCuboDB()||collisioneCuboSA();
//	}
//
//	if (nextY() >= poscamy && nextX() < poscamx) {
//		return collisioneCuboSA()||collisioneCuboDA()||collisioneCuboSB();
//	}
//
//	if (nextX() >= poscamx && nextY() > poscamy) {
//		return collisioneCuboDA()||collisioneCuboDB()||collisioneCuboSA();
//	}


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

	return collisioneCuboDA()||collisioneCuboSA()||collisioneCuboDB()||collisioneCuboSB();


}

void rimpFantasma()
{
	if (dif > 0.2) {
			dif -= 0.005;
			//glutSolidSphere(dif,200,200);

			}
	else{
		muoviFantasma();
		ing=true;
	}


}

void setIngFalse(int sec){
	ing=false;
	glutTimerFunc(sec, setIngFalse, sec);
}


void stampaFantasma()
{

	glPushMatrix();

	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rouge);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, Speculare);
//	glMaterialfv(GL_FRONT, GL_SHININESS, reflex);


	glTranslatef(verticiGrandi[posFantasmaY][posFantasmaX].x,verticiGrandi[posFantasmaY][posFantasmaX].y,l);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	GLUquadric * q= gluNewQuadric();
	gluQuadricTexture(q,true);
	gluSphere(q,dif,200,200);

	if(!ing)
	rimpFantasma();
	else{

		ingFantasma();
	}

	glPopMatrix();

}
void ingFantasma(){
	if (dif < l/2){
			dif += 0.005;
			//glutSolidSphere(dif, 200, 200);

	}
	else{
		if(presoFantasma)
					preso();
		else
			collisioneFantasma();




	}
	}
void preso()
{
	if(!(indice(poscamy)==posOsservatoreY && indice(poscamx)==posOsservatoreX))
	{
		if(indice(poscamy)<posOsservatoreY && (indice(poscamy)!=posOsservatoreY ))
			poscamy=verticiGrandi[indice(poscamy)+1][0].y;

		else
			if((indice(poscamy)!=posOsservatoreY ))
			poscamy=verticiGrandi[indice(poscamy)-1][0].y;

		if(indice(poscamx)<posOsservatoreX && (indice(poscamx)!=posOsservatoreX ))
			poscamx=verticiGrandi[0][indice(poscamx)+1].x;

				else
					if((indice(poscamx)!=posOsservatoreX ))
					poscamx=verticiGrandi[0][indice(poscamx)-1].x;

		presoFantasma=true;
	}
	else{
		presoFantasma=false;
		gioco=true;

		posfx = poscamx + cos((alpha * pgreco) / 180);
					posfy = poscamy + sin((alpha * pgreco) / 180);
					if(alto)
					{
					traslazionex = verticiGrandi[indice(poscamy)][indice(poscamx)].x;
								traslazioney = verticiGrandi[indice(poscamy)][indice(poscamx)].y;
								labx = indice(traslazionex);
								laby = indice(traslazioney);
					}
					//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, PosLuceAmbiente);
							glFogfv(GL_FOG_COLOR, coloreNebbia);

	}




}
void collisioneFantasma(){
	if(!alto)
	{
	if(posFantasmaX-(indice(poscamx))<=1&&posFantasmaX-indice(poscamx)>=-1&&
			(posFantasmaY-indice(poscamy)<=1&&posFantasmaY-indice(poscamy)>=-1))
		{gioco=false;
		//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, PosLuceAmbienteF);
		glFogfv(GL_FOG_COLOR, rouge);
		preso();}
	}
	else
	{
		if(posFantasmaX-(indice(poscamx))<=0.7&&posFantasmaX-indice(poscamx)>=-0.7&&
			(posFantasmaY-indice(poscamy)<=0.7&&posFantasmaY-indice(poscamy)>=-0.7))
		{gioco=false;
				preso();}
	}

//	else
//		if(presoFantasma)
//		gioco=true;
//			presoFantasma=false;
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
	int g;
	((tipo == "tetto") ? z = 4.0 : z = 0.0);
	((tipo == "tetto") ? g=2 : g=0);
	glBindTexture(GL_TEXTURE_2D, textures[g]);
//	glBindTexture(GL_TEXTURE_2D, textures[g]);
	//if(tipo!="tetto")
	int i;
	((z>0)? i=-1: i=1);
	for(int q=0;q<dim;q++)
	{
		for(int p=0;p<dim;p++)
		{
			if(labirinto[q][p]!=1||loser){
					glBegin(GL_QUADS);
					glNormal3f(0,0,i);
					glTexCoord2f(0,0);
					glVertex3f(verticiGrandi[q][p].x-l/2,verticiGrandi[q][p].y-l/2,z);
					glTexCoord2f(1,0);
					glVertex3f(verticiGrandi[q][p].x+l/2,verticiGrandi[q][p].y-l/2,z);
					glTexCoord2f(1,1);
					glVertex3f(verticiGrandi[q][p].x+l/2,verticiGrandi[q][p].y+l/2,z);
					glTexCoord2f(0,1);
					glVertex3f(verticiGrandi[q][p].x-l/2,verticiGrandi[q][p].y+l/2,z);


					glEnd();

//			glBegin(GL_QUADS);
//			glTexCoord2f(0,0);
//			glVertex3f(verticiGrandi[q][p].x, verticiGrandi[q][p].y, z);
//			glTexCoord2f(0,1);
//			glVertex3f(verticiGrandi[q][p+ 1].x, verticiGrandi[q][p+1].y, z);
//			glTexCoord2f(1,1);
//			glVertex3f(verticiGrandi[q+1][p+1].x, verticiGrandi[q+ 1][p+ 1].y, z);
//			glTexCoord2f(1,0);
//			glVertex3f(verticiGrandi[q+ 1][p].x, verticiGrandi[q+ 1][p].y, z);
//			glEnd();
//		}

			}
	}
	}
//	else
//		{
//		glBegin(GL_QUADS);
//					glTexCoord2f(0,0);
//					glVertex3f(verticiGrandi[0][0].x, verticiGrandi[0][0].y, z);
//					glTexCoord2f(0,1);
//					glVertex3f(verticiGrandi[0][dim-1].x, verticiGrandi[0][dim-1].y, z);
//					glTexCoord2f(1,1);
//					glVertex3f(verticiGrandi[dim-1][dim-1].x, verticiGrandi[dim-1][dim-1].y, z);
//					glTexCoord2f(1,0);
//					glVertex3f(verticiGrandi[dim-1][0].x, verticiGrandi[dim-1][0].y, z);
//					glEnd();
//		}
}

//	glBegin(GL_QUADS);
//	glTexCoord2f(0,0);
//	glVertex3f(verticiGrandi[dim/2-1][dim/2-1].x, verticiGrandi[dim/2-1][dim/2-1].y, z);
//	glTexCoord2f(0,1);
//	glVertex3f(verticiGrandi[dim/2-1][dim - 1].x, verticiGrandi[dim/2-1][dim - 1].y, z);
//	glTexCoord2f(1,1);
//	glVertex3f(verticiGrandi[dim - 1][dim - 1].x, verticiGrandi[dim - 1][dim - 1].y, z);
//		glTexCoord2f(1,0);
//		glVertex3f(verticiGrandi[dim - 1][dim/2-1].x, verticiGrandi[dim - 1][dim/2-1].y, z);
//		glEnd();


//}

void disegnaParete(float a1, float a2,float b, string parete,GLfloat z,int i) {


	if(parete=="o"){
		glBegin(GL_QUADS);
			glNormal3f(0,i ,0 );
		glTexCoord2f(0,1);
		glVertex3f(a1, b, z+l);
		glTexCoord2f(1,1);
		glVertex3f(a2, b, z+l);
		glTexCoord2f(1,0);
		glVertex3f(a2, b, z);
		glTexCoord2f(0,0);
		glVertex3f(a1, b, z);






		glEnd();
		/*for(int i=a1;i<=a2;i++)
			verticiGrandi[i][b].muro=true;*/

		}
	else {

		glBegin(GL_QUADS);
		glNormal3f(i,0 ,0 );
			glTexCoord2f(0,0);
			glVertex3f(b, a1, z);
			glTexCoord2f(0,1);
			glVertex3f(b, a1,z+l);
			glTexCoord2f(1,1);
			glVertex3f(b, a2, z+l);
			glTexCoord2f(1,0);
			glVertex3f(b, a2, z);

		glEnd();
		/*for(int i=a1;i<=a2;i++)
					verticiGrandi[b][i].muro=true;*/

	}

}

void tappi(int z,int k,int o)
{
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0);

	glVertex3f(verticiGrandi[k][o].x-l/2,verticiGrandi[k][o].y-l/2,z);
	glTexCoord2f(1,0);
	glVertex3f(verticiGrandi[k][o].x+l/2,verticiGrandi[k][o].y-l/2,z);
	glTexCoord2f(1,1);
	glVertex3f(verticiGrandi[k][o].x+l/2,verticiGrandi[k][o].y+l/2,z);
	glTexCoord2f(0,1);
	glVertex3f(verticiGrandi[k][o].x-l/2,verticiGrandi[k][o].y+l/2,z);


	glEnd();

}

void disengnaLabirinto()
{
//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, Speculare);
//	glMaterialfv(GL_FRONT, GL_SHININESS, reflex);


//glColor3f(1,1,1);
int z=0;
int zmax;
((alto)?zmax=1:zmax=4);
if(loser)
{
	zmax=zloser;}
glBindTexture(GL_TEXTURE_2D, textures[1]);
	for(unsigned int k=0;k<dim;k++)
		for(unsigned int o=0;o<dim;o++)
		{
			if(labirinto[k][o]==1)
			{


				while(z<zmax)
				{

				disegnaParete(verticiGrandi[k][o].x-l/2,verticiGrandi[k][o].x+l/2,verticiGrandi[k][o].y+l/2,"o",z,+1);
				disegnaParete(verticiGrandi[k][o].x-l/2,verticiGrandi[k][o].x+l/2,verticiGrandi[k][o].y-l/2,"o",z,-1);
				disegnaParete(verticiGrandi[k][o].y+l/2,verticiGrandi[k][o].y-l/2,verticiGrandi[k][o].x-l/2,"v",z,-1);
				disegnaParete(verticiGrandi[k][o].y+l/2,verticiGrandi[k][o].y-l/2,verticiGrandi[k][o].x+l/2,"v",z,+1);


				z+=l;
				}
				tappi(z,k,o);
				z=0.0;
				tappi(z,k,o);

			}

		}

	if(loser)
		glutPostRedisplay();

//	unsigned int rigaVertice,colonnaVertice1,colonnaVertice2;
//	for(unsigned int i=0;i<dim-1;i++)
//	{
//		for(unsigned int j=1;j<dim;j++)
//		{
//			rigaVertice=i;
//			if(labirinto[i][j]==1)
//			{
//
//				colonnaVertice1=j;
//				while(labirinto[i][j]==1 && j<dim)
//				{
//
//					colonnaVertice2=j;
//					j++;
//				}
//				if (colonnaVertice1==colonnaVertice2)
//					colonnaVertice2+=1;
//
//			disegnaParete(colonnaVertice1,colonnaVertice2,rigaVertice,"o");
//			disegnaParete(colonnaVertice1,colonnaVertice2,i+1,"o");
//			disegnaParete(i,i+1,colonnaVertice1,"v");
//			disegnaParete(i,i+1,colonnaVertice2,"v");
//
//			/*glBegin(GL_QUADS);
//				glVertex3f(verticiGrandi[i][colonnaVertice1].x, verticiGrandi[i][colonnaVertice1].y, 5.0);
//				glVertex3f(verticiGrandi[i][colonnaVertice2].x, verticiGrandi[i][colonnaVertice2].y, 5.0);
//				glVertex3f(verticiGrandi[i+1][colonnaVertice2].x, verticiGrandi[i+1][colonnaVertice2].y, 5.0);
//				glVertex3f(verticiGrandi[i+1][colonnaVertice1].x, verticiGrandi[i+1][colonnaVertice1].y, 5.0);
//			glEnd();*/
//
//
//
//			}
//		}
//
//	}
}


/*void disengnaLabirinto(Vertice vertici[][dim]) {
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rouge);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Speculare);
	glMaterialfv(GL_FRONT, GL_SHININESS, reflex);
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

}*/
void disegnaStanza() {

	//glColor3f(1, 0, 0);
//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, nero);
//		glMaterialfv(GL_FRONT, GL_SPECULAR, Speculare);
//		glMaterialfv(GL_FRONT, GL_SHININESS, reflex);

	if (!alto)
		disegnaPiano("tetto");

	disegnaPiano("pavimento");

	//glColor3f(0, 0, 0);

	//disengnaLabirinto(verticiGrandi);

	disengnaLabirinto();


}

//
//
//void glutTimerFunc(unsigned int msec,,0){
//
//}

void TempoRotazione(int secondi)
{
	rotate = (rotate +2) % 360;


	glutTimerFunc(secondi, TempoRotazione, secondi);
}


void disegnaCubo(int  i)
{

					GLfloat h=l/2;
					x1=h*di;
					yh1=(-1*h)*di;
					x2=(-1*h)*di;
					yh2=(h)*di;
					x3=(-1*h)*di;
					yh3=(-1*h)*di;
					x4=h*di;
					yh4=h*di;
					glBindTexture(GL_TEXTURE_2D, textures[i]);

					GLfloat l1=l-(h*di);
							GLfloat l2=l+(h*di);
							glBegin(GL_QUADS);
									glNormal3f(-1,0, 0 );
									glTexCoord2f(1,0);
									glVertex3f(x1,yh1,l1);
									glTexCoord2f(1,1);
									glVertex3f(x1, yh1, l2);
									glTexCoord2f(0,1);
									glVertex3f(x3, yh3,l2);
									glTexCoord2f(0,0);
									glVertex3f(x3, yh3, l1);
									glEnd();
									glBegin(GL_QUADS);
									glNormal3f(0,1 ,0 );
									glTexCoord2f(1,0);
									glVertex3f(x3,yh3,l1);
									glTexCoord2f(1,1);
									glVertex3f(x3, yh3, l2);
									glTexCoord2f(0,1);
									glVertex3f(x2, yh2,l2);
									glTexCoord2f(0,0);
									glVertex3f(x2, yh2, l1);
									glEnd();

									glBegin(GL_QUADS);
									glNormal3f(0,-1 ,0 );
									glTexCoord2f(0,0);
									glVertex3f(x2,yh2,l1);
									glTexCoord2f(0,1);
									glVertex3f(x2, yh2, l2);
									glTexCoord2f(1,1);
									glVertex3f(x4, yh4,l2);
									glTexCoord2f(1,0);
									glVertex3f(x4, yh4, l1);
									glEnd();

									glBegin(GL_QUADS);
									glNormal3f(-1,0 ,0 );
									glTexCoord2f(0,0);
									glVertex3f(x4,yh4,l1);
									glTexCoord2f(0,1);
									glVertex3f(x4, yh4, l2);
									glTexCoord2f(1,1);
									glVertex3f(x1, yh1,l2);
									glTexCoord2f(1,0);
									glVertex3f(x1, yh1, l1);
									glEnd();

									glBegin(GL_QUADS);
								    glNormal3f(0,0 ,1 );
									glTexCoord2f(0,0);
									glVertex3f(x1,yh1,l2);
									glTexCoord2f(0,1);
									glVertex3f(x3, yh3, l2);
									glTexCoord2f(1,1);
									glVertex3f(x2, yh2,l2);
									glTexCoord2f(1,0);
									glVertex3f(x4, yh4, l2);
									glEnd();

									glBegin(GL_QUADS);
									glNormal3f(0,0 ,-1 );
									glTexCoord2f(0,0);
									glVertex3f(x1,yh1,l1);
									glTexCoord2f(0,1);
									glVertex3f(x3, yh3, l1);
									glTexCoord2f(1,1);
									glVertex3f(x2, yh2,l1);
									glTexCoord2f(1,0);
									glVertex3f(x4, yh4, l1);
									glEnd();

}

void rimp() {
	if (di > 0.2) {
		di -= 0.005;
		disegnaCubo(3);
		//glutSolidCube(di);
		//glutPostRedisplay();
		dis = di;
	} else {
		if (dis < 0.8)
			dis += 0.005;
		glBindTexture(GL_TEXTURE_2D, textures[6]);

	glTranslatef(0,0, 1);
//		glRotatef(GLfloat(rotate), 0.0, 0.0, 0.1);

		GLUquadric * q= gluNewQuadric();
		gluQuadricTexture(q,true);
		gluSphere(q,dis,200,200);
		//glutSolidSphere(dis, 200, 200);
		//glutPostRedisplay();
	}
}
void TempoFantasma(int sec)
{
	muoviFantasma();

		glutTimerFunc(sec, TempoFantasma, sec);
}




void gestisciCubo() {
//vinto();
	glPushMatrix();
	//glColor3f(1, 1, 1);
//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, bianco);
//		glMaterialfv(GL_FRONT, GL_SPECULAR, Speculare);
//		glMaterialfv(GL_FRONT, GL_SHININESS, reflex);


//	if (h == 4) {
//		rotate = (rotate + 1) % 360;
//		h = 0;
//	}coordinate(posTargetX))
//	glRotatef(0.0, 0.0, (GLfloat) rotate, 0.1);
		glTranslatef((coordinate(posTargetX)), (coordinate(posTargetY)), 0);
		glRotatef(GLfloat(rotate), 0.0, 0.0, -0.1);

	if (win) {
		rimp();

	}
	else{

		disegnaCubo(3);
		//glutSolidCube(di);
		//alphaCubo -= delta_alpha_cubo;








	}

	glPopMatrix();

	glutPostRedisplay();
	//h++;
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, bianco);
//				glMaterialfv(GL_FRONT, GL_SPECULAR, Speculare);
//				glMaterialfv(GL_FRONT, GL_SHININESS, reflex);


	glPushMatrix();

	if (!alto) {
		//gluLookAt(5,9,19.9,5, 9,0, -1.0, 0.0,-1.0);
		gluLookAt(poscamx, poscamy, poscamz, posfx, posfy, posfz, 0.0, 0.0,
				1.0);

	} else
		gluLookAt(poscamx, poscamy, 19.5, poscamx + 0.1, poscamy, poscamz, 0.0,
				0.0, -1.0);

	disegnaStanza();

	gestisciCubo();

		stampaFantasma();


	//fantasma();
	if (alto) {

		//glColor3f(1, 0, 1);
//		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);
//				glMaterialfv(GL_FRONT, GL_SPECULAR, Speculare);
//				glMaterialfv(GL_FRONT, GL_SHININESS, reflex);


		//if (!alto)
			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, textures[4]);
			glTranslatef(poscamx, poscamy, 1);
			GLUquadric * q= gluNewQuadric();
			gluQuadricTexture(q,true);
			gluSphere(q,0.5,200,200);

			glBegin(GL_QUADS);
			glTexCoord2f(0,0);
			glVertex3f(-9,-17,l*2);
			glTexCoord2f(1,0);
			glVertex3f(-9,-16,l*2);
			glTexCoord2f(1,1);
			glVertex3f(lunghezzaBarra/2,-16,l*2);
			glTexCoord2f(0,1);

			glVertex3f(lunghezzaBarra/2,-17,l*2);


			glEnd();

		glPopMatrix();
		//glPushMatrix();
		//glTranslatef(coordinate(posTargetX),coordinate(posTargetY),1);
//		glTranslatef(verticiGrandi[posTargetY][posTargetX].x,
//				verticiGrandi[posTargetY][posTargetX].y, 1);
//
//		glutSolidCube(1);
		//glPopMatrix();

	}

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

bool vicinoCubo(int intx,  int inty) {
	if (intx <= posTargetX + 2 && intx >= posTargetX - 2
			&& inty <= posTargetY + 2 && inty >= posTargetY - 2)
		{
		gioco=false;
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
		cout << collisioneCuboF() << endl;
		poscamx = nextX();
		poscamy = nextY();
		vicinoCubo(indice(poscamx), indice(poscamy));
		/*if (vicinoCubo(indice(poscamx), indice(poscamy)))
			{win = true;
			glutPostRedisplay();}*/
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
	if ( !collisioneCuboS()&&!collisioneCuboC()) {
		poscamx = lastX();
		poscamy = lastY();
		vicinoCubo(indice(poscamx), indice(poscamy));
		/*if (vicinoCubo(indice(poscamx), indice(poscamy)))
			{win = true;
			glutPostRedisplay();}*/
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
if(gioco){
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
		glDisable(GL_FOG);

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
			glEnable(GL_FOG);

		}
		glutPostRedisplay();
		break;

	case 'v':
		modalitaSemplice = true;
		if (!alto) {
			alto = true;
			prima = true;
			glDisable(GL_FOG);
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
	if(key== 27)
		exit(0);

	cout<<"x"<<poscamx<<"y"<<poscamy<<endl;


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

	poscamx=verticiGrandi[posOsservatoreY][posOsservatoreX].x;
	poscamy=verticiGrandi[posOsservatoreY][posOsservatoreX].y;
	posfx = poscamx + cos((alpha * pgreco) / 180);
	posfy = poscamy + sin((alpha * pgreco) / 180);


}


void scegliLab()
{
	int lab=rand()%3;

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
		default:
			leggiMatrice("src\\lab3.txt");
			break;
	}
}

int main(int argc, char** argv) {
	srand(time(0));
	Inizializza();
	scegliLab();
	//leggiMatrice();


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1300, 710);
	glutCreateWindow("la PERFEZIONE FATTA PIANO");
	init();

		abbassaMuri(1000);
	TempoRotazione(25);
	Timer(1000);
	setIngFalse(7000);

	//TempoFantasma(300);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutReshapeFunc(reshape);
	texture();
	glutMainLoop();
	 glDeleteTextures(numTex, textures);

	return 0;
}

