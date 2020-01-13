/* inclusion des fichiers d'en-tete Glut */
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include "shader.hpp"
#include <string.h>
#include <vector>

#include <fstream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <algorithm>
#include <string>
#include <utility>

// Include GLM
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
using namespace glm;
using namespace std;

#define M_PI 3.1415
#define MAXMERID 20
#define BUFFER_OFFSET(i) ((unsigned int *)NULL + (i))

//hyperbole
GLfloat sommets[2*MAXMERID*3+6] ; // x 3 coordonnées
GLuint indices[MAXMERID*12]; // x6 car pour chaque face quadrangulaire on a 6 indices (2 triangles=2x 3 indices)
GLfloat normales[2*MAXMERID*3];
double theta=2*M_PI/double(MAXMERID);
double alpha=M_PI/1.2;

//tore
GLfloat sommetstore[MAXMERID*3*MAXMERID];
GLuint indicestore[4*MAXMERID*MAXMERID];
double rayon1=2.0;
double rayon2=1.0;
double zeta=2*M_PI/double(MAXMERID);

GLfloat sommetscube[3*8*8*8];
GLuint indicescube[4*8*8*8];


// initialisations

void genereVBO();
void deleteVBO();
void traceObjet();

void appelfonction1();
void appelfonction2();
void appelfonction3();
void appelfonction4();
void appelfonction5();
void appelfonction6();
void appelfonction7();
void appelfonction8();
void appelfonction9();
void appelfonction10();
void appelfonction11();
void appelfonction12();
void appelfonction13();
void appelfonction14();
void appelfonction15();
void appelfonction16();
void appelfonction17();
void appelfonction18();
void appelfonction19();
void appelfonction20();
void appelfonction21();
void appelfonction22();

enum TypeBouton
{
    action1 = 0,
    action2,
    action3,
    action4,
    action5,
    action6,
    action7,
    action8,
    action9,
    action10,
    action11,
    action12,
    action13,
    action14,
    action15,
    action16,
    action17,
    action18,
    action19,
    action20,
    action21,
    action22,
    action23,
    action24,
    action25,
    action26
} bouton_action = action1;

static void  menu (int item){
    bouton_action = static_cast<TypeBouton> (item);
    glutPostRedisplay(); 
} 

// fonctions de rappel de glut
void affichage();
void clavier(unsigned char,int,int);
void mouse(int, int, int, int);
void mouseMotion(int, int);
void reshape(int,int);
// misc
void drawString(const char *str, int x, int y, float color[4], void *font);
void showInfo();
void *font = GLUT_BITMAP_8_BY_13; // pour afficher des textes 2D sur l'ecran
// variables globales pour OpenGL
bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance=290.;
int choice=1;

// variables Handle d'opengl
//--------------------------
GLuint programID;   // handle pour le shader
GLuint MatrixIDMVP,MatrixIDView,MatrixIDModel,MatrixIDPerspective;    // handle pour la matrice MVP
GLuint VBO_sommets,VBO_normales, VBO_indices,VAO;
GLuint locCameraPosition ;
GLuint ChoiceLocation ;


// location des VBO
//------------------
GLuint indexVertex=0,indexNormale=3 ;

//variable pour paramétrage eclairage
//--------------------------------------
vec3 cameraPosition(0.,0.,300);

glm::mat4 MVP;      // justement la voilà
glm::mat4 Model, View, Projection;    // Matrices constituant MVP

int screenHeight = 500;
int screenWidth = 500;


/*********************************DEBUT PROJET*********************************/
void createtore()
{
    for(int j=0;j<MAXMERID;j++) {
        for(int i=0;i<MAXMERID;i++){
            sommetscube[3*(i*MAXMERID+j)]=(rayon1 + rayon2*cos(j*theta))*cos(i*zeta);
            sommetscube[3*(i*MAXMERID+j)+1]=(rayon1 + rayon2*cos(j*theta))*sin(i*zeta);
            sommetscube[3*(i*MAXMERID+j)+2]=rayon2*sin(j*theta);
        }
    }



    for(int i=0;i<MAXMERID;i++){
        for (int j=0;j<MAXMERID;j++){
                //corps
                indicescube[4*(i*MAXMERID+j)]=(unsigned int) i*MAXMERID+j;
                indicescube[4*(i*MAXMERID+j)+1]=(unsigned int) ((i+1)%MAXMERID)*MAXMERID+j;
                indicescube[4*(i*MAXMERID+j)+2]=(unsigned int) (((i+1)%MAXMERID)*MAXMERID)+(j+1)%MAXMERID;
                indicescube[4*(i*MAXMERID+j)+3]=(unsigned int) i*MAXMERID+(j+1)%MAXMERID;

        }
    }
}
/**********************************FIN PROJET**********************************/

