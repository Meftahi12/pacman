#ifndef _GRILLE_H_
#define _GRILLE_H_

#include "Position.h"

#include <array>
#include <fstream>
#include <iostream>

using namespace std;

enum Cases
{
    Chemin,
    Mur,
    Maison,
    Porte,
    Demitour,
    Exterieur,
    Pastille,
    Invalide
};

enum Etat
{
    Chasse,  // Chase mode
    Appeure, // Frightened mode
    Explore, // Scatter mode
    Attend   // Pour dans la maison
};

class Grille
{
    static const unsigned int LIGNE = 36;
    static const unsigned int COLONNE = 28;

    Position m_pacman;
    Direction m_pacmanDirection;
    Position m_blinkyPosition;
    Position m_inkyPosition;
    Position m_pinkyPosition;
    Position m_clydePosition;
    Etat m_blinkyEtat;
    Etat m_inkyEtat;
    Etat m_pinkyEtat;
    Etat m_clydeEtat;

    array<array<Cases, COLONNE>, LIGNE> m_cases;

    bool EstConsidereChemin(Cases) const;
    bool DevraitFaireDemiTour(const Position&) const;

public:
    Grille();

    void LireCarte(ifstream&);

    Cases getAt(const Position&) const;
    Position PacmanPosition() const;
    Direction PacmanDirection() const;
    Position BlinkyPosition() const;
    bool DeplacePacman(const Position&);
    void MangePastille();
    void UpdatePacmanDirection(Direction);
    void UpdateBlinky(const Position&, Etat);
    void UpdatePinky(const Position&, Etat);
    void UpdateInky(const Position&, Etat);
    void UpdateClyde(const Position&, Etat);

    bool PositionValide(const Position&) const;
    bool PositionValideFantome(const Position&) const;

    friend ostream& operator<<(ostream&, const Grille&);
};

ostream& operator<<(ostream&, const Grille&);

#endif //_GRILLE_H_
