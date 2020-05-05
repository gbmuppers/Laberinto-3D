/*
 * OGL01Shape3D.cpp: 3D Shapes
 */
#include <windows.h>  // for MS Windows
#include <glut.h>  // GLUT, include glu.h and gl.h
#include <fstream> //For read files
#include <iomanip>
#include <fstream>
#include "ImageLoader.h"
#include "stdafx.h"
#include "main.h"



 /* Global variables */

static double x = 0.7, y = 0.0, z = -0.1;
static double tras = 0.1;
static double zz = 0, xx = 0;
static double r = 0;
bool salir = false;
static const char* texto = "Encuentra la salida y recoge cajitas acercándote a ellas presinando la tecla +";
static int currentAngle = 0;
static int angles[] = { 0,30,60,90,120,150,180,210,240,270,300,330 };
static int cameraValidation[72][81];
static int matriz_laberinto[24][27];

static int posz = 34, posx = 41;


static int esferas[5][2];

using namespace std;
static int contador = 0;


/* Declaramos nuestras texturas*/
GLuint _pastito, _pared, _cubito, _cielo;

/* Metodos para cargar texturas*/
GLuint loadTexture(Image* image) {
	GLuint idtextura;
	glGenTextures(1, &idtextura);
	glBindTexture(GL_TEXTURE_2D, idtextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return idtextura;
}


void initRendering() {
	Image* lado1 = loadBMP("pastito.bmp");
	_pastito = loadTexture(lado1);
	delete lado1;

	Image* lado2 = loadBMP("pared.bmp");
	_pared = loadTexture(lado2);
	delete lado2;

	Image* lado3 = loadBMP("1.bmp");
	_cubito = loadTexture(lado3);
	delete lado3;

	Image* lado4 = loadBMP("sky.bmp");
	_cielo = loadTexture(lado4);
	delete lado4;

}

void cargarTextura(GLuint _textura) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


/* Initialize OpenGL Graphics */
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void inline printString(const char *s)
{
	unsigned int i;
	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
}

void generarCubito(int x, int z) {
	glPushMatrix();
	cargarTextura(_cubito);
	glRotated(r, 0, 1, 0);
	glTranslated(xx + x, -0.5, zz + z);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	cargarTextura(_cubito);
	glRotated(r, 0, 1, 0);
	glTranslated(xx + x, -0.5, zz + z);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5, 0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	cargarTextura(_cubito);
	glRotated(r, 0, 1, 0);
	glTranslated(xx + x, -0.5, zz + z);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	cargarTextura(_cubito);
	glRotated(r, 0, 1, 0);
	glTranslated(xx + x, -0.5, zz + z);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	cargarTextura(_cubito);
	glRotated(r, 0, 1, 0);
	glTranslated(xx + x, -0.5, zz + z);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	cargarTextura(_cubito);
	glRotated(r, 0, 1, 0);
	glTranslated(xx + x, -0.5, zz + z);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5, -0.5, -0.5);
	glEnd();
	glPopMatrix();
}

