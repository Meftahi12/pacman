/**
* \file Pacman.cpp
* \author Vincent Ducharme
* \version 1.0 - Hiver 2017
* \brief Ce fichier contient le code des methodes de la classe Pacman responsable de la logique du jeu de Pacman
*/

#include "Pacman.h"

#include <fstream>

/**
* \brief Efface completement l'ecran
* \param Aucun
* \return Aucun
* \note Cette fonction contient du code specifique au systeme d'exploitation utilise.
*/
void ClearScreen()
{
#if defined(_WIN32)
    std::system("cls");
#else
    // Assume POSIX
    std::system("clear");
#endif
}

/**
* \brief Constructeur du jeu Pacman
* \param Aucun
*/
Pacman::Pacman()
    : m_derniereDirection(Droite)
    , m_blinky(Position(14, 14))
    , m_inky(Position(16, 12))
    , m_pinky(Position(17, 14))
    , m_clyde(Position(16, 16))
    , m_etatCourant(Etat::Explore)
    , m_iterationCount(TEMPS_EXPLORE)
    , m_iterationSortieMaison(0)
    , m_mode(GameMode::Normal)
{
}

/**
* \brief Ouvre une carte a partir d'un fichier
* \param [in] Nom du fichier contenant la carte
* \return Aucun
*/
bool Pacman::OuvrirCarte(string nomFichier)
{
    ifstream fichier;
    // 1. Ouvre le fichier
    fichier.open(nomFichier);
    // 2. Si le fichier est ouvert
    if (fichier.is_open())
    {
        // 2.1 Lit la carte
        m_grille.LireCarte(fichier);
        // 2.2 Initialise l'etat de Blinky dans la carte
        m_grille.UpdateBlinky(m_blinky.PositionCourante(), m_blinky.EtatCourant());
        // 2.3 Initialise l'etat de Pinky dans la carte
        m_grille.UpdatePinky(m_pinky.PositionCourante(), m_pinky.EtatCourant());
        // 2.4 Initialise l'etat de Inky dans la carte
        m_grille.UpdateInky(m_inky.PositionCourante(), m_inky.EtatCourant());
        // 2.5 Initialise l'etat de Clyde dans la carte
        m_grille.UpdateClyde(m_clyde.PositionCourante(), m_clyde.EtatCourant());
        // 2.6 Ferme le fichier
        fichier.close();
        // 2.7 Retourne vrai
        return true;
    }

    // 3. Retourne faux
    return false;
}

/**
* \brief Traduit une valeur de l'enumeration Etat en chaine de caracteres pour l'affichage
* \param [in] Etat a traduire
* \return Chaine de caractere represantant l'etat
*/
string Pacman::TraduireEtat(Etat e) const
{
    switch (e)
    {
    case Chasse:
        return "Chasse";
    case Appeure:
        return "Appeure";
    case Explore:
        return "Explore";
    case Attend:
        return "En attente";
    }
    return "Inconnu";
}

string Pacman::TraduireMode(GameMode m) const
{
    switch (m)
    {
    case GameMode::Normal:
        return "Normal";
    case GameMode::ChasseOnly:
        return "Chasse seulement";
    case GameMode::ExploreOnly:
        return "Exploration seulement";
    case GameMode::AppeureOnly:
        return "Appeure seulement";
    }
    return "Inconnu";
}

