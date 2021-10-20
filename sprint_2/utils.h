//
//  PROJET IAP
//  Sprint 2 - Release
//  utils.h
//
// Sara Zaibet
// Clément Mauperon
//
#pragma once

#pragma region Valeurs

#define LGMOT 35 // Longueur maximum d'un Mot
#define NBCHIFFREMAX 5 // Longueur maximum des entiers

#pragma endregion

#pragma region Types

typedef enum { FAUX = 0, VRAI = 1 } Booleen; // Type booleen
Booleen EchoActif = FAUX; // Echo mode

typedef char Mot[LGMOT + 1]; // Type Mot

#pragma endregion

#pragma region Fonctions

// get_id : Demande un mot à l'utilisateur et le stock dans 'id'
void get_id(Mot id)
{
    scanf("%s", id);
    if (EchoActif) printf(">>echo %s\n", id); // Echo mode
}

// get_int : Demande un entier à l'utilisateur et le retourne
int get_int()
{
    char buffer[NBCHIFFREMAX + 1]; // Format des entiers
    scanf("%s", buffer);
    if (EchoActif) printf(">>echo %s\n", buffer); // Echo mode
    return atoi(buffer);
}

#pragma endregion