void generarCubo(int xmet, int zmet) {
	glPushMatrix();
	cargarTextura(_pared);
	glRotated(r, 0, 1, 0);
	glTranslated(xx + xmet, 0.4, zz + zmet);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.5, -1.5, 1.5);
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(-1.5, 1.5, 1.5);
	glTexCoord2f(3.0f, 3.0f);
	glVertex3f(1.5, 1.5, 1.5);
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(1.5, -1.5, 1.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	cargarTextura(_pared);
	glRotated(r, 0, 1, 0);
	glTranslated(xx + xmet, 0.4, zz + zmet);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.5, 1.5, 1.5);
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(-1.5, 1.5, -1.5);
	glTexCoord2f(3.0f, 3.0f);
	glVertex3f(1.5, 1.5, -1.5);
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(1.5, 1.5, 1.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	cargarTextura(_pared);
	glRotated(r, 0, 1, 0);
	glTranslated(xx + xmet, 0.4, zz + zmet);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.5, 1.5, 1.5);
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(1.5, 1.5, -1.5);
	glTexCoord2f(3.0f, 3.0f);
	glVertex3f(1.5, -1.5, -1.5);
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(1.5, -1.5, 1.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	cargarTextura(_pared);
	glRotated(r, 0, 1, 0);
	glTranslated(xx + xmet, 0.4, zz + zmet);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.5, -1.5, 1.5);
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(-1.5, 1.5, 1.5);
	glTexCoord2f(3.0f, 3.0f);
	glVertex3f(-1.5, 1.5, -1.5);
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(-1.5, -1.5, -1.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	cargarTextura(_pared);
	glRotated(r, 0, 1, 0);
	glTranslated(xx + xmet, 0.4, zz + zmet);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.5, -1.5, 1.5);
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(-1.5, -1.5, -1.5);
	glTexCoord2f(3.0f, 3.0f);
	glVertex3f(1.5, -1.5, -1.5);
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(1.5, -1.5, 1.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	cargarTextura(_pared);
	glRotated(r, 0, 1, 0);
	glTranslated(xx + xmet, 0.4, zz + zmet);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.5, -1.5, -1.5);
	glTexCoord2f(3.0f, 0.0f);
	glVertex3f(-1.5, 1.5, -1.5);
	glTexCoord2f(3.0f, 3.0f);
	glVertex3f(1.5, 1.5, -1.5);
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(1.5, -1.5, -1.5);
	glEnd();
	glPopMatrix();
}

bool checkPositionCoins(int position_1, int position_2) {
	for (int n = 0; n < 5; n++){
		if (esferas[n][0] == position_1 && esferas[n][1] == position_2){
			return false;
		}
	}
	return true;
}


void generarMoneditas() {
	srand(time(0));
	int randomNum_1,randomNum_2;
	for (int k = 0; k < 5; k++)
	{
		boolean flag = true;
		while (flag) {
			randomNum_1 = (int)rand() % 62;
			randomNum_2 = (int)rand() % 62;
			if (randomNum_1 < 72 && randomNum_2 < 81) {
				if (cameraValidation[randomNum_1][randomNum_2] == 0) {
					if (checkPositionCoins(randomNum_1, randomNum_2)) {
						esferas[k][0]=randomNum_1;
						esferas[k][1]=randomNum_2;
						printf("Numeros random: %d\n", randomNum_1);
						printf("Numeros random: %d\n", randomNum_2);
						printf("\n");
						cameraValidation[esferas[k][0]][esferas[k][1]] = 3;
						flag = false;
					}
				}
			}
		}

	}
}

void generaLaberinto()
{
	int x = -33, z = -40, i, j;

	for (i = 0; i < 24; i++)
	{
		for (j = 0; j < 27; j++)
		{
			if (matriz_laberinto[i][j] == 1)
			{
				if (!(i == 23 && j == 1 && salir))
				{
					generarCubo(x, z);
				}
			}
			x = x + 3;
		}
		z = z + 3;
		x = -33;
	}
}

void setPuntuacion() {
	if (contador == 500) {
		texto = "Fin del juego, tu puntuacion es de 500";
	} else if (contador == 400) {
		texto = "Fin del juego, tu puntuacion es de 400";
	} else if (contador == 300) {
		texto = "Fin del juego, tu puntuacion es de 300";
	} else if (contador == 200) {
		texto = "Fin del juego, tu puntuacion es de 200";
	} else if (contador == 100) {
		texto = "Fin del juego, tu puntuacion es de 100";
	}else {
		texto = "Fin del juego, tu puntuacion es de 0";
	}

}


