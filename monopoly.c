#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

struct Joueur {
    int argent;
    int nb_Batiment;
    float Benefice;
    struct Joueur *suivant;
};
typedef struct Joueur Joueur;

struct Batiment {
    int prix;
    int y;
    int x;
    int type;
    struct Batiment *suivant;
};
typedef struct Batiment Batiment;


void calculateYearsMonthsDaysPassed(long long int seconds,long long int *result) {
    int secondsPerHour = 3600;
    int hoursPerDay = 24;
    int daysPerMonth = 30;

    long long int totalHours = seconds / 2;
    long long int years = totalHours / (hoursPerDay * 365);
    long long int remainingHours = totalHours % (hoursPerDay * 365);
    int months = remainingHours / (hoursPerDay * daysPerMonth);
    int remainingDays = (remainingHours % (hoursPerDay * daysPerMonth)) / hoursPerDay;
    result[0] = years;
    result[1] = months;
    result[2] = remainingDays;

}
void afficherTableau(char **tableau, int LIGNES, int COLONNES) {
    printf(" ___");
    for (int j = 0; j < COLONNES; j++) {
        if(j<10){
            printf("| %d ", j);;
        }else{
            printf("| %d", j);;
        }
    }
    printf("|");
    printf("\n");
    for (int i = 0; i < LIGNES; i++) {
        if(i<10){
            printf(" %d  |", i);
        }else{
            printf(" %d |", i);
        }
        for (int j = 0; j < COLONNES; j++) {
            printf(" %c |",tableau[i][j]);
        }
        printf("\n");
    }
}

Joueur *inisJoueur() {
    Joueur *joueur = malloc(sizeof(Joueur));
    joueur->argent = 10000;
    joueur->nb_Batiment = 0;
    joueur->Benefice = 0;
    return joueur;
}

void deplacerJoueur(char **tableau, int LIGNES, int COLONNES, int nouvelleLigne, int nouvelleColonne, int *ligne, int *colonne) { //fini
    tableau[*ligne][*colonne] = ' ';
    if (nouvelleLigne < 0) {
        nouvelleLigne = 0;
    } 
    if (nouvelleLigne >= LIGNES) {
        nouvelleLigne = LIGNES - 1;
    }
    if (nouvelleColonne < 0) {
        nouvelleColonne = 0;
    }
    if (nouvelleColonne >= COLONNES) {
        nouvelleColonne = COLONNES - 1;
    }
    *ligne = nouvelleLigne;
    *colonne = nouvelleColonne;
    tableau[*ligne][*colonne] = 'X';
}

Batiment *construire(int LIGNES,int COLONNES,char **tableau, int casex, int casey, int *ligne, int *colonne){ //fini
    tableau[*ligne][*colonne] = ' ';
    Batiment *bat = malloc(sizeof(Batiment));
    *ligne = casex;
    *colonne = casey;
    bat->x = casex;
    bat->y = casey;
    printf("Liste des Batiments constructibles :\n1 : Batiment 1x1 -> 500e\n2 : Batiment 2x2 ->1000e\n3 : Batiment 3x3 -> 2000e\n4 : La Banque -> 4000e\n");
    printf("Quelle type de batiment : ");
    scanf("%d",&bat->type);
    if(bat->type==1){
        for(int i=0;i<1;i++){
            for(int j=0;j<1;j++){
                tableau[*ligne+j][*colonne+i] = 'S';
            }
        }
        bat->prix = 500;
    }else if(bat->type==2){
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                tableau[*ligne+j][*colonne+i] = 'S';
            }
        }
        bat->prix = 1000;
    }else if(bat->type==3){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                tableau[*ligne+j][*colonne+i] = 'S';
            }
        }
        bat->prix = 2000;
    }else if(bat->type==4){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                tableau[*ligne+j][*colonne+i] = 'B';
            }
        }
        bat->prix = 4000;
    }
    
    return bat;
}

void zonesNC(char **tableau, int LIGNES, int COLONNES) { //fini mais wallah c'est bizarre
    srand(time(NULL));
    int nb_zone = (rand() % (8 - 4 + 1)) + 3;
    while (nb_zone != 0) {
        int random_x = (rand() % (LIGNES - 1 + 1)) + 1;
        int random_y = (rand() % (COLONNES - 1 + 1)) + 1;
        int taille = (rand() % (3 - 1 + 1)) + 1;
        for (int i = 0; i < taille; i++) {
            for (int j = 0; j < taille; j++) {
                int new_x = random_x + i;
                int new_y = random_y + j;
                tableau[new_x][new_y] = '/';
            }
        }

        nb_zone--;
    }
}

