// PacmanProject.cpp : définit le point d'entrée pour l'application console.
#include "stdafx.h"
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include "Game.h"

using namespace std;

//Constantes
#define NBLIGNES 31
#define NBCOLONNES 28

int HAUTEUR_FENETRE = 1920;
int LARGEUR_FENETRE = 1024;

//variables globales
vector<GLuint>	texture; // tableau qui contient nos textures
Game game; // Classe qui definit le niveau : matrice, affichage du niveau
Pacman pacman(13,23);
Ghost clyde(16, 12, "clyde");
Ghost pinky(15, 12, "pinky");
Ghost inky(13, 12, "inky");
Ghost blinky(12, 12, "blinky");
bool AfficherChoixNiveau = false;
bool voirCommande = false;

// Déclarations de fonctions
void LabyAffichage();
void LabyRedim(int width, int height);
void LabyTimerFantome(int z);
void LabyTimerMode(int z);
void TraitementClavier(int key, int x, int y);
void TraitementClavierASCII(unsigned char key, int x, int y);
int LoadGLTextures(string name);

//Fonction Main
void main(void)
{
	srand((unsigned)time(0));
	// Gestion de la fenêtre
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(HAUTEUR_FENETRE, LARGEUR_FENETRE);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutCreateWindow("Pacman Game");
	//glutIgnoreKeyRepeat(1);
	//glutFullScreen();

	// Gestion des événements
	glutDisplayFunc(LabyAffichage);
	glutReshapeFunc(LabyRedim);
	glutKeyboardFunc(TraitementClavierASCII);
	glutSpecialFunc(TraitementClavier);
	
	glutTimerFunc(500, LabyTimerFantome, 0);
	glutTimerFunc(500, LabyTimerMode, 0);

	//chargement des textures
	LoadGLTextures("image/PacmanLevel-1.png");// 0
	LoadGLTextures("image/fantome.png");	  // 1
	LoadGLTextures("image/pacman.png");	      // 2
	LoadGLTextures("image/clyde.png");	      // 3
	LoadGLTextures("image/pinky.png");	      // 4 
	LoadGLTextures("image/inky.png");		  // 5
	LoadGLTextures("image/blinky.png");	      // 6
	LoadGLTextures("image/GameOver.png");	  // 7
	LoadGLTextures("image/Winner.png");	      // 8
	LoadGLTextures("image/choix_niveau.png"); // 9
	LoadGLTextures("image/Commandes.png");	  // 10
	LoadGLTextures("image/fond_jeux.png");	  // 11
	LoadGLTextures("image/pause.png");        // 12
	LoadGLTextures("image/menu.png");         // 13
	LoadGLTextures("image/PacmanLevel-2.png");// 14
	LoadGLTextures("image/Case_Sortie.png");  // 15
	glutMainLoop();
}

// Evénement d'affichage
void LabyAffichage()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	//VIEWPORT 1 : Fond d'ecran
	glViewport(0, 0, LARGEUR_FENETRE, HAUTEUR_FENETRE);
	glLoadIdentity();
	game.AfficherFond();

	if (game.getPlay()) {
		//VIEWPORT : comporte le score
		glViewport(LARGEUR_FENETRE*0.28, HAUTEUR_FENETRE * 0.97, LARGEUR_FENETRE * 0.44, HAUTEUR_FENETRE *0.15);
		glLoadIdentity();
		game.AfficherScore();

		//VIEWPORT : comporte les vies
		for (int i = 0; i < pacman.getNbVies(); i++) {
			glViewport(LARGEUR_FENETRE*0.65 + i * LARGEUR_FENETRE*0.02, HAUTEUR_FENETRE * 0.97, LARGEUR_FENETRE * 0.02, HAUTEUR_FENETRE *0.03); //pour 2 vies
			glLoadIdentity();
			game.AfficherVies();
		}

		//VIEWPORT : Comporte le niveau
		glViewport(LARGEUR_FENETRE *0.28, 0, LARGEUR_FENETRE * 0.44, HAUTEUR_FENETRE *0.95);
		glLoadIdentity();

		game.DessinerNiveau(); // Affiche le niveau
		game.DessinerPerso(); // Affiche les personnages
	}
	else if (!game.getJoueurLose() && !game.getJoueurWin() && !AfficherChoixNiveau) {
		//Afficher Menu
		glViewport(LARGEUR_FENETRE *0.28, 0, LARGEUR_FENETRE *0.44, HAUTEUR_FENETRE *0.95);
		glLoadIdentity();
		game.AfficherMenu();
	}
	else {
		if (!voirCommande) {
			//Afficher choix du niveau
			glViewport(LARGEUR_FENETRE *0.28, 0, LARGEUR_FENETRE *0.44, HAUTEUR_FENETRE *0.95);
			glLoadIdentity();
			game.AfficherChoixNiveau();
		}
		else {
			glViewport(LARGEUR_FENETRE *0.28, 0, LARGEUR_FENETRE *0.44, HAUTEUR_FENETRE *0.95);
			glLoadIdentity();
			game.AfficherCommandes();
		}
	}

	if (game.getPause() && game.getPlay()) {
		game.AfficherEcranPause();
	}

	if (game.getJoueurLose()) {
		glViewport(LARGEUR_FENETRE*0.28, 0, LARGEUR_FENETRE *0.44, HAUTEUR_FENETRE *0.95);
		glLoadIdentity();
		game.AfficherEcranGameOver();
	}

	if(game.getJoueurWin()) 
	{
		glViewport(LARGEUR_FENETRE*0.28, 0, LARGEUR_FENETRE *0.44, HAUTEUR_FENETRE *0.95);
		glLoadIdentity();
		game.AfficherEcranVictoire();
	}

	//on regarde si on est en mode special, si oui, on relance le timer
	if (game.getMode() == 2) {
		glutTimerFunc(12000, LabyTimerMode, 0);
	}

	glFlush();
}

