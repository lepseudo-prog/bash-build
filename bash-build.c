#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h> 

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
    int numero;
    struct Batiment *suivant;
};
typedef struct Batiment Batiment;

void sauvegarder_partie(char **tab, int nb_lignes, int nb_colonnes){
    FILE *file = fopen("sauvegarde.txt", "w");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
    }
    else{
        for (int i = 0; i < nb_lignes; i++) {
            for (int j = 0; j < nb_colonnes; j++) {
                fprintf(file, "%c ", tab[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }
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

Batiment *construire(int LIGNES,int COLONNES,char **tableau, int casex, int casey, int *ligne, int *colonne,Joueur *joueur,int *numbat){ //fini
    //tableau[*ligne][*colonne] = ' ';
    
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
                if(tableau[*ligne+j][*colonne+i]!='/'){
                    tableau[*ligne+j][*colonne+i] = 'S';
                    
                }else{
                    printf("espace insuffisant\n");
                }
            }
            bat->prix = 500;
            joueur->nb_Batiment +=1;
            joueur->argent -= bat->prix;
        }
        
    }else if(bat->type==2){
        bool cons=true;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                if(tableau[*ligne+j][*colonne+i]=='/'){
                    cons=false;
                }
            }
        }
        if(cons){
            for(int i=0;i<2;i++){
                for(int j=0;j<2;j++){
                    tableau[*ligne+j][*colonne+i] = 'S';
                }
            }
            bat->prix = 1000;
            joueur->nb_Batiment +=1;
            joueur->argent -= bat->prix;
        }else{
            printf("espace insuffisant\n");
        }
        
    }else if(bat->type==3){
        bool cons=true;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(tableau[*ligne+j][*colonne+i]=='/'){
                    cons=false;
                }
            }
        }
        if(cons){
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    tableau[*ligne+j][*colonne+i] = 'S';
                }
            }
            bat->prix = 2000;
            joueur->nb_Batiment +=1;
            joueur->argent -= bat->prix;
        }else{
            printf("espace insuffisant\n");
        }
        
    }else if(bat->type==4){
        bool cons=true;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(tableau[*ligne+j][*colonne+i]=='/'){
                    cons=false;
                }
            }
        }
        if(cons){
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    tableau[*ligne+j][*colonne+i] = 'B';
                    
                }
            }
            bat->prix = 4000;
            joueur->nb_Batiment +=1;
            joueur->argent -= bat->prix;
        }else{
            printf("espace insuffisant\n");
        }
        
    }
    (*numbat)++;
    bat->numero = *numbat;
    
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

void pret(Joueur *joueur) {
    float taux = 0.05;
    float montantMax, montant, tauxMensuel, remboursement;
    int mensualite;
    montantMax = 3 * joueur->argent;
    printf("Selon votre capital, vous avez droit à un emprunt de %.2f euros maximum.\n", montantMax);
    printf("Quelle somme voulez-vous emprunter : ");
    scanf("%f", &montant);
    
    while (montant <= 0 || montant > montantMax) {
        printf("Votre emprunt ne peut excéder %.2f euros : ",montantMax);
        scanf("%f", &montant);
    }
    
    printf("En combien de mensualités rembourserez-vous (maximum 60 mois / 5 ans) : ");
    scanf("%d", &mensualite);
    while (mensualite <= 0 || mensualite > 60); {
        printf("En combien de mensualités rembourserez-vous (maximum 60 mois / 5 ans) : ");
        scanf("%d", &mensualite);
    } 
    tauxMensuel = taux / 12.0;
    remboursement = (montant * tauxMensuel) / (1 - pow(1 + tauxMensuel, -mensualite));
    joueur->argent += montant;
    printf("\nPrêt accordé :\n");
    printf("Montant emprunté : %.2f euros\n", montant);
    printf("Taux d'intérêt : %.2f%%\n", taux * 100);
    printf("Durée du prêt : %d mois\n", mensualite);
    printf("Mensualité : %.2f euros\n", remboursement);
    printf("Votre porte-monnaie est de %de\n",joueur->argent);
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
        printf("Numéro de Batiment : %d\n", bat->numero);
        printf("Type : %s\n", typebat);
        printf("Position : (%d, %d)\n", bat->y, bat->x);
        printf("\n");

        bat = bat->suivant;
    }
}

