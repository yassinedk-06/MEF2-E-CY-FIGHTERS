#include <stdio.h>
#include <stdlib.h> 

#define ROUGE   "\033[1;31m"
#define VERT    "\033[1;32m"
#define JAUNE   "\033[1;33m"
#define BLEU    "\033[1;36m"
#define RESET   "\033[0m"


#define PVMAX 120
#define ENNERGY 10

typedef struct{
  char* name;
  float pv; //50<x<100
  float pv_max; //120
  float def; // 0.1<x<0.5 pourcentage de reduction des degat
  float att;// 3<x<8  
  int speed; // vitesse de regen d ennergie 
  float dodge;  // 0.1<x<0.5 probabilite de dodge
  int ennergie ; // 10 de base

  char* crit_name1 ; //nom de l attaque critique
  float crit1; // 0.1<x<1 multiplicateur des degats
  float crit_conso1; // la consommation d ennergie de l attaque speciale 1 : entre 1 et 3

  char* crit_name2 ; //nom de l attaque critique
  float crit2; // 0.1<x<1 multiplicateur des degats
  float crit_conso2; // la consommation d ennergie de l attaque speciale 2 : entre 2 et 6

}Player;


typedef enum{Bouclier, Epee, Mitraillette, Baton, Medkit ,Eclair , None}Assets; // enumeration des assets



 // declaration des joueurs ( a chager par les files ) 
Player p1 = {"luffy" , 70 , PVMAX, 0.3 , 7 , 2 , 0.4 , ENNERGY , "Gum Gum no Gum Gum" , 1.4 , 2 , "Gear 5" , 1.8 , 4 };
Player p2 = {"sanji", 60, PVMAX, 0.4, 8, 3, 0.2, ENNERGY, "diabolo jumbo", 1.2, 2, "bien cuit grill shot", 1.4, 4};
Player p3 = {"zoro", 80, PVMAX, 0.1, 7, 4, 0.3, ENNERGY, "tiger slash", 1.1, 2, "oni giri", 1.2, 4};
Player p4 = {"ace", 90, PVMAX, 0.3, 5, 1, 0.5, ENNERGY, "Flame fence", 1.2, 1, "Heat haze", 1.4, 2};
Player p5 = {"brook", 70, PVMAX, 0.4, 5, 4, 0.3, ENNERGY, "Song slash", 1.2, 3, "blizzard slice", 1.4, 6};
Player p6 = {"ussop", 80, PVMAX, 0.3, 5, 3, 0.4, ENNERGY, "Skull bomb blast", 1.1, 1, "Platanus Shuriken", 1.2, 2};
Player p7 = {"do flamingo", 60, PVMAX, 0.4, 5, 5, 0.3, ENNERGY, "Fallbright", 1.2, 2, "String saw", 1.4, 4};
Player p8 = {"big mom", 80, PVMAX, 0.3, 6, 1, 0.5, ENNERGY, "Master cannon", 1.3, 1, "Mama raid", 1.6, 2};
Player p9 = {"katakuri", 80, PVMAX, 0.4, 8, 1, 0.2, ENNERGY, "Mochi hadan", 1.3, 3, "Zan Giri Mochi", 1.6, 6};
Player p10 = {"black beard", 80, PVMAX, 0.1, 7, 4, 0.3, ENNERGY, "Black hole", 1.4, 2, "Black vortex", 1.8, 4};
Player p11 = {"crocodile", 60, PVMAX, 0.5, 4, 5, 0.3, ENNERGY, "Desert spada", 1.2, 3, "Ground death", 1.4, 6};
Player p12 = {"Kaido", 90, PVMAX, 0.3, 8, 4, 0.2, ENNERGY, "Thunder", 1.4, 2, "Blast breath", 1.8, 4};





typedef struct {
    char* nom;
    int pv;
    int att;
    int def;
    int speed;
    int dodge;
    int crit;
} Personnage;

Personnage persos[12] = {  //pour l affichage 
    {"(1)  Luffy", 2, 4, 3, 2, 4, 4},
    {"(2)  Sanji", 1, 5, 4, 3, 2, 2},
    {"(3)  Zoro", 3, 4, 1, 4, 3, 1},
    {"(4)  Ace", 4, 2, 3, 1, 5, 2},
    {"(5)  Brook", 2, 2, 4, 4, 3, 2},
    {"(6)  Ussop", 3, 2, 3, 3, 4, 1},
    {"(7)  Do Flamingo", 1, 2, 4, 5, 3, 2},
    {"(8)  Big Mom", 3, 3, 3, 1, 5, 3},
    {"(9)  Katakuri", 3, 5, 4, 1, 2, 3},
    {"(10) Black Beard", 3, 4, 1, 4, 3, 4},
    {"(11) Crocodile", 1, 1, 5, 5, 3, 2},
    {"(12) Kaido", 4, 5, 3, 4, 2, 4}
};

void atout(Personnage *p, int a) {
    switch (a) {
        case 1: p->def++; p->dodge--; break;
        case 2: p->att++; p->def--; break;
        case 3: p->crit++; p->pv--; break;
        case 4: p->dodge++; p->crit--; break;
        case 5: p->pv++; p->att--; break;
        case 6: p->speed++; p->att--; break;
        case 0: break;
        default:
            printf("Erreur : atout non reconnu\n");
            exit(1);
    }
}


int demanderChoixDansIntervalle(const char *texte, int min, int max, const char *couleur) {
    int choix = 0;
    char ligne[10];

    do {
        printf("%s%s (%d à %d) : " RESET, couleur, texte, min, max);
        if (fgets(ligne, sizeof(ligne), stdin)) {
            if (sscanf(ligne, "%d", &choix) == 1 && choix >= min && choix <= max) {
                return choix;
            }
        }
        printf(ROUGE "Choix incorrect, rechoisis\n" RESET);
    } while (1);
}

int demanderChoix(const char *texte ) {
    int choix = 0;
    char ligne[10];

    do {
        printf(JAUNE "%s (1 ou 2) : " RESET, texte);
        if (fgets(ligne, sizeof(ligne), stdin)) {
            if (sscanf(ligne, "%d", &choix) == 1 && (choix == 1 || choix == 2)) {
                return choix;
            }
        }
        printf(ROUGE "Choix incorrect, rechoisis\n" RESET);
    } while (1);
}