void achat(Joueur *joueur,Batiment *b){ //fini
    joueur->argent -= b->prix;
    joueur->nb_Batiment +=1;
    printf("Votre porte-monnaie est de %de\n",joueur->argent);
    printf("Vous avez %d Batiment(s)\n",joueur->nb_Batiment);
}



void benef(Joueur *joueur, Batiment **liste) { //fini
    Batiment *bat = *liste;
    while (bat != NULL) {
        if (bat->type == 1) {
            joueur->Benefice += 150;
            joueur->argent += 150;
        } else if (bat->type == 2) {
            joueur->Benefice += 300;
            joueur->argent += 300;
        } else if (bat->type == 3) {
            joueur->Benefice += 600;
            joueur->argent += 600;
        }
        bat = bat->suivant;
    }
}

void pret(Joueur *joueur){
    float taux=0.05;
    int mensualite;
    float montant,montant_max;
    float remboursement;
    joueur->argent = (joueur->argent)-((joueur->argent)*taux);
    montant_max = (joueur->argent)*3;
    printf("Selon votre capital vous avez droit à un emprunt de %f euros maximum\n",montant_max);
    printf("Quelle somme voulez-vous emprunté : ");
    scanf("%f",&montant);
    while(montant>montant_max){
        printf("Votre emprunt ne peut excéder %f euros : ");
        scanf("%f",&montant);
    }
    printf("En combien de mensualités rembourserez-vous : ");
    scanf("%d",&mensualite);
    while(mensualite>60){
        printf("Ne peut pas être supérieur a 60 mensualités (5ans) : ");
        scanf("%d",&mensualite);
    }
    remboursement = (montant*((taux*100)/12)/(1-(1+(taux*100)/12)-(12*(mensualite/12))));
    printf("\nPrêt accordé :\n");
    printf("Montant emprunté : %f\n", montant);
    printf("Taux d'intérêt : %.2f%%\n", (taux*100));
    printf("Durée du prêt : %d mois\n", mensualite);
    printf("Mensualité : %.2f\n", remboursement);

}
void initListe(Batiment *liste){ //fini
    liste=NULL;
}

void listBat(Batiment *bat, Batiment **liste) { //fini
    bat->suivant = *liste;
    *liste = bat;
}