/**
* \brief Joue au jeu Pacman
* \param Aucun
* \return Aucun
*/
void Pacman::Jouer()
{
    // 1. Initialise le nombre d'iteration a faire pour l'etat Explore
    m_iterationCount = TEMPS_EXPLORE;
    // 2. Initialise l'etat courant a Explore
    m_etatCourant = Etat::Explore;
    char direction;
    bool mort = false;
    bool updateFantome = true;

    // 3. Faire
    do
    {
        updateFantome = true;

        // 3.1 Effacer tout ce qui est affiche a l'ecran
        ClearScreen();
        // 3.2 Afficher l'etat courant et le nombre d'iteration a faire avant de changer l'etat
        cout << " Mode : " << TraduireMode(m_mode) << endl;
        cout << " Etat courant : " << TraduireEtat(m_etatCourant) << "  ::::  Iteration restante : " << m_iterationCount << endl;
        // 3.3 Afficher la grille
        cout << m_grille;
        // 3.4 Lire la direction pour Pacman
        cin >> direction;
                
        // 3.5 Pour l'option choisie, recupere la direction voulue par le joueur
        // 3.6 Si l'option n'est pas valide, Pacman continue dans la derniere direction valide
        Direction directionDemande = m_derniereDirection;
        switch (direction)
        {
        case 'a':
        case 'A':
            directionDemande = Direction::Gauche;
            break;
        case 'w':
        case 'W':
            directionDemande = Direction::Haut;
            break;
        case 'd':
        case 'D':
            directionDemande = Direction::Droite;
            break;
        case 's':
        case 'S':
            directionDemande = Direction::Bas;
            break;
        case '1':
            m_mode = GameMode::Normal;
            updateFantome = false;
            break;
        case '2':
            m_mode = GameMode::ExploreOnly;
            updateFantome = false;
            break;
        case '3':
            m_mode = GameMode::ChasseOnly;
            updateFantome = false;
            break;
        case '4':
            m_mode = GameMode::AppeureOnly;
            updateFantome = false;
            break;
        }

        Position pacmanPosition = m_grille.PacmanPosition();

        // 3.7 Pour la direction voulue, execute le deplacement dans la direction demandee
        // 3.8 Si le deplacement est valide, on remplace la derniere direction valide par la nouvelle
        switch (directionDemande)
        {
        case Direction::Gauche:
            if (m_grille.DeplacePacman(pacmanPosition.Gauche()))
            {
                m_derniereDirection = directionDemande;
            }
            break;
        case Direction::Droite:
            if (m_grille.DeplacePacman(pacmanPosition.Droite()))
            {
                m_derniereDirection = directionDemande;
            }
            break;
        case Direction::Bas:
            if (m_grille.DeplacePacman(pacmanPosition.Bas()))
            {
                m_derniereDirection = directionDemande;
            }
            break;
        case Direction::Haut:
            if (m_grille.DeplacePacman(pacmanPosition.Haut()))
            {
                m_derniereDirection = directionDemande;
            }
            break;
        }

        // 3.9 Met a jour la direction de Pacman pour que les fantomes puissent l'utiliser
        m_grille.UpdatePacmanDirection(m_derniereDirection);

        // 3.10 Si Pacman est sur un fantome
        if (!TestFantomes())
        {
            // 3.10.1 Pacman s'est fait mange. On a perdu!
            mort = true;
            direction = 'q';
        }

        // 3.11 Decrementer le nombre d'iteration a effectue dans l'etat courant
        if (m_mode == GameMode::Normal)
        {
            --m_iterationCount;
        }
        // 3.12 Incrementer le nombre d'iteration pour les sorties des fantomes de la maison
        ++m_iterationSortieMaison;

        // 3.13 Si Pacman est sur une pastille
        if (m_mode == GameMode::Normal && m_grille.getAt(m_grille.PacmanPosition()) == Cases::Pastille)
        {
            // 3.13.1 On la mange
            m_grille.MangePastille();
            // 3.13.2 On sauvegarde l'etat courant
            m_etatSauvegarde = m_etatCourant;
            m_iterationSauvegarde = m_iterationCount;
            // 3.13.3 On change l'etat courant pour Appeure
            m_etatCourant = Etat::Appeure;
            // 3.13.4 On reset le compteur de tour pour l'etat
            m_iterationCount = TEMPS_APPEURE;
        }

        // 3.14 Mettre a jour l'etat courant
        MetAJourEtat();

        // 3.15 Mettre a jour les fantomes
        MetAJourFantomes(updateFantome);

        // 3.16 Si Pacman est sur un fantome
        if (!TestFantomes())
        {
            // 3.16.1 Pacman s'est fait mange. On a perdu!
            mort = true;
            direction = 'q';
        }
        
        // 3.17 Tant qu'on ne veut pas quitter (ou qu'on se soit fait manger)
    } while (direction != 'q' && direction != 'Q');

    // 4. Effacer tout ce qui est affiche a l'ecran
    ClearScreen();
    // 5. Afficher l'etat courant et le nombre d'iteration a faire avant de changer l'etat
    cout << " Etat courant : " << TraduireEtat(m_etatCourant) << "  ::::  Iteration restante : " << m_iterationCount << endl;
    // 6. Afficher la grille
    cout << m_grille;
    // 7. Si Pacman etait mort
    if (mort)
    {
        // 7.1 Afficher un message de fin de partie
        cout << "Vous etes mort! Vous avez perdu." << endl;
    }
}

