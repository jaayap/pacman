#include "stdafx.h"
#include <iostream>
#include <string>
#include "Personnage.h"
#include "Game.h"

using namespace std;
extern Game game;

Personnage::Personnage(int xDepart,int yDepart)
{
	this->x = xDepart;
	this->y = yDepart;
}


Personnage::~Personnage()
{
}

// Getters.
int Personnage::getX() {
	return this->x;
}

int Personnage::getY() {
	return this->y;
}

// Setter.
void Personnage::setX(int x) {
	this->x = x;
}

void Personnage::setY(int y) {
	this->y = y;
}

void Personnage::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

// Deplacements.
void Personnage::depGauche()
{
	if (this->x == 0 && this->y == 14) this->x = 27; // teleportation
	else if (game.CaseLibre(this->y, this->x - 1)) this->x--;
}

void Personnage::depDroite()
{
	if (this->x == 27 && this->y == 14) this->x = 0; // teleportation
	else if (game.CaseLibre(this->y,this->x+1)) this->x++;
}

void Personnage::depHaut()
{
	if (game.CaseLibre(this->y-1, this->x)) this->y = this->y - 1;
}

void Personnage::depBas()
{
	if (game.CaseLibre(this->y+1, this->x)) this->y = this->y + 1;
}