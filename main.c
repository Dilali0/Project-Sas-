#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Définition de la structure pour la date de naissance
typedef struct {
    int Jour;
    int Mois;
    int Annee;
} date_naissance;

// Définition de la structure pour un étudiant
typedef struct {
    int Numero;
    char Nom[100];
    char Prenom[100];
    date_naissance date;
    char Departement[200];
    float Note_generale;
} etudiant;

// Declaration de tableau et les variables globale--------
etudiant Tab[100];
int id = 1;
int Nombre_total_d_etudiants = 0;

// Nombre de departement
#define NOMBRE_DEPARTEMENTS 6

// Tableau des noms des departement--------
const char *departements[NOMBRE_DEPARTEMENTS] = {
    "Mathematiques", "Physique", "Chimie", "Biologie", "Anglais", "Informatique",
};
//================================Function Menue===============================================
void mainMenu() {
    int choice;
    while (1) {
        printf("\n=============================== Main Menu ================================\n");
        printf("  1. Ajouter un etudiant \n");
        printf("  2. Modifier ou supprimer un etudiant.\n");
        printf("  3. Afficher les détails d'un etudiant.\n");
        printf("  4. Calculer la moyenne generale.\n");
        printf("  5. Statistiques \n");
        printf("  6. Rechercher un etudiant \n");
        printf("  7. Trier les etudiants \n");
        printf("  8. Quitter\n");

        printf("Entrez votre choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Ajouter_etudiant();
                break;
            case 2:
                Modifier_supprimer();
                break;
            case 3:
                Afficher_etudiant();
                break;
            case 4:
               Calculer_moyenne_generale();
                break;
            case 5:
               Statistiques();
                break;
            case 6:
              Rechercher_par_nom_departement();
                break;
            case 7:
                Trier_etudiants();
                break;
            case 8:
                exit(0);  // Quitter le programme
            default:
                printf("Choix invalide !\n");
        }
    }
}
//==============================================================================================
//====================Pour l'addition d'un departement
void choisirDepartement(char *Departement) {
    int choix;
    do {
        printf("Choisir le Departement par Nombre : \n");
        for (int i = 0; i < NOMBRE_DEPARTEMENTS; i++) {
            printf("%d. %s\n", i + 1, departements[i]);
        }
        printf("Votre choix : ");
        scanf("%d", &choix);
    } while (choix < 1 || choix > NOMBRE_DEPARTEMENTS);

    strcpy(Departement, departements[choix - 1]);
}
//===============================================================================================
//====================== function de l'ajout
void Ajouter_etudiant() {
    system("cls");
    Tab[Nombre_total_d_etudiants].Numero = id;

    // Entrer les informations de l'étudiant
    printf("Entrez le Nom de l'etudiant : ");
    scanf("%s", Tab[Nombre_total_d_etudiants].Nom);

    printf("Entrez le Prenom de l'etudiant : ");
    scanf("%s", Tab[Nombre_total_d_etudiants].Prenom);

    printf("Entrez la Date de naissance : \n");
Resaisir_Jour:
    printf("Jour : ");
    scanf("%d", &Tab[Nombre_total_d_etudiants].date.Jour);
    if (Tab[Nombre_total_d_etudiants].date.Jour < 1 || Tab[Nombre_total_d_etudiants].date.Jour > 31) {
        printf("Jour invalide \n");
        goto Resaisir_Jour;
    }
Resaisie_Mois:
    printf("Mois : ");
    scanf("%d", &Tab[Nombre_total_d_etudiants].date.Mois);
    if (Tab[Nombre_total_d_etudiants].date.Mois < 1 || Tab[Nombre_total_d_etudiants].date.Mois > 12) {
        printf("Mois invalide \n ");
        goto Resaisie_Mois;
    }
Resaisie_Annee:
    printf("Annee : ");
    scanf("%d", &Tab[Nombre_total_d_etudiants].date.Annee);
    if (Tab[Nombre_total_d_etudiants].date.Annee < 1999 || Tab[Nombre_total_d_etudiants].date.Annee > 2024) {
        printf("Annee invalide \n");
        goto Resaisie_Annee;
    }

    // Choisir le département
    choisirDepartement(Tab[Nombre_total_d_etudiants].Departement);

    // Entrer la note générale
Resaisir_note:
    printf("Entrez la Note generale : ");
    scanf("%f", &Tab[Nombre_total_d_etudiants].Note_generale);
    if (Tab[Nombre_total_d_etudiants].Note_generale < 0 || Tab[Nombre_total_d_etudiants].Note_generale > 20) {
        printf("La note generale doit etre entre 0 et 20 \n");
        goto Resaisir_note;
    }

    // Mise à jour des informations globales
    id++;
    Nombre_total_d_etudiants++;

    printf("Etudiant ajoute avec succes!\n");
}
//===============================================================================================
//==================function D'affichage
void Afficher_etudiant() {
    printf("\n--------------------------------------------------------------------------------------------------------\n");
    printf("\t %-5s %-15s %-15s %-20s \t %-20s %-20s\n", "Id", "Nom", "Prenom", "Date de naissance", "Departement", "Note generale");
    printf("--------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < Nombre_total_d_etudiants; i++) {
        printf("\t %-5d %-15s %-15s %02d/%02d/%04d \t \t %-20s %-20.2f\n",
               Tab[i].Numero,
               Tab[i].Nom,
               Tab[i].Prenom,
               Tab[i].date.Jour,
               Tab[i].date.Mois,
               Tab[i].date.Annee,
               Tab[i].Departement,
               Tab[i].Note_generale);
        printf("--------------------------------------------------------------------------------------------------------\n");
    }
}
//===============================================================================================
//function de supprission----------
void Supprimer_etudiant() {
    int id_trouve;
    printf("Entrez l'ID de l'etudiant que vous voulez supprimer : ");
    scanf("%d", &id_trouve);

    int found = 0;

    for (int i = 0; i < Nombre_total_d_etudiants; i++) {
        if (Tab[i].Numero == id_trouve) {
            found = 1;

            for (int j = i; j < Nombre_total_d_etudiants - 1; j++) {
                Tab[j] = Tab[j + 1];
            }

            Nombre_total_d_etudiants--;
            printf("Etudiant avec l'ID %d supprime avec succes.\n", id_trouve);
            break;
        }
    }

    if (!found) {
        printf("Etudiant non trouve !\n");
    }
}
//---------------------------------------------------------
void Modifier_etudiant() {
    {
    int numero_etudiant, choix_modification, found = 0;

    // Demander à l'utilisateur de saisir le numéro unique de l'étudiant
    printf("Entrez le Numero de l'etudiant que vous voulez modifier : ");
    scanf("%d", &numero_etudiant);

    // Rechercher l'étudiant dans le tableau
    for (int i = 0; i < Nombre_total_d_etudiants; i++) {
        if (Tab[i].Numero == numero_etudiant) {
            found = 1;

            // Présenter un menu pour choisir ce qu'il souhaite modifier
            while (1) {
                printf("\nQue voulez-vous modifier ?\n");
                printf("1. Nom\n");
                printf("2. Prenom\n");
                printf("3. Date de naissance\n");
                printf("4. Departement\n");
                printf("5. Note generale\n");
                printf("6. Terminer les modifications\n");
                printf("Entrez votre choix : ");
                scanf("%d", &choix_modification);

                switch (choix_modification) {
                    case 1:
                        printf("Entrez le nouveau Nom (ancien: %s): ", Tab[i].Nom);
                        scanf("%s", Tab[i].Nom);
                        break;

                    case 2:
                        printf("Entrez le nouveau Prenom (ancien: %s): ", Tab[i].Prenom);
                        scanf("%s", Tab[i].Prenom);
                        break;

                    case 3:
                        printf("Entrez la nouvelle Date de naissance : \n");

                        // Validation du jour
                        do {
                            printf("Jour (1-31) : ");
                            scanf("%d", &Tab[i].date.Jour);
                        } while (Tab[i].date.Jour < 1 || Tab[i].date.Jour > 31);

                        // Validation du mois
                        do {
                            printf("Mois (1-12) : ");
                            scanf("%d", &Tab[i].date.Mois);
                        } while (Tab[i].date.Mois < 1 || Tab[i].date.Mois > 12);

                        // Validation de l'année
                        do {
                            printf("Annee (1999-2024) : ");
                            scanf("%d", &Tab[i].date.Annee);
                        } while (Tab[i].date.Annee < 1999 || Tab[i].date.Annee > 2024);

                        break;

                    case 4:
                        choisirDepartement(Tab[i].Departement);
                        break;

                    case 5:
                        // Validation de la note générale
                        do {
                            printf("Entrez la nouvelle Note generale (0-20) : ");
                            scanf("%f", &Tab[i].Note_generale);
                        } while (Tab[i].Note_generale < 0 || Tab[i].Note_generale > 20);

                        break;

                    case 6:
                        printf("Modifications terminees.\n");
                        return;  // Terminer la boucle et revenir au menu principal

                    default:
                        printf("Choix invalide, veuillez essayer de nouveau.\n");
                }
            }
        }
    }

    if (!found) {
        printf("Aucun etudiant avec le numero %d n'a ete trouve.\n", numero_etudiant);
    }
}
}
//---------------------------------------------------------------
// Fonction pour modifier ou supprimer un étudiant
void Modifier_supprimer() {
    int choix;
    while (1) {
        printf("\n*********** Modifier ou Supprimer *************\n");
        printf("1. Modifier\n");
        printf("2. Supprimer\n");
        printf("3. Retourner au menu principal\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                Modifier_etudiant();
                break;
            case 2:
                Supprimer_etudiant();
                break;
            case 3:
                return;
            default:
                printf("Choix invalide !\n");
        }
    }
}
//===============================================================================================
// 4- Calculer la moyenne générale :
void Calculer_moyenne_generale() {
    float somme_note_universite = 0;
    int total_etudiants_universite = 0;

    for (int i = 0; i < NOMBRE_DEPARTEMENTS; i++)
    {
        float somme_note_departement = 0;
        int nombre_etudiants_departement = 0;

        for (int j = 0; j < Nombre_total_d_etudiants; j++)
        {
            if (strcasecmp(Tab[j].Departement, departements[i]) == 0)
            {
                somme_note_departement += Tab[j].Note_generale;
                nombre_etudiants_departement++;
            }
        }

        if (nombre_etudiants_departement > 0)
        {
            float moyenne_departement = somme_note_departement / nombre_etudiants_departement;
            printf("      Moyenne generale dans le departement %s: %.2f\n", departements[i], moyenne_departement);
        } else
        {
            printf("      Aucun etudiant dans le departement %s.\n", departements[i]);
        }

        // Ajouter à la somme note d'universite  et au total des étudiants d'universite------------------
        somme_note_universite += somme_note_departement;
        total_etudiants_universite += nombre_etudiants_departement;
    }

//-------------------- moyenne générale d'université------------------------------------------------------
    if (total_etudiants_universite > 0)
    {
        float moyenne_generale_universite = somme_note_universite / total_etudiants_universite;
        printf("     Moyenne generale de l'universite: %.2f\n", moyenne_generale_universite);
    } else
    {
        printf("      Aucun etudiant dans l'universite.\n");
    }
}
//==========================================================================================================
//========================== Statistiques :
//--------------------function nombre-------------
void Afficher_nombre_etudiant_Departement(){

    for (int i = 0; i < NOMBRE_DEPARTEMENTS; i++)
    {
        int nombre_etudiants_departement = 0;

        for (int j = 0; j < Nombre_total_d_etudiants; j++)
        {
            if (strcasecmp(Tab[j].Departement, departements[i]) == 0)
            {
                nombre_etudiants_departement++;
            }
        }

        printf("Nombre d'etudiants dans le departement %s: %d\n", departements[i], nombre_etudiants_departement);
    }

}
//--------------------Function  -------------------
void Afficher_par_seuil(){
     float suil ;
     printf("vuillez entrez une suil ");
     scanf("%f",&suil);
     printf("\n--------------------------------------------------------------------------------------------------------\n");
     printf("\t %-5s %-15s %-15s %-20s \t %-20s %-20s\n", "Id", "Nom", "Prenom", "Date de naissance", "Departement", "Note generale");
     printf("--------------------------------------------------------------------------------------------------------\n");
     for(int i = 0 ; i < Nombre_total_d_etudiants ; i++){
        if(Tab[i].Note_generale > suil){
    printf("\t %-5d %-15s %-15s %02d/%02d/%04d \t \t %-20s %-20.2f\n",
               Tab[i].Numero,
               Tab[i].Nom,
               Tab[i].Prenom,
               Tab[i].date.Jour,
               Tab[i].date.Mois,
               Tab[i].date.Annee,
               Tab[i].Departement,
               Tab[i].Note_generale);
    printf("--------------------------------------------------------------------------------------------------------\n");
        }
     }
}
//---------------------3 top note ----------------------------------------
void Trois_notes(){
   for (int i = 0; i < Nombre_total_d_etudiants - 1; i++) {
        for (int j = 0; j < Nombre_total_d_etudiants - i - 1; j++) {
            if (Tab[j].Note_generale < Tab[j + 1].Note_generale) {
                etudiant tmp = Tab[j];
                Tab[j] = Tab[j + 1];
                Tab[j + 1] = tmp;
            }
        }
}
 printf("Les trois premiers Etudiants sont : \n");
 printf("\n--------------------------------------------------------------------------------------------------------\n");
    printf("\t %-5s %-15s %-15s %-20s \t %-20s %-20s\n", "Id", "Nom", "Prenom", "Date de naissance", "Departement", "Note generale");
    printf("--------------------------------------------------------------------------------------------------------\n");
 for(int i = 0 ; i < 3 ; i++){
      printf("\t %-5d %-15s %-15s %02d/%02d/%04d \t \t %-20s %-20.2f\n",
               Tab[i].Numero,
               Tab[i].Nom,
               Tab[i].Prenom,
               Tab[i].date.Jour,
               Tab[i].date.Mois,
               Tab[i].date.Annee,
               Tab[i].Departement,
               Tab[i].Note_generale);
      printf("--------------------------------------------------------------------------------------------------------\n");
 }
}
//------------------e nombre d'étudiants ayant réussi dans chaque département
void Nombr_reussi_departement(){
       for (int i = 0; i < NOMBRE_DEPARTEMENTS; i++)
    {
        int nombre_etudiants_departement = 0;

        for (int j = 0; j < Nombre_total_d_etudiants; j++)
        {
            if (strcasecmp(Tab[j].Departement, departements[i]) == 0 && Tab[j].Note_generale >= 10)
            {
                nombre_etudiants_departement++;
            }
        }

        if (nombre_etudiants_departement > 0)
        {
            printf("      le Nombre d'etudant reussi en departement %s: %d\n", departements[i], nombre_etudiants_departement);
        } else
        {
            printf("     le Nombre d'etudant reussi en departement %s est 0 .\n", departements[i]);

        }
    }
 }
