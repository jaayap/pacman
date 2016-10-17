#pragma once
#include "Personnage.h"

class Pacman : public Personnage
{
	int direction = 4; // 1 : vers le haut, 2 : vers le bas, 3 : vers la gauche, 4 : vers la droite
	int ancienne_direction = 4;
	int score = 0; // Score obtenu avec pacman
	int nb_vies=2;
	int nb_ghost_eat = 0;

public:
	Pacman(int positionDepart_x, int PositionDepart_y);
	~Pacman();
	//Getters
	int getScore();
	int getNbVies();
	int getNbGhostEat();
	int getDirection();

	//Setters
	void setScore(int score);
	void setNbVies(int vies);
	void setNbGhostEat_oneMore();
	void setNbGhostEat_Zero();
	void setDirection(int direction);

	//fonction
	void dessiner();
	void dessinerVersHaut();
	void dessinerVersHautBis();
	void dessinerVersBas();
	void dessinerVersBasBis();
	void dessinerVersGauche();
	void dessinerVersDroite();

	//Redefinition des methodes
	void depGauche();
	void depDroite();
	void depHaut();
	void depBas();
};