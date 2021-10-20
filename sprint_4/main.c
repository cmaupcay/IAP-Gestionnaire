//
//  PROJET IAP
//  Sprint 4 - Release
//  main.c
//
// Sara Zaibet
// Clément Mauperon
//

#pragma warning(disable:4996) // Enlève l'avertissement de sécurité pour 'scanf' dans Visual Studio
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "donnees.h" // Stockage des données

// Messages emis par les instructions -----------------------------------------
#define MSG_INTERRUPTION "## fin de programme\n"


#pragma region Prototypes

void traite_developpe(Specialites* specialites);
void traite_embauche(Travailleurs* travailleurs, const Specialites specialites);
void traite_demarche(Clients* clients);
void traite_commande(Commandes* commandes, const Clients clients);
void traite_tache(Commandes* commandes, const Specialites specialites, Travailleurs* travailleurs);
void traite_progression(Commandes* commandes, Travailleurs* travailleurs, const Specialites specialites, const Clients clients);
void traite_progression_passe();
void traite_client(const Clients clients, const Commandes commandes);
void traite_travailleurs(const Travailleurs travailleurs, const Specialites specialites);
void traite_supervision(const Commandes commandes, const Specialites specialites);
void traite_charge(const Travailleurs travailleurs, const Commandes commandes, const Specialites specialites);
void traite_specialites(const Specialites specialites);
void traite_interruption();

#pragma endregion

// Boucle principale -----------------------------------------------------------
int main(int argc, char* argv[]) {
    // Echo mode
    if (argc >= 2 && strcmp("echo", argv[1]) == 0) {
        EchoActif = VRAI;
    }

    Mot buffer; // Variable de pivot entre toutes les instructions
    strcpy(buffer, "undefined"); // Initialization
    Mot dernier_buffer; // Buffer a t - 1
    Booleen continuer = VRAI;

    // Données
    Specialites specialites; // Ensemble des spécialités
    specialites.nb_specialites = 0; // Initialisation
    Travailleurs travailleurs; // Ensemble des travailleurs
    travailleurs.nb_travailleurs = 0; // Initialization
    Clients clients; // Ensemble des clients
    clients.nb_clients = 0; // Initialisation
    Commandes commandes; // Ensemble des clients
    commandes.nb_commandes = 0; // Initialisation

    // Boucle principale
    while (continuer) {
        strcpy(dernier_buffer, buffer); // Sauvegarde de buffer dans dernier_buffer
        get_id(buffer); // Demande à l'utilisateur l'identifieur de l'instruction voulue

        // Switch
        if (strcmp(buffer, "developpe") == 0) {
            traite_developpe(&specialites);
        }
        else if (strcmp(buffer, "embauche") == 0) {
            traite_embauche(&travailleurs, specialites);
        }
        else if (strcmp(buffer, "demarche") == 0) {
            traite_demarche(&clients);
        }
        else if (strcmp(buffer, "commande") == 0) {
            traite_commande(&commandes, clients);
        }
        else if (strcmp(buffer, "tache") == 0) {
            traite_tache(&commandes, specialites, &travailleurs);
        }
        else if (strcmp(buffer, "progression") == 0) {
            traite_progression(&commandes, &travailleurs, specialites, clients);
        }
        else if (strcmp(buffer, "client") == 0) {
            traite_client(clients, commandes);
        }
        else if (strcmp(buffer, "travailleurs") == 0) {
            traite_travailleurs(travailleurs, specialites);
        }
        else if (strcmp(buffer, "specialites") == 0) {
            traite_specialites(specialites);
        }
        else if (strcmp(buffer, "supervision") == 0) {
            traite_supervision(commandes, specialites);
        }
        else if (strcmp(buffer, "charge") == 0) {
            traite_charge(travailleurs, commandes, specialites);
        }
        else if (strcmp(buffer, "passe") == 0) // Mot clé passe
        {
            if (strcmp(dernier_buffer, "progression") == 0) {
                traite_progression_passe();
                continue;
            }
        }
        else if (strcmp(buffer, "interruption") == 0) {
            traite_interruption();
            break;
        }
        else // L'instruction est inconnue
        {
            printf("!!! instruction inconnue >%s< !!!\n", buffer); // L'identifieur n'est associé à aucune instruction
        }
    }
    return 0;
}