Batiment *amelioration(Batiment **liste, int LIGNES, int COLONNES, char **tableau, int casex, int casey, int *ligne, int *colonne, Joueur *joueur, int *numbat) {
    Batiment *bat = *liste, *pbat = NULL;
    int num;

    affichBat(liste);

    printf("Quel bâtiment voulez-vous améliorer : ");
    scanf("%d", &num);

    while (bat != NULL && bat->numero != num) {
        pbat = bat;
        bat = bat->suivant;
    }
    if (bat == NULL) {
        printf("Batiment pas trouvé\n");
        return NULL;
    }
    int newligne = bat->x;
    int newcolonne = bat->y;
    Batiment *newbat = construire(LIGNES, COLONNES, tableau, casex, casey, &newligne, &newcolonne, joueur, numbat);
    newbat->numero = *numbat;
    if (bat->type == 1) {
        newbat->type = 2;
    } else if (bat->type == 2) {
        newbat->type = 3;
    }

    // Définir le prix de l'amélioration en fonction du type du nouvel étage
    int prix;
    switch (newbat->type) {
        case 2:
            prix = 500;
            break;
        case 3:
            prix = 1500;
            break;
        default:
            break;
    }

    // Afficher le coût de l'amélioration
    printf("L'amélioration a coûté %d euros.\n", prix);

    listBat(newbat,liste);


    return newbat;
}

int jeu(int lignes1, int colonnes1, int chargement){
    

    
    int choix , modeGame,eligible=0,choixpret;
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
    if (chargement == 1){
        char nom_file[40];
        int LIGNES, COLONNES;
        printf("donnez le nom de votre fichier ");
        scanf("%s", &nom_file);
        printf("donnez le nombre de lignes de votre sauvegarde :");
        scanf("%d", &LIGNES);
        printf("donnez le nombre de colonnes de votre sauvegarde :");
        scanf("%d", &COLONNES);
        FILE *file = fopen(nom_file, "r");
        if (file == NULL) {
            printf("Impossible d'ouvrir le fichier\n");
        }
        else {
            for (int i = 0; i < LIGNES; i++) {
                for (int j = 0; j < COLONNES; j++) {
                    fscanf(file, " %c", &tableau[i][j]);
                }
            }
        }
        fclose(file);
    }
    // Position initiale du joueur
    int ligneJoueur = 0;
    int colonneJoueur = 0;
    tableau[ligneJoueur][colonneJoueur] = 'X';  // Marquer la position du joueur sur le tableau
    afficherTableau(tableau, LIGNES, COLONNES);
    Batiment *b,*l=NULL;
    Joueur *j;
    int numbat=0;
    int ouibanque=0;
    j = inisJoueur();
    do{
        printf("Choisissez le mode de jeu:\n1: Mode de Construction \n2: Mode Avatar\n3: Retourner au menu principal");
        scanf("%d", &modeGame);
        int nouvelleLigne , nouvelleColonne;
        switch (modeGame) {
            case 1:
                
                printf("Choix n°1\n");
                zonesNC(tableau, LIGNES, COLONNES);
                afficherTableau(tableau, LIGNES, COLONNES);
                while(1){
                    if(eligible>=5 && ouibanque==1){
                        printf("Vous êtes éligible au prêt\nSouhaitez-vous en faire un :\n1 : oui\n2 : non\n ");
                        scanf("%d",&choixpret);
                        if(choixpret==1){
                            pret(j);
                            eligible=0;
                        }
                    }
                    printf("Entrez les nouvelles coordonnées du Batiment (ligne colonne) ou -1 -1 pour quitter : ");
                    scanf("%d %d", &nouvelleLigne, &nouvelleColonne);
                    if(nouvelleLigne == -1 && nouvelleColonne == -1){
                        break;
                    }
                    b = construire(LIGNES,COLONNES,tableau,nouvelleLigne, nouvelleColonne, &ligneJoueur, &colonneJoueur,j,&numbat);
                    if(b->type==4){
                        ouibanque=1;
                    }
                    listBat(b,&l);
                    printf("Votre porte-monnaie est de %de\n",j->argent);
                    printf("Vous avez %d Batiment(s)\n",j->nb_Batiment);
                    benef(j,&l);
                    int amelio;
                    if(eligible>2){
                        printf("souhaitez-vous améliorez un batiment :");
                        scanf("%d",&amelio);
                        if(amelio==1){
                            amelioration(&l,LIGNES,COLONNES,tableau,nouvelleLigne, nouvelleColonne, &ligneJoueur, &colonneJoueur,j,&numbat);
                        }
                    }
                    eligible++;
                    afficherTableau(tableau, LIGNES, COLONNES);
                }         
                break;
            case 2:
                printf("Mode avatar \n");
                while(1){
                    printf("Entrez les nouvelles coordonnées du joueur (ligne colonne) ou -1 -1 pour quitter : ");
                    scanf("%d %d", &nouvelleLigne, &nouvelleColonne);
                    if(nouvelleLigne == -1 && nouvelleColonne == -1){
                        break;
                    }

                    deplacerJoueur(tableau, LIGNES, COLONNES, nouvelleLigne, nouvelleColonne, &ligneJoueur, &colonneJoueur);
                    afficherTableau(tableau, LIGNES, COLONNES);
                    printf("info sur ce batiment : \n");
                    if(tableau[nouvelleLigne][nouvelleColonne]==' '){
                        printf("il n'ya rien \n");
                    }else if(tableau[nouvelleLigne][nouvelleColonne+1]=='B'){
                        printf("il ya une banque ici \n");
                    }else if(tableau[nouvelleLigne][nouvelleColonne+1]=='S'){
                        printf("il ya un batiment de type 2 ici \n");
                    }else if(tableau[nouvelleLigne][nouvelleColonne+1]=='Y'){
                        printf("il ya un batiment de type 3 ici \n");
                    }else if(tableau[nouvelleLigne][nouvelleColonne+1]=='U'){
                        printf("il ya un batiment de type 4 ici \n");
                    }
                }
                break;
            case 3:
                menu_principal();
                break;
            default:
                printf("Choix non disponible\n");
                break;
                }   
        } while (modeGame != 3);

    for (int i = 0; i < LIGNES; i++) {
        free(tableau[i]);
    }
    free(tableau);

    return 0;
}

