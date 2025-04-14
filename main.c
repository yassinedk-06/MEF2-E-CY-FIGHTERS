#include <stdio.h>
#include <stdlib.h>
#include "test.h"

#define ROUGE   "\033[1;31m"
#define VERT    "\033[1;32m"
#define JAUNE   "\033[1;33m"
#define BLEU    "\033[1;36m"
#define RESET   "\033[0m"



void afficherTitre() {
    system("clear");
    printf(ROUGE);
    printf("  _____ _            _        ______ _       _     _            \n");
    printf(" / ____| |          | |      |  ____(_)     | |   | |           \n");
    printf("| (___ | |_ ___  ___| |_     | |__   _  __ _| |__ | |_ ___ _ __ \n");
    printf(" \\___ \\| __/ _ \\/ __| __|    |  __| | |/ _` | '_ \\| __/ _ \\ '__|\n");
    printf(" ____) | ||  __/ (__| |_     | |    | | (_| | | | | ||  __/ |   \n");
    printf("|_____/ \\__\\___|\\___|\\__|    |_|    |_|\\__, |_| |_|\\__\\___|_|   \n");
    printf("                                        __/ |                  \n");
    printf("                                       |___/                   \n");
    printf(RESET);
    printf("\nAppuyer sur Enter pour ouvrir le jeu");
    while (getchar() != '\n');
}



void afficherMenu(int *mode , int *nbr_joueur) {
    system("clear");

    printf(BLEU "+========================================+\n");
    printf("║            🌟  MODE DE JEU 🌟           ║\n");
    printf("+========================================+\n" RESET);
    printf(" 1. 🎮  Joueur vs Joueur (PVP)\n");
    printf(" 2. 🤖 Joueur vs Ordinateur (PVC)\n\n");

    *mode = demanderChoixDansIntervalle("👉 Choisis ton mode", 1, 2 , JAUNE);
    system("clear");

    printf(BLEU "\n+========================================+  \n");
    printf("║       🛡️  TAILLE DE L'ÉQUIPE 🛡️        ║\n");
    printf("+========================================+\n" RESET);
    printf(" 1. 👥  2 contre 2\n");
    printf(" 2. 👥  3 contre 3\n\n");

    *nbr_joueur =  demanderChoixDansIntervalle("👉 Choisis la taille de ton équipe", 1, 2 , JAUNE);

    printf(VERT "\n✅  Tu as choisi : %s\n", (*mode== 1) ? "PVP" : "PVC");
    printf("👥  Taille : %s\n\n" RESET, (*nbr_joueur == 1) ? "2v2" : "3v3");
    
    printf("\nAppuyer sur Enter pour choisir vos Personnages ");
    while (getchar() != '\n');
}

// === NOUVEAU CODE POUR AFFICHAGE DES PERSOS ===

void afficherBarre(int valeur) {
    for (int i = 0; i < valeur; i++) {
        printf(VERT "#" RESET);
    }
    for (int j = 0; j <8 -  valeur; j ++) {
        printf(" ");
    }
    printf(" ");
}

void afficherPersonnage(int x) {
    Personnage p = persos[x];

    printf(ROUGE"[%-17s]"RESET, p.nom );
    printf("PV    : "); afficherBarre(p.pv);
    printf("Att   : "); afficherBarre(p.att);
    printf("Def   : "); afficherBarre(p.def);
    printf("Spd   : "); afficherBarre(p.speed);
    printf("Dodge : "); afficherBarre(p.dodge);
    printf("Crit  : "); afficherBarre(p.crit);
    printf("\n");
}




void afficherTousLesPersos() {
    system("clear");
    printf(BLEU "+=====================================================================================================================+\n");
    printf("║                                            👥  PERSONNAGES DISPONIBLES 👥                                             ║\n");
    printf("+=====================================================================================================================+\n\n" RESET);


    for (int i = 0; i < 12; i++) {
        afficherPersonnage(i);
        
    }

    printf("Appuie sur Entrée pour continuer...");
    while (getchar() != '\n');
}

