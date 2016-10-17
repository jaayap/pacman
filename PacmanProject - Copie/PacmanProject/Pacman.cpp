#include "stdafx.h"
#include <vector>
#include "GL/glut.h"
#include "SOIL/SOIL.h"
#include "Pacman.h"
#include "Game.h"

using namespace std;

extern vector<GLuint> texture;
extern Game game;

//Variables 
bool hautBis;
bool basBis;

Pacman::Pacman(int positionDepart_x, int PositionDepart_y) : Personnage(x, y)
{
	this->x = positionDepart_x;
	this->y = PositionDepart_y;
}

Pacman::~Pacman()
{
}
//Getters
int Pacman::getScore()
{
	return this->score;
}

int Pacman::getNbVies() 
{
	return this->nb_vies;
}

int Pacman::getNbGhostEat()
{
	return this->nb_ghost_eat;
}

int Pacman::getDirection() 
{
	return this->direction;
}

//Setters
void Pacman::setScore(int score)
{
	this->score = score;
}

void Pacman::setNbVies(int vies) 
{
	this->nb_vies = vies;
}

void Pacman::setNbGhostEat_oneMore()
{
	this->nb_ghost_eat++;
}

void Pacman::setNbGhostEat_Zero() 
{
	this->nb_ghost_eat = 0;
}

void Pacman::setDirection(int direction)
{
	this->direction = direction;
}

//Redefinition des fonctions de deplacement
void Pacman::depGauche()
{
	Personnage::depGauche();
	game.CaseManger(this->y,this->x);
	direction = 3;
}

void Pacman::depDroite()
{
	Personnage::depDroite();
	game.CaseManger(this->y, this->x);
	direction = 4;
}

void Pacman::depHaut()
{
	Personnage::depHaut();
	game.CaseManger(this->y, this->x);
	direction = 1;
}

void Pacman::depBas()
{
	Personnage::depBas();
	game.CaseManger(this->y, this->x);
	direction = 2;
}

//Fonctions pour afficher le pacman :
void Pacman::dessiner() {

	switch (direction) { // 1 : vers le haut, 2 : vers le bas, 3 : vers la gauche, 4 : vers la droite.
		case 1:
			if (ancienne_direction == 4) { dessinerVersHaut(); hautBis = false; }
			else if (ancienne_direction == 3) { dessinerVersHautBis(); hautBis = true; }
			else if (hautBis) {
				dessinerVersHautBis();
			}
			else dessinerVersHaut();
			break;
		case 2:
			if (ancienne_direction == 4) { dessinerVersBas(); basBis = false; }
			else if (ancienne_direction == 3) { dessinerVersBasBis(); basBis = true; }
			else if (basBis) {
				dessinerVersBasBis();
			}
			else dessinerVersBas();
			break;
		case 3:
			dessinerVersGauche();
			break;
		case 4:
			dessinerVersDroite();
			break;
	}
}

void Pacman::dessinerVersGauche()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glColor3d(1.0, 1.0, 1.0);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(x + 1, y + 1);//top left
	glTexCoord2f(1.0f, 0.0f); glVertex2d(x, y + 1);//bottom left	
	glTexCoord2f(1.0f, 1.0f); glVertex2d(x, y);//bottom right	
	glTexCoord2f(0.0f, 1.0f); glVertex2d(x + 1, y);	//top right	
	glEnd();
	
	glDisable(GL_TEXTURE_2D); 
	glDisable(GL_BLEND);
	ancienne_direction = 3;
}

void Pacman::dessinerVersDroite()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glColor3d(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(x + 1, y + 1);//top left
	glTexCoord2f(0.0f, 0.0f); glVertex2d(x, y + 1);//bottom left	
	glTexCoord2f(0.0f, 1.0f); glVertex2d(x, y);//bottom right	
	glTexCoord2f(1.0f, 1.0f); glVertex2d(x + 1, y);	//top right	
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	ancienne_direction = 4;
}

void Pacman::dessinerVersBas()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glColor3d(1.0, 1.0, 1.0);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(x + 1, y + 1);//top left
	glTexCoord2f(1.0f, 0.0f); glVertex2d(x, y + 1);//bottom left	
	glTexCoord2f(0.0f, 0.0f); glVertex2d(x, y);//bottom right	
	glTexCoord2f(0.0f, 1.0f); glVertex2d(x + 1, y);	//top right	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	ancienne_direction = 2;
}

void Pacman::dessinerVersBasBis()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture[2]);
			glBegin(GL_QUADS);
			glColor3d(1.0, 1.0, 1.0);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(x + 1, y + 1);//top left
			glTexCoord2f(1.0f, 1.0f); glVertex2d(x, y + 1);//bottom left	
			glTexCoord2f(0.0f, 1.0f); glVertex2d(x, y);//bottom right	
			glTexCoord2f(0.0f, 0.0f); glVertex2d(x + 1, y);	//top right	
			glEnd();
		glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	ancienne_direction = 2;
}

void Pacman::dessinerVersHaut()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glColor3d(1.0, 1.0, 1.0);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(x + 1, y + 1);//top left
	glTexCoord2f(0.0f, 1.0f); glVertex2d(x, y + 1);//bottom left	
	glTexCoord2f(1.0f, 1.0f); glVertex2d(x, y);//bottom right	
	glTexCoord2f(1.0f, 0.0f); glVertex2d(x + 1, y);	//top right	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	ancienne_direction = 1;
}

void Pacman::dessinerVersHautBis()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glColor3d(1.0, 1.0, 1.0);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(x + 1, y + 1);//top left
	glTexCoord2f(0.0f, 0.0f); glVertex2d(x, y + 1);//bottom left	
	glTexCoord2f(1.0f, 0.0f); glVertex2d(x, y);//bottom right	
	glTexCoord2f(1.0f, 1.0f); glVertex2d(x + 1, y);	//top right	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	ancienne_direction = 1;
}