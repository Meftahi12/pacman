#ifndef _FANTOMES_H_
#define _FANTOMES_H_

#include "Grille.h"
#include "Position.h"

#include <string>

using namespace std;



class Blinky
{

    Etat m_etatCourant;
    Direction m_derniereDirection;
    Position m_PositionCourante;


public:

    Blinky(Position p);

    void Deplace(Grille grille);
    int Direction(Grille grille, Position cible);
    void DeplaceDirection(int direction);
    Position PositionCourante();
    Etat EtatCourant();
    void RetourneMaison();
    void UpdateEtat(Etat e);
};

class Pinky
{

    Etat m_etatCourant;
    Direction m_derniereDirection;
    Position m_PositionCourante;


public:

    Pinky(Position p);

    void Deplace(Grille grille);
    int Direction(Grille grille, Position cible);
    void DeplaceDirection(int direction);
    Position PositionCourante();
    Etat EtatCourant();
    void RetourneMaison();
    void UpdateEtat(Etat e);
};


class Inky
{

    Etat m_etatCourant;
    Direction m_derniereDirection;
    Position m_PositionCourante;


public:

    Inky(Position p);

    void Deplace(Grille grille);
    int Direction(Grille grille, Position cible);
    void DeplaceDirection(int direction);
    Position PositionCourante();
    Etat EtatCourant();
    void RetourneMaison();
    void UpdateEtat(Etat e);
};

class Clyde
{

    Etat m_etatCourant;
    Direction m_derniereDirection;
    Position m_PositionCourante;


public:

    Clyde(Position p);

    void Deplace(Grille grille);
    int Direction(Grille grille, Position cible);
    void DeplaceDirection(int direction);
    Position PositionCourante();
    Etat EtatCourant();
    void RetourneMaison();
    void UpdateEtat(Etat e);
};


#endif //_FANTOMES_H_