void affichBat(Batiment **liste) { //fini
    Batiment *bat = *liste;
    char *typebat;

    while (bat != NULL) {
        if (bat->type == 1) {
            typebat = "Batiment 1x1";
        } else if (bat->type == 2) {
            typebat = "Batiment 2x2";
        } else if (bat->type == 3) {
            typebat = "Batiment 3x3";
        } else if (bat->type == 4) {
            typebat = "Banque";
        }
    
        printf("Type : %s\n", typebat);
        printf("Position : (%d, %d)\n", bat->y, bat->x);
        printf("\n");

        bat = bat->suivant;
    }
}
int jeu(int lignes1, int colonnes1){
    long long int tab_temps[3];
    time_t startTime, currentTime;
    long long int elapsedSeconds;
    int choix , modeGame,cons,eligible=3,choixpret;
    // Déclarer le tableau 10x10 au minimum
    char **tableau;
    int LIGNES = lignes1;
    int COLONNES = colonnes1;
    // Initialiser le tableau avec des caractères d'espace (' ')
    tableau = (char **)malloc(LIGNES * sizeof(char *));
    for (int i = 0; i < LIGNES; i++) {
        tableau[i] = (char *)malloc(COLONNES * sizeof(char));
        for (int j = 0; j < COLONNES; j++) {
            tableau[i][j] = ' ';
        }
    }
    // Position initiale du joueur
    int ligneJoueur = 0;
    int colonneJoueur = 0;
    tableau[ligneJoueur][colonneJoueur] = 'X';  // Marquer la position du joueur sur le tableau
    afficherTableau(tableau, LIGNES, COLONNES);
    Batiment *b,*l=NULL;
    Joueur *j;
    int ouibanque=0;
    j = inisJoueur();
    time(&startTime);
    time(&currentTime);
    do{
        printf("Choisissez le mode de jeu:\n1: Mode de Construction \n2: vide\n3: Afficher la zone de jeu\n");
        scanf("%d", &modeGame);
        int nouvelleLigne , nouvelleColonne;
        switch (modeGame) {
            case 1:
                
                printf("Choix n°1\n");
                zonesNC(tableau, LIGNES, COLONNES);
                afficherTableau(tableau, LIGNES, COLONNES);
                while(1){
                    time(&currentTime);
                    elapsedSeconds = (currentTime - startTime) * 64;
                    calculateYearsMonthsDaysPassed(elapsedSeconds, tab_temps);
                    if(eligible>=5 && ouibanque==1){
                        printf("Vous êtes éligible au prêt\nSouhaitez-vous en faire un :\n1 : oui\n2 : non\n ");
                        scanf("%d",&choixpret);
                        if(choixpret==1){
                            pret(j);
                            eligible=0;
                        }
                    }
                    printf("Entrez les nouvelles coordonnées du joueur (ligne colonne) ou -1 -1 pour quitter : ");
                    scanf("%d %d", &nouvelleLigne, &nouvelleColonne);
                    if(nouvelleLigne == -1 && nouvelleColonne == -1){
                        break;
                    }
                    deplacerJoueur(tableau, LIGNES, COLONNES, nouvelleLigne, nouvelleColonne, &ligneJoueur, &colonneJoueur);
                    printf("voulez-vous construire :\n1 : oui \n2 : non\n");
                    scanf("%d",&cons);
                    if(cons==1){
                        b = construire(LIGNES,COLONNES,tableau,nouvelleLigne, nouvelleColonne, &ligneJoueur, &colonneJoueur);
                        if(b->type==4){
                            ouibanque=1;
                        }
                        listBat(b,&l);
                        //affichBat(&l);
                        achat(j,b);
                        benef(j,&l);
                    }
                    eligible++;
                    printf("eligible %d\n",eligible);
                    afficherTableau(tableau, LIGNES, COLONNES);
                }         
                break;
            case 2:
                printf("Choix n°2\n");
                break;
            case 3:
                printf("Votre zone de jeu:\n");
                while(1){
                    time(&currentTime);
                    elapsedSeconds = (currentTime - startTime) * 64;
                    calculateYearsMonthsDaysPassed(elapsedSeconds, tab_temps);
                    printf("Entrez les nouvelles coordonnées du joueur (ligne colonne) ou -1 -1 pour quitter : ");
                    scanf("%d %d", &nouvelleLigne, &nouvelleColonne);
                    if(nouvelleLigne == -1 && nouvelleColonne == -1){
                        break;
                    }
                    deplacerJoueur(tableau, LIGNES, COLONNES, nouvelleLigne, nouvelleColonne, &ligneJoueur, &colonneJoueur);
                              
                    afficherTableau(tableau, LIGNES, COLONNES);
                }
                break;
                default:
                    printf("Choix non disponible\n");
                    break;
                }   
        } while (modeGame != 1 && modeGame != 3);

    for (int i = 0; i < LIGNES; i++) {
        free(tableau[i]);
    }
    free(tableau);

    return 0;
}

void menu_principal(){
    int choix;
    printf("Bienvenue dans Bash-Build \nFaites votre choix dans le Menu \n1: Visualiser les règles\n2: Commencer une nouvelle partie\n3: Charger une partie\n");
    scanf("%d", &choix);
    switch(choix){
            case 1:
                printf("Le joueur dispose d’une certaine somme d’argent au début du jeu, assez pour construire \nau moins 1 à 2 bâtiments de faible coût. Le joueur, en construisant un bâtiment de type Banque, peut alors\nobtenir un prêt à hauteur de 3 fois son capital, avec un pourcentage d’au moins 5 pourcent, sur une durée inférieure\nà 5 ans, avec des mensualités proportionnelles aux données.\n");
                break;
            case 2:
                int choix_plat;
                printf("Choisissez les dimensions du plateau : \n");
                printf("1: 10x10 \n2: 15x15 \n3: Dimension Personnalisés\n");
                scanf("%d", &choix_plat);
                switch(choix_plat){
                    case 1:
                        jeu(10, 10);
                        break;
                    case 2:
                        jeu(15,15);
                        break;
                    case 3:
                        int LIGNES, COLONNES;
                        do{
                        printf("Maintenant tu peux entrer les dimensions de l'air de jeu :\n");
                        printf("Lignes :");
                        scanf("%d", &LIGNES);
                        printf("Colonnes :");
                        scanf("%d", &COLONNES);
                        } while (LIGNES < 10 && COLONNES<10);
                        jeu(LIGNES, COLONNES);
            
                }
                break;
    }

}

int main() {
    menu_principal();
}
