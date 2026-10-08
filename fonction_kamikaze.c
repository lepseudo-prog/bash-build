typedef struct {
    char* name;
    int probability;
    int cooldown;
} RandomEvent;
//au début de jeu
Batiment *parcours;
parcours = *b;
int nb_banques = 0;
//dans la boucle (1)
while (parcours->suivant != NULL) {
    if (parcours->type == 4){
        nb_banques ++;
    }
    *parcours = parcours->suivant;
}
srand(time(NULL));
int nb_random = rand() % 300;
if (nb_random == tab_temp) 
cooldown = 1;
kamikaze(tab)
