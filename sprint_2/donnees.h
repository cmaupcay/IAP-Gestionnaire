//
//  PROJET IAP
//  Sprint 2 - Release
//  donnees.h
//
// Sara Zaibet
// Cl�ment Mauperon
//
#pragma once

#include <assert.h>

#include "utils.h"

#pragma region Specialites

#define MAX_SPECIALITES 10 // Nombre maximum de Sp�cialit�s en m�moire

typedef struct { // Type Specialit�
    Mot nom; // Nom de la sp�cialit�
    int cout_horaire; // Cout horaire
} Specialite;

typedef struct { // Base de donn�e des sp�cialit�s
    Specialite tab_specialites[MAX_SPECIALITES]; // Tableau des sp�cialit�s
    unsigned int nb_specialites; // Nombre total de sp�cialit�
} Specialites;

unsigned int getIndexSpecialite(const Mot specialite, const Specialites specialites)
{
    unsigned int i;
    for (i = 0; i < specialites.nb_specialites; i++) // Parcours des sp�cialit�s
    {
        if (strcmp(specialites.tab_specialites[i].nom, specialite) == 0) // La sp�cialit� a �t� trouv�e
        {
            return i; // Retourne l'index de specialite
        }
    }
    return MAX_SPECIALITES; // La sp�cialit� n'a pas �t� trouv�e
}

#pragma endregion

#pragma region Clients

#define MAX_CLIENT 10 // Nombre maximum de Client en m�moire
// Les clients sont simplement repr�sent�s par des Mots

typedef struct { // Base de donn�e des clients
    Mot tab_clients[MAX_CLIENT]; // Tableau des clients
    unsigned int nb_clients; // Nombre total de clients
} Clients;

unsigned int getIndexClient(const Mot client, const Clients clients)
{
    unsigned int i;
    for (i = 0; i < clients.nb_clients; i++) // Parcours des clients
    {
        if (strcmp(clients.tab_clients[i], client) == 0) // Le client � �t� trouv�
        {
            return i; // Retourne l'index du client
        }
    }
    return MAX_CLIENT; // Le client n'a pas �t� trouv�
}

#pragma endregion

#pragma region Travailleurs

#define MAX_TRAVAILLEURS 50 // Nombre maximum de Travailleurs en m�moire

typedef struct { // Type Travailleur
    Mot nom; // Nom du travailleur
    Booleen tags_competences[MAX_SPECIALITES]; // Tableau de comp�tences
    unsigned int nb_tache_affectee; // Nombre de tache affectees
} Travailleur;

typedef struct { // Base de donn�e des travailleurs
    Travailleur tab_travailleurs[MAX_TRAVAILLEURS]; // Tableau des travailleurs
    unsigned int nb_travailleurs; // Nombre total de travailleurs
} Travailleurs;

unsigned int getIndexTravailleur(const Mot travailleur, const Travailleurs travailleurs)
{
    unsigned int i;
    for (i = 0; i < travailleurs.nb_travailleurs; i++) // Parcours des travailleurs
    {
        if (strcmp(travailleurs.tab_travailleurs[i].nom, travailleur) == 0) // Le travailleur � �t� trouv�
        {
            return i; // Retourne l'index du travailleur
        }
    }
    return MAX_TRAVAILLEURS; // Le travailleur n'a pas �t� trouv�e
}

#pragma endregion