static void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '+':
		if ((r >= 0 && r <= 30) || r == 330)
		{
			int masx = posx - 1;
			int masz = posz;
			if (cameraValidation[masx][masz]==3) {
				texto = "Lo tienes, más 100 puntos";
				contador += 100;
				cameraValidation[masx][masz] = 0;
			}
		}
		if (r >= 60 && r <= 120)
		{
			int masx = posx;
			int masz = posz + 1;
			if (cameraValidation[masx][masz]==3) {
				texto = "Lo tienes, más 100 puntos";
				contador += 100;
				cameraValidation[masx][masz] = 0;
			}
		}
		if (r >= 150 && r <= 210)
		{
			int masx = posx + 1;
			int masz = posz;
			if (cameraValidation[masx][masz]==3) {
				texto = "Lo tienes, más 100 puntos";
				contador += 100;
				cameraValidation[masx][masz] = 0;
			}
		}
		if (r >= 240 && r <= 300)
		{
			int masx = posx;
			int masz = posz - 1;
			if (cameraValidation[masx][masz]==3) {
				texto = "Lo tienes, más 100 puntos";
				contador += 100;
				cameraValidation[masx][masz] = 0;
			}
		}
		break;
	case '-':
		//zz = zz - 1.5;
		break;
	case 'a':

		if (currentAngle == 0)
		{
			currentAngle = 11;
			r = angles[currentAngle];
		}

		else {
			currentAngle = currentAngle - 1;
			r = angles[currentAngle];
		}
		break;
	case 'd':

		if (currentAngle == 0)
		{
			currentAngle = 1;
			r = angles[currentAngle];
		}
		else if (currentAngle == 11)
		{
			currentAngle = 0;
			r = angles[currentAngle];
		}
		else {
			currentAngle = currentAngle + 1;
			r = angles[currentAngle];
		}
		break;

	case 'w':
		texto = " ";

		if ((r >= 0 && r <= 30) || r == 330)
		{
			int masx = posx - 1;
			int masz = posz;
			if (cameraValidation[masx][masz] != 1 && cameraValidation[masx][masz] != 3)
			{
				zz = zz + 1;
				posx = posx - 1;
			}
			if ((masx == 71 && masz == 3) || (masx == 71 && masz == 4) || (masx == 71 && masz == 5))
			{
				
				setPuntuacion();
				exit(0);
			}

		}
		if (r >= 60 && r <= 120)
		{
			int masx = posx;
			int masz = posz + 1;
			if (cameraValidation[masx][masz] != 1 && cameraValidation[masx][masz] != 3)
			{
				xx = xx - 1;
				posz = posz + 1;
			}
			if ((masx == 71 && masz == 3) || (masx == 71 && masz == 4) || (masx == 71 && masz == 5))
			{

				setPuntuacion();
				exit(0);
			}


		}
		if (r >= 150 && r <= 210)
		{
			int masx = posx + 1;
			int masz = posz;
			if (cameraValidation[masx][masz] != 1 && cameraValidation[masx][masz] != 3)
			{
				zz = zz - 1;
				posx = posx + 1;
			}
			if ((masx == 71 && masz == 3) || (masx == 71 && masz == 4) || (masx == 71 && masz == 5))
			{

				setPuntuacion();
				exit(0);
			}

		}
		if (r >= 240 && r <= 300)
		{
			int masx = posx;
			int masz = posz - 1;
			if (cameraValidation[masx][masz] != 1 && cameraValidation[masx][masz] != 3)
			{
				xx = xx + 1;
				posz = posz - 1;
			}
			if ((masx == 71 && masz == 3) || (masx == 71 && masz == 4) || (masx == 71 && masz == 5))
			{

				setPuntuacion();
				exit(0);
			}

		}

		break;
	}

	glutPostRedisplay();
}