void Statistiques() {
    while(1){
     int choix;
    printf("\n******** Statistiques ***********\n");
    printf("1. Afficher le nombre total d'etudiants inscrits..\n");
    printf("2. Afficher le nombre total d'etudiants par Departement.\n");
    printf("3. Afficher les etudiants ayant une moyenne generale superieure à un certain seuil.\n");
    printf("4.Afficher les 3 etudiants ayant les meilleures notes. \n");
    printf("5. Afficher le nombre d'etudiants ayant réussi dans chaque departement \n");
    printf("6. Retourner au menu principal.\n");
    printf("Entrez votre choix : ");
    scanf("%d",&choix);
    switch (choix) {
    case 1:
         printf("Afficher le nombre total d'étudiants inscrits : %d",Nombre_total_d_etudiants);
        break;
    case 2:
        Afficher_nombre_etudiant_Departement();
        break;
    case 3:
       Afficher_par_seuil();
        break;
    case 4:
       Trois_notes();
        break;
        case 5:
       Nombr_reussi_departement() ;
        break;
    case 6:
        mainMenu();
        break;
    default:
        printf("Choix invalide !\n");
    }
    }
}
//===========================================================================================================
//==============================Rechercher un étudiant par:
//----------Par nom -----
void Recherche_par_nom(){
    char nom_recherche[100];
    printf("Entrez le Nom de l'etudiant que vous voulez rechercher : ");
    scanf("%s",nom_recherche);
    int found = 0;
    for(int i = 0 ; i < Nombre_total_d_etudiants ; i++)
    {
    if( strcasecmp(Tab[i].Nom ,nom_recherche)==0){
    printf("\n--------------------------------------------------------------------------------------------------------\n");
    printf("\t %-5s %-15s %-15s %-20s \t %-20s %-20s\n", "Id", "Nom", "Prenom", "Date de naissance", "Departement", "Note generale");
    printf("--------------------------------------------------------------------------------------------------------\n");
    printf("\t %-5d %-15s %-15s %02d/%02d/%04d \t \t %-20s %-20.2f\n",
               Tab[i].Numero,
               Tab[i].Nom,
               Tab[i].Prenom,
               Tab[i].date.Jour,
               Tab[i].date.Mois,
               Tab[i].date.Annee,
               Tab[i].Departement,
               Tab[i].Note_generale);
      printf("--------------------------------------------------------------------------------------------------------\n");

       }
    }
    if (!found) {
        printf("Aucun etudiant trouve avec ce nom.\n");
    }
}
//--------------------------------------------------------------
void Recherche_par_Departement()
{
    char Departement_Chercher[100];
    printf("Donner un departement : ");
    scanf("%s", Departement_Chercher);
    int found = 0;
    printf("\n--------------------------------------------------------------------------------------------------------\n");
    printf("\t %-5s %-15s %-15s %-20s \t %-20s %-20s\n", "Id", "Nom", "Prenom", "Date de naissance", "Departement", "Note generale");
    printf("--------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < Nombre_total_d_etudiants; i++) {
        if (strcasecmp(Tab[i].Departement, Departement_Chercher) == 0) {
            // Display student details
            printf("\t %-5d %-15s %-15s %02d/%02d/%04d \t \t %-20s %-20.2f\n",
                   Tab[i].Numero,
                   Tab[i].Nom,
                   Tab[i].Prenom,
                   Tab[i].date.Jour,
                   Tab[i].date.Mois,
                   Tab[i].date.Annee,
                   Tab[i].Departement,
                   Tab[i].Note_generale);
            printf("--------------------------------------------------------------------------------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("Aucun etudiant trouve dans le departement %s.\n", Departement_Chercher);
    }
}
//----------------------------------------
Rechercher_par_nom_departement(){
printf(" - Recherche par : ");
    while(1){
    int choix_recherche;
    printf("\n***********  Nom / Departement  *************\n");
    printf("1. Par Nom \n");
    printf("2. Par departement\n");
    printf("3. Retourner au menu principal\n");
    printf("Entrez votre choix : ");
    scanf("%d",&choix_recherche);

    switch(choix_recherche){
        case 1:
            Recherche_par_nom();
            break;
        case 2:
            Recherche_par_Departement();
            break;
        case 3:
            return ;
            break;
        default:
            printf("Choix invalide\n");
    }
    }

}
//============================================================================================
//======================== Trier un étudiant par:
//--------------
void Tri_moyenne_generale() {
    // Implémentez la fonction de tri par note générale
   for(int i = 0 ; i < Nombre_total_d_etudiants -1 ; i++)
      {

        for (int j = 0; j < Nombre_total_d_etudiants - i - 1; j++)
        {

            if ( Tab[j].Note_generale < Tab[j + 1].Note_generale )
            {
                etudiant temp = Tab[j];
                Tab[j] = Tab[j + 1];
                Tab[j + 1] = temp;
            }
        }

      }
      printf("Tri des etudiants par  moyenne generale effectue.\n");
}

// Fonction pour trier les étudiants par réussite (note générale > 10)
void Tri_reussite() {
    // Implémentez la fonction de tri par réussite
    int count = 0;

    //--------Comter combien d 'etudiant ont une note passable
    for (int i = 0; i < Nombre_total_d_etudiants; i++) {
        if (Tab[i].Note_generale >= 10) {
            count++;
        }
    }

    if (count == 0) {
        printf("Aucun étudiant avec une note supérieure ou égale à 10.\n");
        return;
    }

    // Sort students who passed (Note_generale >= 10)
    for (int i = 0; i < Nombre_total_d_etudiants - 1; i++) {
        for (int j = 0; j < Nombre_total_d_etudiants - i - 1; j++) {
            if (Tab[j].Note_generale < 10 && Tab[j + 1].Note_generale >= 10) {
                etudiant temp = Tab[j];
                Tab[j] = Tab[j + 1];
                Tab[j + 1] = temp;
            }
        }
    }

    printf("\n Tri des étudiants ayant réussi (Note >= 10) effectué.\n");

    // Afficher les étudiants qui ont une note >= 10
    printf("\n--------------------------------------------------------------------------------------------------------\n");
    printf("\t %-5s %-15s %-15s %-20s \t %-20s %-20s\n", "Id", "Nom", "Prenom", "Date de naissance", "Departement", "Note generale");
    printf("--------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < Nombre_total_d_etudiants; i++) {
        if (Tab[i].Note_generale >= 10) {
           printf("\t %-5d %-15s %-15s %02d/%02d/%04d \t \t %-20s %-20.2f\n",
                   Tab[i].Numero,
                   Tab[i].Nom,
                   Tab[i].Prenom,
                   Tab[i].date.Jour,
                   Tab[i].date.Mois,
                   Tab[i].date.Annee,
                   Tab[i].Departement,
                   Tab[i].Note_generale);
        }
    }
    printf("--------------------------------------------------------------------------------------------------------\n");
}

// Fonction pour trier les étudiants par ordre alphabétique
void Trie_Alphabetique() {
    for (int i = 0; i < Nombre_total_d_etudiants - 1; i++) {
        for (int j = 0; j < Nombre_total_d_etudiants - i - 1; j++) {
            if (strcasecmp(Tab[j].Nom, Tab[j + 1].Nom) > 0) {
                etudiant temp = Tab[j];
                Tab[j] = Tab[j + 1];
                Tab[j + 1] = temp;
            }
        }
    }
    printf("Tri des etudiants par ordre alphabetique effectue.\n");
}
//-----------------------------------------

void Trier_etudiants(){
    int choix;
    printf("\n*********** Trier les etudiants *************\n");
    printf("1. Trier par Nom\n");
    printf("2. Trier par Note generale\n");
    printf("3. Tri des etudiants selon leur statut de reussite\n");
    printf("4. Retourner au menu principal\n");
    printf("Entrez votre choix : ");
    scanf("%d", &choix);

    switch(choix){
        case 1:
            Trie_Alphabetique();
            break;
        case 2:
            Tri_moyenne_generale();
            break;
        case 3:
            Tri_reussite();
            break;
        case 4:
            mainMenu();
            break;
        default :
             printf("Choix invalide\n");

}
    }

int main()
{
    //------------------------------------------------------------------
    strcpy(Tab[0].Nom, "Dupont");
    strcpy(Tab[0].Prenom, "Jean");
    Tab[0].date.Jour = 12;
    Tab[0].date.Mois = 5;
    Tab[0].date.Annee = 2002;
    strcpy(Tab[0].Departement, "Informatique");
    Tab[0].Note_generale = 15.5;
    Tab[0].Numero = id++;
    Nombre_total_d_etudiants++;

    strcpy(Tab[1].Nom, "Martin");
    strcpy(Tab[1].Prenom, "Lucie");
    Tab[1].date.Jour = 8;
    Tab[1].date.Mois = 11;
    Tab[1].date.Annee = 2001;
    strcpy(Tab[1].Departement, "Mathematiques");
    Tab[1].Note_generale = 18.0;
    Tab[1].Numero = id++;
    Nombre_total_d_etudiants++;

    strcpy(Tab[2].Nom, "Durand");
    strcpy(Tab[2].Prenom, "Pierre");
    Tab[2].date.Jour = 20;
    Tab[2].date.Mois = 3;
    Tab[2].date.Annee = 2000;
    strcpy(Tab[2].Departement, "Physique");
    Tab[2].Note_generale = 12.0;
    Tab[2].Numero = id++;
    Nombre_total_d_etudiants++;

    strcpy(Tab[3].Nom, "Ali");
    strcpy(Tab[3].Prenom, "Daoudi");
    Tab[3].date.Jour = 2;
    Tab[3].date.Mois = 4;
    Tab[3].date.Annee = 2012;
    strcpy(Tab[3].Departement, "Physique");
    Tab[3].Note_generale = 12.0;
    Tab[3].Numero = id++;
    Nombre_total_d_etudiants++;

    strcpy(Tab[4].Nom, "badr");
    strcpy(Tab[4].Prenom, "Daoudi");
    Tab[4].date.Jour = 22;
    Tab[4].date.Mois = 8;
    Tab[4].date.Annee = 2010;
    strcpy(Tab[4].Departement, "Anglais");
    Tab[4].Note_generale = 18;
    Tab[4].Numero = id++;
    Nombre_total_d_etudiants++;
    //-----------------------------------------------------------------
    mainMenu();
    return 0;
}
