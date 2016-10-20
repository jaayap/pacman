#pragma once
class Personnage
{
	protected: int x, y; //Position dans la matrice.
	public :   bool vivant=true;//true : le personnage est vivant; false : le personnage est mort.

public:
	Personnage(int xDepart, int yDepart);
	~Personnage();
	void depGauche();
	void depDroite();
	void depHaut();
	void depBas();
	//getter
	int getX();
	int getY();
	//setter
	void setX(int x);
	void setY(int y);
	void setPosition(int x, int y);
};
