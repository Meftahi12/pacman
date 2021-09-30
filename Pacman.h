#ifndef _PACMAN_H_
#define _PACMAN_H_

#include "Fantomes.h"
#include "Grille.h"
#include "Position.h"

#include <string>

using namespace std;

class Pacman
{
    // Constante pour les differents changement d'etat
    static const int TEMPS_APPEURE = 25;
    static const int TEMPS_EXPLORE = 14; // Habituellement 7 secondes
    static const int TEMPS_CHASSE = 40; // Habituellement 20 secondes

    enum GameMode
    {
        Normal,
        ExploreOnly,
        ChasseOnly,
        AppeureOnly
    };

    Grille m_grille;

    GameMode m_mode;
    Etat m_etatCourant;
    Etat m_etatSauvegarde;
    int m_iterationSauvegarde;
    int m_iterationCount;
    int m_iterationSortieMaison;

    // Derniere direction valide de Pacman
    Direction m_derniereDirection;

    // Les quatres fantomes
    Blinky m_blinky;
    Pinky m_pinky;
    Inky m_inky;
    Clyde m_clyde;

    // Methodes privees utilitaires
    string TraduireEtat(Etat) const;
    string TraduireMode(GameMode) const;
    void MetAJourFantomes(bool);
    void MetAJourEtat();
    bool TestFantomes();

public:
    Pacman();

    bool OuvrirCarte(string nomFichier);
    void Jouer();
};

#endif //_PACMAN_H_
