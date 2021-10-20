//
//  PROJET IAP
//  Sprint 2 - Release
//  donnees.h
//
// Sara Zaibet
// Clément Mauperon
//
#pragma once

#include <assert.h>

#include "utils.h"

#pragma region Specialites

#define MAX_SPECIALITES 10 // Nombre maximum de Spécialités en mémoire

typedef struct { // Type Specialité
    Mot nom; // Nom de la spécialité
    int cout_horaire; // Cout horaire
} Specialite;

typedef struct { // Base de donnée des spécialités
    Specialite tab_specialites[MAX_SPECIALITES]; // Tableau des spécialités
    unsigned int nb_specialites; // Nombre total de spécialité
} Specialites;

unsigned int getIndexSpecialite(const Mot specialite, const Specialites specialites)
{
    unsigned int i;
    for (i = 0; i < specialites.nb_specialites; i++) // Parcours des spécialités
    {
        if (strcmp(specialites.tab_specialites[i].nom, specialite) == 0) // La spécialité a été trouvée
        {
            return i; // Retourne l'index de specialite
        }
    }
    return MAX_SPECIALITES; // La spécialité n'a pas été trouvée
}

#pragma endregion

#pragma region Clients

#define MAX_CLIENT 10 // Nombre maximum de Client en mémoire
// Les clients sont simplement représentés par des Mots

typedef struct { // Base de donnée des clients
    Mot tab_clients[MAX_CLIENT]; // Tableau des clients
    unsigned int nb_clients; // Nombre total de clients
} Clients;

unsigned int getIndexClient(const Mot client, const Clients clients)
{
    unsigned int i;
    for (i = 0; i < clients.nb_clients; i++) // Parcours des clients
    {
        if (strcmp(clients.tab_clients[i], client) == 0) // Le client à été trouvé
        {
            return i; // Retourne l'index du client
        }
    }
    return MAX_CLIENT; // Le client n'a pas été trouvé
}

#pragma endregion

#pragma region Travailleurs

#define MAX_TRAVAILLEURS 50 // Nombre maximum de Travailleurs en mémoire

typedef struct { // Type Travailleur
    Mot nom; // Nom du travailleur
    Booleen tags_competences[MAX_SPECIALITES]; // Tableau de compétences
    unsigned int nb_tache_affectee; // Nombre de tache affectees
} Travailleur;

typedef struct { // Base de donnée des travailleurs
    Travailleur tab_travailleurs[MAX_TRAVAILLEURS]; // Tableau des travailleurs
    unsigned int nb_travailleurs; // Nombre total de travailleurs
} Travailleurs;

unsigned int getIndexTravailleur(const Mot travailleur, const Travailleurs travailleurs)
{
    unsigned int i;
    for (i = 0; i < travailleurs.nb_travailleurs; i++) // Parcours des travailleurs
    {
        if (strcmp(travailleurs.tab_travailleurs[i].nom, travailleur) == 0) // Le travailleur à été trouvé
        {
            return i; // Retourne l'index du travailleur
        }
    }
    return MAX_TRAVAILLEURS; // Le travailleur n'a pas été trouvée
}

#pragma endregion