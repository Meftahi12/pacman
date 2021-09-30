

#include "Fantomes.h"
#include "Random.h"
#include <fstream>


Blinky::Blinky(Position p){
    this -> m_PositionCourante = p;
    this -> m_derniereDirection = Direction::Gauche;

}

int Blinky::Direction(Grille grille, Position cible){
    int min = -1;
    double minValue = -1;
    
    if(grille.PositionValideFantome(this -> PositionCourante().Haut())) {
        min = Direction::Haut;
        minValue = cible.Distance(this -> PositionCourante().Haut());
    }

    if(grille.PositionValideFantome(this -> PositionCourante().Bas())) {
        if(min == -1){
            min = Direction::Bas;
            minValue = cible.Distance(this -> PositionCourante().Bas());
        }
        else{
            if(minValue < cible.Distance(this -> PositionCourante().Bas())){
                min = Direction::Bas;
                minValue = cible.Distance(this -> PositionCourante().Bas());
            }
        }
    }
    if(grille.PositionValideFantome(this -> PositionCourante().Droite())) {
        if(min == -1){
            min = Direction::Droite;
            minValue = cible.Distance(this -> PositionCourante().Droite());
        }
        else{
            if(minValue < cible.Distance(this -> PositionCourante().Droite())){
                min = Direction::Droite;
                minValue = cible.Distance(this -> PositionCourante().Droite());
            }
        }
    }

    if(grille.PositionValideFantome(this -> PositionCourante().Gauche())) {
        if(min == -1){
            min = Direction::Gauche;
            minValue = cible.Distance(this -> PositionCourante().Gauche());
        }
        else{
            if(minValue < cible.Distance(this -> PositionCourante().Gauche())){
                min = Direction::Gauche;
                minValue = cible.Distance(this -> PositionCourante().Gauche());
            }
        }
    }

    return min;
}

void Blinky::Deplace(Grille grille){  
    cout << "etat courant : " << m_etatCourant << endl;  
    if(this -> m_etatCourant == Etat::Appeure){
        int direction = Random::GenereValeur(0, 4);
        bool isDone = false;
        while (!isDone){
            switch(direction){
            case Direction::Gauche:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Gauche())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            case Direction::Droite:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Droite())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            case Direction::Bas:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Bas())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            case Direction::Haut:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Haut())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            }
        }
        this -> DeplaceDirection(direction);
        grille.UpdateBlinky(this -> m_PositionCourante, this -> m_etatCourant); 
    }
    else if(this -> m_etatCourant == Etat::Attend){
            Position haut = this -> m_PositionCourante.Haut();
            Position bas = this -> m_PositionCourante.Bas();
            if (grille.getAt(haut) == Cases::Mur && grille.getAt(bas) == Cases::Mur){
                this -> DeplaceDirection((this -> m_derniereDirection + 2) % 4);
                grille.UpdateBlinky(this -> m_PositionCourante, this -> m_etatCourant);
            }
    }
    else if(this -> m_etatCourant == Etat::Chasse){
        int direction = this -> Direction(grille, grille.PacmanPosition());
        this -> DeplaceDirection(direction);
        grille.UpdateBlinky(this -> m_PositionCourante, this -> m_etatCourant);
    }
    else{
        int direction = this -> Direction(grille, Position(0, 25));
        this -> DeplaceDirection(direction);
        grille.UpdateBlinky(this -> m_PositionCourante, this -> m_etatCourant);
    }
}

void Blinky::DeplaceDirection(int direction){

    switch(direction){
        case Direction::Gauche:
            this -> m_PositionCourante = this -> m_PositionCourante.Gauche();
            this -> m_derniereDirection = Direction::Gauche;
            break;
        case Direction::Droite:
            this -> m_PositionCourante = this -> m_PositionCourante.Droite();
            this -> m_derniereDirection = Direction::Droite;
            break;
        case Direction::Bas:
            this -> m_PositionCourante = this -> m_PositionCourante.Bas();
            this -> m_derniereDirection = Direction::Bas;
            break;
        case Direction::Haut:
            this -> m_PositionCourante = this -> m_PositionCourante.Haut();
            this -> m_derniereDirection = Direction::Haut;
            break;
    }
}