#pragma region Declarations

void traite_developpe(Specialites* specialites)
{
    Mot nom_specialite; get_id(nom_specialite); // Nom de la spécialité à developper
    int cout_horaire = get_int(); // Cout horaire de la spécialité
    Specialite specialite; // Création d'une nouvelle spécialité
    strcpy(specialite.nom, nom_specialite); // Définition du nom
    specialite.cout_horaire = cout_horaire; // Définition du coût horaire
    unsigned int index_specialite = specialites->nb_specialites++; // Récupération de l'index courant et incrémentation
    specialites->tab_specialites[index_specialite] = specialite; // Ajout de la spécialité
}

void traite_embauche(Travailleurs* travailleurs, const Specialites specialites)
{
    Mot nom_travailleur; get_id(nom_travailleur); // Nom du nouveau travailleur
    Mot specialite; get_id(specialite); // Nom de la spécialité
    unsigned int index_specialite = getIndexSpecialite(specialite, specialites); // Index de la spécialité
    assert(index_specialite < MAX_SPECIALITES); // Vérification de l'index de la spécialité
    int index_travailleur = getIndexTravailleur(nom_travailleur, *travailleurs); // Index du travailleur cible
    if (index_travailleur == MAX_TRAVAILLEURS) // Le travailleur n'existe pas
    {
        Travailleur travailleur; // Création d'un nouveau travailleur
        strcpy(travailleur.nom, nom_travailleur); // Nom
        travailleur.nb_tache_affectee = 0; // Taches affectees
        index_travailleur = travailleurs->nb_travailleurs; // Récupération de l'index courant et incrémentation
        travailleurs->nb_travailleurs++;
        travailleurs->tab_travailleurs[index_travailleur] = travailleur; // Ajout du travailleur
    }
    travailleurs->tab_travailleurs[index_travailleur].tags_competences[index_specialite] = VRAI; // Ajout de la compétence
}

void traite_demarche(Clients* clients)
{
    Mot nom_client; get_id(nom_client); // Nom du nouveau client
    unsigned int index_client = clients->nb_clients++; // Récupération de l'index courant et incrémentation
    strcpy(clients->tab_clients[index_client], nom_client); // Ajout du client
}

void traite_commande(Commandes* commandes, const Clients clients)
{
    Mot nom_commande; get_id(nom_commande); // Nom de la nouvelle commande
    Mot nom_client; get_id(nom_client); // Nom du client émissaire de la commande
    Commande commande; // Création d'une nouvelle commande
    strcpy(commande.nom, nom_commande); // Ecriture du nom
    commande.terminee = FAUX; // La commande n'est pas terminee par défaut
    // Initialisation des taches
    int i;
    for (i = 0; i < MAX_SPECIALITES; i++)
    {
        commande.taches_par_specialite[i].index_travailleur = -1; // Aucun travailleur affecté
        commande.taches_par_specialite[i].nb_heures_requises = 0; // La tâche n'est pas active
    }
    commande.idx_client = getIndexClient(nom_client, clients); // Sauvegarde de l'index du client
    assert(commande.idx_client < MAX_CLIENT); // Vérification de l'index du client
    commandes->tab_commandes[commandes->nb_commandes] = commande; // Ajout de la commande
    commandes->nb_commandes++; // Incrémentation du nombre de commande
}

