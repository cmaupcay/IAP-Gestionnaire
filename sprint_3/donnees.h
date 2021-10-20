//
//  PROJET IAP
//  Sprint 3 - Release
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

#pragma region Commandes

#define MAX_COMMANDES 500 // Nombre maximum de commandes

typedef struct { // Tache a effectuer pour une Commande
    unsigned int nb_heures_requises; // Nombre d'heure pour compléter la tache
    unsigned int nb_heures_effectuees; // Nombre d'heure remplie
    int index_travailleur; // Index du travailleur affecté à la tache
} Tache;

typedef struct { // Command effectuée par un Client
    Mot nom; // Nom de la commande
    int idx_client; // Index du client dans clients
    Tache taches_par_specialite[MAX_SPECIALITES]; // nb heures requises == 0 <=> pas de tache pour cette specialite
    Booleen terminee; // Indique si la commande est terminée
} Commande;

typedef struct { // Base de données des commandes
    Commande tab_commandes[MAX_COMMANDES]; // Tableau des commandes
    unsigned int nb_commandes; // Nombre de commandes
} Commandes;

unsigned int getIndexCommande(const Mot commande, const Commandes commandes)
{
    unsigned int i;
    for (i = 0; i < commandes.nb_commandes; i++) // Parcours des commandes
    {
        if (strcmp(commandes.tab_commandes[i].nom, commande) == 0) // La commande à été trouvée
        {
            return i; // Retourne l'index de la commande
        }
    }
    return MAX_COMMANDES; // La commande n'a pas été trouvée
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

// Fonctions utilitaires
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

unsigned int getTravailleurCompetent(const int index_specialite, const Travailleurs travailleurs, const Commandes commandes)
{
    unsigned int index_travailleur = MAX_TRAVAILLEURS; // Index du travailleur compétent // Aucun travailleur trouvé : return MAX_TRAVAILLEURS
    unsigned int score_travailleur; // score = nombre d'heure de travail restant
    int plus_petit_score = -1; // Plus petit score obtenu jusque là // -1 par defaut
    unsigned int i;
    for (i = 0; i < travailleurs.nb_travailleurs; i++) // Parcours des travailleurs
    {
        score_travailleur = 0; // Par défaut pour chaque travailleur
        if (travailleurs.tab_travailleurs[i].tags_competences[index_specialite] == VRAI) // Le travailleur à la compétence
        {
            unsigned int j;
            for (j = 0; j < commandes.nb_commandes; j++) // Parcours des commandes
            {
                unsigned int h;
                for (h = 0; h < MAX_SPECIALITES; h++) // Parcours des taches de la commande
                {
                    if (commandes.tab_commandes[j].taches_par_specialite[h].index_travailleur == i) // La tache est affecté au travailleur
                    {
                        // Heures requises - Heures effectuees
                        score_travailleur += (commandes.tab_commandes[j].taches_par_specialite[h].nb_heures_requises - commandes.tab_commandes[j].taches_par_specialite[h].nb_heures_effectuees);
                    }
                }
            }
            if (score_travailleur < plus_petit_score || plus_petit_score == -1)
            {
                index_travailleur = i; // Sauvegarde de l'index
                plus_petit_score = score_travailleur; // Sauvegarde du score de reference
            }
        }
    }
    return index_travailleur;
}

#pragma endregion