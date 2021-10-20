//
//  PROJET IAP
//  Sprint 6 - Release
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

/*
    [brief] Demande un mot à l'utilisateur.
    id [in-out] Mot où sera stocké l'entrée utilisateur.
*/
void get_id(Mot id)
{
    scanf("%s", id);
    if (EchoActif) printf(">>echo %s\n", id); // Echo mode
}

/*
    [brief] Demande un entier à l'utilisateur.
    [return] L'entier retourné est celui entré par l'utilisateur.
*/
int get_int()
{
    char buffer[NBCHIFFREMAX + 1]; // Format des entiers
    scanf("%s", buffer);
    if (EchoActif) printf(">>echo %s\n", buffer); // Echo mode
    return atoi(buffer);
}

#pragma endregion