void traite_tache(Commandes* commandes, const Specialites specialites, Travailleurs* travailleurs)
{
    Mot commande; get_id(commande); // Nom de la commande
    Mot specialite; get_id(specialite); // Nom de la spécialité correspondante
    int nombreheures = get_int(); // Nombre d'heures requises
    int index_specialite = getIndexSpecialite(specialite, specialites); // Index de la spécialité correspondante
    assert(index_specialite < MAX_SPECIALITES); // Vérification de l'index de la spécialité
    int index_travailleur = getTravailleurCompetent(index_specialite, *travailleurs, *commandes); // Recherche d'un travailleur compétent
    assert(index_travailleur < MAX_TRAVAILLEURS); // Vérification de l'index du travailleur
    unsigned int index_commande = getIndexCommande(commande, *commandes); // Récupération de l'index de la commande
    assert(index_commande < MAX_COMMANDES); // Vérification de l'index de la commande
    Tache tache; // Création d'une nouvelle tache
    tache.nb_heures_effectuees = 0; // Initialisation des heures remplies
    tache.nb_heures_requises = nombreheures; // Ecriture du nombre d'heure requise
    tache.index_travailleur = index_travailleur; // Ecriture de l'affectation
    commandes->tab_commandes[index_commande].taches_par_specialite[index_specialite] = tache; // Ajout de la tache
    travailleurs->tab_travailleurs[index_travailleur].nb_tache_affectee++; // Incrémentation du nombre de tache
}

void traite_progression(Commandes* commandes, Travailleurs* travailleurs, const Specialites specialites, const Clients clients)
{
    Mot commande; get_id(commande); // Nom de la commande
    Mot specialite; get_id(specialite); // Nom de la spécialité correspondante
    int heures_passe = get_int(); // Nombre d'heures effectuées
    int index_commande = getIndexCommande(commande, *commandes); // Récupération de l'index de la commande
    assert(index_commande < MAX_COMMANDES); // Vérification de l'index de la commande
    unsigned int nb_taches = 0, nb_taches_terminees = 0; // Prérequis pour l'appel de facturation
    unsigned int i;
    for (i = 0; i < specialites.nb_specialites; i++) // Parcours des specialité
    {
        if (commandes->tab_commandes[index_commande].taches_par_specialite[i].nb_heures_requises != 0) // La tache est définie
        {
            if (strcmp(specialites.tab_specialites[i].nom, specialite) == 0) // La spécialité a été trouvée
            {
                commandes->tab_commandes[index_commande].taches_par_specialite[i].nb_heures_effectuees += heures_passe; // Ajout des heures effectuees
                if (commandes->tab_commandes[index_commande].taches_par_specialite[i].nb_heures_requises
                    == commandes->tab_commandes[index_commande].taches_par_specialite[i].nb_heures_effectuees) // La tache est complétée
                {
                    travailleurs->tab_travailleurs[commandes->tab_commandes[index_commande].taches_par_specialite[i].index_travailleur].nb_tache_affectee--; // Retrait de la tache
                }
            }
            nb_taches++; // Incrémentation du nombre de tache pour la commande
            if (commandes->tab_commandes[index_commande].taches_par_specialite[i].nb_heures_requises
                == commandes->tab_commandes[index_commande].taches_par_specialite[i].nb_heures_effectuees) // La tache est complétée
            {
                nb_taches_terminees++; // Incrémentation du nombre de tache terminée pour la commande
            }
        }
    }
    if (nb_taches > 0 && nb_taches == nb_taches_terminees) // Si la commande est terminée
    {
        commandes->tab_commandes[index_commande].terminee = VRAI; // La commande est inscrite comme terminee
    }
}

void traite_progression_passe() // Argument passe
{
    assert(VRAI); // Ne fais rien
}

