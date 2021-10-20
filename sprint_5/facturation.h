//
//  PROJET IAP
//  Sprint 5 - Release
//  facturation.h
//
// Sara Zaibet
// Clément Mauperon
//
#pragma once

#include "donnees.h"

void facturation(const int index_commande, const int nb_taches, const int index_taches[], const Commandes commandes, const Specialites specialites)
{
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