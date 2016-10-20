#include "stdafx.h"
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include <vector>
#include <string>
#include<time.h>
#include<iostream>
#include "Ghost.h"
#include "Game.h"

using namespace std;

extern vector<GLuint>	texture;
extern Game game;

Ghost::Ghost(int positionDepart_x, int PositionDepart_y, string name) : Personnage (x,y)
{
	this->x = positionDepart_x;
	this->y = PositionDepart_y;
	this->name = name;
}

Ghost::~Ghost()
{
}


// Setter.
void Ghost::setX(int x)
{
	this->x = x;
}

void Ghost::setY(int y)
{
	this->y = y;
}

// Fonction d'affichage.
void Ghost::dessiner()
{
	if (vivant) {
		if ( game.getMode() == 1 ) {
			if (this->name == "clyde") {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[3]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.0f, 0.0f); glVertex2d(x + 1, y + 1);//top left
				glTexCoord2f(1.0f, 0.0f); glVertex2d(x, y + 1);//bottom left	
				glTexCoord2f(1.0f, 1.0f); glVertex2d(x, y);//bottom right	
				glTexCoord2f(0.0f, 1.0f); glVertex2d(x + 1, y);	//top right	
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}
			else if (this->name == "pinky") {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[4]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.0f, 0.0f); glVertex2d(x + 1, y + 1);//top left
				glTexCoord2f(1.0f, 0.0f); glVertex2d(x, y + 1);//bottom left	
				glTexCoord2f(1.0f, 1.0f); glVertex2d(x, y);//bottom right	
				glTexCoord2f(0.0f, 1.0f); glVertex2d(x + 1, y);	//top right	
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}
			else if (this->name == "inky") {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[5]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.0f, 0.0f); glVertex2d(x + 1, y + 1);//top left
				glTexCoord2f(1.0f, 0.0f); glVertex2d(x, y + 1);//bottom left	
				glTexCoord2f(1.0f, 1.0f); glVertex2d(x, y);//bottom right	
				glTexCoord2f(0.0f, 1.0f); glVertex2d(x + 1, y);	//top right	
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}
			else if (this->name == "blinky") {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture[6]);
				glBegin(GL_QUADS);
				glColor3d(1.0, 1.0, 1.0);
				glTexCoord2f(0.0f, 0.0f); glVertex2d(x + 1, y + 1);//top left
				glTexCoord2f(1.0f, 0.0f); glVertex2d(x, y + 1);//bottom left	
				glTexCoord2f(1.0f, 1.0f); glVertex2d(x, y);//bottom right	
				glTexCoord2f(0.0f, 1.0f); glVertex2d(x + 1, y);	//top right	
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}
		}
		else if ( game.getMode() == 2 )  {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[1]);
			glBegin(GL_QUADS);
			glColor3d(1.0, 1.0, 1.0);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(x + 1, y + 1);//top left
			glTexCoord2f(1.0f, 0.0f); glVertex2d(x, y + 1);//bottom left	
			glTexCoord2f(1.0f, 1.0f); glVertex2d(x, y);//bottom right	
			glTexCoord2f(0.0f, 1.0f); glVertex2d(x + 1, y);	//top right	
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
	}
}

