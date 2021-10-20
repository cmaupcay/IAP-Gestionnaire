//
//  PROJET IAP
//  Sprint 3 - Release
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

#pragma region Commandes

#define MAX_COMMANDES 500 // Nombre maximum de commandes

typedef struct { // Tache a effectuer pour une Commande
    unsigned int nb_heures_requises; // Nombre d'heure pour compl�ter la tache
    unsigned int nb_heures_effectuees; // Nombre d'heure remplie
    int index_travailleur; // Index du travailleur affect� � la tache
} Tache;

typedef struct { // Command effectu�e par un Client
    Mot nom; // Nom de la commande
    int idx_client; // Index du client dans clients
    Tache taches_par_specialite[MAX_SPECIALITES]; // nb heures requises == 0 <=> pas de tache pour cette specialite
    Booleen terminee; // Indique si la commande est termin�e
} Commande;

typedef struct { // Base de donn�es des commandes
    Commande tab_commandes[MAX_COMMANDES]; // Tableau des commandes
    unsigned int nb_commandes; // Nombre de commandes
} Commandes;

unsigned int getIndexCommande(const Mot commande, const Commandes commandes)
{
    unsigned int i;
    for (i = 0; i < commandes.nb_commandes; i++) // Parcours des commandes
    {
        if (strcmp(commandes.tab_commandes[i].nom, commande) == 0) // La commande � �t� trouv�e
        {
            return i; // Retourne l'index de la commande
        }
    }
    return MAX_COMMANDES; // La commande n'a pas �t� trouv�e
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

// Fonctions utilitaires
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

unsigned int getTravailleurCompetent(const int index_specialite, const Travailleurs travailleurs, const Commandes commandes)
{
    unsigned int index_travailleur = MAX_TRAVAILLEURS; // Index du travailleur comp�tent // Aucun travailleur trouv� : return MAX_TRAVAILLEURS
    unsigned int score_travailleur; // score = nombre d'heure de travail restant
    int plus_petit_score = -1; // Plus petit score obtenu jusque l� // -1 par defaut
    unsigned int i;
    for (i = 0; i < travailleurs.nb_travailleurs; i++) // Parcours des travailleurs
    {
        score_travailleur = 0; // Par d�faut pour chaque travailleur
        if (travailleurs.tab_travailleurs[i].tags_competences[index_specialite] == VRAI) // Le travailleur � la comp�tence
        {
            unsigned int j;
            for (j = 0; j < commandes.nb_commandes; j++) // Parcours des commandes
            {
                unsigned int h;
                for (h = 0; h < MAX_SPECIALITES; h++) // Parcours des taches de la commande
                {
                    if (commandes.tab_commandes[j].taches_par_specialite[h].index_travailleur == i) // La tache est affect� au travailleur
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