Etat Blinky::EtatCourant(){
    return m_etatCourant;
}

Position Blinky::PositionCourante(){
    return m_PositionCourante;
}

void Blinky::UpdateEtat(Etat e){
    this -> m_etatCourant = e;
}

void Blinky::RetourneMaison(){
    this -> m_PositionCourante = Position(18, 14);
}

Pinky::Pinky(Position p){
    this -> m_PositionCourante = p;
    this -> m_derniereDirection = Direction::Haut;
}

int Pinky::Direction(Grille grille, Position cible){
    int min = -1;
    double minValue = -1;
    
    if(grille.PositionValideFantome(this -> PositionCourante().Haut())) {
        min = Direction::Haut;
        minValue = cible.Distance(this -> PositionCourante().Haut());
    }

    if(grille.PositionValideFantome(this -> PositionCourante().Bas())) {
        if(min == -1){
            min = Direction::Bas;
            minValue = cible.Distance(this -> PositionCourante().Bas());
        }
        else{
            if(minValue < cible.Distance(this -> PositionCourante().Bas())){
                min = Direction::Bas;
                minValue = cible.Distance(this -> PositionCourante().Bas());
            }
        }
    }
    if(grille.PositionValideFantome(this -> PositionCourante().Droite())) {
        if(min == -1){
            min = Direction::Droite;
            minValue = cible.Distance(this -> PositionCourante().Droite());
        }
        else{
            if(minValue < cible.Distance(this -> PositionCourante().Droite())){
                min = Direction::Droite;
                minValue = cible.Distance(this -> PositionCourante().Droite());
            }
        }
    }

    if(grille.PositionValideFantome(this -> PositionCourante().Gauche())) {
        if(min == -1){
            min = Direction::Gauche;
            minValue = cible.Distance(this -> PositionCourante().Gauche());
        }
        else{
            if(minValue < cible.Distance(this -> PositionCourante().Gauche())){
                min = Direction::Gauche;
                minValue = cible.Distance(this -> PositionCourante().Gauche());
            }
        }
    }

    return min;
}

void Pinky::Deplace(Grille grille){
    
    if(this -> m_etatCourant == Etat::Appeure){
        int direction = Random::GenereValeur(0, 4);
        bool isDone = false;
        while (!isDone){
            switch(direction){
            case Direction::Gauche:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Gauche())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            case Direction::Droite:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Droite())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            case Direction::Bas:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Bas())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            case Direction::Haut:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Haut())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            }
        }
        this -> DeplaceDirection(direction);
        grille.UpdatePinky(this -> m_PositionCourante, this -> m_etatCourant); 
    }
    else if(this -> m_etatCourant == Etat::Attend){
            Position haut = this -> m_PositionCourante.Haut();
            Position bas = this -> m_PositionCourante.Bas();
            if (grille.getAt(haut) == Cases::Mur && grille.getAt(bas) == Cases::Mur){
                this -> DeplaceDirection((this -> m_derniereDirection + 2) % 4);
                grille.UpdatePinky(this -> m_PositionCourante, this -> m_etatCourant);
            }
    }
    else if(this -> m_etatCourant == Etat::Explore){
        int direction = this -> Direction(grille, Position(0, 2));
        this -> DeplaceDirection(direction);
    }
    else if(this -> m_etatCourant == Etat::Chasse){
        int Pacman_direction = grille.PacmanDirection();
        int direction;
        switch(Pacman_direction){
            case Direction::Gauche:
                direction = this -> Direction(grille, Position(grille.PacmanPosition().getLigne(), grille.PacmanPosition().getColonne() + 4));
                break;
            case Direction::Droite:
                direction = this -> Direction(grille, Position(grille.PacmanPosition().getLigne(), grille.PacmanPosition().getColonne() - 4));
                break;
            case Direction::Bas:
                direction = this -> Direction(grille, Position(grille.PacmanPosition().getLigne() + 4, grille.PacmanPosition().getColonne()));
                break;
            case Direction::Haut:
                direction = this -> Direction(grille, Position(grille.PacmanPosition().getLigne() - 4, grille.PacmanPosition().getColonne()));
                break;
        }
        this -> DeplaceDirection(direction);
    }
    grille.UpdatePinky(this -> m_PositionCourante, this -> m_etatCourant);
}

