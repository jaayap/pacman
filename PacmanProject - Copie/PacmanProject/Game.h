#pragma once
#include "Personnage.h"
#include "Pacman.h"
#include "Ghost.h"

class Game
{
	//Représentation du niveau.
	char Matrice[31][28]; //2 : cases vides, 1 : mur, 2 : pas de bille, 3 : sortie,	8 : bille speciale

	int mode = 1; //1 : normal / 2 : special
	bool pause = true; // jeu en pause.
	bool play = false; // permet de lancer le jeu.
	bool joueur_win = false, joueur_lose = false;
	bool sortie = false; // enregistre si la case de sortie est affiché ou non .
	std::string choixMatrice; // choix de l'utilisateur.

public:int matriceEnCours=1;//permet dafficher la bonne texture

public:
	Game();
	~Game();
	//Affichage
	void AfficherTexture(int numero_texture,bool transparent);
	void DessinerNiveau();
	void AfficherScore();
	void AfficherVies();
	void DessinerPerso();
	void AfficheCaseSortie();
	void AfficherEcranGameOver();
	void AfficherEcranVictoire();
	void AfficherEcranPause();
	void AfficherMenu();
	void AfficherFond();
	void AfficherChoixNiveau();
	void AfficherCommandes();
	//Tests
	bool CaseLibre(int x,int y);
	void CaseManger(int x, int y);
	bool pacman_gagner(); // test si le pacman a gagne
	//fonctions
	//void JouerSon(std::string songName,bool sync);
	void JouerSonDepart();
	void JouerSonMiamPacGomme();
	void JouerSonMiamGhost();
	void JouerSonPerdu();
	void JouerSonGagner();
	void initialiserMatrice(std::string numeroNiveau);
	void perdu(); // test si le pacman a perdu / doit perdre des vies / ou si un fantome a ete mange
	void resetPosition();//Replace les personnages a leurs position initiale
	void resetGame(); //Remet toutes les valeurs initial , permet de rejouer apres avoir perdu ou gagner
	//Getters
	int getMode();
	bool getPause();
	bool getPlay();
	bool getJoueurWin();
	bool getJoueurLose();
	//Setters
	void setMode(int mode);
	void setPause(bool pause);
	void setPlay(bool play);
};