// Evénement de redimensionnement
void LabyRedim(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)NBCOLONNES, (double)NBLIGNES, 0.0);
	HAUTEUR_FENETRE = height;
	LARGEUR_FENETRE = width;
	
}

//Gestion des entrees clavier
void TraitementClavier(int key, int x, int y) {
	glutPostRedisplay();

	if (!game.getPause()) {
		if (key == GLUT_KEY_UP) {
			pacman.depHaut();
		}
		if (key == GLUT_KEY_DOWN) {
			pacman.depBas();
		}
		if (key == GLUT_KEY_LEFT) {
			pacman.depGauche();
		}
		if (key == GLUT_KEY_RIGHT) {
			pacman.depDroite();
		}
	}
	
	//Verification apres le deplacement
	game.perdu();//on verifie si l'on a perdu ou non

	if (game.pacman_gagner()) {
		game.AfficherEcranVictoire();
	}

	glFlush();
}

void TraitementClavierASCII( unsigned char key, int x,int y) {
	glutPostRedisplay();

	if (key == 27) {// Escape key
		glutDestroyWindow(1);
		exit(0);
	}

	if (key == 112 || key == 80) { // touche p
		if (game.getPause()) game.setPause(false);
		else game.setPause(true);
	}

	if (key == 10 || key == 13) { // touche entree
		if (game.getPlay() == false) {
			AfficherChoixNiveau = true;
		}
	}

	if (key == 49) { // touche 1
		if (game.getPlay() == false) {
			game.setPause(false);
			game.setPlay(true);
			game.initialiserMatrice("Niveaux/matrice.txt");
			game.matriceEnCours = 1;
			AfficherChoixNiveau = false;
		}
	}

	if(key == 50) // touche 2
	{
		if (game.getPlay() == false) {
			game.setPause(false);
			game.setPlay(true);
			game.initialiserMatrice("Niveaux/matrice_2.txt");
			game.matriceEnCours = 2;
			AfficherChoixNiveau = false;
		}
	}

	if (key == 67 || key == 99) { // touche c
		if (voirCommande) voirCommande = false;
		else voirCommande = true;
	}

	if (key == 32 && (game.getJoueurLose() || game.getJoueurWin())) { // touche espace
		game.resetGame();
	}

	glFlush();
}

//Chargement des textures
int LoadGLTextures(string name) //Charge l'image et la convertit en texture
{
	GLuint essai = SOIL_load_OGL_texture
	(
		name.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);

	texture.push_back(essai);

	if (texture.at(texture.size() - 1) == 0)
		return false;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return true;  // Return Success
}

void LabyTimerFantome(int z) {
	if (!game.getPause()){
		clyde.CalculDeplacement();
		pinky.CalculDeplacement();
		inky.CalculDeplacement();
		blinky.CalculDeplacement();

		clyde.dessiner();
		pinky.dessiner();
		inky.dessiner();
		blinky.dessiner();
	}
	glutTimerFunc(250, LabyTimerFantome, 0);
}

void LabyTimerMode(int z) {
	game.setMode(1); //on revient au mode normal
}