void choix_joueur_E(int *equipe, int nbr_joueur) {
    int x = -1 , y =-1 ; 
    for (int i = 0; i <= nbr_joueur; i++) {
        switch(i) {
            case 0:
                equipe[i] = demanderChoixDansIntervalle("👉 Choisis le premier Personnage",  1,  12 , JAUNE);
                x = equipe[i];
                break;
                
            case 1:
                equipe[i] = demanderChoixDansIntervalle("👉 Choisis le deuxième Personnage",  1, 12 , JAUNE);
                
                while(equipe[i] == x){
                    equipe[i] = demanderChoixDansIntervalle(" Vous ne pouvez pas choisir deux fois le meme personnage",  1, 12 , ROUGE);
                }
                y = equipe[i];
                
                break;
                
            case 2:
                equipe[i] = demanderChoixDansIntervalle("👉 Choisis le troisième Personnage", 1, 12 , JAUNE);
                
                while(equipe[i] == x || equipe[i] == y){
                equipe[i] = demanderChoixDansIntervalle(" Vous ne pouvez pas choisir deux fois le meme personnage",  1, 12 , ROUGE);
                }
            
                break;
            default:
                printf("Erreur : nombre de personnages non supporté\n");
                exit(1);
        }
         

        printf("✅  Vous avez choisi : %s\n", persos[equipe[i] - 1].nom);
        
    }
}

void choix_joueur(int *equipe1, int *equipe2, int nbr_joueur , int mode) {
    switch(mode){
        case 1 : 
        printf("\n👥  EQUIPE 1, c’est à votre tour :\n");
    choix_joueur_E(equipe1, nbr_joueur);

    printf("\n👥  EQUIPE 2, c’est à votre tour :\n");
    choix_joueur_E(equipe2, nbr_joueur);
    break;
        case 2 : //  PVE
        
        printf("\n👥  EQUIPE 1, c’est à votre tour :\n");
    choix_joueur_E(equipe1, nbr_joueur);
    break;
    default:
                printf("Erreur : nombre de personnages non supporté\n");
                exit(1);
    
        // a voir pour le choix de l equipe du bot ...
    }
    
    printf("\n Appuie sur Entrée pour continuer... \n");
    while (getchar() != '\n');
}

void afficher_stats() {
    system("clear");
    const char* noms_assets[] = {
        "1 - Bouclier     ",
        "2 - Épée         ",
        "3 - Mitraillette ",
        "4 - Bâton        ",
        "5 - Medkit       ",
        "6 - Éclair       "
    };
    const char *stats_pos[] = { "DEF", "ATT", "CRIT", "DODGE", "PV", "SPEED" };
    const char *stats_neg[] = { "DODGE", "DEF", "PV", "CRIT", "ATT", "ATT" };

    // Ligne des noms d'atouts
    for (int i = 0; i < 6; i++) {
        printf("[ %s]",noms_assets[i]);
    }

    printf("\n\n");

    // Ligne des stats positives
    for (int i = 0; i < 6; i++) {
        printf(VERT"[+] %-16s", stats_pos[i]);
    }

    printf("\n\n");

    // Ligne des stats négatives
    for (int i = 0; i < 6; i++) {
        printf(ROUGE"[-] %-16s" RESET, stats_neg[i]);
    }

    printf("\n\n\n");
}

void choix_assets(int equipe[], int nbr_joueur) {
    int arme  = 0;
    for (int i = 0; i <= nbr_joueur; i++) {
        
        arme  = demanderChoixDansIntervalle("choisir arme : " , 0,6 , VERT);
        Personnage *p = &persos[equipe[i] - 1]; // récupérer le pointeur vers le personnage
        atout(p, arme);                        // appliquer l'atout directement
        afficherPersonnage(equipe[i] - 1);     // afficher les stats mises à jour
        
        // METRE A JOUR LA STRUCT PLAYER AVEC L AUTRE FONCTION ATOUT ...
    }
}

void choix_assets_E(int equipe1[],int equipe2[], int nbr_joueur ) {
    afficher_stats();
    printf("Au tour de l equipe 1:  \n");
    choix_assets(equipe1 , nbr_joueur);
    
    printf("\n Appuie sur Entrée pour continuer... \n");
    while (getchar() != '\n');
    
    afficher_stats();
    printf("Au tour de l equipe 2:  \n");
    choix_assets(equipe2 , nbr_joueur);
    
    
    
}


int main() { 
    int mode = 0 , nbr_joueur = 0 ; 
    int equipe1[3] , equipe2[3];
    
    afficherTitre();
    afficherMenu(&mode , &nbr_joueur);
    afficherTousLesPersos();
    choix_joueur(equipe1, equipe2, nbr_joueur , mode);
    choix_assets_E(equipe1,equipe2 ,nbr_joueur);
    return 0;
}
