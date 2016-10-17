#pragma once
class Personnage
{
	public: int x, y; //Position
	public:bool vivant=true;

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
