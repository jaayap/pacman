#include "stdafx.h"
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Game.h"
#include <Windows.h> //pour les sons

//Constantes
#define NBLIGNES 31
#define NBCOLONNES 28

using namespace std;

extern vector<GLuint> texture;
extern Pacman pacman;
extern Ghost clyde;
extern Ghost pinky;
extern Ghost inky;
extern Ghost blinky;

Game::Game()
{	
}

Game::~Game()
{
}

//Getters
int Game::getMode() {
	return this->mode;
}

bool Game::getPause() {
	return this->pause;
}

bool Game::getPlay() {
	return this->play;
}

bool Game::getJoueurWin() {
	return this->joueur_win;
}

bool Game::getJoueurLose() {
	return this->joueur_lose;
}

//Setters
void Game::setMode(int mode) {
	this->mode = mode;
}

void Game::setPause(bool pause) {
	this->pause = pause;
}

void Game::setPlay(bool play) {
	this->play = play;
}

//Fonction pour les bruitages
void Game::JouerSonDepart() {	
	PlaySound(TEXT("sons//pacman_beginning.wav"), NULL, SND_SYNC);// ASYNC ou SYNC : bloque le jeu	
}
void Game::JouerSonMiamPacGomme() {
	PlaySound(TEXT("sons//pacman_chomp.wav"), NULL, SND_ASYNC);// ASYNC ou SYNC : bloque le jeu
}
void Game::JouerSonMiamGhost() {
	PlaySound(TEXT("sons//pacman_eatGhost.wav"), NULL, SND_ASYNC);// ASYNC ou SYNC : bloque le jeu
}
void Game::JouerSonPerdu() {
	PlaySound(TEXT("sons//pacman_death.wav"), NULL, SND_SYNC);// ASYNC ou SYNC : bloque le jeu
}
void Game::JouerSonGagner() {
	PlaySound(TEXT("sons//pacman_death.wav"), NULL, SND_SYNC);// ASYNC ou SYNC : bloque le jeu
}

//Fonction qui fait le lien entre le fichier et la matrice
void Game::initialiserMatrice(string nomFile) {
	ifstream file(nomFile);
	if (file.is_open()) {
		for (int i = 0; i < NBLIGNES; i++) {
			for (int j = 0; j < NBCOLONNES; j++) {
				file >> Matrice[i][j];
			}
		}
	}
	choixMatrice = nomFile;
}

//Fonctions d'Affichages :

//fonction qui permet d'appliquer une texture
void Game::AfficherTexture(int numeroTexture, bool transparent) {
	if (transparent) {
		glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[numeroTexture]);
					glBegin(GL_QUADS);
						glColor3d(1.0, 1.0, 1.0);//important
						glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);//top left
						glTexCoord2f(1.0f, 1.0f); glVertex2d(28, 0);//bottom left	
						glTexCoord2f(1.0f, 0.0f); glVertex2d(28, 31);//bottom right	
						glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 31);//top right	
					glEnd();
			glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}
	else {	
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[numeroTexture]);
			glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);//important
				glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);//top left
				glTexCoord2f(1.0f, 1.0f); glVertex2d(28, 0);//bottom left	
				glTexCoord2f(1.0f, 0.0f); glVertex2d(28, 31);//bottom right	
				glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 31);//top right	
			glEnd();
		glDisable(GL_TEXTURE_2D);
	}
}

//Affiche les differents elements du niveau
void Game::DessinerNiveau()
{
	//Affichage du fond
	glColor3d(0.0, 0.0, 1.0);
	
	if (matriceEnCours == 1) { //Niveau 1
		AfficherTexture(0, false);
	}
	else { // Niveau 2
		AfficherTexture(14, false);
	}

	for (int i = 0; i < NBLIGNES; i++) {
		for (int j = 0; j < NBCOLONNES; j++) {
			//Affichage des "pac-gommes"
			if (Matrice[i][j] == '0' || Matrice[i][j] == '5') { 	
					glPushMatrix();
					glTranslatef(j + 0.5, i + 0.5, 0);
					glColor3d(0.913725, 0.588235, 0.478431); // darksalmon
					glutSolidSphere(0.1, 50, 40);
					glPopMatrix();
				
			}
			if (Matrice[i][j] == '8') {
					glPushMatrix();
					glTranslatef(j + 0.5, i + 0.5, 0);
					glColor3d(0.913725, 0.588235, 0.478431); // darksalmon
					glutSolidSphere(0.25, 50, 40);
					glPopMatrix();
			}

			//Affichage de la case sortie
			if (Matrice[i][j] == '3') {
				glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glEnable(GL_TEXTURE_2D);
						glBindTexture(GL_TEXTURE_2D, texture[15]);
						glBegin(GL_QUADS);
							glColor3d(1.0, 1.0, 1.0);
							glTexCoord2f(0.0f, 0.0f); glVertex2d(i + 1, j + 1);
							glTexCoord2f(1.0f, 0.0f); glVertex2d(i, j + 1);
							glTexCoord2f(1.0f, 1.0f); glVertex2d(i, j);
							glTexCoord2f(0.0f, 1.0f); glVertex2d(i + 1, j);	
						glEnd();
					glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND);
			}
		}
	}
}

