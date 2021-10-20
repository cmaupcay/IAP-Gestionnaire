//
//  PROJET IAP
//  Sprint 1 - Release
//  main.c
//
// Sara Zaibet
// Clément Mauperon
//

#pragma warning(disable:4996) // Enlève l'avertissement de sécurité pour 'scanf' dans Visual Studio
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h" // Utilitaires

// Messages emis par les instructions -----------------------------------------
#define MSG_DEVELOPPE "## nouvelle specialite \"%s\" ; cout horaire \"%d\"\n"
#define MSG_EMBAUCHE "## nouveau travailleur \"%s\" competent pour la specialite \"%s\"\n"
#define MSG_DEMARCHE "## nouveau client \"%s\"\n"
#define MSG_COMMANDE "## nouvelle commande \"%s\", par client \"%s\"\n"
#define MSG_TACHE "## la commande \"%s\" requiere la specialite \"%s\" (nombre d\'heures \"%d\")\n"
#define MSG_PROGRESSION "## pour la commande \"%s\", pour la specialite \"%s\" : \"%d\" heures de plus ont ete realisees\n"
#define MSG_PROGRESSION_PASSE "## une reallocation est requise\n"
#define MSG_SPECIALITES "## consultation des specialites\n"
#define MSG_TRAVAILLEURS "## consultation des travailleurs competents pour la specialite \"%s\"\n"
#define MSG_TRAVAILLEURS_TOUS "## consultation des travailleurs competents pour chaque specialite\n"
#define MSG_CLIENT "## consultation des commandes effectuees par \"%s\"\n"
#define MSG_CLIENT_TOUS "## consultation des commandes effectuees par chaque client\n"
#define MSG_SUPERVISION "## consultation de l\'avancement des commandes\n"
#define MSG_CHARGE "## consultation de la charge de travail de \"%s\"\n"
#define MSG_INTERRUPTION "## fin de programme\n"


#pragma region Prototypes

void traite_developpe();
void traite_embauche();
void traite_demarche();
void traite_commande();
void traite_tache();
void traite_progression();
void traite_progression_passe();
void traite_client();
void traite_travailleurs();
void traite_supervision();
void traite_charge();
void traite_specialites();
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

    // Boucle principale
    while (continuer) {
        strcpy(dernier_buffer, buffer); // Sauvegarde de buffer dans dernier_buffer
        get_id(buffer); // Demande à l'utilisateur l'identifieur de l'instruction voulue

        // Switch
        if (strcmp(buffer, "developpe") == 0) {
            traite_developpe();
        }
        else if (strcmp(buffer, "embauche") == 0) {
            traite_embauche();
        }
        else if (strcmp(buffer, "demarche") == 0) {
            traite_demarche();
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
            traite_client();
        }
        else if (strcmp(buffer, "travailleurs") == 0) {
            traite_travailleurs();
        }
        else if (strcmp(buffer, "specialites") == 0) {
            traite_specialites();
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

void traite_developpe()
{
    Mot nom_specialite; get_id(nom_specialite); // Nom de la spécialité à developper
    int cout_horaire = get_int(); // Cout horaire de la spécialité
    printf(MSG_DEVELOPPE, nom_specialite, cout_horaire);
}

void traite_embauche()
{
    Mot nom_travailleur; get_id(nom_travailleur); // Nom du nouveau travailleur
    Mot specialite; get_id(specialite); // Nom de la spécialité
    printf(MSG_EMBAUCHE, nom_travailleur, specialite);
}

void traite_demarche()
{
    Mot nom_client; get_id(nom_client); // Nom du nouveau client
    printf(MSG_DEMARCHE, nom_client);
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

void traite_client()
{
    Mot nom_client; get_id(nom_client); // Nom du client
    if (strcmp(nom_client, "tous") == 0)
        printf(MSG_CLIENT_TOUS);
    else
        printf(MSG_CLIENT, nom_client);
}

void traite_travailleurs()
{
    Mot nom_specialite; get_id(nom_specialite); // Nom de la spécialité
    if (strcmp(nom_specialite, "tous") == 0)
        printf(MSG_TRAVAILLEURS_TOUS);
    else
        printf(MSG_TRAVAILLEURS, nom_specialite);
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

void traite_specialites()
{
    printf(MSG_SPECIALITES);
}

void traite_interruption()
{
    printf(MSG_INTERRUPTION);
}

#pragma endregion
