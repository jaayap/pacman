#pragma once
#include <string>
#include "Personnage.h"


class Ghost : public Personnage
{
	int deplacement; // 1 : A gauche, 2 : A droite, 3 : En bas, 4 : En haut.
	int deplacement_precedent=1;	
	std::string name;

public:
	Ghost(int positionDepart_x, int PositionDepart_y,std::string name);
	~Ghost();

	//setter
	void setX(int x);
	void setY(int y);
	//fonction
	void dessiner();
	void CalculDeplacement();
	void Deplacer();
};