void Pinky::DeplaceDirection(int direction){

    switch(direction){
        case Direction::Gauche:
            this -> m_PositionCourante = this -> m_PositionCourante.Gauche();
            this -> m_derniereDirection = Direction::Gauche;
            break;
        case Direction::Droite:
            this -> m_PositionCourante = this -> m_PositionCourante.Droite();
            this -> m_derniereDirection = Direction::Droite;
            break;
        case Direction::Bas:
            this -> m_PositionCourante = this -> m_PositionCourante.Bas();
            this -> m_derniereDirection = Direction::Bas;
            break;
        case Direction::Haut:
            this -> m_PositionCourante = this -> m_PositionCourante.Haut();
            this -> m_derniereDirection = Direction::Haut;
            break;
    }
}

Etat Pinky::EtatCourant(){
    return m_etatCourant;
}

Position Pinky::PositionCourante(){
    return m_PositionCourante;
}

void Pinky::UpdateEtat(Etat e){
    this -> m_etatCourant = e;
}

void Pinky::RetourneMaison(){
    this -> m_PositionCourante = Position(18, 14);
}

Clyde::Clyde(Position p){
    this -> m_PositionCourante = p;
    this -> m_derniereDirection = Direction::Bas;
}

void Clyde::DeplaceDirection(int direction){

    switch(direction){
        case Direction::Gauche:
            this -> m_PositionCourante = this -> m_PositionCourante.Gauche();
            this -> m_derniereDirection = Direction::Gauche;
            break;
        case Direction::Droite:
            this -> m_PositionCourante = this -> m_PositionCourante.Droite();
            this -> m_derniereDirection = Direction::Droite;
            break;
        case Direction::Bas:
            this -> m_PositionCourante = this -> m_PositionCourante.Bas();
            this -> m_derniereDirection = Direction::Bas;
            break;
        case Direction::Haut:
            this -> m_PositionCourante = this -> m_PositionCourante.Haut();
            this -> m_derniereDirection = Direction::Haut;
            break;
    }
}

int Clyde::Direction(Grille grille, Position cible){
    int min = -1;
    double minValue = -1;
    
    if(grille.PositionValideFantome(this -> PositionCourante().Haut())) {
        min = Direction::Haut;
        minValue = cible.Distance(this -> PositionCourante().Haut());
    }

    if(grille.PositionValideFantome(this -> PositionCourante().Bas())) {
        if(min == -1){
            min = Direction::Bas;
            minValue = cible.Distance(this -> PositionCourante().Bas());
        }
        else{
            if(minValue < cible.Distance(this -> PositionCourante().Bas())){
                min = Direction::Bas;
                minValue = cible.Distance(this -> PositionCourante().Bas());
            }
        }
    }
    if(grille.PositionValideFantome(this -> PositionCourante().Droite())) {
        if(min == -1){
            min = Direction::Droite;
            minValue = cible.Distance(this -> PositionCourante().Droite());
        }
        else{
            if(minValue < cible.Distance(this -> PositionCourante().Droite())){
                min = Direction::Droite;
                minValue = cible.Distance(this -> PositionCourante().Droite());
            }
        }
    }

    if(grille.PositionValideFantome(this -> PositionCourante().Gauche())) {
        if(min == -1){
            min = Direction::Gauche;
            minValue = cible.Distance(this -> PositionCourante().Gauche());
        }
        else{
            if(minValue < cible.Distance(this -> PositionCourante().Gauche())){
                min = Direction::Gauche;
                minValue = cible.Distance(this -> PositionCourante().Gauche());
            }
        }
    }

    return min;
}

