#include "Grille.h"

#if defined(_WIN32)
#include <Windows.h>
#endif

enum Color
{
    BleuFonce = 1,
    Bleu = 9,
    Cyan = 11,
    Rouge = 12,
    Rose = 13,
    Orange = 6,
    Jaune = 14,
    Blanc = 15
};

void SetConsoleColor(Color c)
{
#if defined(_WIN32)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (int)c);
#else
    string color = "\033[0m";
    switch (c)
    {
    case BleuFonce:
        color = "\033[2;34;40m";
        break;
    case Bleu:
        color = "\033[0;34;40m";
        break;
    case Cyan:
        color = "\033[0;36;40m";
        break;
    case Rouge:
        color = "\033[0;31;40m";
        break;
    case Rose:
        color = "\033[0;35;40m";
        break;
    case Orange:
        color = "\033[2;33;40m";
        break;
    case Jaune:
        color = "\033[1;33;40m";
        break;
    case Blanc:
        color = "\033[0;37;40m";
        break;
    }
    cout << color;
#endif
}

Grille::Grille()
    : m_pacman(20, 13)
{
}

void Grille::LireCarte(ifstream& fichierCarte)
{
    for (int ligne = 0; ligne < LIGNE; ++ligne)
    {
        for (int colonne = 0; colonne < COLONNE; ++colonne)
        {
            int valeur;
            fichierCarte >> valeur;

            switch (valeur)
            {
            case 0:
                m_cases.at(ligne).at(colonne) = Cases::Chemin;
                break;
            case 1:
                m_cases.at(ligne).at(colonne) = Cases::Mur;
                break;
            case 2:
                m_cases.at(ligne).at(colonne) = Cases::Maison;
                break;
            case 3:
                m_cases.at(ligne).at(colonne) = Cases::Porte;
                break;
            case 4:
                m_cases.at(ligne).at(colonne) = Cases::Demitour;
                break;
            case 5:
                m_cases.at(ligne).at(colonne) = Cases::Exterieur;
                break;
            case 6:
                m_cases.at(ligne).at(colonne) = Cases::Pastille;
                break;
            default:
                m_cases.at(ligne).at(colonne) = Cases::Invalide;
                break;
            }
        }
    }
}

bool Grille::PositionValideFantome(const Position& p) const
{
    Cases c = getAt(p);
    return c == Cases::Chemin || c == Cases::Pastille;
}

bool Grille::PositionValide(const Position& p) const
{
    Cases c = getAt(p);
    return c == Cases::Chemin || c == Cases::Demitour || c == Cases::Pastille;
}

bool Grille::DevraitFaireDemiTour(const Position& p) const
{
    return p.getLigne() == 17 && (p.getColonne() == 0 || p.getColonne() == COLONNE - 1);
}

Cases Grille::getAt(const Position& p) const
{
    if (p.getLigne() >= 0 && p.getLigne() < LIGNE && p.getColonne() >= 0 && p.getColonne() < COLONNE)
        return m_cases.at(p.getLigne()).at(p.getColonne());
    else
        return Cases::Invalide;
}

void Grille::MangePastille()
{
    m_cases.at(m_pacman.getLigne()).at(m_pacman.getColonne()) = Cases::Chemin;
}

Position Grille::BlinkyPosition() const
{
    return m_blinkyPosition;
}

Position Grille::PacmanPosition() const
{
    return m_pacman;
}

Direction Grille::PacmanDirection() const
{
    return m_pacmanDirection;
}

void Grille::UpdatePacmanDirection(Direction d)
{
    m_pacmanDirection = d;
}

bool Grille::DeplacePacman(const Position& p)
{
    if (DevraitFaireDemiTour(m_pacman) && !PositionValide(p))
    {
        if (m_pacman.Droite() == p)
        {
            m_pacman = Position(p.getLigne(), 0);
        }
        else
        {
            m_pacman = Position(p.getLigne(), COLONNE - 1);
        }
        return true;
    }
    else if (PositionValide(p))
    {
        m_pacman = p;
        return true;
    }
    return false;
}

void Grille::UpdateBlinky(const Position& p, Etat e)
{
    m_blinkyPosition = p;
    m_blinkyEtat = e;
}

void Grille::UpdatePinky(const Position& p, Etat e)
{
    m_pinkyPosition = p;
    m_pinkyEtat = e;
}

void Grille::UpdateInky(const Position& p, Etat e)
{
    m_inkyPosition = p;
    m_inkyEtat = e;
}

void Grille::UpdateClyde(const Position& p, Etat e)
{
    m_clydePosition = p;
    m_clydeEtat = e;
}

bool Grille::EstConsidereChemin(Cases c) const
{
    return c == Cases::Chemin || c == Cases::Demitour || c == Cases::Porte || c == Cases::Pastille;
}

