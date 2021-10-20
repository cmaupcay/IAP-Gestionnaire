//
//  PROJET IAP
//  Sprint 2 - Release
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
#define MSG_COMMANDE "## nouvelle commande \"%s\", par client \"%s\"\n"
#define MSG_TACHE "## la commande \"%s\" requiere la specialite \"%s\" (nombre d\'heures \"%d\")\n"
#define MSG_PROGRESSION "## pour la commande \"%s\", pour la specialite \"%s\" : \"%d\" heures de plus ont ete realisees\n"
#define MSG_PROGRESSION_PASSE "## une reallocation est requise\n"
#define MSG_SUPERVISION "## consultation de l\'avancement des commandes\n"
#define MSG_CHARGE "## consultation de la charge de travail de \"%s\"\n"
#define MSG_INTERRUPTION "## fin de programme\n"


#pragma region Prototypes

void traite_developpe(Specialites* specialites);
void traite_embauche(Travailleurs* travailleurs, const Specialites specialites);
void traite_demarche(Clients* clients);
void traite_commande();
void traite_tache();
void traite_progression();
void traite_progression_passe();
void traite_client(const Clients clients);
void traite_travailleurs(const Travailleurs travailleurs, const Specialites specialites);
void traite_supervision();
void traite_charge();
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
            traite_commande();
        }
        else if (strcmp(buffer, "tache") == 0) {
            traite_tache();
        }
        else if (strcmp(buffer, "progression") == 0) {
            traite_progression();
        }
        else if (strcmp(buffer, "client") == 0) {
            traite_client(clients);
        }
        else if (strcmp(buffer, "travailleurs") == 0) {
            traite_travailleurs(travailleurs, specialites);
        }
        else if (strcmp(buffer, "specialites") == 0) {
            traite_specialites(specialites);
        }
        else if (strcmp(buffer, "supervision") == 0) {
            traite_supervision();
        }
        else if (strcmp(buffer, "charge") == 0) {
            traite_charge();
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

void traite_commande()
{
    Mot nom_commande; get_id(nom_commande); // Nom de la nouvelle commande
    Mot nom_client; get_id(nom_client); // Nom du client émissaire de la commande
    printf(MSG_COMMANDE, nom_commande, nom_client);
}

void traite_tache()
{
    Mot commande; get_id(commande); // Nom de la commande
    Mot specialite; get_id(specialite); // Nom de la spécialité correspondante
    int nombreheures = get_int(); // Nombre d'heures requises
    printf(MSG_TACHE, commande, specialite, nombreheures);
}

void traite_progression()
{
    Mot commande; get_id(commande); // Nom de la commande
    Mot specialite; get_id(specialite); // Nom de la spécialité correspondante
    int heures_passe = get_int(); // Nombre d'heures effectuées
    printf(MSG_PROGRESSION, commande, specialite, heures_passe);
}

void traite_progression_passe() // Argument passe
{
    printf(MSG_PROGRESSION_PASSE);
}

void traite_client(const Clients clients)
{
    Mot nom_client; get_id(nom_client); // Nom du client
    Booleen tous = FAUX; // Mot spécial "tous"
    if (strcmp(nom_client, "tous") == 0)
        tous = VRAI; // "tous" a été entré
    unsigned int i;
    for (i = 0; i < clients.nb_clients; i++) // Parcours des clients
    {
        if (strcmp(clients.tab_clients[i], nom_client) == 0 || tous) // Le client a été trouvé
        {
            printf("le client %s a commande : ", clients.tab_clients[i]); // En-tête
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

void traite_supervision()
{
    printf(MSG_SUPERVISION);
}

void traite_charge()
{
    Mot travailleur; get_id(travailleur); // Nom du travailleur
    printf(MSG_CHARGE, travailleur);
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