//Dessine tout les personnages 
void Game::DessinerPerso() {
	pacman.dessiner();
	clyde.dessiner();
	pinky.dessiner();
	inky.dessiner();
	blinky.dessiner();
}

//fonction utile pour l'affichage de texte
void vBitmapOutput(int x, int y, char *string, void *font)
{
	int len, i; // len donne la longueur de la chaîne de caracteres.

	glRasterPos2f(x, y); // Positionne le premier caractere de la chaîne.
	len = (int)strlen(string); // Calcule la longueur de la chaîne.
	for (i = 0; i < len; i++) glutBitmapCharacter(font, string[i]); // Affiche chaque caractere de la chaîne.
}

//Affiche le score du joueur
void Game::AfficherScore() {
	glColor3d(0.0, 0.0, 0.0);

	//Affichage du libelle
	vBitmapOutput(0, 31, "Score : ", GLUT_BITMAP_HELVETICA_18);
	//Affichage de l'entier score
	char buffer[10] = { '\0' };
	sprintf_s(buffer, "%d", pacman.getScore()); //on convertit l'entier en chaîne de caractere.
	vBitmapOutput(3, 31, buffer, GLUT_BITMAP_HELVETICA_18);
}

void Game::AfficherVies() {	
	AfficherTexture(2, true);
}

//Affiche le menu
void Game::AfficherMenu() {
	AfficherTexture(13,false);
}

