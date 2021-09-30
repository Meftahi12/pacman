#ifndef _POSITION_H_
#define _POSITION_H_

enum Direction
{
    Haut,
    Gauche,
    Bas,
    Droite,
};

class Position
{
    int m_ligne;
    int m_colonne;

public:
    Position();
    Position(int ligne, int colonne);

    int getLigne() const;
    int getColonne() const;

    double Distance(const Position&) const;
    Position Gauche() const;
    Position Droite() const;
    Position Haut() const;
    Position Bas() const;

    bool operator!=(const Position&);
    bool operator==(const Position&);

    Position operator-(const Position&) const;
    Position operator+(const Position&) const;
};

#endif //_POSITION_H_
