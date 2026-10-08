void sauvegarder_partie(char **tab, int nb_lignes, int nb_colonnes){
    FILE *file = fopen("sauvegarde.txt", "w");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        return 1;
    }
    for (int i = 0; i < nb_lignes; i++) {
        for (int j = 0; j < nb_colonnes; j++) {
            fprintf(file, "%c ", tab[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return 0;
}
void charger_partie(char **tab, int nb_lignes, int nb_colonnes){
    FILE *file = fopen("sauvegarde.txt", "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
    }
    else {
        for (int i = 0; i < LIGNES; i++) {
            for (int j = 0; j < COLONNES; j++) {
                fscanf(file, " %c", &tableau[i][j]);
            }
        }

    fclose(file);
}
charger_partie(tableau, LIGNES, COLONNES);
sauvegarder_partie(tableau, LIGNES, COLONNES);