//----------------------------------------
void initOpenGL(void)
{
  glCullFace (GL_BACK); // on spécifie queil faut éliminer les face arriere
  glEnable(GL_DEPTH_TEST);
// le shader
   programID = LoadShaders( "PhongShader.vert", "PhongShader.frag" );

  MatrixIDMVP = glGetUniformLocation(programID, "MVP");

  Projection = glm::perspective( glm::radians(60.f), 1.0f, 1.0f, 1000.0f);

/* on recupere l'ID */
locCameraPosition = glGetUniformLocation(programID, "cameraPosition");

}

//----------------------------------------
int main(int argc,char **argv)
{
  /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE|GLUT_RGB);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(screenWidth,screenHeight);
  glutCreateWindow("Projet VBO SHADER ");

  /* le menuuuu */
  glutCreateMenu (menu);
  glutAddMenuEntry ("Base", action1);
  glutAddMenuEntry ("Compression X", action2);
  glutAddMenuEntry ("Compression X_YZ", action3);
  glutAddMenuEntry ("Compression Y_XZ", action4);
  glutAddMenuEntry ("Compression Z_XY", action5);
  glutAddMenuEntry ("Compression Y", action6);
  glutAddMenuEntry ("Compression Z", action7);
  glutAddMenuEntry ("Rotation Diff Y", action8);
  glutAddMenuEntry ("Rotation Diff X", action9);
  glutAddMenuEntry ("Rotation Diff Y2", action10);
  glutAddMenuEntry ("Rotation Diff Z2", action11);
  glutAddMenuEntry ("Rotation Diff X2", action12);
  glutAddMenuEntry ("Compression xtrem", action13);
  glutAddMenuEntry ("Vortex Y", action14);
  glutAddMenuEntry ("Vortex Z", action15);
  glutAddMenuEntry ("Torvex Y", action16);
  glutAddMenuEntry ("Decompression xtrem", action17);
  glutAddMenuEntry ("Pliage X", action18);
  glutAddMenuEntry ("Pliage Y", action19);
  glutAddMenuEntry ("Pliage Z", action20);
  glutAddMenuEntry ("Rotation diff X", action21);
  glutAddMenuEntry ("Compression X", action22);

  glutAttachMenu (GLUT_MIDDLE_BUTTON);

  // Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

    //info version GLSL
    std::cout << "***** Info GPU *****" << std::endl;
    std::cout << "Fabricant : " << glGetString (GL_VENDOR) << std::endl;
    std::cout << "Carte graphique: " << glGetString (GL_RENDERER) << std::endl;
    std::cout << "Version : " << glGetString (GL_VERSION) << std::endl;
    std::cout << "Version GLSL : " << glGetString (GL_SHADING_LANGUAGE_VERSION) << std::endl << std::endl;

	initOpenGL();

/********************TRACE***********************/
  createtore();
/****************FIN TRACE*********************/

 // construction des VBO a partir des tableaux du cube deja construit
  genereVBO();


  /* enregistrement des fonctions de rappel */
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);

  /* Entree dans la boucle principale glut */
  glutMainLoop();

  glDeleteProgram(programID);
  deleteVBO();
  return 0;
}

void genereVBO ()
{
    glGenBuffers(1, &VAO);
    glBindVertexArray(VAO); // ici on bind le VAO , c'est lui qui recupèrera les configurations des VBO glVertexAttribPointer , glEnableVertexAttribArray...

    if(glIsBuffer(VBO_sommets) == GL_TRUE) glDeleteBuffers(1, &VBO_sommets);
    glGenBuffers(1, &VBO_sommets);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_sommets);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(sommets),sommets , GL_STATIC_DRAW); //pour hyperbole
    //glBufferData(GL_ARRAY_BUFFER, sizeof(sommetstore),sommetstore , GL_STATIC_DRAW); //pour tore
    glBufferData(GL_ARRAY_BUFFER, sizeof(sommetscube),sommetscube , GL_STATIC_DRAW); //pour accordeon
    glVertexAttribPointer ( indexVertex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    if(glIsBuffer(VBO_normales) == GL_TRUE) glDeleteBuffers(1, &VBO_normales);
    glGenBuffers(1, &VBO_normales);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normales);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normales),normales , GL_STATIC_DRAW);
    glVertexAttribPointer ( indexNormale, 3, GL_FLOAT, GL_FALSE, 0, (void*)0  );

    if(glIsBuffer(VBO_indices) == GL_TRUE) glDeleteBuffers(1, &VBO_indices);
    glGenBuffers(1, &VBO_indices); // ATTENTIOn IBO doit etre un GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicescube),indicescube , GL_STATIC_DRAW);//accordéon

   glEnableVertexAttribArray(indexVertex);
   glEnableVertexAttribArray(indexNormale );

  // une fois la config terminée   ]
  // on désactive le dernier VBO et le VAO pour qu'ils ne soit pas accidentellement modifié
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

}

