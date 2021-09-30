#include <iostream>
#include <string>

#include "Pacman.h"

using namespace std;

int main()
{
    string fileName;
    cout << "Entrez le nom du fichier contenant la carte : ";
    cin >> fileName;

    Pacman pacman;
    pacman.OuvrirCarte(fileName);
    pacman.Jouer();
}