int menu_principal(){
    int choix = 0;
    while(choix != 1 || choix != 2 || choix != 3) {
        printf("Bienvenue dans Bash-Build \nFaites votre choix dans le Menu \n1: Visualiser les règles\n2: Commencer une nouvelle partie\n3: Charger une partie\n4: Quitter\n");
        scanf("%d", &choix);
        
        switch (choix) {
            case 1:
                printf("Le joueur dispose d’une certaine somme d’argent au début du jeu, assez pour construire \nau moins 1 à 2 bâtiments de faible coût. Le joueur, en construisant un bâtiment de type Banque, peut alors\nobtenir un prêt à hauteur de 3 fois son capital, avec un pourcentage d’au moins 5 pourcent, sur une durée inférieure\nà 5 ans, avec des mensualités proportionnelles aux données.\n");
                break;
            case 2:
                printf("Choisissez les dimensions du plateau : \n");
                printf("1: 10x10 \n2: 15x15 \n3: Dimension Personnalisés\n");
                scanf("%d", &choix);
                switch (choix) {
                    case 1:
                        jeu(10, 10, 0);
                        break;
                    case 2:
                        jeu(15, 15, 0);
                        break;
                    case 3:
                        int LIGNES, COLONNES;
                        do {
                            printf("Maintenant tu peux entrer les dimensions de l'air de jeu :\n");
                            printf("Lignes :");
                            scanf("%d", &LIGNES);
                            printf("Colonnes :");
                            scanf("%d", &COLONNES);
                        } while (LIGNES < 10 && COLONNES < 10);
                        jeu(LIGNES, COLONNES, 0);
                        break;
                }
                break;
            case 3:
                jeu(0,0,1);
                break;
            case 4:
                printf("Au revoir !");
                return 0;
            default:
                printf("Choix non valide. Veuillez choisir à nouveau.\n");
        }
        break;
    } 
    return 0;
}

int main() {
    menu_principal();
}