//-----------------
void deleteVBO ()
{
  glDeleteBuffers(1, &VBO_sommets);
  glDeleteBuffers(1, &VBO_normales);
  glDeleteBuffers(1, &VBO_indices);
  glDeleteBuffers(1, &VAO);
}


/* fonction d'affichage */
void affichage()
{

  /* effacement de l'image avec la couleur de fond */
  /* Initialisation d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glClearDepth(10.0f);                         // 0 is near, >0 is far
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);
  glPointSize(2.0);

     View       = glm::lookAt(   cameraPosition, // Camera is at (0,0,3), in World Space
                                            glm::vec3(0,0,0), // and looks at the origin
                                            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                             );
     Model = glm::mat4(1.0f);
     Model = glm::translate(Model,glm::vec3(0,0,cameraDistance));
     Model = glm::rotate(Model,glm::radians(cameraAngleX),glm::vec3(1, 0, 0) );
     Model = glm::rotate(Model,glm::radians(cameraAngleY),glm::vec3(0, 1, 0) );
     Model = glm::scale(Model,glm::vec3(0.4, 0.4, 0.4));
     MVP = Projection * View * Model;
     traceObjet();        // trace VBO avec ou sans shader

switch(bouton_action){
        case action1: choice=1;
        break;

        case action2: choice=2;
        break;

        case action3: choice=3;
        break;

        case action4: choice=4;
        break;

        case action5: choice=5;
        break;

        case action6: choice=6;
        break;

        case action7: choice=7;
        break;

        case action8: choice=8;
        break;

        case action9: choice=9;
        break;

        case action10: choice=10;
        break;

        case action11: choice=11;
        break;

        case action12: choice=12;
        break;

        case action13: choice=13;
        break;

        case action14: choice=14;
        break;

        case action15: choice=15;
        break;

        case action16: choice=16;
        break;

        case action17: choice=17;
        break;

        case action18: choice=18;
        break;

        case action19: choice=19;
        break;

        case action20: choice=20;
        break;

        case action21: choice=21;
        break;

        case action22: choice=22;
        break;
    }

 /* on force l'affichage du resultat */
   glutPostRedisplay();
   glutSwapBuffers();
}

//-------------------------------------
//Trace le tore 2 via le VAO
void traceObjet()
{
 // Use  shader & MVP matrix   MVP = Projection * View * Model;
 glUseProgram(programID);
 ChoiceLocation = glGetUniformLocation(programID, "choice");

//on envoie les données necessaires aux shaders */
 glUniformMatrix4fv(MatrixIDMVP, 1, GL_FALSE, &MVP[0][0]);
 glUniform1f(ChoiceLocation,choice);
 //glUniformMatrix4fv(MatrixIDView, 1, GL_FALSE,&View[0][0]);
 //glUniformMatrix4fv(MatrixIDModel, 1, GL_FALSE, &Model[0][0]);
 //glUniformMatrix4fv(MatrixIDPerspective, 1, GL_FALSE, &Projection[0][0]);

 glUniform3f(locCameraPosition,cameraPosition.x, cameraPosition.y, cameraPosition.z);


//pour l'affichage
	glBindVertexArray(VAO); // on active le VAO
  //glDrawElements(GL_TRIANGLES,  sizeof(indices), GL_UNSIGNED_INT, 0);// on appelle la fonction dessin pour hyperbole
  //glDrawElements(GL_QUADS,  sizeof(indicestore), GL_UNSIGNED_INT, 0);//pour tore
  glDrawElements(GL_QUADS,  sizeof(indicescube), GL_UNSIGNED_INT, 0);//et cube

  glBindVertexArray(0);    // on desactive les VAO
  glUseProgram(0);         // et le pg

}

void reshape(int w, int h)
{
    // set viewport to be the entire window
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);// ATTENTION GLsizei important - indique qu'il faut convertir en entier non négatif

    // set perspective viewing frustum
    float aspectRatio = (float)w / h;

    Projection = glm::perspective(glm::radians(60.0f),(float)(w)/(float)h, 1.0f, 1000.0f);
}

void clavier(unsigned char touche,int x,int y)
{
  switch (touche)
    {
    case 'f': /* affichage du carre plein */
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
    case 'e': /* affichage en mode fil de fer */
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
    case 'v' : /* Affichage en mode sommets seuls */
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;

 case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
    }
}

void mouse(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }

    else if(button == GLUT_MIDDLE_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseMiddleDown = true;
        }
        else if(state == GLUT_UP)
            mouseMiddleDown = false;
    }
}

void mouseMotion(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        cameraDistance += (y - mouseY) * 0.2f;
        mouseY = y;
    }

    glutPostRedisplay();
}