/**
* \brief Tests si Pacman est sur un fantome et effectue le traitement approprie
* \param Aucun
* \return Faut si Pacman s'est fait mange, vrai autrement
*/
bool Pacman::TestFantomes()
{
    // 1. Si Pacman est sur Blinky
    if (m_grille.PacmanPosition() == m_blinky.PositionCourante())
    {
        // 1.1 Si l'etat est Appeure
        if (m_etatCourant == Etat::Appeure)
        {
            // 1.1.1 Blinky est mange, on le remet dans la maison
            m_blinky.RetourneMaison();
            // 1.1.2 On met a jour les informations de Blinky dans la grille
            m_grille.UpdateBlinky(m_blinky.PositionCourante(), m_blinky.EtatCourant());
        }
        else
        {
            // 1.2 Sinon, Pacman s'est fait mange. On a perdu!
            return false;
        }
    }

    // 2. Si Pacman est sur Inky
    if (m_grille.PacmanPosition() == m_inky.PositionCourante())
    {
        // 2.1 Si l'etat est Appeure
        if (m_etatCourant == Etat::Appeure)
        {
            // 2.1.1 Inky est mange, on le remet dans la maison
            m_inky.RetourneMaison();
            // 2.1.2 On met a jour les informations de Inky dans la grille
            m_grille.UpdateInky(m_inky.PositionCourante(), m_inky.EtatCourant());
        }
        else
        {
            // 2.2 Sinon, Pacman s'est fait mange. On a perdu!
            return false;
        }
    }

    // 3. Si Pacman est sur Pinky
    if (m_grille.PacmanPosition() == m_pinky.PositionCourante())
    {
        // 3.1 Si l'etat est Appeure
        if (m_etatCourant == Etat::Appeure)
        {
            // 3.1.1 Pinky est mange, on le remet dans la maison
            m_pinky.RetourneMaison();
            // 3.1.2 On met a jour les informations de Pinky dans la grille
            m_grille.UpdatePinky(m_pinky.PositionCourante(), m_pinky.EtatCourant());
        }
        else
        {
            // 3.2 Sinon, Pacman s'est fait mange. On a perdu!
            return false;
        }
    }

    // 4. Si Pacman est sur Clyde
    if (m_grille.PacmanPosition() == m_clyde.PositionCourante())
    {
        // 4.1 Si l'etat est Appeure
        if (m_etatCourant == Etat::Appeure)
        {
            // 4.1.1 Clyde est mange, on le remet dans la maison
            m_clyde.RetourneMaison();
            // 4.1.2 On met a jour les informations de Clyde dans la grille
            m_grille.UpdateClyde(m_clyde.PositionCourante(), m_clyde.EtatCourant());
        }
        else
        {
            // 4.2 Sinon, Pacman s'est fait mange. On a perdu!
            return false;
        }
    }

    // 5. Retourne vrai, tout est beau
    return true;
}

/**
* \brief Met a jour l'etat courant du jeu
* \param Aucun
* \return Aucun
*/
void Pacman::MetAJourEtat()
{
    if (m_mode == GameMode::Normal)
    {
        // 1. Si l'etat des fantomes n'est pas Appeure
        if (m_etatCourant != Etat::Appeure)
        {
            // 1.1 Si on est dans la phase d'exploration et qu'on a termine cette phase
            if (m_etatCourant == Etat::Explore && m_iterationCount <= 0)
            {
                // 1.1.1 On tombe en mode Chasse
                m_etatCourant = Etat::Chasse;
                // 1.1.2 Reinitialise le nombre d'iteration a faire dans cette phase a TEMPS_CHASSE
                m_iterationCount = TEMPS_CHASSE;
            }
            // 1.2 Sinon, si on est dans la phase de Chasse et qu'on a termine cette phase
            else if (m_etatCourant == Etat::Chasse && m_iterationCount <= 0)
            {
                // 1.2.1 On tombe en mode Exploration
                m_etatCourant = Etat::Explore;
                // 1.2.2 Reinitialise le nombre d'iteration a faire dans cette phase a TEMPS_EXPLORE
                m_iterationCount = TEMPS_EXPLORE;
            }
        }
        else // 2. Sinon
        {
            // 2.1 Si le nombre d'iteration dans lequel les fantomes ont peur est fini
            if (m_iterationCount <= 0)
            {
                // 2.1.1 On revient dans l'etat precedent valide
                m_etatCourant = m_etatSauvegarde;
                // 2.1.2 On reset le compteur de tour
                m_iterationCount = m_iterationSauvegarde;
            }
        }
    }
    else if (m_mode == GameMode::ChasseOnly)
    {
        m_etatCourant = Etat::Chasse;
    }
    else if (m_mode == GameMode::ExploreOnly)
    {
        m_etatCourant = Etat::Explore;
    }
    else if (m_mode == GameMode::AppeureOnly)
    {
        m_etatSauvegarde = m_etatCourant;
        m_iterationSauvegarde = m_iterationCount;
        m_etatCourant = Etat::Appeure;
    }
}

/**
* \brief Met a jour les fantomes
* \param Aucun
* \return Aucun
*/
void Pacman::MetAJourFantomes(bool deplace)
{
    // 1. Met a jour l'etat de Blinky
    m_blinky.UpdateEtat(m_etatCourant);
    // 2. Met a jour l'etat de Pinky
    m_pinky.UpdateEtat(m_etatCourant);
    // 3. Si le nombre d'iteration est plus grand que 30
    if (m_iterationSortieMaison >= 30)
    {
        // 3.1 On met a jour l'etat de Inky
        m_inky.UpdateEtat(m_etatCourant);
        // 3.2 Si le nombre d'iteration est plus grand que 90
        if (m_iterationSortieMaison >= 90)
        {
            // 3.2.1 On met a jour l'etat de Clyde
            m_clyde.UpdateEtat(m_etatCourant);
        }
    }

    //4. Deplace les fantomes
    if (deplace)
    {
        m_blinky.Deplace(m_grille);
        m_inky.Deplace(m_grille);
        m_pinky.Deplace(m_grille);
        m_clyde.Deplace(m_grille);
    }
}

