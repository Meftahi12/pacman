#include "Position.h"

#include <cmath>

Position::Position()
    : m_ligne(0)
    , m_colonne(0)
{
}

Position::Position(int ligne, int colonne)
    : m_ligne(ligne)
    , m_colonne(colonne)
{
}

int Position::getLigne() const
{
    return m_ligne;
}

int Position::getColonne() const
{
    return m_colonne;
}

double Position::Distance(const Position& p) const
{
    Position distance = p - (*this);
    return std::sqrt((distance.getLigne() * distance.getLigne()) + (distance.getColonne() * distance.getColonne()));
}

Position Position::Gauche() const
{
    return Position(this->getLigne(), this->getColonne() + 1);
}

Position Position::Droite() const
{
    return Position(this->getLigne(), this->getColonne() - 1);
}

Position Position::Haut() const
{
    return Position(this->getLigne() - 1, this->getColonne());
}

Position Position::Bas() const
{
    return Position(this->getLigne() + 1, this->getColonne());
}

bool Position::operator!=(const Position& p)
{
    return !(*this == p);
}

bool Position::operator==(const Position& p) 
{
    return (this -> getLigne() == p.getLigne() && this -> getColonne() == p.getColonne());
}


Position Position::operator+(const Position& p) const
{
    return Position(m_ligne + p.getLigne(), m_colonne + p.getColonne());
}

Position Position::operator-(const Position& p) const
{
    return Position(m_ligne - p.getLigne(), m_colonne - p.getColonne());
}