//Affiche l'interface du jeu
void Game::AfficherFond() {
	glClearColor(0.54, 0.0, 0.54, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	AfficherTexture(11, false);

}

//Determine ou doit se positionner la case de sortie
void Game::AfficheCaseSortie() {
	if (!sortie) {
		int nombre_aleatoire_x;
		int nombre_aleatoire_y;

		do { //L'emplacement de la case de sortie est aleatoire
			nombre_aleatoire_x = rand() % (NBLIGNES)+1;
			nombre_aleatoire_y = rand() % (NBCOLONNES)+1;
		} while (!CaseLibre(nombre_aleatoire_y, nombre_aleatoire_x));

		Matrice[nombre_aleatoire_x][nombre_aleatoire_y] = '3';//on definit l'emplacement dans la matrice;
		sortie = true;
	}
}

void Game::AfficherEcranPause() {
	AfficherTexture(12, true);
}

void Game::AfficherEcranGameOver() {	
	AfficherTexture(7,true);
	play = false;
	pause = true;
	joueur_lose = true;
}

void Game::AfficherEcranVictoire() {

	AfficherTexture(8,false);
	play = false;
	pause = true;
	joueur_win = true;
}

void Game::AfficherChoixNiveau() {
	AfficherTexture(9, false);
}

void Game::AfficherCommandes() {
	AfficherTexture(10, false);
}

//Test si l'on peut aller dans la case x,y
bool Game::CaseLibre(int x, int y) //ligne colonne
{
	if (x < 0 || x > 31 || y < 0 || y > 28) return false; // case inexistante.

	if (Matrice[x][y] != '1') { // la case n'est pas un mur.
		return true;
	}
	else return false;
}

//Met a jour le score et la matrice lorsqu'on mange des pacgomme
void Game::CaseManger(int x, int y) {

	if (Matrice[x][y] == '8') {
		pacman.setScore(pacman.getScore() + 50);
		Matrice[x][y] = '2';
		this->mode = 2;
		//JouerSonMiamPacGomme();
	} 
	else if (Matrice[x][y] != '2') {
		pacman.setScore(pacman.getScore() +10);
		Matrice[x][y] = '2';
		//JouerSonMiamPacGomme();
	}
}

/*cette fonction teste si un fantome a rencontre pacman*/
void Game::perdu()
{
	if (mode == 1) {
		if (clyde.getX() == pacman.getX() && clyde.getY() == pacman.getY() && clyde.vivant
			|| pinky.getX() == pacman.getX() && pinky.getY() == pacman.getY() && pinky.vivant
			|| inky.getX() == pacman.getX() && inky.getY() == pacman.getY() && inky.vivant
			|| blinky.getX() == pacman.getX() && blinky.getY() == pacman.getY() && blinky.vivant) {

			if (pacman.getNbVies() == 0) {
				joueur_lose = true; // le joueur a perdu.
			}
			else {
				pacman.setNbVies(pacman.getNbVies() - 1 ); //le joueur perd une vie.
				JouerSonPerdu();
				resetPosition();//on replace pacman et les ennemis a leurs positions initial.
			}
		}
	}
	else if (mode == 2) {

		if (clyde.getX() == pacman.getX() && clyde.getY() == pacman.getY() && clyde.vivant) {
			clyde.vivant = false;
			//calcul du score : pacman.score += 200 + (200 * nbGhostEat)
			pacman.setScore(pacman.getScore()+ 200 + (200 * pacman.getNbGhostEat()));		
			pacman.setNbGhostEat_oneMore(); //incremente le nombre de fantome manges.
			JouerSonMiamGhost();
		}
		if (pinky.getX() == pacman.getX() && pinky.getY() == pacman.getY() && pinky.vivant) {
			pinky.vivant = false;
			pacman.setScore(pacman.getScore() + 200 + (200 * pacman.getNbGhostEat()));
			pacman.setNbGhostEat_oneMore(); //incremente le nombre de fantome manges.
			JouerSonMiamGhost();
		}
		if (inky.getX() == pacman.getX() && inky.getY() == pacman.getY() && inky.vivant) {
			inky.vivant = false;
			pacman.setScore(pacman.getScore() + 200 + (200 * pacman.getNbGhostEat()));
			pacman.setNbGhostEat_oneMore(); //incremente le nombre de fantome manges.
			JouerSonMiamGhost();
		}
		if (blinky.getX() == pacman.getX() && blinky.getY() == pacman.getY() && blinky.vivant) {
			blinky.vivant = false;
			pacman.setScore(pacman.getScore() + 200 + (200 * pacman.getNbGhostEat()));
			pacman.setNbGhostEat_oneMore(); //incremente le nombre de fantome manges.
			JouerSonMiamGhost();
		}
	}

	//Si tout les fantomes sont mange, on les ressucite.
	if (!blinky.vivant && !inky.vivant && !pinky.vivant && !clyde.vivant) {
		clyde.vivant = true;
		clyde.setX(16); clyde.setY(12);
		pinky.vivant = true;
		pinky.setX(15); pinky.setY(12);
		inky.vivant = true;
		inky.setX(13); inky.setY(12);
		blinky.vivant = true;
		blinky.setX(12); blinky.setY(12);
	}
}

bool Game::pacman_gagner()
{
	int nombre_bonbon = 0;
	if (!sortie) {
		for (int i = 0; i < NBLIGNES; i++) {
			for (int j = 0; j < NBCOLONNES; j++) {
				if (Matrice[i][j] != '2' && Matrice[i][j] != '1') {
					nombre_bonbon ++;
				}
			}
		}
		if (nombre_bonbon == 0) {
			AfficheCaseSortie();			
		}
		return false;
	}
	else { //on teste si le pacman est sur la case de sortie.
		if (Matrice[pacman.getX()][pacman.getY()] == '3') return true; //le joueur a gagne.
		else return false;	//le joueur n'a pas rejoint la case de sortie.
	}
}

void Game::resetPosition() {
	pacman.setPosition(13,23);
	pacman.setDirection(4); //direction initial = vers la droite
	clyde.setPosition(16, 12);
	pinky.setPosition(15,12);
	inky.setPosition(13, 12);
	blinky.setPosition(12, 12);
}

void Game::resetGame() {
	//on remet les valeurs a zero.
	pacman.setScore(0);
	pacman.setNbVies(2);
	pacman.setNbGhostEat_Zero();

	//on dit que tout les fantomes sont vivant.
	pinky.vivant = true;
	clyde.vivant = true;
	inky.vivant = true;
	blinky.vivant = true;

	//On replace les perso.
	resetPosition();
	
	//on reinitialise nos booleens pour l'affichage.
	joueur_lose = false;
	joueur_win = false;
	play = false;
	pause = true;
	sortie = false;
	mode = 1;
}