void Ghost::CalculDeplacement()// 1 : A gauche, 2 : A droite, 3 : En bas, 4 : En haut.
{
	//GAUCHE
	if (deplacement_precedent == 1) {

		if (!(this->x == 0 && this->y == 14)) {
		
			if (!game.CaseLibre(y, x - 1)) { //Mur devant (gauche)
				if (!game.CaseLibre(y - 1, x)) deplacement = 3; // Mur en haut
				else if (!game.CaseLibre(y + 1, x)) deplacement = 4; //Mur en bas
				else deplacement = rand() % (5 - 3) + 3; //nombre aleatoire entre 3 et 4
			}
			else if (!game.CaseLibre(y - 1, x)) { // Mur en haut
				if (!game.CaseLibre(y + 1, x)) deplacement = deplacement_precedent; //et Mur en bas
				else {
						deplacement = rand() % (2) + 1; // nombre aleatoire entre 1 et 2
						if (deplacement == 2) { // 2 : on veut aller en bas -> 3
							deplacement = 3;
						}
				}
			}
			else if (!game.CaseLibre(y + 1, x)) { // Mur en bas
				deplacement = rand() % (2) + 1; // nombre aleatoire entre 1 et 2
				if (deplacement == 2) { // 2 : on veut aller en haut -> 4
					deplacement = 4;
				}
			}
			else {
				do {
					deplacement = rand() % (4) + 1; // nombre aleatoire entre 1 et 4
				} while (deplacement == 2);//Evite le retour en arriere
			}
		}
	}
	//DROITE
	else if (deplacement_precedent == 2) { // Droite
		
		if (!(this->x == 27 && this->y == 14)) {

			if (!game.CaseLibre(y, x + 1)) { //Mur devant (droite)
				if (!game.CaseLibre(y - 1, x)) deplacement = 3; // Mur en haut
				else if (!game.CaseLibre(y + 1, x)) deplacement = 4; //Mur en bas
				else deplacement = rand() % (5 - 3) + 3; //nombre aleatoire entre 3 et 4
			}
			else if (!game.CaseLibre(y - 1, x)) { // Mur en haut
				if (!game.CaseLibre(y + 1, x)) deplacement = deplacement_precedent; //et Mur en bas
				else {
					deplacement = rand() % (4 - 2) + 2; // nombre aleatoire entre 2 et 3
				}
			}
			else if (!game.CaseLibre(y + 1, x)) { // Mur en bas
				deplacement = rand() % (2) + 1; // nombre aleatoire entre 1 et 2
				if (deplacement == 1) { // 2 : on veut aller en haut -> 4
					deplacement = 4;
				}
			}
			else {
				do {
					deplacement = rand() % (4) + 1; // nombre aleatoire entre 1 et 4
				} while (deplacement == 1);
			}
		}
	}
	//BAS
	else if (deplacement_precedent == 3) {
		if (!game.CaseLibre(y + 1, x)) { //Mur devant
			if (!game.CaseLibre(y, x - 1)) deplacement = 2; // Mur a gauche
			else if (!game.CaseLibre(y, x+1)) deplacement = 1; //Mur a droite
			else deplacement = rand() % (2) + 1; //nombre aleatoire entre 1 et 2
		}
		else if (!game.CaseLibre(y, x - 1)) { // Mur a gauche
			if (!game.CaseLibre(y, x + 1)) deplacement = deplacement_precedent; //et Mur a droite
			else {
				deplacement = rand() % (4 - 2) + 2; // nombre aleatoire entre 2 et 3
			}
		}
		else if (!game.CaseLibre(y, x + 1)) { // Mur a droite
			deplacement = rand() % (2) + 1; // nombre aleatoire entre 1 et 2
			if (deplacement == 2) { // 2 : on veut aller en bas -> 3
				deplacement = 3;
			}
		}
		else {
			do {
				deplacement = rand() % (4) + 1; // nombre aleatoire entre 1 et 4
			} while (deplacement == 4);
		}
	}
	//HAUT
	else if (deplacement_precedent == 4) {
		if (!game.CaseLibre(y - 1, x)) { //Mur devant
			if (!game.CaseLibre(y, x - 1)) deplacement = 2; // Mur a gauche
			else if (!game.CaseLibre(y, x + 1)) deplacement = 1; //Mur a droite
			else deplacement = rand() % (2) + 1; //nombre aleatoire entre 1 et 2
		}
		else if (!game.CaseLibre(y, x - 1)) { // Mur a gauche
			if (!game.CaseLibre(y, x + 1)) deplacement = deplacement_precedent; //et Mur a droite
			else {
				deplacement = rand() % (2) + 1; // nombre aleatoire entre 2 et 4
				if (deplacement == 1) { deplacement = 4; }
			}
		}
		else if (!game.CaseLibre(y, x + 1)) { // Mur a droite
			deplacement = rand() % (2) + 1; // nombre aleatoire entre 1 et 4
			if (deplacement == 2) { // 2 : on veut aller en haut -> 4
				deplacement = 4;
			}
		}
		else {
			do {
				deplacement = rand() % (4) + 1; // nombre aleatoire entre 1 et 4
			} while (deplacement == 3);
		}
	}

	deplacement_precedent = deplacement; // on enregistre la valeur
	Deplacer(); // on se deplace
}

void Ghost::Deplacer() {
	if (vivant) {
		
		switch (deplacement) {	//1 : A gauche, 2 : A droite, 3 : En bas, 4 : En haut
		case 1:
			depGauche();
			break;
		case 2:
			depDroite();
			break;
		case 3:
			depBas();
			break;
		case 4:
			depHaut();
			break;
		default:
			break;
		}
	}

	game.perdu(); //on verifie si le fantome a rencontrer le pacman/
	glutPostRedisplay();
}