void Clyde::Deplace(Grille grille){
    
    if(this -> m_etatCourant == Etat::Appeure){
        int direction = Random::GenereValeur(0, 4);
        bool isDone = false;
        while (!isDone){
            switch(direction){
            case Direction::Gauche:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Gauche())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            case Direction::Droite:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Droite())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            case Direction::Bas:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Bas())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            case Direction::Haut:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Haut())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            }
        }
        this -> DeplaceDirection(direction);
        grille.UpdateClyde(this -> m_PositionCourante, this -> m_etatCourant); 
    }
    else if(this -> m_etatCourant == Etat::Attend){
            Position haut = this -> m_PositionCourante.Haut();
            Position bas = this -> m_PositionCourante.Bas();
            if (grille.getAt(haut) == Cases::Mur && grille.getAt(bas) == Cases::Mur){
                this -> DeplaceDirection((this -> m_derniereDirection + 2) % 4);
                grille.UpdateClyde(this -> m_PositionCourante, this -> m_etatCourant);
            }
    }
    else if(this -> m_etatCourant == Etat::Explore){
        int direction = this -> Direction(grille, Position(35, 0));
        this -> DeplaceDirection(direction);
    }
    else if(this -> m_etatCourant == Etat::Chasse){
        int directionPacman = this -> Direction(grille, grille.PacmanPosition());
        switch(directionPacman){
            case Direction::Gauche:
                if(grille.PacmanPosition().Distance(this -> PositionCourante().Gauche()) <= 8){
                    int direction = this -> Direction(grille, Position(35, 0));
                    this -> DeplaceDirection(direction);
                }
                else{
                     this -> m_PositionCourante = this -> m_PositionCourante.Gauche();
                }
                break;
            case Direction::Droite:
                if(grille.PacmanPosition().Distance(this -> PositionCourante().Droite()) <= 8){
                    int direction = this -> Direction(grille, Position(35, 0));
                    this -> DeplaceDirection(direction);
                }
                else{
                     this -> m_PositionCourante = this -> m_PositionCourante.Droite();
                }
                break;
            case Direction::Bas:
                if(grille.PacmanPosition().Distance(this -> PositionCourante().Bas()) <= 8){
                    int direction = this -> Direction(grille, Position(35, 0));
                    this -> DeplaceDirection(direction);
                }
                else{
                     this -> m_PositionCourante = this -> m_PositionCourante.Bas();
                }
                break;
            case Direction::Haut:
                if(grille.PacmanPosition().Distance(this -> PositionCourante().Haut()) <= 8){
                    int direction = this -> Direction(grille, Position(35, 0));
                    this -> DeplaceDirection(direction);
                }
                else{
                     this -> m_PositionCourante = this -> m_PositionCourante.Haut();
                }
                break;
         
        }   
    }
    grille.UpdateClyde(this -> m_PositionCourante, this -> m_etatCourant);
}

Etat Clyde::EtatCourant(){
    return m_etatCourant;
}

Position Clyde::PositionCourante(){
    return m_PositionCourante;
}

void Clyde::UpdateEtat(Etat e){
    this -> m_etatCourant = e;
}

void Clyde::RetourneMaison(){
    this -> m_PositionCourante = Position(18, 14);
}
    
Inky::Inky(Position p){
    this -> m_PositionCourante = p;
    this -> m_derniereDirection = Direction::Bas;
}

