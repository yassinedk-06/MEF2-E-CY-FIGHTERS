#include <stdio.h>
#include <stdlib.h> 

#define ROUGE   "\033[1;31m"
#define VERT    "\033[1;32m"
#define JAUNE   "\033[1;33m"
#define BLEU    "\033[1;36m"
#define RESET   "\033[0m"


#define PVMAX 120
#define ENNERGIE 10


typedef struct{
  float pv; //50<x<100
  float pv_max; //120
  float def; // 0.1<x<0.5 pourcentage de reduction des degat
  float att;// 3<x<8  
  int speed; // probabilite de rejouer 
  float dodge;  // 0.1<x<0.5 probabilite de dodge
}Stats;



typedef struct {
    int pv;
    int att;
    int def;
    int speed;
    int dodge;
} Effect;

typedef struct{
  char* name;
  float valeur;
  char description[200];
  int tour_actif;
  int recharge;
  Effect buff;
} Special;


typedef struct{
  char* name;
  Stats stats;
  Stats stats_temp;
  Special atk_spe;
  int tour_buff_restant;
   
}Player;


Player p[12] = {  //liste de tout les personnages 
  {
    "luffy",                    /// nom du perso
    {70, PVMAX, 0.3, 7, 2, 0.4},   /// stats du perso
    {70, PVMAX, 0.3, 7, 2, 0.4}, /// stats temporaire du perso 
    {"Gum Gum no Gum Gum", 1.4, "", 2, 0, {0, 0, 0, 0, 0}},  /// l'attaque spéciale et ses attributs 
    0
  },
  
  {
    "sanji",
    {60, PVMAX, 0.4, 8, 3, 0.2},
    {60, PVMAX, 0.4, 8, 3, 0.2},
    {"diabolo jumbo", 1.2, "", 2, 0, {0, 0, 0, 0, 0}},
    0
  },
  
  {
    "zoro",
    {80, PVMAX, 0.1, 7, 4, 0.3},
    {80, PVMAX, 0.1, 7, 4, 0.3},
    {"tiger slash", 1.1, "", 2, 0, {0, 0, 0, 0, 0}},
    0
  },
  
  {
    "ace",
    {90, PVMAX, 0.3, 5, 1, 0.5},
    {90, PVMAX, 0.3, 5, 1, 0.5},
    {"Flame fence", 1.2, "", 1, 0, {0, 0, 0, 0, 0}},
    0
  },

  {
    "brook",
    {70, PVMAX, 0.4, 5, 4, 0.3},
    {70, PVMAX, 0.4, 5, 4, 0.3},
    {"Song slash", 1.2, "", 3, 0, {0, 0, 0, 0, 0}},
    0
  },
  {
    "ussop",
    {80, PVMAX, 0.3, 5, 3, 0.4},
    {80, PVMAX, 0.3, 5, 3, 0.4},
    {"Skull bomb blast", 1.1, "", 1, 0, {0, 0, 0, 0, 0}},
    0
  },

  {
    "do flamingo",
    {60, PVMAX, 0.4, 5, 5, 0.3},
    {60, PVMAX, 0.4, 5, 5, 0.3},
    {"Fallbright", 1.2, "", 2, 0, {0, 0, 0, 0, 0}},
    0
  },

  {
    "big mom",
    {80, PVMAX, 0.3, 6, 1, 0.5},
    {80, PVMAX, 0.3, 6, 1, 0.5},
    {"Master cannon", 1.3, "", 1, 0, {0, 0, 0, 0, 0}},
    0
  },

  {
    "katakuri",
    {80, PVMAX, 0.4, 8, 1, 0.2},
    {80, PVMAX, 0.4, 8, 1, 0.2},
    {"Mochi hadan", 1.3, "", 3, 0, {0, 0, 0, 0, 0}},
    0
  },
  
  {
    "black beard",
    {80, PVMAX, 0.1, 7, 4, 0.3},
    {80, PVMAX, 0.1, 7, 4, 0.3},
    {"Black hole", 1.4, "", 2, 0, {0, 0, 0, 0, 0}},
    0
  },
  
  {
    "crocodile",
    {60, PVMAX, 0.5, 4, 5, 0.3},
    {60, PVMAX, 0.5, 4, 5, 0.3},
    {"Desert spada", 1.2, "", 3, 0, {0, 0, 0, 0, 0}},
    0
  },
  
  {
    "Kaido",                           
    {90, PVMAX, 0.3, 8, 4, 0.2},
    {90, PVMAX, 0.3, 8, 4, 0.2},
    {"Thunder", 1.4, "", 2, 0, {0, 0, 0, 0, 0}},
    0
  }
};



void vraiatout(Player* p, int a) { //change les stats des perso
  switch(a) {
      case 1 : //Bouclier
          p->stats_temp.def += 0.1;
          p->stats_temp.dodge -= 0.1;
          break;
      case 2: //Epee
          p->stats_temp.att += 0.1;
          p->stats_temp.def -= 0.1;
          break;
      case 3: //Mitraillette
          p->stats_temp.pv -= 10;
          break;
      case 4: //Baton
          p->stats_temp.dodge += 0.1;
          break;
      case 5: //medkit
          p->stats_temp.pv += 10;
          p->stats_temp.att -= 0.1;
          break;
      case 6: //Eclair
          p->stats_temp.speed += 1;
          p->stats_temp.att -= 0.1;
          break;
      case 0 : //none
          break;
      default:
          printf("Erreur : atout non reconnu\n");
          exit(1);
  }

  // Sécurité : éviter de dépasser les limites si nécessaire
  if (p->stats_temp.pv > p->stats.pv_max) {
      p->stats_temp.pv = p->stats.pv_max;
  }
}




typedef struct {
  char* nom;
    int pv;
    int att;
    int def;
    int speed;
    int dodge;
    int crit;
} AffichagePerso;

AffichagePerso persos_affichage[12] = { // struct pour l affichage des barres
  {"(1)  Luffy", 2, 4, 3, 2, 4},
  {"(2)  Sanji", 1, 5, 4, 3, 2},
  {"(3)  Zoro", 3, 4, 1, 4, 3},
  {"(4)  Ace", 4, 2, 3, 1, 5},
  {"(5)  Brook", 2, 2, 4, 4, 3},
  {"(6)  Ussop", 3, 2, 3, 3, 4},
  {"(7)  Do Flamingo", 1, 2, 4, 5, 3},
  {"(8)  Big Mom", 3, 3, 3, 1, 5},
  {"(9)  Katakuri", 3, 5, 4, 1, 2},
  {"(10) Black Beard", 3, 4, 1, 4, 3},
  {"(11) Crocodile", 1, 1, 5, 5, 3},
  {"(12) Kaido", 4, 5, 3, 4, 2}
};

void atout(AffichagePerso *p, int a) {
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


