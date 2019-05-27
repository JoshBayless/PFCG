#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "cmodel/CModel.h"


static GLuint ciudad_display_list;	//Display List for the monito1


CFiguras mi_figura;
//NEW// Keyframes

//Variables de dibujo y manipulacion
float posX = 0, posY = 2.5, posZ = -3.5, rotRodIzq = 0, rotRodDer = 0, rotManIzq = 0, rotManDer = 0, rotaCuello = 0;
float giromonito1 = 0;

//variables de dibujo y manipulación de balón
float posXBal=0, posYBal=0.48, posZBal=0;

float colorR = 1.0, colorG = 1.0, colorB = 1.0; // Color escenario


#define MAX_FRAMES 15
int i_max_steps = 90;
int i_curr_steps = 0;

typedef struct _frame
{

	//monito1 COMPLETO

	float posX;		
	float posY;		
	float posZ;		
	float incX;		
	float incY;		
	float incZ;		
	
	//monito1 PARTES

	float rotRodIzq;
	float rotRodDer;
	float rotManIzq;
	float rotManDer;
	float incRotMD;
	float incRotMI;
	float incRotRD;
	float rotInc;
	float giromonito1;
	float giromonito1Inc;
	float rotaCuello;
	float incRotaCuello;
	

	//BALON
	float posXBal;
	float posYBal;
	float posZBal;
	float IncXBal;
	float IncYBal;
	float IncZBal;

	
	
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=0;			//introducir datos
bool play=true;
int playIndex=0;




int w = 500, h = 500;
int frame=0,time,timebase=0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

long int font=(long int)GLUT_BITMAP_HELVETICA_18;



//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

/*
GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = {22};
*/


CTexture text1;
CTexture text2; //Acero
CTexture text3;	//Asfalto
CTexture text4;	//Pavimento
CTexture text5;	//Pasto
CTexture text6;	//Casa01
CTexture text7;	//textura cemento
CTexture text8;	//textura blanca
CTexture text9; //Ciudad
CTexture campoText;	//textura para campo de futbol
CTexture balonText; //textura para balon de futbol
CTexture textUNAM;
CTexture textCA;
CTexture textArbol;
CTexture textArbusto;
CTexture textCamino;
CTexture textEscalera;
CTexture textTunel;
CTexture textCarretera;
CTexture textCasa1;
CTexture textCasa2;
CTexture textCasa3;
CTexture textCasa4;


CTexture textSkyboxFrontal;
CTexture textSkyboxAtras;
CTexture textSkyboxIzquierda;
CTexture textSkyboxDerecha;
CTexture textSkyboxArriba;


CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;
CFiguras jugador;	//Para crear monito1
CFiguras figBalon;		//Para crear balon


void saveFrame(void)
{
	printf("frameindex %d\n", FrameIndex);


	//monito1 COMPLETO
	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	printf("\n Indice de Frame posicion: %d\n", FrameIndex);
	printf("\n\t Posicion x: %g", KeyFrame[FrameIndex].posX);
	printf("\n\t Posicion y: %g", KeyFrame[FrameIndex].posY);
	printf("\n\t Posicion z: %g", KeyFrame[FrameIndex].posZ);

	//monito1 PARTES
	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].rotRodDer = rotRodDer;
	KeyFrame[FrameIndex].rotManIzq = rotManIzq;
	KeyFrame[FrameIndex].rotManDer = rotManDer;
	KeyFrame[FrameIndex].giromonito1 = giromonito1;
	KeyFrame[FrameIndex].rotaCuello = rotaCuello;

	printf("\n monito partes: %d\n", FrameIndex);
	printf("\n\t Posicion rotRodIzq: %g", KeyFrame[FrameIndex].rotRodIzq);
	printf("\n\t Posicion rotRodDer: %g", KeyFrame[FrameIndex].rotRodDer);
	printf("\n\t Posicion rotManIzq: %g", KeyFrame[FrameIndex].rotManIzq);
	printf("\n\t Posicion rotManIzq: %g", KeyFrame[FrameIndex].rotManDer);
	printf("\n\t Posicion rotManIzq: %g", KeyFrame[FrameIndex].giromonito1);
	printf("\n\t Posicion rotManIzq: %g", KeyFrame[FrameIndex].rotaCuello);

	//BALON
	KeyFrame[FrameIndex].posXBal = posXBal;
	KeyFrame[FrameIndex].posYBal = posYBal;
	KeyFrame[FrameIndex].posZBal = posZBal;

	printf("\n balon: %d\n", FrameIndex);
	printf("\n\t Posicion posxbal: %g", KeyFrame[FrameIndex].posXBal);
	printf("\n\t Posicion posybal: %g", KeyFrame[FrameIndex].posYBal);
	printf("\n\t Posicion poszbal: %g", KeyFrame[FrameIndex].posZBal);

	FrameIndex++;
}

void resetElements(void)
{
	//monito1 COMPLETO
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;


	//monito1 PARTES
	rotRodIzq = KeyFrame[0].rotRodIzq;
	rotRodDer = KeyFrame[0].rotRodDer;
	rotManIzq = KeyFrame[0].rotManIzq;
	rotManDer = KeyFrame[0].rotManDer;
	giromonito1 = KeyFrame[0].giromonito1;
	rotaCuello = KeyFrame[0].rotaCuello;

	//BALON
	posXBal = KeyFrame[0].posXBal;
	posYBal = KeyFrame[0].posYBal;
	posZBal = KeyFrame[0].posZBal;
}

void interpolation(void)
{
	//monito1 COMPLETO
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	//monito1 PARTES
	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	KeyFrame[playIndex].incRotRD = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;
	KeyFrame[playIndex].incRotMI = (KeyFrame[playIndex + 1].rotManIzq - KeyFrame[playIndex].rotManIzq) / i_max_steps;
	KeyFrame[playIndex].incRotMD = (KeyFrame[playIndex + 1].rotManDer - KeyFrame[playIndex].rotManDer) / i_max_steps;
	KeyFrame[playIndex].giromonito1Inc = (KeyFrame[playIndex + 1].giromonito1 - KeyFrame[playIndex].giromonito1) / i_max_steps;
	KeyFrame[playIndex].incRotaCuello = (KeyFrame[playIndex + 1].rotaCuello - KeyFrame[playIndex].rotaCuello) / i_max_steps;

	//información de frame para balón
	KeyFrame[playIndex].IncXBal = (KeyFrame[playIndex + 1].posXBal - KeyFrame[playIndex].posXBal) / i_max_steps;
	KeyFrame[playIndex].IncYBal = (KeyFrame[playIndex + 1].posYBal - KeyFrame[playIndex].posYBal) / i_max_steps;
	KeyFrame[playIndex].IncZBal = (KeyFrame[playIndex + 1].posZBal - KeyFrame[playIndex].posZBal) / i_max_steps;
}


void ciudad ()
{


		glPushMatrix(); //Campo
			glScalef(54, 0.1, 36);
			glDisable(GL_LIGHTING);
			fig3.prisma2(campoText.GLindex, campoText.GLindex);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //Pasto
			glScalef(57, 0.09, 39);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text5.GLindex, text5.GLindex);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glPushMatrix(); //CIUDAD
			glScalef(200, 0.01, 200);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text3.GLindex, text3.GLindex);
			glEnable(GL_LIGHTING);
		glPopMatrix();

	//	glPushMatrix(); //poste1


		/*

		//LUMNIARIAS
		

	glPushMatrix();
	
		glPushMatrix();
			glTranslatef(0.0, 0.0, 0.0);
			fig4.cilindro(0.4, 10.0, 30.0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.5, 10.0, 0.0);
			glRotatef(90, 1, 0, 0);
			glRotatef(90, 0, 0, 1);
			fig4.cilindro(0.2, 5.0, 30.0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.5, 13.0, 0.0);
			glRotatef(90, 1, 0, 0);
			glRotatef(90, 0, 0, 1);
			fig4.cilindro(0.2, 5.0, 30.0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.5, 10.0, 0.0);
			fig4.cilindro(0.2, 3.0, 30.0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-2.5, 10.0, 0.0);
			fig4.cilindro(0.2, 3.0, 30.0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.5, 12.0, 0.0);
			glRotatef(90, 1, 0, 0);
			glRotatef(90, 0, 0, 1);
			fig4.cilindro(0.2, 5.0, 30.0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.5, 11.0, 0.0);
			glRotatef(90, 1, 0, 0);
			glRotatef(90, 0, 0, 1);
			fig4.cilindro(0.2, 5.0, 30.0, 0);
		glPopMatrix();

		*/

	//glPopMatrix();


		//glPopMatrix();
}

void bandera(void) {

	glBegin(GL_TRIANGLES); //INICIO DE FUNCION PARA LA CREACION DE UNA FIGURA DE 3 VERTICES
		glVertex3f(0.0f, 1.0f, 0.0f); //PRIMER VERTICE
		glVertex3f(0.0f, 2.0f, 0.0f); //SEGUNDO VERTICE
		glVertex3f(0.0f, 1.5f, 2.0f); //TERCER VERTICE
	glEnd(); //FIN DE FUNCION, EN ESTE CASO SE GENERA UN TRIANGULO

}

void banderin() {


	glPushMatrix();
		glTranslatef(24.7, 0.0, 16.0);
		fig4.cilindro(0.1, 2.0, 10.0, 0);
		bandera();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-24.7, 0.0, -16.0);
		fig4.cilindro(0.1, 2.0, 10.0, 0);
		bandera();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-24.7, 0.0, 16.0);
		fig4.cilindro(0.1, 2.0, 10.0, 0);
		bandera();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(24.7, 0.0, -16.0);
		fig4.cilindro(0.1, 2.0, 10.0, 0);
		bandera();
	glPopMatrix();
}