/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glColor3f(1.0f, 0.5f, 0.0f);     // Orange

	glColor3d(0.5, 0.5, 0.5);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);

	generaLaberinto(); //Genera el laberinto con cubos :D

	glColor3d(0.5, 0.5, 0.5);
	glPushMatrix();
	cargarTextura(_pastito);
	glRotated(r, 0, 1, 0);
	glTranslated(xx, 0.4, zz);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-33, -1.6, -42);
	glTexCoord2f(100.0f, 0.0f);
	glVertex3f(48, -1.6, -42);
	glTexCoord2f(100.0f, 100.0f);
	glVertex3f(48, -1.6, 30);
	glTexCoord2f(0.0f, 100.0f);
	glVertex3f(-33, -1.6, 30);
	glEnd();
	glPopMatrix();

	glColor3d(0.5, 0.5, 0.5);
	glPushMatrix();
	cargarTextura(_cielo);
	cargarTextura(_cielo);
	glRotated(r, 0, 1, 0);
	glTranslated(xx, 15, zz);



	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-43, -11.6, -52);
	glTexCoord2f(100.0f, 0.0f);
	glVertex3f(58, -11.6, -52);
	glTexCoord2f(100.0f, 100.0f);
	glVertex3f(58, -11.6, 40);
	glTexCoord2f(0.0f, 100.0f);
	glVertex3f(-43, -11.6, 40);
	glEnd();
	glPopMatrix();

	int x = -34, z = -41, i, j;

	for (i = 0; i < 72; i++)
	{
		for (j = 0; j < 81; j++)
		{
			if (cameraValidation[i][j] == 3)
			{
				glColor3d(0.6, 0.6, 0.6);
				generarCubito(x, z);
			}
			x = x + 1;
		}
		z = z + 1;
		x = -34;
	}


	glColor3d(256, 266, 256);
	glRasterPos3f(-0.4, 0, -1);

	printString(texto);

	glutSwapBuffers();
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(int width, int height) {
	const float ar = (float)width / (float)height;
	double aspect = height / width;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

static void idle(void) {
	glutPostRedisplay();
}


/*Va por un archivo txt con un contenido de 1 y 0 que nos ayuda a generar una matriz que
servirá como guía para crear el laberinto, más, los lugares por donde es permisible que pase
el jugador*/
void laberintosTXT(const char* fileName) {
	ifstream inFile;
	inFile.open(fileName);
	if (!inFile) {
		printf("Unable to open");
		exit(1); // terminate with error
	}
	int i, j, x;
	i = j = x = 0;
	while (inFile >> x) {
		matriz_laberinto[j][i] = x;
		i++;
		if (i > 26) {
			i = 0;
			j++;
		}
	}
	inFile.close();
	int value;
	for (i = 0; i < 24; i++) {
		for (j = 0; j < 27; j++) {
			value = matriz_laberinto[i][j];
			cameraValidation[i * 3][j * 3] = value;
			cameraValidation[i * 3 + 1][j * 3] = value;
			cameraValidation[i * 3 + 2][j * 3] = value;

			cameraValidation[i * 3][j * 3 + 1] = value;
			cameraValidation[i * 3 + 1][j * 3 + 1] = value;
			cameraValidation[i * 3 + 2][j * 3 + 1] = value;

			cameraValidation[i * 3][j * 3 + 2] = value;
			cameraValidation[i * 3 + 1][j * 3 + 2] = value;
			cameraValidation[i * 3 + 2][j * 3 + 2] = value;
		}
		salir = true;
		cameraValidation[69][3] = 0;
		cameraValidation[69][4] = 0;
		cameraValidation[69][5] = 0;
		cameraValidation[70][3] = 0;
		cameraValidation[70][4] = 0;
		cameraValidation[70][5] = 0;
		cameraValidation[71][3] = 0;
		cameraValidation[71][4] = 0;
		cameraValidation[71][5] = 0;
	}
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	//Cargamos el laberinto desde un .txt :D
	//Solo tenemos dos, pero fueron hechos con mucho amor xd
	laberintosTXT("laberinto2.txt");
	generarMoneditas();
	glutInit(&argc, argv);
	glutInitWindowSize(1900, 5000);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Laberinto - Proyecto final - Graficacion");
	glutSetCursor(GLUT_CURSOR_NONE);
	initRendering();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	glClearColor(0, 0.5, 0.7, 1);
	glutMainLoop();
	return 0;
}