int Inky::Direction(Grille grille, Position cible){
    int min = -1;
    double minValue = -1;
    
    if(grille.PositionValideFantome(this -> PositionCourante().Haut())) {
        min = Direction::Haut;
        minValue = cible.Distance(this -> PositionCourante().Haut());
    }

    if(grille.PositionValideFantome(this -> PositionCourante().Bas())) {
        if(min == -1){
            min = Direction::Bas;
            minValue = cible.Distance(this -> PositionCourante().Bas());
        }
        else{
            if(minValue < cible.Distance(this -> PositionCourante().Bas())){
                min = Direction::Bas;
                minValue = cible.Distance(this -> PositionCourante().Bas());
            }
        }
    }
    if(grille.PositionValideFantome(this -> PositionCourante().Droite())) {
        if(min == -1){
            min = Direction::Droite;
            minValue = cible.Distance(this -> PositionCourante().Droite());
        }
        else{
            if(minValue < cible.Distance(this -> PositionCourante().Droite())){
                min = Direction::Droite;
                minValue = cible.Distance(this -> PositionCourante().Droite());
            }
        }
    }

    if(grille.PositionValideFantome(this -> PositionCourante().Gauche())) {
        if(min == -1){
            min = Direction::Gauche;
            minValue = cible.Distance(this -> PositionCourante().Gauche());
        }
        else{
            if(minValue < cible.Distance(this -> PositionCourante().Gauche())){
                min = Direction::Gauche;
                minValue = cible.Distance(this -> PositionCourante().Gauche());
            }
        }
    }

    return min;
}

void Inky::Deplace(Grille grille){    
    if(this -> m_etatCourant == Etat::Appeure){
        int direction = Random::GenereValeur(0, 4);
        bool isDone = false;
        while (!isDone){
            switch(direction){
            case Direction::Gauche:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Gauche())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            case Direction::Droite:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Droite())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            case Direction::Bas:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Bas())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            case Direction::Haut:
                if(direction != this -> m_derniereDirection && grille.PositionValideFantome(this -> m_PositionCourante.Haut())) 
                    isDone = true;
                    else{
                        direction = (direction + 1) % 4;
                    }
                break;
            }
        }
        this -> DeplaceDirection(direction);
        grille.UpdateInky(this -> m_PositionCourante, this -> m_etatCourant); 
    }
    else if(this -> m_etatCourant == Etat::Attend){
            Position haut = this -> m_PositionCourante.Haut();
            Position bas = this -> m_PositionCourante.Bas();
            if (grille.getAt(haut) == Cases::Mur && grille.getAt(bas) == Cases::Mur){
                this -> DeplaceDirection((this -> m_derniereDirection + 2) % 4);
                grille.UpdateInky(this -> m_PositionCourante, this -> m_etatCourant);
            }
    }
    else if(this -> m_etatCourant == Etat::Chasse){
        int direction = this -> Direction(grille, grille.PacmanPosition());
        this -> DeplaceDirection(direction);
        grille.UpdateBlinky(this -> m_PositionCourante, this -> m_etatCourant);
    }
    else{
        int direction = this -> Direction(grille, Position(0, 25));
        this -> DeplaceDirection(direction);
        grille.UpdateBlinky(this -> m_PositionCourante, this -> m_etatCourant);
    }
}

void Inky::DeplaceDirection(int direction){

    switch(direction){
        case Direction::Gauche:
            this -> m_PositionCourante = this -> m_PositionCourante.Gauche();
            this -> m_derniereDirection = Direction::Gauche;
            break;
        case Direction::Droite:
            this -> m_PositionCourante = this -> m_PositionCourante.Droite();
            this -> m_derniereDirection = Direction::Droite;
            break;
        case Direction::Bas:
            this -> m_PositionCourante = this -> m_PositionCourante.Bas();
            this -> m_derniereDirection = Direction::Bas;
            break;
        case Direction::Haut:
            this -> m_PositionCourante = this -> m_PositionCourante.Haut();
            this -> m_derniereDirection = Direction::Haut;
            break;
    }
}

Etat Inky::EtatCourant(){
    return m_etatCourant;
}

Position Inky::PositionCourante(){
    return m_PositionCourante;
}

void Inky::UpdateEtat(Etat e){
    this -> m_etatCourant = e;
}

void Inky::RetourneMaison(){
    this -> m_PositionCourante = Position(18, 14);
}