void traite_client(const Clients clients, const Commandes commandes)
{
    Mot nom_client; get_id(nom_client); // Nom du client
    Booleen tous = FAUX; // Mot spécial "tous"
    if (strcmp(nom_client, "tous") == 0)
        tous = VRAI; // "tous" a été entré
    unsigned int nb_commande_client; // Nombre de commande pour chaque client
    Mot commande_client[MAX_COMMANDES]; // Tableau des index des commandes a afficher pour chaque client
    unsigned int i;
    for (i = 0; i < clients.nb_clients; i++) // Parcours des clients
    {
        nb_commande_client = 0; // Remise a zéro pour chaque nouveau client trouvé
        if (strcmp(clients.tab_clients[i], nom_client) == 0 || tous) // Le client a été trouvé
        {
            printf("le client %s a commande : ", clients.tab_clients[i]); // En-tête
            unsigned int j;
            for (j = 0; j < commandes.nb_commandes; j++) // Parcours des commandes
            {
                if (commandes.tab_commandes[j].idx_client == i) // La commande émane du client
                {
                    strcpy(commande_client[nb_commande_client], commandes.tab_commandes[j].nom); // Sauvegarde du nom de la commande
                    nb_commande_client++; // Incrémentation du nombre de commande
                }
            }
            for (j = 0; j < nb_commande_client; j++) // Affichage final des commandes
            {
                printf("%s", commande_client[j]); // Affichage de la commande
                if (j < nb_commande_client - 1) // Pour tous sauf le dernier
                    printf(", "); // Afficher une virgule
            }
            printf("\n"); // Fin
            if (!tous) // Si on ne cherchait qu'un client
                break; // Arrêt
        }
    }
}

void traite_travailleurs(const Travailleurs travailleurs, const Specialites specialites)
{
    Mot nom_specialite; get_id(nom_specialite); // Nom de la spécialité
    int index_specialite = -1; // Index de la spécialité // Spécialité introuvable (par défaut)
    unsigned int nb_specialite_a_traiter = specialites.nb_specialites; // Nombre de spécialité a traiter // S'arrete a la fin du tableau par défaut
    if (strcmp(nom_specialite, "tous") != 0) // Le mot "tous" n'a pas été rentré
    {
        index_specialite = getIndexSpecialite(nom_specialite, specialites); // Recherche de l'index de la spécialité
        nb_specialite_a_traiter = index_specialite + 1; // S'arrete juste après le traitement de la premiere specialité
    }
    else // Traitement de toutes les spécialités
        index_specialite = 0; // Commence a la premiere specialite
    unsigned int nb_travailleur_competent; // Nombre de travailleur compétent pour chaque specialité traitée
    Mot travailleur_competent[MAX_TRAVAILLEURS]; // Tableau des noms à afficher
    unsigned int i, j;
    for (i = index_specialite; i < nb_specialite_a_traiter; i++) // Parcours des spécialités à traiter
    {
        nb_travailleur_competent = 0; // Remise à zéro pour chaque spécialité
        printf("la specialite %s peut etre prise en charge par : ", specialites.tab_specialites[i].nom); // En-tête
        for (j = 0; j < travailleurs.nb_travailleurs; j++) // Parcours des travailleurs
        {
            if (travailleurs.tab_travailleurs[j].tags_competences[i] == VRAI) // Le travailleur possède la compétence
            {
                strcpy(travailleur_competent[nb_travailleur_competent], travailleurs.tab_travailleurs[j].nom); // Sauvegarde du nom du travailleur
                nb_travailleur_competent++; // Incrémentation du nombre de travailleur compétent
            }
        }
        for (j = 0; j < nb_travailleur_competent; j++) // Parcours des travailleurs compétents trouvés
        {
            printf("%s", travailleur_competent[j]); // Affichage du nom
            if (j < nb_travailleur_competent - 1) // Pour tous sauf le dernier
                printf(", ");
        }
        printf("\n"); // Fin
    }
}

