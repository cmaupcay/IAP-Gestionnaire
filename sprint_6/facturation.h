//
//  PROJET IAP
//  Sprint 6 - Release
//  facturation.h
//
// Sara Zaibet
// Clément Mauperon
//

#pragma once

#include "donnees.h"

/*
    [brief] Calcule et affiche le prix final d'une commande.
    index_commande [in] Index dans le tableau des commandes de "commandes" de la commande à facturer.
    nb_taches [in] Nombre de tâche active pour la commande cible.
    index_taches [in] Tableau des index des spécialités requises pour chaque tâche de la commande cible.
    commandes [in] Structure Commandes contenant l'ensemble des commandes de l'entreprise.
    specialites [in] Structure Specialites contenant toutes les specialités gérées par l'entreprise.
    [pre] "index_commande" doit être inférieur à MAX_COMMANDES.
    [pre] "nb_taches" doit être inférieur à MAX_SPECIALITES.
*/
void facturation(const int index_commande, const int nb_taches, const int* index_taches, const Commandes commandes, const Specialites specialites)
{
    assert(index_commande < MAX_COMMANDES); // Vérification de l'index commande
    assert(nb_taches < MAX_SPECIALITES); // Vérification du nombre de tâche
    printf("facturation %s : ", commandes.tab_commandes[index_commande].nom); // En tête
    unsigned int i;
    for (i = 0; i < nb_taches; i++)
    {
        printf("%s:%d", // Format
            specialites.tab_specialites[index_taches[i]].nom, // Nom
            specialites.tab_specialites[index_taches[i]].cout_horaire * commandes.tab_commandes[index_commande].taches_par_specialite[index_taches[i]].nb_heures_effectuees // Calcul du prix
        );
        if (i < nb_taches - 1) // Pour tous sauf le dernier
            printf(", "); // Afficher une virgule
    }
    printf("\n"); // Fin
}

/*
    [brief] Pour chaque client, calcule le coût total pour toutes ses commandes. Affiche la liste finale.
    clients [in] Structure Clients contenant le tableau des clients enregistrés.
    commandes [in] Structure Commandes contenant l'ensemble des commandes de l'entreprise.
    specialites [in] Structure Specialites contenant toutes les specialités gérées par l'entreprise.
*/
void facturations(const Clients clients, const Commandes commandes, const Specialites specialites)
{
    printf("facturations : "); // En-tête
    unsigned int i, j, k, cout_total_client; // Cout total des commandes pour un client
    for (i = 0; i < clients.nb_clients; i++) // Parcours des clients
    {
        cout_total_client = 0; // Initialisation pour chaque client
        for (j = 0; j < commandes.nb_commandes; j++) // Parcours des commandes
        {
            if (commandes.tab_commandes[j].idx_client == i) // La commande émane du client
            {
                for (k = 0; k < specialites.nb_specialites; k++) // Parcours des taches de la commande
                {
                    if (commandes.tab_commandes[j].taches_par_specialite[k].nb_heures_effectuees == commandes.tab_commandes[j].taches_par_specialite[k].nb_heures_requises)
                        cout_total_client += commandes.tab_commandes[j].taches_par_specialite[k].nb_heures_effectuees * specialites.tab_specialites[k].cout_horaire;
                }
            }
        }
        printf("%s:%d", // Format d'affichage
            clients.tab_clients[i], // Nom du client
            cout_total_client // Cout total
        );
        if (i < clients.nb_clients - 1) // Pour tous sauf le dernier
            printf(", "); // Afficher une virgule
    }
    printf("\n"); // Fin
}