ostream& operator<<(ostream& out, const Grille& grille)
{
#if defined(_WIN32)
    const unsigned char BARRE_HORIZONTALE = 205;
    const unsigned char BARRE_VERTICALE = 186;
    const unsigned char COIN_INF_DROIT = 200;
    const unsigned char COIN_SUP_DROIT = 201;
    const unsigned char COIN_SUP_GAUCHE = 187;
    const unsigned char COIN_INF_GAUCHE = 188;
    const unsigned char PASTILLE_DROITE = 219;
    const unsigned char PASTILLE_GAUCHE = 219;
    const unsigned char PORTE = 196;
    const unsigned char SPACER = ' ';
#else
    const string BARRE_HORIZONTALE = "\u2550";
    const string BARRE_VERTICALE = "\u2551";
    const string COIN_INF_DROIT = "\u255a";
    const string COIN_SUP_DROIT = "\u2554";
    const string COIN_SUP_GAUCHE = "\u2557";
    const string COIN_INF_GAUCHE = "\u255d";
    const string PASTILLE_GAUCHE = "\u2590";
    const string PASTILLE_DROITE = "\u258c";
    const string PORTE = "\u2500";
    const unsigned char SPACER = ' ';
#endif
    for (int ligne = 0; ligne < Grille::LIGNE; ++ligne)
    {
        for (int colonne = 0; colonne < Grille::COLONNE; ++colonne)
        {
            Cases c = grille.m_cases.at(ligne).at(colonne);
            Position courante(ligne, colonne);
            Position haut = courante.Haut();
            Position bas = courante.Bas();
            Position gauche = courante.Gauche();
            Position droite = courante.Droite();
            if (c == Cases::Mur)
            {
                SetConsoleColor(Color::Bleu);
                if (grille.getAt(haut) == Cases::Mur && grille.getAt(bas) == Cases::Mur)
                {
                    // On est entre deux murs, de fa�on verticale
                    // Si le chemin est � droite, on met l'espace apr�s le symbole
                    if (grille.EstConsidereChemin(grille.getAt(droite)))
                    {
                        out << BARRE_VERTICALE << SPACER;
                    }
                    // Sinon, si le chemin est � gauche, on le met avant
                    else if (grille.EstConsidereChemin(grille.getAt(gauche)))
                    {
                        out << SPACER << BARRE_VERTICALE;
                    }
                    // Sinon, on fait un coin int�rieur
                    else
                    {
                        if (grille.EstConsidereChemin(grille.getAt(bas.Gauche())))
                        {
                            out << BARRE_HORIZONTALE << COIN_SUP_GAUCHE;
                        }
                        else if (grille.EstConsidereChemin(grille.getAt(bas.Droite())))
                        {
                            out << COIN_SUP_DROIT << BARRE_HORIZONTALE;
                        }
                        else if (grille.EstConsidereChemin(grille.getAt(haut.Gauche())))
                        {
                            out << BARRE_HORIZONTALE << COIN_INF_GAUCHE;
                        }
                        else if (grille.EstConsidereChemin(grille.getAt(haut.Droite())))
                        {
                            out << COIN_INF_DROIT << BARRE_HORIZONTALE;
                        }
                        else
                        {
                            out << SPACER << SPACER;
                        }
                    }
                }
                // On met un mur horizontal
                else if ((grille.getAt(droite) == Cases::Mur && grille.getAt(gauche) == Cases::Mur) || (grille.getAt(droite) == Cases::Porte || grille.getAt(gauche) == Cases::Porte))
                {
                    if (grille.EstConsidereChemin(grille.getAt(haut)) || grille.EstConsidereChemin(grille.getAt(bas)))
                    {
                        out << BARRE_HORIZONTALE << BARRE_HORIZONTALE;
                    }
                    else
                    {
                        if (grille.EstConsidereChemin(grille.getAt(bas.Gauche())))
                        {
                            out << BARRE_HORIZONTALE << COIN_SUP_GAUCHE;
                        }
                        else if (grille.EstConsidereChemin(grille.getAt(bas.Droite())))
                        {
                            out << COIN_SUP_DROIT << BARRE_HORIZONTALE;
                        }
                        else if (grille.EstConsidereChemin(grille.getAt(haut.Gauche())))
                        {
                            out << BARRE_HORIZONTALE << COIN_INF_GAUCHE;
                        }
                        else if (grille.EstConsidereChemin(grille.getAt(haut.Droite())))
                        {
                            out << COIN_INF_DROIT << BARRE_HORIZONTALE;
                        }
                        else
                        {
                            out << SPACER << SPACER;
                        }
                    }
                }
                // Le bout du passage turnaround
                else if ((grille.getAt(droite) == Cases::Invalide && grille.getAt(gauche) == Cases::Mur && grille.getAt(bas) == Cases::Chemin)
                      || (grille.getAt(droite) == Cases::Invalide && grille.getAt(gauche) == Cases::Mur && grille.getAt(haut) == Cases::Chemin)
                      || (grille.getAt(droite) == Cases::Mur && grille.getAt(gauche) == Cases::Invalide && grille.getAt(bas) == Cases::Chemin)
                      || (grille.getAt(droite) == Cases::Mur && grille.getAt(gauche) == Cases::Invalide && grille.getAt(haut) == Cases::Chemin))
                {
                    out << BARRE_HORIZONTALE << BARRE_HORIZONTALE;
                }
                else if (grille.getAt(haut) == Cases::Mur && (grille.EstConsidereChemin(grille.getAt(bas)) || grille.getAt(bas) == Cases::Exterieur))
                {
                    if (grille.getAt(droite) == Cases::Mur)
                    {
                        if (grille.getAt(bas) == Cases::Exterieur)
                        {
                            out << COIN_INF_DROIT << BARRE_HORIZONTALE;
                        }
                        else
                        {
                            out << SPACER << COIN_INF_DROIT;
                        }
                    }
                    else if (grille.getAt(gauche) == Cases::Mur)
                    {
                        if (grille.getAt(bas) == Cases::Exterieur)
                        {
                            out << BARRE_HORIZONTALE << COIN_INF_GAUCHE;
                        }
                        else
                        {
                            out << COIN_INF_GAUCHE << SPACER;
                        }
                    }
                }
                else if (grille.getAt(bas) == Cases::Mur && (grille.EstConsidereChemin(grille.getAt(haut)) || grille.getAt(haut) == Cases::Exterieur))
                {
                    if (grille.getAt(droite) == Cases::Mur)
                    {
                        if (grille.getAt(haut) == Cases::Exterieur)
                        {
                            out << COIN_SUP_DROIT << BARRE_HORIZONTALE;
                        }
                        else
                        {
                            out << SPACER << COIN_SUP_DROIT;
                        }
                    }
                    else if (grille.getAt(gauche) == Cases::Mur)
                    {
                        if (grille.getAt(haut) == Cases::Exterieur)
                        {
                            out << BARRE_HORIZONTALE << COIN_SUP_GAUCHE;
                        }
                        else
                        {
                            out << COIN_SUP_GAUCHE << SPACER;
                        }
                    }
                }
                else
                {
                    out << (unsigned char)219 << (unsigned char)219;
                }
                SetConsoleColor(Color::Blanc);
            }
            else if (courante == grille.m_pacman)
            {
                SetConsoleColor(Color::Jaune);
                if (grille.PacmanDirection() == Direction::Bas)
                {
                    out << "/\\";
                }
                else if (grille.PacmanDirection() == Direction::Droite)
                {
                    out << "(<";
                }
                else if (grille.PacmanDirection() == Direction::Gauche)
                {
                    out << ">)";
                }
                else if (grille.PacmanDirection() == Direction::Haut)
                {
                    out << "\\/";
                }
                else
                {
                    out << '(' << ')';
                }
                SetConsoleColor(Color::Blanc);
            }
            else if (courante == grille.m_blinkyPosition)
            {
                if (grille.m_blinkyEtat == Etat::Appeure)
                {
                    SetConsoleColor(Color::BleuFonce);
                }
                else
                {
                    SetConsoleColor(Color::Rouge);
                }
                out << "##";
                SetConsoleColor(Color::Blanc);
            }
            else if (courante == grille.m_inkyPosition)
            {
                if (grille.m_inkyEtat == Etat::Appeure)
                {
                    SetConsoleColor(Color::BleuFonce);
                }
                else
                {
                    SetConsoleColor(Color::Cyan);
                }
                out << "%%";
                SetConsoleColor(Color::Blanc);
            }
            else if (courante == grille.m_pinkyPosition)
            {
                if (grille.m_pinkyEtat == Etat::Appeure)
                {
                    SetConsoleColor(Color::BleuFonce);
                }
                else
                {
                    SetConsoleColor(Color::Rose);
                }
                out << "88";
                SetConsoleColor(Color::Blanc);
            }
            else if (courante == grille.m_clydePosition)
            {
                if (grille.m_clydeEtat == Etat::Appeure)
                {
                    SetConsoleColor(Color::BleuFonce);
                }
                else
                {
                    SetConsoleColor(Color::Orange);
                }
                out << "69";
                SetConsoleColor(Color::Blanc);
            }
            else if (grille.EstConsidereChemin(c) || c == Cases::Maison || c == Cases::Exterieur)
            {
                if (c == Cases::Pastille)
                {
                    out << PASTILLE_GAUCHE << PASTILLE_DROITE;
                }
                else if (c == Cases::Porte)
                {
                    out << PORTE << PORTE;
                }
                else
                {
                    out << "  ";
                }
            }
            
        }
        out << endl;
    }
    return out;
}