void traite_supervision(const Commandes commandes, const Specialites specialites)
{
    unsigned int nb_tache; // Nombre de tache a afficher
    unsigned int index_tache[MAX_SPECIALITES]; // Tableau des index a afficher
    unsigned int i, j;
    for (i = 0; i < commandes.nb_commandes; i++) // Parcours des commandes
    {
        nb_tache = 0; // Remise a zéro pour toute les commandes
        printf("etat des taches pour %s : ", commandes.tab_commandes[i].nom); // En-tête
        for (j = 0; j < specialites.nb_specialites; j++) // Parcours des taches par spécialités
        {
            if (commandes.tab_commandes[i].taches_par_specialite[j].nb_heures_requises != 0) // La tâche est définie
            {
                index_tache[nb_tache] = j; // Sauvegarde de l'index
                nb_tache++; // Incrémentation du nombre de tache
            }
        }
        for (j = 0; j < nb_tache; j++) // Parcours des taches à afficher
        {
            printf("%s:%d/%d", // Format d'affichage
                specialites.tab_specialites[index_tache[j]].nom, // Nom de la spécialité
                commandes.tab_commandes[i].taches_par_specialite[index_tache[j]].nb_heures_effectuees, // Heures effectuées
                commandes.tab_commandes[i].taches_par_specialite[index_tache[j]].nb_heures_requises // Heures à faire
            );
            if (j < nb_tache - 1) // Pour tous sauf le dernier
                printf(", "); // Afficher une virgule
        }
        printf("\n"); // Fin
    }
}

void traite_charge(const Travailleurs travailleurs, const Commandes commandes, const Specialites specialites)
{
    Mot travailleur; get_id(travailleur); // Nom du travailleur
    Booleen tous = FAUX; // Mot clé 'tous'
    if (strcmp(travailleur, "tous") == 0) // Le mot clé "tous" a été rentré
        tous = VRAI;
    unsigned int i;
    for (i = 0; i < travailleurs.nb_travailleurs; i++) // Parcours des travailleurs
    {
        if (strcmp(travailleurs.tab_travailleurs[i].nom, travailleur) == 0 || tous) // Le nom correspond OU le mot clé 'tous' a été entré
        {
            printf("charge de travail pour %s : ", travailleurs.tab_travailleurs[i].nom); // En-tête
            unsigned int j, h, nb_taches_afficher = 0;
            for (j = 0; j < commandes.nb_commandes; j++)
            {
                for (h = 0; h < MAX_SPECIALITES; h++)
                {
                    if (commandes.tab_commandes[j].taches_par_specialite[h].index_travailleur == i
                        && commandes.tab_commandes[j].taches_par_specialite[h].nb_heures_requises > commandes.tab_commandes[j].taches_par_specialite[h].nb_heures_effectuees)
                    {
                        printf("%s/%s/%dheure(s)", // Format d'affichage
                            commandes.tab_commandes[j].nom, // Nom de la commande
                            specialites.tab_specialites[h].nom, // Nom de la spécialité
                            commandes.tab_commandes[j].taches_par_specialite[h].nb_heures_requises - commandes.tab_commandes[j].taches_par_specialite[h].nb_heures_effectuees
                        );
                        if (nb_taches_afficher < travailleurs.tab_travailleurs[i].nb_tache_affectee - 1) // Pour tous sauf le dernier
                            printf(", "); // Afficher une virgule
                        nb_taches_afficher++;
                    }
                }
            }
            printf("\n"); // Fin
        }
    }
}

void traite_specialites(const Specialites specialites)
{
    unsigned int i;
    printf("specialites traitees : "); // En-tête
    for (i = 0; i < specialites.nb_specialites; i++)
    {
        printf("%s/%d", specialites.tab_specialites[i].nom, specialites.tab_specialites[i].cout_horaire);

        if (i < specialites.nb_specialites - 1) // Pour tous sauf le dernier
            printf(", "); // Virgule
    }
    printf("\n");
}

void traite_interruption()
{
    printf(MSG_INTERRUPTION);
}

#pragma endregion