void Grada() {

	//PRIMERO_ESQUINA
	glPushMatrix(); //Grada frontal
		glTranslatef(30.0, 1.0, -21.0);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 3);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(30.0, 1.0, -19.5);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 1, 3);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();


	//SEGUNDO_ESQUINA
	glPushMatrix(); //Grada frontal
		glTranslatef(30.0, 2.0, -23.0);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 5);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(32.0, 2.0, -21.5);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 5, 5);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	
	//TERCER_ESQUINA
	glPushMatrix(); //Grada frontal
		glTranslatef(31, 3.0, -25.0);
		glRotatef(90, 1, 0, 0);
		glScalef(4, 2, 7);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(34.0, 3.0, -22.5);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 7, 7);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();
	
	//CUARTA_ESQUINA
	glPushMatrix(); //Grada frontal
		glTranslatef(32, 4.0, -27.0);
		glRotatef(90, 1, 0, 0);
		glScalef(6, 2, 9);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(36.0, 4.0, -23.5);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 9, 9);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//QUINTA_ESQUINA
	glPushMatrix(); //Grada frontal
		glTranslatef(33, 5.0, -29.0);
		glRotatef(90, 1, 0, 0);
		glScalef(8, 2, 11);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(38.0, 5.0, -24.5);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 11, 11);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//GRADA FONDO
	glPushMatrix(); //Grada frontal
		glTranslatef(0.0, 1.0, -21.0);
		glRotatef(90, 1, 0, 0);
		glScalef(58, 2.0, 3);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(0.0, 2.0, -23.0);
		glRotatef(90, 1, 0, 0);
		glScalef(58, 2.0, 5);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix(); //Grada frontal
		glTranslatef(0.0, 3.0, -25.0);
		glRotatef(90, 1, 0, 0);
		glScalef(58, 2.0, 7);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(0.0, 4.0, -27.0);
		glRotatef(90, 1, 0, 0);
		glScalef(58, 2.0, 9);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(0.0, 5.0, -29.0);
		glRotatef(90, 1, 0, 0);
		glScalef(58, 2.0, 11);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//GRADA FONDO

	//PRIMERO_ESQUINA
	glPushMatrix(); //Grada frontal
		glTranslatef(-30.0, 1.0, -21.0);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 3);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(-30.0, 1.0, -19.5);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 1, 3);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();


	//SEGUNDO_ESQUINA
	glPushMatrix(); //Grada frontal
		glTranslatef(-30.0, 2.0, -23.0);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 2, 5);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(-32.0, 2.0, -21.5);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 5, 5);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();


	//TERCER_ESQUINA
	glPushMatrix(); //Grada frontal
		glTranslatef(-31, 3.0, -25.0);
		glRotatef(90, 1, 0, 0);
		glScalef(4, 2, 7);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(-34.0, 3.0, -22.5);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 7, 7);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//CUARTA_ESQUINA
	glPushMatrix(); //Grada frontal
		glTranslatef(-32, 4.0, -27.0);
		glRotatef(90, 1, 0, 0);
		glScalef(6, 2, 9);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(-36.0, 4.0, -23.5);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 9, 9);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//QUINTA_ESQUINA
	glPushMatrix(); //Grada frontal
		glTranslatef(-33, 5.0, -29.0);
		glRotatef(90, 1, 0, 0);
		glScalef(8, 2, 11);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(-38.0, 5.0, -24.5);
		glRotatef(90, 1, 0, 0);
		glScalef(2, 11, 11);
		glDisable(GL_LIGHTING);
		fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();


	//GRADA FRENTE
	glPushMatrix(); //Grada frontal
		glTranslatef(0.0, 1, 21.0);
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 0, 1);
		glScalef(58, 2.0, 3);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(0.0, 2.0, 23.0);
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 0, 1);
		glScalef(58, 2.0, 5);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix(); //Grada frontal
		glTranslatef(0.0, 3.0, 25.0);
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 0, 1);
		glScalef(58, 2.0, 7);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(0.0, 4.0, 27.0);
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 0, 1);
		glScalef(58, 2.0, 9);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(0.0, 5.0, 29.0);
		glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 0, 1);
		glScalef(58, 2.0, 11);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//GRADA FRENTE

	//PRIMERO_ESQUINA
	glPushMatrix(); //Grada frontal
	glTranslatef(-30.0, 1.0, 21.0);
	glRotatef(90, 1, 0, 0);
	glScalef(2, 2, 3);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
	glTranslatef(-30.0, 1.0, 19.5);
	glRotatef(90, 1, 0, 0);
	glScalef(2, 1, 3);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	//SEGUNDO_ESQUINA
	glPushMatrix(); //Grada frontal
	glTranslatef(-30.0, 2.0, 23.0);
	glRotatef(90, 1, 0, 0);
	glScalef(2, 2, 5);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
	glTranslatef(-32.0, 2.0, 21.5);
	glRotatef(90, 1, 0, 0);
	glScalef(2, 5, 5);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	//TERCER_ESQUINA
	glPushMatrix(); //Grada frontal
	glTranslatef(-31, 3.0, 25.0);
	glRotatef(90, 1, 0, 0);
	glScalef(4, 2, 7);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
	glTranslatef(-34.0, 3.0, 22.5);
	glRotatef(90, 1, 0, 0);
	glScalef(2, 7, 7);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//CUARTA_ESQUINA
	glPushMatrix(); //Grada frontal
	glTranslatef(-32, 4.0, 27.0);
	glRotatef(90, 1, 0, 0);
	glScalef(6, 2, 9);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
	glTranslatef(-36.0, 4.0, 23.5);
	glRotatef(90, 1, 0, 0);
	glScalef(2, 9, 9);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//QUINTA_ESQUINA
	glPushMatrix(); //Grada frontal
	glTranslatef(-33, 5.0, 29.0);
	glRotatef(90, 1, 0, 0);
	glScalef(8, 2, 11);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
	glTranslatef(-38.0, 5.0, 24.5);
	glRotatef(90, 1, 0, 0);
	glScalef(2, 11, 11);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	//GRADA DERECHA
	glPushMatrix(); //Grada frontal
		glTranslatef(30.0, 1.0, 0.0);
		glRotatef(270, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(38, 2.0, 3);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(32.0, 2.0, 0.0);
		glRotatef(270, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(38, 2.0, 5);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(34.0, 3.0, 0.0);
		glRotatef(270, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(38, 2.0, 7);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(36.0, 4.0, 0.0);
		glRotatef(270, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(38, 2.0, 9);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(38.0, 5.0, 0.0);
		glRotatef(270, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(38, 2.0, 11);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//GRADA DERECHA

	//PRIMERO_ESQUINA
	glPushMatrix(); //Grada frontal
	glTranslatef(30.0, 1.0, 21.0);
	glRotatef(90, 1, 0, 0);
	glScalef(2, 2, 3);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);;
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
	glTranslatef(30.0, 1.0, 19.5);
	glRotatef(90, 1, 0, 0);
	glScalef(2, 1, 3);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	//SEGUNDO_ESQUINA
	glPushMatrix(); //Grada frontal
	glTranslatef(30.0, 2.0, 23.0);
	glRotatef(90, 1, 0, 0);
	glScalef(2, 2, 5);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
	glTranslatef(32.0, 2.0, 21.5);
	glRotatef(90, 1, 0, 0);
	glScalef(2, 5, 5);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	//TERCER_ESQUINA
	glPushMatrix(); //Grada frontal
	glTranslatef(31, 3.0, 25.0);
	glRotatef(90, 1, 0, 0);
	glScalef(4, 2, 7);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
	glTranslatef(34.0, 3.0, 22.5);
	glRotatef(90, 1, 0, 0);
	glScalef(2, 7, 7);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//CUARTA_ESQUINA
	glPushMatrix(); //Grada frontal
	glTranslatef(32, 4.0, 27.0);
	glRotatef(90, 1, 0, 0);
	glScalef(6, 2, 9);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
	glTranslatef(36.0, 4.0, 23.5);
	glRotatef(90, 1, 0, 0);
	glScalef(2, 9, 9);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//QUINTA_ESQUINA
	glPushMatrix(); //Grada frontal
	glTranslatef(33, 5.0, 29.0);
	glRotatef(90, 1, 0, 0);
	glScalef(8, 2, 11);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
	glTranslatef(38.0, 5.0, 24.5);
	glRotatef(90, 1, 0, 0);
	glScalef(2, 11, 11);
	glDisable(GL_LIGHTING);
	fig5.prisma2(textEscalera.GLindex, textEscalera.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();



	//GRADA IZQUIERDA

	glPushMatrix(); //Grada frontal
		glTranslatef(-30.0, 1.0, 0.0);
		glRotatef(90, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(38, 2.0, 3);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(-32.0, 2.0, 0.0);
		glRotatef(90, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(38, 2.0, 5);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(-34.0, 3.0, 0.0);
		glRotatef(90, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(38, 2.0, 7);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(-36.0, 4.0, 0.0);
		glRotatef(90, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(38, 2.0, 9);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Grada frontal
		glTranslatef(-38.0, 5.0, 0.0);
		glRotatef(90, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glScalef(38, 2.0, 11);
		glDisable(GL_LIGHTING);
		fig5.prisma2(text7.GLindex, text6.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//GRADA IZQUIERDA

}

void porteriaD() {

	//PORTERIA DERECHA
	glPushMatrix(); //poste1
		glTranslatef(25.0, 0.0, -3.6);
		fig4.cilindro(0.1, 2.0, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //poste2
		glTranslatef(25.0, 0.0, 3.6);
		fig4.cilindro(0.1, 2.0, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //travesaño
		glTranslatef(25.0, 2.05, -3.65);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		fig4.cilindro(0.1, 7.32, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //poste2
		glTranslatef(25.0, 0.1, -3.6);
		glRotatef(270, 0, 0, 1);
		fig4.cilindro(0.1, 2.0, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //poste2
		glTranslatef(25.0, 0.1, 3.6);
		glRotatef(270, 0, 0, 1);
		fig4.cilindro(0.1, 2.0, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //travesaño
		glTranslatef(27.0, 0.1, -3.65);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		fig4.cilindro(0.1, 7.32, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //poste2
		glTranslatef(27.0, 0.1, -3.6);
		glRotatef(35, 0, 0, 1);
		fig4.cilindro(0.1, 2.4, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //poste2
		glTranslatef(27.0, 0.1, 3.6);
		glRotatef(35, 0, 0, 1);
		fig4.cilindro(0.1, 2.4, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //poste2
		glTranslatef(25.0, 2.0, -3.6);
		glRotatef(270, 0, 0, 1);
		fig4.cilindro(0.1, 0.80, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //poste2
		glTranslatef(25.0, 2.0, 3.6);
		glRotatef(270, 0, 0, 1);
		fig4.cilindro(0.1, 0.80, 30.0, 0);
	glPopMatrix();

	//PORTERIA DERECHA


}

void porteriaI() {

	//PORTERIA IZQUIERDA
	glPushMatrix(); //poste1
		glTranslatef(-25.0, 0.0, -3.6);
		fig4.cilindro(0.1, 2.0, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //poste2
		glTranslatef(-25.0, 0.0, 3.6);
		fig4.cilindro(0.1, 2.0, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //travesaño
		glTranslatef(-25.0, 2.05, -3.65);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		fig4.cilindro(0.1, 7.32, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //poste2
		glTranslatef(-25.0, 0.1, -3.6);
		glRotatef(90, 0, 0, 1);
		fig4.cilindro(0.1, 2.0, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //poste2
		glTranslatef(-25.0, 0.1, 3.6);
		glRotatef(90, 0, 0, 1);
		fig4.cilindro(0.1, 2.0, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //travesaño
		glTranslatef(-27.0, 0.1, -3.65);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		fig4.cilindro(0.1, 7.32, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //poste2
		glTranslatef(-27.0, 0.1, -3.6);
		glRotatef(325, 0, 0, 1);
		fig4.cilindro(0.1, 2.4, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //poste2
		glTranslatef(-27.0, 0.1, 3.6);
		glRotatef(325, 0, 0, 1);
		fig4.cilindro(0.1, 2.4, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //poste2
		glTranslatef(-25.0, 2.0, -3.6);
		glRotatef(90, 0, 0, 1);
		fig4.cilindro(0.1, 0.80, 30.0, 0);
	glPopMatrix();

	glPushMatrix(); //poste2
		glTranslatef(-25.0, 2.0, 3.6);
		glRotatef(90, 0, 0, 1);
		fig4.cilindro(0.1, 0.80, 30.0, 0);
	glPopMatrix();

}

void monito1()
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
	glScalef(0.5, 0.5, 0.5);
	jugador.prisma(2.0, 2.0, 1, textUNAM.GLindex);

	glPushMatrix();//Cuello
	glTranslatef(0, 1.0, 0.0);
	glRotatef(rotaCuello, 0, 0, 1);
	jugador.cilindro(0.25, 0.25, 15, 0);
	glPushMatrix();//Cabeza
	glTranslatef(0, 1.0, 0);
	jugador.esfera(0.75, 15, 15, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo derecho-->
	glTranslatef(1.25, 0.65, 0);
	jugador.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	glRotatef(-45 - rotManDer, 0, 1, 0);
	glTranslatef(0.75, 0, 0);
	jugador.prisma(0.7, 1.5, 0.7, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo izquierdo <--
	glTranslatef(-1.25, 0.65, 0);
	jugador.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(-0.25, 0, 0);
	glRotatef(45 + rotManIzq, 0, 1, 0);
	glRotatef(25, 0, 0, 1);
	glRotatef(25, 1, 0, 0);
	glTranslatef(-0.75, 0, 0);
	jugador.prisma(0.7, 1.5, 0.7, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();//Cintura
	glColor3f(0, 0, 1);
	glTranslatef(0, -1.5, 0);
	jugador.prisma(1, 2, 1, 0);

	glPushMatrix(); //Pie Derecho -->
	glTranslatef(0.75, -0.5, 0);
	glRotatef(-15, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	jugador.prisma(1.0, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15 + rotRodDer, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	jugador.prisma(1.5, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	jugador.prisma(0.2, 1.2, 1.5, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix(); //Pie Izquierdo -->
	glTranslatef(-0.75, -0.5, 0);
	glRotatef(-5, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	jugador.prisma(1.0, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15 + rotRodIzq, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	jugador.prisma(1.5, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	jugador.prisma(0.2, 1.2, 1.5, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPopMatrix();


	glColor3f(1, 1, 1);
	glPopMatrix();
	//glEndList();
}

void monito2()
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
	glScalef(0.5, 0.5, 0.5);
	jugador.prisma(2.0, 2.0, 1, textCA.GLindex);

	glPushMatrix();//Cuello
	glTranslatef(0, 1.0, 0.0);
	glRotatef(rotaCuello, 0, 0, 1);
	jugador.cilindro(0.25, 0.25, 15, 0);
	glPushMatrix();//Cabeza
	glTranslatef(0, 1.0, 0);
	jugador.esfera(0.75, 15, 15, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo derecho-->
	glTranslatef(1.25, 0.65, 0);
	jugador.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	glRotatef(-45 - rotManDer, 0, 1, 0);
	glTranslatef(0.75, 0, 0);
	jugador.prisma(0.7, 1.5, 0.7, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo izquierdo <--
	glTranslatef(-1.25, 0.65, 0);
	jugador.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(-0.25, 0, 0);
	glRotatef(45 + rotManIzq, 0, 1, 0);
	glRotatef(25, 0, 0, 1);
	glRotatef(25, 1, 0, 0);
	glTranslatef(-0.75, 0, 0);
	jugador.prisma(0.7, 1.5, 0.7, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();//Cintura
	glColor3f(0, 0, 1);
	glTranslatef(0, -1.5, 0);
	jugador.prisma(1, 2, 1, 0);

	glPushMatrix(); //Pie Derecho -->
	glTranslatef(0.75, -0.5, 0);
	glRotatef(-15, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	jugador.prisma(1.0, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15 + rotRodDer, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	jugador.prisma(1.5, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	jugador.prisma(0.2, 1.2, 1.5, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix(); //Pie Izquierdo -->
	glTranslatef(-0.75, -0.5, 0);
	glRotatef(-5, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	jugador.prisma(1.0, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	glRotatef(15 + rotRodIzq, 1, 0, 0);
	glTranslatef(0, -0.75, 0);
	jugador.prisma(1.5, 0.5, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.75, 0.3);
	jugador.prisma(0.2, 1.2, 1.5, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPopMatrix();


	glColor3f(1, 1, 1);
	glPopMatrix();
	//glEndList();
}

void banca(float x, float y, float z, float roatY) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(roatY, 0, 1, 0);
	glPushMatrix();
	mi_figura.prisma(0.5f, 0.15f, 0.15f, text2.GLindex);
	glPushMatrix();
	glTranslatef(1.0f, 0.25f, -0.325);
	mi_figura.prisma(0.1f, 2.0f, 0.75f, text2.GLindex);
	glPopMatrix();
	glTranslatef(2.0f, 0.0f, 0.0f);
	mi_figura.prisma(0.50f, 0.15f, 0.15f, text2.GLindex);
	glTranslatef(0.0f, 0.50f, -0.75f);
	mi_figura.prisma(1.5f, 0.15f, 0.15f, text2.GLindex);
	glTranslatef(-2.0f, 0.0f, 0.0f);
	mi_figura.prisma(1.5f, 0.15f, 0.15f, text2.GLindex);
	glPushMatrix();
	glTranslatef(0.0f, -0.1f, 0.0f);
	glRotatef(-90.0f, 0, 0, 1);
	mi_figura.cilindro(0.05f, 2.0f, 4, text2.GLindex);
	glTranslatef(-0.175f, 0.0f, 0.0f);
	mi_figura.cilindro(0.05f, 2.0f, 4, text2.GLindex);
	glTranslatef(-0.175f, 0.0f, 0.0f);
	mi_figura.cilindro(0.05f, 2.0f, 4, text2.GLindex);
	glTranslatef(-0.175f, 0.0f, 0.0f);
	mi_figura.cilindro(0.05f, 2.0f, 4, text2.GLindex);
	glTranslatef(-0.175f, 0.0f, 0.0f);
	mi_figura.cilindro(0.05f, 2.0f, 4, text2.GLindex);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void barandal(float x, float y, float z, float roatY) {
	//Barandal izquierdo
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(roatY, 0, 1, 0);
	glPushMatrix();
		glTranslatef(1.45f, 0.15f, 1.20f);
		mi_figura.cilindro(0.025f, 1.80f, 4.0, text2.GLindex);
	glPushMatrix();
		glTranslatef(0.0f, 1.80f, 0.0f);
		mi_figura.esfera(0.025f, 4.0, 4.0, text2.GLindex);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
	glPopMatrix();
		glTranslatef(-0.80f, 0.0f, 0.0f);
		mi_figura.cilindro(0.025f, 1.80f, 4.0, text2.GLindex);
	glPushMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
	glPopMatrix();
		glTranslatef(-0.80f, 0.0f, 0.0f);
		mi_figura.cilindro(0.025f, 1.80f, 4.0, text2.GLindex);
	glPushMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
		glTranslatef(0.0f, 0.30f, 0.0f);
	glPushMatrix();
		glRotatef(90, 0, 0, 1);
		mi_figura.cilindro(0.025f, 0.80f, 4.0, text2.GLindex);
	glPopMatrix();
	glPopMatrix();
		glTranslatef(-0.80f, 0.0f, 0.0f);
		mi_figura.cilindro(0.025f, 1.80f, 4.0, text2.GLindex);
		glPushMatrix();
		glTranslatef(0.0f, 1.80f, 0.0f);
		mi_figura.esfera(0.025f, 4.0, 4.0, text2.GLindex);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//Fin del barandal

}

void arbol_fondoTransparente(float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glBindTexture(GL_TEXTURE_2D, textArbol.GLindex);
		
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0, 10.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0, 10.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(45, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0, 10.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0, 10.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(-45, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0, 10.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0, 10.0, 0.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glBegin(GL_QUADS); //plano
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0, 0.0, 0.0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0, 10.0, 0.0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0, 10.0, 0.0);
		glEnd();
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_LIGHTING);

	glPopMatrix();
glPopMatrix();
}

void arbusto_fondoTransparente(float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, textArbusto.GLindex);

	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0, 2.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0, 2.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0, 2.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0, 2.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0, 2.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0, 2.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(22.5, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0, 2.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0, 2.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-22.5, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0, 2.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0, 2.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(67.5, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0, 2.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0, 2.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-67.5, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0, 2.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0, 2.0, 0.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_QUADS); //plano
	glColor3f(1.0, 1.0, 1.0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.0, 0.0, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.0, 2.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0, 2.0, 0.0);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);

	glPopMatrix();
	glPopMatrix();
}

void camino(float x, float y, float z, float roatY) {
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(roatY, 0, 1, 0);
		mi_figura.prisma(0.3f, 10.0f, 8.0f, textCamino.GLindex);
	glPopMatrix();
}

void carretera(float x, float y, float z, float roatY) {
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(roatY, 0, 1, 0);
		mi_figura.prisma(0.3f, 10.0f, 8.0f, textCarretera.GLindex);
	glPopMatrix();
}

void casa(float x, float y, float z, float text) {
	glPushMatrix();
	glTranslatef(x, y, z);
	mi_figura.prisma(10.0f, 10.0f, 10.0f, text);
	glPopMatrix();
}

void tunel(float x, float y, float z, float roatY) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(roatY, 0, 1, 0);
	mi_figura.prisma(8.0f, 10.0f, 0.1f, textTunel.GLindex);
	glPopMatrix();
}

GLuint createDL() 
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL,GL_COMPILE);
	// call the function that contains 
	// the rendering commands
		ciudad();
		//monito1();
	// endList
	glEndList();

	return(ciudadDL);
}
			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

 
    campoText.LoadTGA("city/campo.tga");
	campoText.BuildGLTexture();
	campoText.ReleaseImage();
    
	textUNAM.LoadBMP("city/logopumas.bmp");
	textUNAM.BuildGLTexture();
	textUNAM.ReleaseImage();

	textCA.LoadTGA("city/CA.tga");
	textCA.BuildGLTexture();
	textCA.ReleaseImage();

	text9.LoadTGA("city/Ciudad.tga");
	text9.BuildGLTexture();
	text9.ReleaseImage();

	balonText.LoadTGA("city/balon.tga");
	balonText.BuildGLTexture();
	balonText.ReleaseImage();

	//text1.LoadBMP("city/01.bmp");
	//text1.BuildGLTexture();
	//text1.ReleaseImage();

	text2.LoadTGA("city/acero.tga");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/Asfalto.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/GRADA.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();

	text7.LoadTGA("city/Cemento.tga");
	text7.BuildGLTexture();
	text7.ReleaseImage();

	text8.LoadTGA("city/textura-blanca.tga");
	text8.BuildGLTexture();
	text8.ReleaseImage();

	textSkyboxFrontal.LoadTGA("city/velcor_ft.tga");
	textSkyboxFrontal.BuildGLTexture();
	textSkyboxFrontal.ReleaseImage();

	textSkyboxAtras.LoadTGA("city/velcor_bk.tga");
	textSkyboxAtras.BuildGLTexture();
	textSkyboxAtras.ReleaseImage();

	textSkyboxIzquierda.LoadTGA("city/velcor_lf.tga");
	textSkyboxIzquierda.BuildGLTexture();
	textSkyboxIzquierda.ReleaseImage();

	textSkyboxDerecha.LoadTGA("city/velcor_rt.tga");
	textSkyboxDerecha.BuildGLTexture();
	textSkyboxDerecha.ReleaseImage();

	textSkyboxArriba.LoadTGA("city/velcor_up.tga");
	textSkyboxArriba.BuildGLTexture();
	textSkyboxArriba.ReleaseImage();

	textArbol.LoadTGA("city/Arbol.tga");
	textArbol.BuildGLTexture();
	textArbol.ReleaseImage();

	textArbusto.LoadTGA("city/Arbusto.tga");
	textArbusto.BuildGLTexture();
	textArbusto.ReleaseImage();

	textCamino.LoadTGA("city/camino.tga");
	textCamino.BuildGLTexture();
	textCamino.ReleaseImage();

	textEscalera.LoadTGA("city/Escalera.tga");
	textEscalera.BuildGLTexture();
	textEscalera.ReleaseImage();

	textTunel.LoadTGA("city/Tunel.tga");
	textTunel.BuildGLTexture();
	textTunel.ReleaseImage();

	textCarretera.LoadTGA("city/Carretera.tga");
	textCarretera.BuildGLTexture();
	textCarretera.ReleaseImage();

	textCasa1.LoadTGA("city/Casa1.tga");
	textCasa1.BuildGLTexture();
	textCasa1.ReleaseImage();

	textCasa2.LoadTGA("city/Casa2.tga");
	textCasa2.BuildGLTexture();
	textCasa2.ReleaseImage();

	textCasa3.LoadTGA("city/Casa3.tga");
	textCasa3.BuildGLTexture();
	textCasa3.ReleaseImage();

	textCasa4.LoadTGA("city/Casa4.tga");
	textCasa4.BuildGLTexture();
	textCasa4.ReleaseImage();

	objCamera.Position_Camera(0,2.5f,3, 0,2.5f,0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	/*for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].rotRodDer = 0;
		KeyFrame[i].rotManIzq = 0;
		KeyFrame[i].rotManDer = 0;
		KeyFrame[i].incRotMD = 0;
		KeyFrame[i].incRotMI = 0;
		KeyFrame[i].incRotRD = 0;
		KeyFrame[i].rotInc = 0;
		KeyFrame[i].giromonito1 = 0;
		KeyFrame[i].giromonito1Inc = 0;
		
		
		//información de frame para balón
		KeyFrame[i].posXBal = 0;
		KeyFrame[i].posYBal = 0;
		KeyFrame[i].posZBal = 0;


		
		
	}*/
	//frames guardados
	//monito1 COMPLETO
	KeyFrame[0].posX = 0;
	KeyFrame[0].posY = 2.5;
	KeyFrame[0].posZ = -3.5;
	KeyFrame[0].rotRodIzq = 0;
	KeyFrame[0].rotRodDer = 0;
	KeyFrame[0].rotManIzq = 0;
	KeyFrame[0].rotManDer = 0;
	KeyFrame[0].giromonito1 = 0;
	KeyFrame[0].rotaCuello = 0;
	//BALON
	KeyFrame[0].posXBal = 0;
	KeyFrame[0].posYBal = 0.48;
	KeyFrame[0].posZBal = 0;

	KeyFrame[1].posX = 0;
	KeyFrame[1].posY = 2.5;
	KeyFrame[1].posZ = -1.5;
	KeyFrame[1].rotRodIzq = 0;
	KeyFrame[1].rotRodDer = 0;
	KeyFrame[1].rotManIzq = 0;
	KeyFrame[1].rotManDer = 0;
	KeyFrame[1].giromonito1 = 0;
	KeyFrame[1].rotaCuello = 0;
	//BALON
	KeyFrame[1].posXBal = 0;
	KeyFrame[1].posYBal = 0.48;
	KeyFrame[1].posZBal = 0;



	KeyFrame[2].posX = 0;
	KeyFrame[2].posY = 2.5;
	KeyFrame[2].posZ = -1.5;
	KeyFrame[2].rotRodIzq = 24;
	KeyFrame[2].rotRodDer = 0;
	KeyFrame[2].rotManIzq = -4;
	KeyFrame[2].rotManDer = 0;
	KeyFrame[2].giromonito1 = 0;
	KeyFrame[2].rotaCuello = 0;
	//BALON
	KeyFrame[2].posXBal = 0;
	KeyFrame[2].posYBal = 0.48;
	KeyFrame[2].posZBal = 0;


	KeyFrame[3].posX = 0;
	KeyFrame[3].posY = 2.5;
	KeyFrame[3].posZ = -1.5;
	KeyFrame[3].rotRodIzq = -46;
	KeyFrame[3].rotRodDer = 0;
	KeyFrame[3].rotManIzq = -4;
	KeyFrame[3].rotManDer = 0;
	KeyFrame[3].giromonito1 = 0;
	KeyFrame[3].rotaCuello = 0;
	//BALON
	KeyFrame[3].posXBal = 0;
	KeyFrame[3].posYBal = 0.48;
	KeyFrame[3].posZBal = 0;

	KeyFrame[4].posX = 0;
	KeyFrame[4].posY = 2.5;
	KeyFrame[4].posZ = -1.5;
	KeyFrame[4].rotRodIzq = -46;
	KeyFrame[4].rotRodDer = 0;
	KeyFrame[4].rotManIzq = -4;
	KeyFrame[4].rotManDer = 0;
	KeyFrame[4].giromonito1 = 0;
	KeyFrame[4].rotaCuello = 0;
	//BALON
	KeyFrame[4].posXBal = 0;
	KeyFrame[4].posYBal = 0.48;
	KeyFrame[4].posZBal = 1;


	KeyFrame[5].posX = 0;
	KeyFrame[5].posY = 2.5;
	KeyFrame[5].posZ = -1.5;
	KeyFrame[5].rotRodIzq = -46;
	KeyFrame[5].rotRodDer = 0;
	KeyFrame[5].rotManIzq = -4;
	KeyFrame[5].rotManDer = 0;
	KeyFrame[5].giromonito1 = 0;
	KeyFrame[5].rotaCuello = 0;
	//BALON
	KeyFrame[5].posXBal = 0;
	KeyFrame[5].posYBal = 0.48;
	KeyFrame[5].posZBal = 4;
	

	//NEW//////////////////NEW//////////////////NEW///////////

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glPushMatrix();
	

	glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
				fig1.skyboxH(200.0, 200.0, 200.0, textSkyboxFrontal.GLindex, textSkyboxAtras.GLindex, textSkyboxIzquierda.GLindex, textSkyboxDerecha.GLindex, textSkyboxArriba.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();
			
			glPushMatrix();
				glEnable ( GL_COLOR_MATERIAL );
					glColor3f(1, 1, 1);
					glCallList(ciudad_display_list);		
				glDisable ( GL_COLOR_MATERIAL );
			glPopMatrix();			

			glPushMatrix();
				glTranslatef(posX, posY, posZ);
				glRotatef(giromonito1, 0, 1, 0);
				monito1();
			glPopMatrix();

			/*
			glPushMatrix();
				glTranslatef(posX+3, posY, posZ);
				monito1();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(posX - 3, posY, posZ);
				monito1();
			glPopMatrix();


			glPushMatrix();
				glTranslatef(posX, posY, posZ+9);
				glRotatef(180, 0, 1, 0);
				monito2();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(posX + 3, posY, posZ+9);
				glRotatef(180, 0, 1, 0);
				monito2();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(posX - 3, posY, posZ+9);
				glRotatef(180, 0, 1, 0);
				monito2();
			glPopMatrix();

			*/

			glPushMatrix();
				Grada();
			glPopMatrix();

			glPushMatrix();
				porteriaD();
			glPopMatrix();

			glPushMatrix();
				porteriaI();
			glPopMatrix();

			glPushMatrix();
				banderin();
			glPopMatrix();

			//PRIMERO_FRENTE
			glPushMatrix();
				banca(0.0, 2.75, -21.0, 0);
				banca(2.5, 2.75, -21.0, 0);
				banca(5, 2.75, -21.0, 0);
				banca(7.5, 2.75, -21.0, 0);
				banca(10, 2.75, -21.0, 0);
				banca(12.5, 2.75, -21.0, 0);
				banca(15, 2.75, -21.0, 0);
				banca(17.5, 2.75, -21.0, 0);
				banca(20, 2.75, -21.0, 0);
				banca(22.5, 2.75, -21.0, 0);
				banca(25, 2.75, -21.0, 0);
				banca(-2.5, 2.75, -21.0, 0);
				banca(-5, 2.75, -21.0, 0);
				banca(-7.5, 2.75, -21.0, 0);
				banca(-10, 2.75, -21.0, 0);
				banca(-12.5, 2.75, -21.0, 0);
				banca(-15, 2.75, -21.0, 0);
				banca(-17.5, 2.75, -21.0, 0);
				banca(-20, 2.75, -21.0, 0);
				banca(-22.5, 2.75, -21.0, 0);
				banca(-25, 2.75, -21.0, 0);
				banca(-27.5, 2.75, -21.0, 0);
			glPopMatrix();

			glPushMatrix();
				barandal(0.0, 2.35, -21.3, 0);
				barandal(2.5, 2.35, -21.3, 0);
				barandal(5.0, 2.35, -21.3, 0);
				barandal(7.5, 2.35, -21.3, 0);
				barandal(10.0, 2.35, -21.3, 0);
				barandal(12.5, 2.35, -21.3, 0);
				barandal(15.0, 2.35, -21.3, 0);
				barandal(17.5, 2.35, -21.3, 0);
				barandal(20.0, 2.35, -21.3, 0);
				barandal(22.5, 2.35, -21.3, 0);
				barandal(25.0, 2.35, -21.3, 0);
				barandal(27.5, 2.35, -21.3, 0);
				barandal(27.75, 2.35, -21.1, 90);
				barandal(-2.5, 2.35, -21.3, 0);
				barandal(-5.0, 2.35, -21.3, 0);
				barandal(-7.5, 2.35, -21.3, 0);
				barandal(-10.0, 2.35, -21.3, 0);
				barandal(-12.5, 2.35, -21.3, 0);
				barandal(-15.0, 2.35, -21.3, 0);
				barandal(-17.5, 2.35, -21.3, 0);
				barandal(-20.0, 2.35, -21.3, 0);
				barandal(-22.5, 2.35, -21.3, 0);
				barandal(-25.0, 2.35, -21.3, 0);
				barandal(-27.5, 2.35, -21.3, 0);
				barandal(-29.65, 2.35, -21.1, 90);
			glPopMatrix();

			//SEGNDO_FRENTE
			glPushMatrix();
			banca(0.0, 4.75, -23.0, 0);
			banca(2.5, 4.75, -23.0, 0);
			banca(5, 4.75, -23.0, 0);
			banca(7.5, 4.75, -23.0, 0);
			banca(10, 4.75, -23.0, 0);
			banca(12.5, 4.75, -23.0, 0);
			banca(15, 4.75, -23.0, 0);
			banca(17.5, 4.75, -23.0, 0);
			banca(20, 4.75, -23.0, 0);
			banca(22.5, 4.75, -23.0, 0);
			banca(25, 4.75, -23.0, 0);
			banca(-2.5, 4.75, -23.0, 0);
			banca(-5, 4.75, -23.0, 0);
			banca(-7.5, 4.75, -23.0, 0);
			banca(-10, 4.75, -23.0, 0);
			banca(-12.5, 4.75, -23.0, 0);
			banca(-15, 4.75, -23.0, 0);
			banca(-17.5, 4.75, -23.0, 0);
			banca(-20, 4.75, -23.0, 0);
			banca(-22.5, 4.75, -23.0, 0);
			banca(-25, 4.75, -23.0, 0);
			banca(-27.5, 4.75, -23.0, 0);
			glPopMatrix();

			glPushMatrix();
			barandal(0.0, 4.35, -23.3, 0);
			barandal(2.5, 4.35, -23.3, 0);
			barandal(5.0, 4.35, -23.3, 0);
			barandal(7.5, 4.35, -23.3, 0);
			barandal(10.0, 4.35, -23.3, 0);
			barandal(12.5, 4.35, -23.3, 0);
			barandal(15.0, 4.35, -23.3, 0);
			barandal(17.5, 4.35, -23.3, 0);
			barandal(20.0, 4.35, -23.3, 0);
			barandal(22.5, 4.35, -23.3, 0);
			barandal(25.0, 4.35, -23.3, 0);
			barandal(27.5, 4.35, -23.3, 0);
			barandal(27.75, 4.35, -23.1, 90);
			barandal(-2.5, 4.35, -23.3, 0);
			barandal(-5.0, 4.35, -23.3, 0);
			barandal(-7.5, 4.35, -23.3, 0);
			barandal(-10.0, 4.35, -23.3, 0);
			barandal(-12.5, 4.35, -23.3, 0);
			barandal(-15.0, 4.35, -23.3, 0);
			barandal(-17.5, 4.35, -23.3, 0);
			barandal(-20.0, 4.35, -23.3, 0);
			barandal(-22.5, 4.35, -23.3, 0);
			barandal(-25.0, 4.35, -23.3, 0);
			barandal(-27.5, 4.35, -23.3, 0);
			barandal(-29.65, 4.35, -23.1, 90);
			glPopMatrix();


			//TERCERO_FRENTE
			glPushMatrix();
			banca(0.0, 6.75, -25.0, 0);
			banca(2.5, 6.75, -25.0, 0);
			banca(5, 6.75, -25.0, 0);
			banca(7.5, 6.75, -25.0, 0);
			banca(10, 6.75, -25.0, 0);
			banca(12.5, 6.75, -25.0, 0);
			banca(15, 6.75, -25.0, 0);
			banca(17.5, 6.75, -25.0, 0);
			banca(20, 6.75, -25.0, 0);
			banca(22.5, 6.75, -25.0, 0);
			banca(25, 6.75, -25.0, 0);
			banca(-2.5, 6.75, -25.0, 0);
			banca(-5, 6.75, -25.0, 0);
			banca(-7.5, 6.75, -25.0, 0);
			banca(-10, 6.75, -25.0, 0);
			banca(-12.5, 6.75, -25.0, 0);
			banca(-15, 6.75, -25.0, 0);
			banca(-17.5, 6.75, -25.0, 0);
			banca(-20, 6.75, -25.0, 0);
			banca(-22.5, 6.75, -25.0, 0);
			banca(-25, 6.75, -25.0, 0);
			banca(-27.5, 6.75, -25.0, 0);
			glPopMatrix();

			glPushMatrix();
			barandal(0.0, 6.35, -25.3, 0);
			barandal(2.5, 6.35, -25.3, 0);
			barandal(5.0, 6.35, -25.3, 0);
			barandal(7.5, 6.35, -25.3, 0);
			barandal(10.0, 6.35, -25.3, 0);
			barandal(12.5, 6.35, -25.3, 0);
			barandal(15.0, 6.35, -25.3, 0);
			barandal(17.5, 6.35, -25.3, 0);
			barandal(20.0, 6.35, -25.3, 0);
			barandal(22.5, 6.35, -25.3, 0);
			barandal(25.0, 6.35, -25.3, 0);
			barandal(27.5, 6.35, -25.3, 0);
			barandal(27.75, 6.35, -25.1, 90);
			barandal(-2.5, 6.35, -25.3, 0);
			barandal(-5.0, 6.35, -25.3, 0);
			barandal(-7.5, 6.35, -25.3, 0);
			barandal(-10.0, 6.35, -25.3, 0);
			barandal(-12.5, 6.35, -25.3, 0);
			barandal(-15.0, 6.35, -25.3, 0);
			barandal(-17.5, 6.35, -25.3, 0);
			barandal(-20.0, 6.35, -25.3, 0);
			barandal(-22.5, 6.35, -25.3, 0);
			barandal(-25.0, 6.35, -25.3, 0);
			barandal(-27.5, 6.35, -25.3, 0);
			barandal(-29.65, 6.35, -25.1, 90);
			glPopMatrix();
			
			//CUARTO_FRENTE
			glPushMatrix();
			banca(0.0, 8.75, -27.0, 0);
			banca(2.5, 8.75, -27.0, 0);
			banca(5, 8.75, -27.0, 0);
			banca(7.5, 8.75, -27.0, 0);
			banca(10, 8.75, -27.0, 0);
			banca(12.5, 8.75, -27.0, 0);
			banca(15, 8.75, -27.0, 0);
			banca(17.5, 8.75, -27.0, 0);
			banca(20, 8.75, -27.0, 0);
			banca(22.5, 8.75, -27.0, 0);
			banca(25, 8.75, -27.0, 0);
			banca(-2.5, 8.75, -27.0, 0);
			banca(-5, 8.75, -27.0, 0);
			banca(-7.5, 8.75, -27.0, 0);
			banca(-10, 8.75, -27.0, 0);
			banca(-12.5, 8.75, -27.0, 0);
			banca(-15, 8.75, -27.0, 0);
			banca(-17.5, 8.75, -27.0, 0);
			banca(-20, 8.75, -27.0, 0);
			banca(-22.5, 8.75, -27.0, 0);
			banca(-25, 8.75, -27.0, 0);
			banca(-27.5, 8.75, -27.0, 0);
			glPopMatrix();

			glPushMatrix();
			barandal(0.0, 8.35, -27.3, 0);

			barandal(2.5, 8.35, -27.3, 0);
			barandal(5.0, 8.35, -27.3, 0);
			barandal(7.5, 8.35, -27.3, 0);
			barandal(10.0, 8.35, -27.3, 0);
			barandal(12.5, 8.35, -27.3, 0);
			barandal(15.0, 8.35, -27.3, 0);
			barandal(17.5, 8.35, -27.3, 0);
			barandal(20.0, 8.35, -27.3, 0);
			barandal(22.5, 8.35, -27.3, 0);
			barandal(25.0, 8.35, -27.3, 0);
			barandal(27.5, 8.35, -27.3, 0);
			barandal(27.75, 8.35, -27.1, 90);

			barandal(-2.5, 8.35, -27.3, 0);
			barandal(-5.0, 8.35, -27.3, 0);
			barandal(-7.5, 8.35, -27.3, 0);
			barandal(-10.0, 8.35, -27.3, 0);
			barandal(-12.5, 8.35, -27.3, 0);
			barandal(-15.0, 8.35, -27.3, 0);
			barandal(-17.5, 8.35, -27.3, 0);
			barandal(-20.0, 8.35, -27.3, 0);
			barandal(-22.5, 8.35, -27.3, 0);
			barandal(-25.0, 8.35, -27.3, 0);
			barandal(-27.5, 8.35, -27.3, 0);
			barandal(-29.65, 8.35, -27.1, 90);
			glPopMatrix();
			

			//PRIMERO_ATRAS
			glPushMatrix();
			glRotatef(180,0,1,0);
			banca(0.0, 2.75, -21.0, 0);
			banca(2.5, 2.75, -21.0, 0);
			banca(5, 2.75, -21.0, 0);
			banca(7.5, 2.75, -21.0, 0);
			banca(10, 2.75, -21.0, 0);
			banca(12.5, 2.75, -21.0, 0);
			banca(15, 2.75, -21.0, 0);
			banca(17.5, 2.75, -21.0, 0);
			banca(20, 2.75, -21.0, 0);
			banca(22.5, 2.75, -21.0, 0);
			banca(25, 2.75, -21.0, 0);
			banca(-2.5, 2.75, -21.0, 0);
			banca(-5, 2.75, -21.0, 0);
			banca(-7.5, 2.75, -21.0, 0);
			banca(-10, 2.75, -21.0, 0);
			banca(-12.5, 2.75, -21.0, 0);
			banca(-15, 2.75, -21.0, 0);
			banca(-17.5, 2.75, -21.0, 0);
			banca(-20, 2.75, -21.0, 0);
			banca(-22.5, 2.75, -21.0, 0);
			banca(-25, 2.75, -21.0, 0);
			banca(-27.5, 2.75, -21.0, 0);
			glPopMatrix();

			glPushMatrix();
			glRotatef(180, 0, 1, 0);
			barandal(0.0, 2.35, -21.3, 0);
			barandal(2.5, 2.35, -21.3, 0);
			barandal(5.0, 2.35, -21.3, 0);
			barandal(7.5, 2.35, -21.3, 0);
			barandal(10.0, 2.35, -21.3, 0);
			barandal(12.5, 2.35, -21.3, 0);
			barandal(15.0, 2.35, -21.3, 0);
			barandal(17.5, 2.35, -21.3, 0);
			barandal(20.0, 2.35, -21.3, 0);
			barandal(22.5, 2.35, -21.3, 0);
			barandal(25.0, 2.35, -21.3, 0);
			barandal(27.5, 2.35, -21.3, 0);
			barandal(27.75, 2.35, -21.1, 90);
			barandal(-2.5, 2.35, -21.3, 0);
			barandal(-5.0, 2.35, -21.3, 0);
			barandal(-7.5, 2.35, -21.3, 0);
			barandal(-10.0, 2.35, -21.3, 0);
			barandal(-12.5, 2.35, -21.3, 0);
			barandal(-15.0, 2.35, -21.3, 0);
			barandal(-17.5, 2.35, -21.3, 0);
			barandal(-20.0, 2.35, -21.3, 0);
			barandal(-22.5, 2.35, -21.3, 0);
			barandal(-25.0, 2.35, -21.3, 0);
			barandal(-27.5, 2.35, -21.3, 0);
			barandal(-29.65, 2.35, -21.1, 90);
			glPopMatrix();

			//SEGNDO_ATRAS
			glPushMatrix();
			glRotatef(180, 0, 1, 0);
			banca(0.0, 4.75, -23.0, 0);
			banca(2.5, 4.75, -23.0, 0);
			banca(5, 4.75, -23.0, 0);
			banca(7.5, 4.75, -23.0, 0);
			banca(10, 4.75, -23.0, 0);
			banca(12.5, 4.75, -23.0, 0);
			banca(15, 4.75, -23.0, 0);
			banca(17.5, 4.75, -23.0, 0);
			banca(20, 4.75, -23.0, 0);
			banca(22.5, 4.75, -23.0, 0);
			banca(25, 4.75, -23.0, 0);
			banca(-2.5, 4.75, -23.0, 0);
			banca(-5, 4.75, -23.0, 0);
			banca(-7.5, 4.75, -23.0, 0);
			banca(-10, 4.75, -23.0, 0);
			banca(-12.5, 4.75, -23.0, 0);
			banca(-15, 4.75, -23.0, 0);
			banca(-17.5, 4.75, -23.0, 0);
			banca(-20, 4.75, -23.0, 0);
			banca(-22.5, 4.75, -23.0, 0);
			banca(-25, 4.75, -23.0, 0);
			banca(-27.5, 4.75, -23.0, 0);
			glPopMatrix();

			glPushMatrix();
			glRotatef(180, 0, 1, 0);
			barandal(0.0, 4.35, -23.3, 0);
			barandal(2.5, 4.35, -23.3, 0);
			barandal(5.0, 4.35, -23.3, 0);
			barandal(7.5, 4.35, -23.3, 0);
			barandal(10.0, 4.35, -23.3, 0);
			barandal(12.5, 4.35, -23.3, 0);
			barandal(15.0, 4.35, -23.3, 0);
			barandal(17.5, 4.35, -23.3, 0);
			barandal(20.0, 4.35, -23.3, 0);
			barandal(22.5, 4.35, -23.3, 0);
			barandal(25.0, 4.35, -23.3, 0);
			barandal(27.5, 4.35, -23.3, 0);
			barandal(27.75, 4.35, -23.1, 90);
			barandal(-2.5, 4.35, -23.3, 0);
			barandal(-5.0, 4.35, -23.3, 0);
			barandal(-7.5, 4.35, -23.3, 0);
			barandal(-10.0, 4.35, -23.3, 0);
			barandal(-12.5, 4.35, -23.3, 0);
			barandal(-15.0, 4.35, -23.3, 0);
			barandal(-17.5, 4.35, -23.3, 0);
			barandal(-20.0, 4.35, -23.3, 0);
			barandal(-22.5, 4.35, -23.3, 0);
			barandal(-25.0, 4.35, -23.3, 0);
			barandal(-27.5, 4.35, -23.3, 0);
			barandal(-29.65, 4.35, -23.1, 90);
			glPopMatrix();


			//TERCERO_ATRAS
			glPushMatrix();
			glRotatef(180, 0, 1, 0);
			banca(0.0, 6.75, -25.0, 0);
			banca(2.5, 6.75, -25.0, 0);
			banca(5, 6.75, -25.0, 0);
			banca(7.5, 6.75, -25.0, 0);
			banca(10, 6.75, -25.0, 0);
			banca(12.5, 6.75, -25.0, 0);
			banca(15, 6.75, -25.0, 0);
			banca(17.5, 6.75, -25.0, 0);
			banca(20, 6.75, -25.0, 0);
			banca(22.5, 6.75, -25.0, 0);
			banca(25, 6.75, -25.0, 0);
			banca(-2.5, 6.75, -25.0, 0);
			banca(-5, 6.75, -25.0, 0);
			banca(-7.5, 6.75, -25.0, 0);
			banca(-10, 6.75, -25.0, 0);
			banca(-12.5, 6.75, -25.0, 0);
			banca(-15, 6.75, -25.0, 0);
			banca(-17.5, 6.75, -25.0, 0);
			banca(-20, 6.75, -25.0, 0);
			banca(-22.5, 6.75, -25.0, 0);
			banca(-25, 6.75, -25.0, 0);
			banca(-27.5, 6.75, -25.0, 0);
			glPopMatrix();

			glPushMatrix();
			glRotatef(180, 0, 1, 0);
			barandal(0.0, 6.35, -25.3, 0);
			barandal(2.5, 6.35, -25.3, 0);
			barandal(5.0, 6.35, -25.3, 0);
			barandal(7.5, 6.35, -25.3, 0);
			barandal(10.0, 6.35, -25.3, 0);
			barandal(12.5, 6.35, -25.3, 0);
			barandal(15.0, 6.35, -25.3, 0);
			barandal(17.5, 6.35, -25.3, 0);
			barandal(20.0, 6.35, -25.3, 0);
			barandal(22.5, 6.35, -25.3, 0);
			barandal(25.0, 6.35, -25.3, 0);
			barandal(27.5, 6.35, -25.3, 0);
			barandal(27.75, 6.35, -25.1, 90);
			barandal(-2.5, 6.35, -25.3, 0);
			barandal(-5.0, 6.35, -25.3, 0);
			barandal(-7.5, 6.35, -25.3, 0);
			barandal(-10.0, 6.35, -25.3, 0);
			barandal(-12.5, 6.35, -25.3, 0);
			barandal(-15.0, 6.35, -25.3, 0);
			barandal(-17.5, 6.35, -25.3, 0);
			barandal(-20.0, 6.35, -25.3, 0);
			barandal(-22.5, 6.35, -25.3, 0);
			barandal(-25.0, 6.35, -25.3, 0);
			barandal(-27.5, 6.35, -25.3, 0);
			barandal(-29.65, 6.35, -25.1, 90);
			glPopMatrix();

			//CUARTO_ATRAS
			glPushMatrix();
			glRotatef(180, 0, 1, 0);
			banca(0.0, 8.75, -27.0, 0);
			banca(2.5, 8.75, -27.0, 0);
			banca(5, 8.75, -27.0, 0);
			banca(7.5, 8.75, -27.0, 0);
			banca(10, 8.75, -27.0, 0);
			banca(12.5, 8.75, -27.0, 0);
			banca(15, 8.75, -27.0, 0);
			banca(17.5, 8.75, -27.0, 0);
			banca(20, 8.75, -27.0, 0);
			banca(22.5, 8.75, -27.0, 0);
			banca(25, 8.75, -27.0, 0);
			banca(-2.5, 8.75, -27.0, 0);
			banca(-5, 8.75, -27.0, 0);
			banca(-7.5, 8.75, -27.0, 0);
			banca(-10, 8.75, -27.0, 0);
			banca(-12.5, 8.75, -27.0, 0);
			banca(-15, 8.75, -27.0, 0);
			banca(-17.5, 8.75, -27.0, 0);
			banca(-20, 8.75, -27.0, 0);
			banca(-22.5, 8.75, -27.0, 0);
			banca(-25, 8.75, -27.0, 0);
			banca(-27.5, 8.75, -27.0, 0);
			glPopMatrix();

			glPushMatrix();
			glRotatef(180, 0, 1, 0);
			barandal(0.0, 8.35, -27.3, 0);

			barandal(2.5, 8.35, -27.3, 0);
			barandal(5.0, 8.35, -27.3, 0);
			barandal(7.5, 8.35, -27.3, 0);
			barandal(10.0, 8.35, -27.3, 0);
			barandal(12.5, 8.35, -27.3, 0);
			barandal(15.0, 8.35, -27.3, 0);
			barandal(17.5, 8.35, -27.3, 0);
			barandal(20.0, 8.35, -27.3, 0);
			barandal(22.5, 8.35, -27.3, 0);
			barandal(25.0, 8.35, -27.3, 0);
			barandal(27.5, 8.35, -27.3, 0);
			barandal(27.75, 8.35, -27.1, 90);

			barandal(-2.5, 8.35, -27.3, 0);
			barandal(-5.0, 8.35, -27.3, 0);
			barandal(-7.5, 8.35, -27.3, 0);
			barandal(-10.0, 8.35, -27.3, 0);
			barandal(-12.5, 8.35, -27.3, 0);
			barandal(-15.0, 8.35, -27.3, 0);
			barandal(-17.5, 8.35, -27.3, 0);
			barandal(-20.0, 8.35, -27.3, 0);
			barandal(-22.5, 8.35, -27.3, 0);
			barandal(-25.0, 8.35, -27.3, 0);
			barandal(-27.5, 8.35, -27.3, 0);
			barandal(-29.65, 8.35, -27.1, 90);
			glPopMatrix();

			//PRIMERO_DERECHA
			glPushMatrix();
			glRotatef(90, 0, 1, 0);
			banca(0.0, 2.75, -30.0, 0);
			banca(2.5, 2.75, -30.0, 0);
			banca(5, 2.75, -30.0, 0);
			banca(7.5, 2.75, -30.0, 0);
			banca(10, 2.75, -30.0, 0);
			banca(12.5, 2.75, -30.0, 0);
			banca(15, 2.75, -30.0, 0);
			banca(-2.5, 2.75, -30.0, 0);
			banca(-5, 2.75, -30.0, 0);
			banca(-7.5, 2.75, -30.0, 0);
			banca(-10, 2.75, -30.0, 0);
			banca(-12.5, 2.75, -30.0, 0);
			banca(-15, 2.75, -30.0, 0);
			banca(-17.5, 2.75, -30.0, 0);
			glPopMatrix();

			glPushMatrix();
			glRotatef(90, 0, 1, 0);
			barandal(0.0, 2.35, -30.3, 0);
			barandal(2.5, 2.35, -30.3, 0);
			barandal(5.0, 2.35, -30.3, 0);
			barandal(7.5, 2.35, -30.3, 0);
			barandal(10.0, 2.35, -30.3, 0);
			barandal(12.5, 2.35, -30.3, 0);
			barandal(15.0, 2.35, -30.3, 0);
			barandal(17.5, 2.35, -30.3, 0);
			barandal(17.75, 2.35, -30.1, 90);
			
			barandal(-2.5, 2.35, -30.3, 0);
			barandal(-5.0, 2.35, -30.3, 0);
			barandal(-7.5, 2.35, -30.3, 0);
			barandal(-10.0, 2.35, -30.3, 0);
			barandal(-12.5, 2.35, -30.3, 0);
			barandal(-15.0, 2.35, -30.3, 0);
			barandal(-17.5, 2.35, -30.3, 0);
			barandal(-19.65, 2.35, -30.1, 90);
			glPopMatrix();

			//SEGUNDO_DERECHA
			glPushMatrix();
			glRotatef(90, 0, 1, 0);
			banca(0.0, 4.75, -32.0, 0);
			banca(2.5, 4.75, -32.0, 0);
			banca(5, 4.75, -32.0, 0);
			banca(7.5, 4.75, -32.0, 0);
			banca(10, 4.75, -32.0, 0);
			banca(12.5, 4.75, -32.0, 0);
			banca(15, 4.75, -32.0, 0);
			banca(-2.5, 4.75, -32.0, 0);
			banca(-5, 4.75, -32.0, 0);
			banca(-7.5, 4.75, -32.0, 0);
			banca(-10, 4.75, -32.0, 0);
			banca(-12.5, 4.75, -32.0, 0);
			banca(-15, 4.75, -32.0, 0);
			banca(-17.5, 4.75, -32.0, 0);
			glPopMatrix();

			glPushMatrix();
			glRotatef(90, 0, 1, 0);
			barandal(0.0, 4.35, -32.3, 0);
			barandal(2.5, 4.35, -32.3, 0);
			barandal(5.0, 4.35, -32.3, 0);
			barandal(7.5, 4.35, -32.3, 0);
			barandal(10.0, 4.35, -32.3, 0);
			barandal(12.5, 4.35, -32.3, 0);
			barandal(15.0, 4.35, -32.3, 0);
			barandal(17.5, 4.35, -32.3, 0);
			barandal(17.75, 4.35, -32.1, 90);
			barandal(-2.5, 4.35, -32.3, 0);
			barandal(-5.0, 4.35, -32.3, 0);
			barandal(-7.5, 4.35, -32.3, 0);
			barandal(-10.0, 4.35, -32.3, 0);
			barandal(-12.5, 4.35, -32.3, 0);
			barandal(-15.0, 4.35, -32.3, 0);
			barandal(-17.5, 4.35, -32.3, 0);
			barandal(-19.65, 4.35, -32.1, 90);
			glPopMatrix();

			//TERCERO_DERECHA
			glPushMatrix();
			glRotatef(90, 0, 1, 0);
			banca(0.0, 6.75, -34.0, 0);
			banca(2.5, 6.75, -34.0, 0);
			banca(5, 6.75, -34.0, 0);
			banca(7.5, 6.75, -34.0, 0);
			banca(10, 6.75, -34.0, 0);
			banca(12.5, 6.75, -34.0, 0);
			banca(15, 6.75, -34.0, 0);
			banca(-2.5, 6.75, -34.0, 0);
			banca(-5, 6.75, -34.0, 0);
			banca(-7.5, 6.75, -34.0, 0);
			banca(-10, 6.75, -34.0, 0);
			banca(-12.5, 6.75, -34.0, 0);
			banca(-15, 6.75, -34.0, 0);
			banca(-17.5, 6.75, -34.0, 0);
			glPopMatrix();

			glPushMatrix();
			glRotatef(90, 0, 1, 0);
			barandal(0.0, 6.35, -34.3, 0);
			barandal(2.5, 6.35, -34.3, 0);
			barandal(5.0, 6.35, -34.3, 0);
			barandal(7.5, 6.35, -34.3, 0);
			barandal(10.0, 6.35, -34.3, 0);
			barandal(12.5, 6.35, -34.3, 0);
			barandal(15.0, 6.35, -34.3, 0);
			barandal(17.5, 6.35, -34.3, 0);
			barandal(17.75, 6.35, -34.1, 90);
			barandal(-2.5, 6.35, -34.3, 0);
			barandal(-5.0, 6.35, -34.3, 0);
			barandal(-7.5, 6.35, -34.3, 0);
			barandal(-10.0, 6.35, -34.3, 0);
			barandal(-12.5, 6.35, -34.3, 0);
			barandal(-15.0, 6.35, -34.3, 0);
			barandal(-17.5, 6.35, -34.3, 0);
			barandal(-19.65, 6.35, -34.1, 90);
			glPopMatrix();

			//CUARTO_DERECHA
			glPushMatrix();
			glRotatef(90, 0, 1, 0);
			banca(0.0, 8.75, -36.0, 0);
			banca(2.5, 8.75, -36.0, 0);
			banca(5, 8.75, -36.0, 0);
			banca(7.5, 8.75, -36.0, 0);
			banca(10, 8.75, -36.0, 0);
			banca(12.5, 8.75, -36.0, 0);
			banca(15, 8.75, -36.0, 0);
			banca(-2.5, 8.75, -36.0, 0);
			banca(-5, 8.75, -36.0, 0);
			banca(-7.5, 8.75, -36.0, 0);
			banca(-10, 8.75, -36.0, 0);
			banca(-12.5, 8.75, -36.0, 0);
			banca(-15, 8.75, -36.0, 0);
			banca(-17.5, 8.75, -36.0, 0);
			glPopMatrix();

			glPushMatrix();
			glRotatef(90, 0, 1, 0);
			barandal(0.0, 8.35, -36.3, 0);
			barandal(2.5, 8.35, -36.3, 0);
			barandal(5.0, 8.35, -36.3, 0);
			barandal(7.5, 8.35, -36.3, 0);
			barandal(10.0, 8.35, -36.3, 0);
			barandal(12.5, 8.35, -36.3, 0);
			barandal(15.0, 8.35, -36.3, 0);
			barandal(17.5, 8.35, -36.3, 0);
			barandal(17.75, 8.35, -36.1, 90);
			barandal(-2.5, 8.35, -36.3, 0);
			barandal(-5.0, 8.35, -36.3, 0);
			barandal(-7.5, 8.35, -36.3, 0);
			barandal(-10.0, 8.35, -36.3, 0);
			barandal(-12.5, 8.35, -36.3, 0);
			barandal(-15.0, 8.35, -36.3, 0);
			barandal(-17.5, 8.35, -36.3, 0);
			barandal(-19.65, 8.35, -36.1, 90);
			glPopMatrix();


			//PRIMERO_IZQUIRDA
			glPushMatrix();
			glRotatef(270, 0, 1, 0);
			banca(0.0, 2.75, -30.0, 0);
			banca(2.5, 2.75, -30.0, 0);
			banca(5, 2.75, -30.0, 0);
			banca(7.5, 2.75, -30.0, 0);
			banca(10, 2.75, -30.0, 0);
			banca(12.5, 2.75, -30.0, 0);
			banca(15, 2.75, -30.0, 0);
			banca(-2.5, 2.75, -30.0, 0);
			banca(-5, 2.75, -30.0, 0);
			banca(-7.5, 2.75, -30.0, 0);
			banca(-10, 2.75, -30.0, 0);
			banca(-12.5, 2.75, -30.0, 0);
			banca(-15, 2.75, -30.0, 0);
			banca(-17.5, 2.75, -30.0, 0);
			glPopMatrix();

			glPushMatrix();
			glRotatef(270, 0, 1, 0);
			barandal(0.0, 2.35, -30.3, 0);
			barandal(2.5, 2.35, -30.3, 0);
			barandal(5.0, 2.35, -30.3, 0);
			barandal(7.5, 2.35, -30.3, 0);
			barandal(10.0, 2.35, -30.3, 0);
			barandal(12.5, 2.35, -30.3, 0);
			barandal(15.0, 2.35, -30.3, 0);
			barandal(17.5, 2.35, -30.3, 0);
			barandal(17.75, 2.35, -30.1, 90);
			barandal(-2.5, 2.35, -30.3, 0);
			barandal(-5.0, 2.35, -30.3, 0);
			barandal(-7.5, 2.35, -30.3, 0);
			barandal(-10.0, 2.35, -30.3, 0);
			barandal(-12.5, 2.35, -30.3, 0);
			barandal(-15.0, 2.35, -30.3, 0);
			barandal(-17.5, 2.35, -30.3, 0);
			barandal(-19.65, 2.35, -30.1, 90);
			glPopMatrix();

			//SEGUNDO_IZQUIERDA
			glPushMatrix();
			glRotatef(270, 0, 1, 0);
			banca(0.0, 4.75, -32.0, 0);
			banca(2.5, 4.75, -32.0, 0);
			banca(5, 4.75, -32.0, 0);
			banca(7.5, 4.75, -32.0, 0);
			banca(10, 4.75, -32.0, 0);
			banca(12.5, 4.75, -32.0, 0);
			banca(15, 4.75, -32.0, 0);
			banca(-2.5, 4.75, -32.0, 0);
			banca(-5, 4.75, -32.0, 0);
			banca(-7.5, 4.75, -32.0, 0);
			banca(-10, 4.75, -32.0, 0);
			banca(-12.5, 4.75, -32.0, 0);
			banca(-15, 4.75, -32.0, 0);
			banca(-17.5, 4.75, -32.0, 0);
			glPopMatrix();

			glPushMatrix();
			glRotatef(270, 0, 1, 0);
			barandal(0.0, 4.35, -32.3, 0);
			barandal(2.5, 4.35, -32.3, 0);
			barandal(5.0, 4.35, -32.3, 0);
			barandal(7.5, 4.35, -32.3, 0);
			barandal(10.0, 4.35, -32.3, 0);
			barandal(12.5, 4.35, -32.3, 0);
			barandal(15.0, 4.35, -32.3, 0);
			barandal(17.5, 4.35, -32.3, 0);
			barandal(17.75, 4.35, -32.1, 90);
			barandal(-2.5, 4.35, -32.3, 0);
			barandal(-5.0, 4.35, -32.3, 0);
			barandal(-7.5, 4.35, -32.3, 0);
			barandal(-10.0, 4.35, -32.3, 0);
			barandal(-12.5, 4.35, -32.3, 0);
			barandal(-15.0, 4.35, -32.3, 0);
			barandal(-17.5, 4.35, -32.3, 0);
			barandal(-19.65, 4.35, -32.1, 90);
			glPopMatrix();

			//TERCERO_IZQUIERDA
			glPushMatrix();
			glRotatef(270, 0, 1, 0);
			banca(0.0, 6.75, -34.0, 0);
			banca(2.5, 6.75, -34.0, 0);
			banca(5, 6.75, -34.0, 0);
			banca(7.5, 6.75, -34.0, 0);
			banca(10, 6.75, -34.0, 0);
			banca(12.5, 6.75, -34.0, 0);
			banca(15, 6.75, -34.0, 0);
			banca(-2.5, 6.75, -34.0, 0);
			banca(-5, 6.75, -34.0, 0);
			banca(-7.5, 6.75, -34.0, 0);
			banca(-10, 6.75, -34.0, 0);
			banca(-12.5, 6.75, -34.0, 0);
			banca(-15, 6.75, -34.0, 0);
			banca(-17.5, 6.75, -34.0, 0);
			glPopMatrix();

			glPushMatrix();
			glRotatef(270, 0, 1, 0);
			barandal(0.0, 6.35, -34.3, 0);
			barandal(2.5, 6.35, -34.3, 0);
			barandal(5.0, 6.35, -34.3, 0);
			barandal(7.5, 6.35, -34.3, 0);
			barandal(10.0, 6.35, -34.3, 0);
			barandal(12.5, 6.35, -34.3, 0);
			barandal(15.0, 6.35, -34.3, 0);
			barandal(17.5, 6.35, -34.3, 0);
			barandal(17.75, 6.35, -34.1, 90);
			barandal(-2.5, 6.35, -34.3, 0);
			barandal(-5.0, 6.35, -34.3, 0);
			barandal(-7.5, 6.35, -34.3, 0);
			barandal(-10.0, 6.35, -34.3, 0);
			barandal(-12.5, 6.35, -34.3, 0);
			barandal(-15.0, 6.35, -34.3, 0);
			barandal(-17.5, 6.35, -34.3, 0);
			barandal(-19.65, 6.35, -34.1, 90);
			glPopMatrix();

			//CUARTO_IZQUIERDA
			glPushMatrix();
			glRotatef(270, 0, 1, 0);
			banca(0.0, 8.75, -36.0, 0);
			banca(2.5, 8.75, -36.0, 0);
			banca(5, 8.75, -36.0, 0);
			banca(7.5, 8.75, -36.0, 0);
			banca(10, 8.75, -36.0, 0);
			banca(12.5, 8.75, -36.0, 0);
			banca(15, 8.75, -36.0, 0);
			banca(-2.5, 8.75, -36.0, 0);
			banca(-5, 8.75, -36.0, 0);
			banca(-7.5, 8.75, -36.0, 0);
			banca(-10, 8.75, -36.0, 0);
			banca(-12.5, 8.75, -36.0, 0);
			banca(-15, 8.75, -36.0, 0);
			banca(-17.5, 8.75, -36.0, 0);
			glPopMatrix();

			glPushMatrix();
			glRotatef(270, 0, 1, 0);
			barandal(0.0, 8.35, -36.3, 0);
			barandal(2.5, 8.35, -36.3, 0);
			barandal(5.0, 8.35, -36.3, 0);
			barandal(7.5, 8.35, -36.3, 0);
			barandal(10.0, 8.35, -36.3, 0);
			barandal(12.5, 8.35, -36.3, 0);
			barandal(15.0, 8.35, -36.3, 0);
			barandal(17.5, 8.35, -36.3, 0);
			barandal(17.75, 8.35, -36.1, 90);
			barandal(-2.5, 8.35, -36.3, 0);
			barandal(-5.0, 8.35, -36.3, 0);
			barandal(-7.5, 8.35, -36.3, 0);
			barandal(-10.0, 8.35, -36.3, 0);
			barandal(-12.5, 8.35, -36.3, 0);
			barandal(-15.0, 8.35, -36.3, 0);
			barandal(-17.5, 8.35, -36.3, 0);
			barandal(-19.65, 8.35, -36.1, 90);
			glPopMatrix();

			glPushMatrix();

			arbol_fondoTransparente(-50, -1, -5);
			arbol_fondoTransparente(-60, -1, -5);
			arbol_fondoTransparente(-50, -1, -15);
			arbol_fondoTransparente(-60, -1, -15);
			arbol_fondoTransparente(-50, -1, -25);
			arbol_fondoTransparente(-60, -1, -25);
			arbol_fondoTransparente(-50, -1, -35);
			arbol_fondoTransparente(-60, -1, -35);
			arbol_fondoTransparente(-50, -1, 5);
			arbol_fondoTransparente(-60, -1, 5);
			arbol_fondoTransparente(-50, -1, 15);
			arbol_fondoTransparente(-60, -1, 15);
			arbol_fondoTransparente(-50, -1, 25);
			arbol_fondoTransparente(-60, -1, 25);
			arbol_fondoTransparente(-50, -1, 35);
			arbol_fondoTransparente(-60, -1, 35);

			arbol_fondoTransparente(50, -1, -5);
			arbol_fondoTransparente(60, -1, -5);
			arbol_fondoTransparente(50, -1, -15);
			arbol_fondoTransparente(60, -1, -15);
			arbol_fondoTransparente(50, -1, -25);
			arbol_fondoTransparente(60, -1, -25);
			arbol_fondoTransparente(50, -1, -35);
			arbol_fondoTransparente(60, -1, -35);
			arbol_fondoTransparente(50, -1, 5);
			arbol_fondoTransparente(60, -1, 5);
			arbol_fondoTransparente(50, -1, 15);
			arbol_fondoTransparente(60, -1, 15);
			arbol_fondoTransparente(50, -1, 25);
			arbol_fondoTransparente(60, -1, 25);
			arbol_fondoTransparente(50, -1, 35);
			arbol_fondoTransparente(60, -1, 35);

			
			arbol_fondoTransparente(-10, -1, 45);
			arbol_fondoTransparente(-20, -1, 45);
			arbol_fondoTransparente(-30, -1, 45);
			arbol_fondoTransparente(-40, -1, 45);
			arbol_fondoTransparente(-50, -1, 45);
			arbol_fondoTransparente(-10, -1, 35);
			arbol_fondoTransparente(-20, -1, 35);
			arbol_fondoTransparente(-30, -1, 35);
			arbol_fondoTransparente(-40, -1, 35);
			arbol_fondoTransparente(-50, -1, 35);
			//arbol_fondoTransparente(0, -1, 35);
			//arbol_fondoTransparente(0, -1, 45);
			arbol_fondoTransparente(10, -1, 45);
			arbol_fondoTransparente(20, -1, 45);
			arbol_fondoTransparente(30, -1, 45);
			arbol_fondoTransparente(40, -1, 45);
			arbol_fondoTransparente(50, -1, 45);
			arbol_fondoTransparente(10, -1, 35);
			arbol_fondoTransparente(20, -1, 35);
			arbol_fondoTransparente(30, -1, 35);
			arbol_fondoTransparente(40, -1, 35);
			arbol_fondoTransparente(50, -1, 35);
	
	
			arbol_fondoTransparente(-10, -1, -45);
			arbol_fondoTransparente(-20, -1, -45);
			arbol_fondoTransparente(-30, -1, -45);
			arbol_fondoTransparente(-40, -1, -45);
			arbol_fondoTransparente(-50, -1, -45);
			arbol_fondoTransparente(-10, -1, -35);
			arbol_fondoTransparente(-20, -1, -35);
			arbol_fondoTransparente(-30, -1, -35);
			arbol_fondoTransparente(-40, -1, -35);
			arbol_fondoTransparente(-50, -1, -35);
			arbol_fondoTransparente(0, -1, -35);
			arbol_fondoTransparente(0, -1, -45);
			arbol_fondoTransparente(10, -1, -45);
			arbol_fondoTransparente(20, -1, -45);
			arbol_fondoTransparente(30, -1, -45);
			arbol_fondoTransparente(40, -1, -45);
			arbol_fondoTransparente(50, -1, -45);
			arbol_fondoTransparente(10, -1, -35);
			arbol_fondoTransparente(20, -1, -35);
			arbol_fondoTransparente(30, -1, -35);
			arbol_fondoTransparente(40, -1, -35);
			arbol_fondoTransparente(50, -1, -35);

			arbol_fondoTransparente(60, -1, 45);
			arbol_fondoTransparente(60, -1, -45);
			arbol_fondoTransparente(-60, -1, 45);
			arbol_fondoTransparente(-60, -1, -45);
			
			arbusto_fondoTransparente(5, 0, 32.5);
			arbusto_fondoTransparente(-5, 0, 32.5);
			

			glPopMatrix();

			glPushMatrix();
			camino(-10, 0, 40, 0);
			camino(-20, 0, 40, 0);
			camino(-30, 0, 40, 0);
			camino(-40, 0, 40, 0);
			camino(-50, 0, 40, 0);
			camino(0,0,40,0);
			camino(10, 0, 40, 0);
			camino(20, 0, 40, 0);
			camino(30, 0, 40, 0);
			camino(40, 0, 40, 0);
			camino(50, 0, 40, 0);
			
			
			camino(55, 0, -10, 90);
			camino(55, 0, -20, 90);
			camino(55, 0, -30, 90);
			camino(55, 0, -40, 90);
			camino(55, 0, 0, 90);
			camino(55, 0, 10, 90);
			camino(55, 0, 20, 90);
			camino(55, 0, 30, 90);
			camino(55, 0, 40, 90);

			camino(-10, 0, -40, 0);
			camino(-20, 0, -40, 0);
			camino(-30, 0, -40, 0);
			camino(-40, 0, -40, 0);
			camino(-50, 0, -40, 0);
			camino(0, 0, -40, 0);
			camino(10, 0, -40, 0);
			camino(20, 0, -40, 0);
			camino(30, 0, -40, 0);
			camino(40, 0, -40, 0);
			camino(50, 0, -40, 0);

			
			camino(-55, 0, -10, 90);
			camino(-55, 0, -20, 90);
			camino(-55, 0, -30, 90);
			camino(-55, 0, -40, 90);
			camino(-55, 0, 0, 90);
			camino(-55, 0, 10, 90);
			camino(-55, 0, 20, 90);
			camino(-55, 0, 30, 90);
			camino(-55, 0, 40, 90);


			glPopMatrix();


			glPushMatrix();
				tunel(0.0, 3.0, 30.0, 0.0);
			glPopMatrix();

			glPushMatrix();
				carretera(-10.0, 0.0, 60.0, 0.0);
				carretera(-20.0, 0.0, 60.0, 0.0);
				carretera(-30.0, 0.0, 60.0, 0.0);
				carretera(-40.0, 0.0, 60.0, 0.0);
				carretera(-50.0, 0.0, 60.0, 0.0);
				carretera(-60.0, 0.0, 60.0, 0.0);
				carretera(-70.0, 0.0, 60.0, 0.0);
				carretera(0.0, 0.0, 60.0, 0.0);
				carretera(10.0, 0.0, 60.0, 0.0);
				carretera(20.0, 0.0, 60.0, 0.0);
				carretera(30.0, 0.0, 60.0, 0.0);
				carretera(40.0, 0.0, 60.0, 0.0);
				carretera(50.0, 0.0, 60.0, 0.0);
				carretera(60.0, 0.0, 60.0, 0.0);
				carretera(70.0, 0.0, 60.0, 0.0);

				carretera(-71, 0, -10, 90);
				carretera(-71, 0, -20, 90);
				carretera(-71, 0, -30, 90);
				carretera(-71, 0, -40, 90);
				carretera(-71, 0, -50, 90);
				carretera(-71, 0, 0, 90);
				carretera(-71, 0, 10, 90);
				carretera(-71, 0, 20, 90);
				carretera(-71, 0, 30, 90);
				carretera(-71, 0, 40, 90);
				carretera(-71, 0, 50, 90);
				
				carretera(-10.0, 0.0, -60.0, 0.0);
				carretera(-20.0, 0.0, -60.0, 0.0);
				carretera(-30.0, 0.0, -60.0, 0.0);
				carretera(-40.0, 0.0, -60.0, 0.0);
				carretera(-50.0, 0.0, -60.0, 0.0);
				carretera(-60.0, 0.0, -60.0, 0.0);
				carretera(-70.0, 0.0, -60.0, 0.0);
				carretera(0.0, 0.0, -60.0, 0.0);
				carretera(10.0, 0.0, -60.0, 0.0);
				carretera(20.0, 0.0, -60.0, 0.0);
				carretera(30.0, 0.0, -60.0, 0.0);
				carretera(40.0, 0.0, -60.0, 0.0);
				carretera(50.0, 0.0, -60.0, 0.0);
				carretera(60.0, 0.0, -60.0, 0.0);
				carretera(70.0, 0.0, -60.0, 0.0);

				carretera(71, 0, -10, 90);
				carretera(71, 0, -20, 90);
				carretera(71, 0, -30, 90);
				carretera(71, 0, -40, 90);
				carretera(71, 0, -50, 90);
				carretera(71, 0, 0, 90);
				carretera(71, 0, 10, 90);
				carretera(71, 0, 20, 90);
				carretera(71, 0, 30, 90);
				carretera(71, 0, 40, 90);
				carretera(71, 0, 50, 90);

			glPopMatrix();


			glPushMatrix();
				glTranslatef(posXBal, posYBal, posZBal);
				figBalon.esfera(0.5, 15, 15, balonText.GLindex);
			glPopMatrix();

			glPushMatrix();
				casa(-10, 05, 90, textCasa2.GLindex);
				casa(-20, 05, 90, textCasa3.GLindex);
				casa(-30, 05, 90, textCasa4.GLindex);
				casa(-40, 05, 90, textCasa1.GLindex);
				casa(-50, 05, 90, textCasa2.GLindex);
				casa(-60, 05, 90, textCasa3.GLindex);
				casa(-70, 05, 90, textCasa4.GLindex);
				casa(-80, 05, 90, textCasa1.GLindex);
				casa(-90, 05, 90, textCasa2.GLindex);
				casa(00, 05, 90, textCasa1.GLindex);
				casa(10, 05, 90, textCasa2.GLindex);
				casa(20, 05, 90, textCasa3.GLindex);
				casa(30, 05, 90, textCasa4.GLindex);
				casa(40, 05, 90, textCasa1.GLindex);
				casa(50, 05, 90, textCasa2.GLindex);
				casa(60, 05, 90, textCasa3.GLindex);
				casa(70, 05, 90, textCasa4.GLindex);
				casa(80, 05, 90, textCasa1.GLindex);
				casa(90, 05, 90, textCasa2.GLindex);

				casa(90, 05, 90, textCasa1.GLindex);
				casa(90, 05, 80, textCasa2.GLindex);
				casa(90, 05, 70, textCasa3.GLindex);
				casa(90, 05, 60, textCasa4.GLindex);
				casa(90, 05, 50, textCasa1.GLindex);
				casa(90, 05, 40, textCasa2.GLindex);
				casa(90, 05, 30, textCasa3.GLindex);
				casa(90, 05, 20, textCasa4.GLindex);
				casa(90, 05, 10, textCasa1.GLindex);
				casa(90, 05, 00, textCasa2.GLindex);
				casa(90, 05, -90, textCasa3.GLindex);
				casa(90, 05, -80, textCasa4.GLindex);
				casa(90, 05, -70, textCasa1.GLindex);
				casa(90, 05, -60, textCasa2.GLindex);
				casa(90, 05, -50, textCasa3.GLindex);
				casa(90, 05, -40, textCasa4.GLindex);
				casa(90, 05, -30, textCasa1.GLindex);
				casa(90, 05, -20, textCasa2.GLindex);
				casa(90, 05, -10, textCasa3.GLindex);



				casa(-10, 05, -90, textCasa2.GLindex);
				casa(-20, 05, -90, textCasa3.GLindex);
				casa(-30, 05, -90, textCasa4.GLindex);
				casa(-40, 05, -90, textCasa1.GLindex);
				casa(-50, 05, -90, textCasa2.GLindex);
				casa(-60, 05, -90, textCasa3.GLindex);
				casa(-70, 05, -90, textCasa4.GLindex);
				casa(-80, 05, -90, textCasa1.GLindex);
				casa(-90, 05, -90, textCasa2.GLindex);
				casa(00, 05, -90, textCasa1.GLindex);
				casa(10, 05, -90, textCasa2.GLindex);
				casa(20, 05, -90, textCasa3.GLindex);
				casa(30, 05, -90, textCasa4.GLindex);
				casa(40, 05, -90, textCasa1.GLindex);
				casa(50, 05, -90, textCasa2.GLindex);
				casa(60, 05, -90, textCasa3.GLindex);
				casa(70, 05, -90, textCasa4.GLindex);
				casa(80, 05, -90, textCasa1.GLindex);
				casa(90, 05, -90, textCasa2.GLindex);
				

				casa(-90, 05, 90, textCasa1.GLindex);
				casa(-90, 05, 80, textCasa2.GLindex);
				casa(-90, 05, 70, textCasa3.GLindex);
				casa(-90, 05, 60, textCasa4.GLindex);
				casa(-90, 05, 50, textCasa1.GLindex);
				casa(-90, 05, 40, textCasa2.GLindex);
				casa(-90, 05, 30, textCasa3.GLindex);
				casa(-90, 05, 20, textCasa4.GLindex);
				casa(-90, 05, 10, textCasa1.GLindex);
				casa(-90, 05, 00, textCasa2.GLindex);
				casa(-90, 05, -90, textCasa3.GLindex);
				casa(-90, 05, -80, textCasa4.GLindex);
				casa(-90, 05, -70, textCasa1.GLindex);
				casa(-90, 05, -60, textCasa2.GLindex);
				casa(-90, 05, -50, textCasa3.GLindex);
				casa(-90, 05, -40, textCasa4.GLindex);
				casa(-90, 05, -30, textCasa1.GLindex);
				casa(-90, 05, -20, textCasa2.GLindex);
				casa(-90, 05, -10, textCasa3.GLindex);

			glPopMatrix();


			glEnable(GL_LIGHTING);
			glPopMatrix();
					

			glColor3f(1.0,1.0,1.0);

		glPopMatrix();
	glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
			glColor3f(1.0,0.0,0.0);
			pintaTexto(-11,12.0,-14.0,(void *)font,"ESTADIO");
			pintaTexto(-11,8.5,-14,(void *)font,s);
			glColor3f(1.0,1.0,1.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

	glPopMatrix();
		glColor3f(colorR, colorG, colorB);
		glutSwapBuffers();
	glPopMatrix();

}

void animacion()
{
	fig3.text_izq -= 0.001;
	fig3.text_der -= 0.001;
	if (fig3.text_izq < -1)
		fig3.text_izq = 0;
	if (fig3.text_der < 0)
		fig3.text_der = 1;

	//Movimiento del monito1
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)
				//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			rotRodIzq += KeyFrame[playIndex].rotInc;
			rotRodDer += KeyFrame[playIndex].incRotRD;
			rotManIzq += KeyFrame[playIndex].incRotMI;
			rotManDer += KeyFrame[playIndex].incRotMD;
			giromonito1 += KeyFrame[playIndex].giromonito1Inc;
			rotaCuello += KeyFrame[playIndex].incRotaCuello;

			//información de frame para balón
			posXBal += KeyFrame[playIndex].IncXBal;
			posYBal += KeyFrame[playIndex].IncYBal;
			posZBal += KeyFrame[playIndex].IncZBal;

			i_curr_steps++;
		}
	}


	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 400.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
		break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;

		case 'k':		//
		case 'K':
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}

			break;

		case 'l':						
		case 'L':
			if(play==false && (FrameIndex>1))
			{

				resetElements();
				//First Interpolation				
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;

		case 'y':
		case 'Y':
			posZ++;
			printf("posZ %f \n", posZ);
			break;

		case 'g':
		case 'G':
			posX--;
			printf("posX %f \n", posX);
			break;

		case 'h':
		case 'H':
			posZ--;
			printf("posZ %f \n", posZ);
			break;

		case 'j':
		case 'J':
			posX++;
			printf("posX %f \n", posX);
			break;

		case 'c':
			rotManDer++;
			printf("rotManDer %f \n", rotManDer);
			break;

		case 'C':
			rotManDer--;
			printf("rotManDer %f \n", rotManDer);
			break;
		case 'x':
			rotManIzq++;
			printf("rotManIzq %f \n", rotManIzq);
			break;

		case 'X':
			rotManIzq--;
			printf("rotManIzq %f \n", rotManIzq);
			break;
		case 'n':
			rotRodDer++;
			printf("rotRodDer %f \n", rotRodDer);
			break;

		case 'N':
			rotRodDer--;
			printf("rotRodDer %f \n", rotRodDer);
			break;

		case 'b':
			rotRodIzq++;
			printf("rotRodIzq %f \n", rotRodIzq);
			break;

		case 'B':
			rotRodIzq--;
			printf("rotRodIzq %f \n", rotRodIzq);
			break;
		case 'v':
			rotaCuello++;
			printf("rotaCuello %f \n", rotaCuello);
			break;

		case 'V':
			rotaCuello--;
			printf("rotaCuello %f \n", rotaCuello);
			break;

		case 'p':
			giromonito1++;
			printf("giromonito1 %f \n", giromonito1);
			break;

		case 'P':
			giromonito1--;
			printf("giromonito1 %f \n", giromonito1);
			break;

		case 'r':
			colorR = 1.0;
			colorG = 1.0;
			colorB = 1.0;
			break;

		case 'R':
			colorR = 0.5;
			colorG = 0.5;
			colorB = 0.5;
			break;


			//TECLAS BALON
		case '8':
			posZBal++;
			printf("%f \n", posZBal);
			break;


		case '4':
			posXBal--;
			printf("%f \n", posXBal);
			break;


		case '2':
			posZBal--;
			printf("%f \n", posZBal);
			break;


		case '6':
			posXBal++;
			printf("%f \n", posXBal);
			break;

		case '7':
			posYBal--;
			printf("%f \n", posYBal);
			break;


		case '9':
			posYBal++;
			printf("%f \n", posYBal);
			break;



		case 27:        // Cuando Esc es presionado...
			exit(0);   // Salimos del programa
			break;
		default:        // Cualquier otra
			break;
	}

	glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

		//Teclas para camara

	case GLUT_KEY_F1:
		objCamera.Position_Camera(0, 2.5, 3, 0, 2.5, 0, 0, 1, 0);
		break;

	case GLUT_KEY_F2:
		objCamera.Position_Camera(0, 10, 20, 0, 2.5, 0, 0, 1, 0);
		break;

	case GLUT_KEY_F3:
		objCamera.Position_Camera(5, 2.5, 0, 20, 2.5, 0, 0, 1, 0);
		break;

	case GLUT_KEY_F4:
		objCamera.Position_Camera(25, 2.5, 0, 20, 2.5, 0, 0, 1, 0);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

void menuKeyFrame( int id)
{
	switch (id)
	{
		case 0:	//Save KeyFrame
			if(FrameIndex<MAX_FRAMES)
			{
				saveFrame();
			}
			break;

		case 1:	//Play animation
			if(play==false && FrameIndex >1)
			{

				resetElements();
				//First Interpolation
				interpolation();

				play=true;
				playIndex=0;
				i_curr_steps = 0;
			}
			else
			{
				play=false;
			}
			break;


	}
}

void menu( int id)
{
	
}

int main ( int argc, char** argv )   // Main Function
{
  int submenu;
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (1200, 700);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("ESTADIO"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );

  submenu = glutCreateMenu	  ( menuKeyFrame );
  glutAddMenuEntry	  ("Guardar KeyFrame", 0);
  glutAddMenuEntry	  ("Reproducir Animacion", 1);
  glutCreateMenu	  ( menu );
  glutAddSubMenu	  ("ESTADIO", submenu);
 
  glutAttachMenu	  (GLUT_RIGHT_BUTTON);


  glutMainLoop        ( );          // 

  return 0;
}
