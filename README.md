# Bash-Build 🏗️

Un jeu de gestion type **monopoly du BTP**, joué entièrement dans le terminal.
Projet d'algorithmique-programmation de première année, réalisé en groupe.

## Gameplay

Sur un plateau ASCII, votre joueur (`X`) achète des terrains et construit des
bâtiments pour développer sa ville :

- **4 types de bâtiments** : Batiment 1x1 (500 €), 2x2 (1 000 €), 3x3 (2 000 €)
  et la **Banque** (4 000 €)
- Des **zones inconstructibles** (`/`) sont réparties aléatoirement sur le
  plateau à chaque partie
- Une fois la **Banque** construite, vous pouvez contracter un **prêt**
  (jusqu'à 3× votre capital, avec mensualités)
- Les bâtiments génèrent des **bénéfices** au fil des tours
- **Sauvegarde / chargement** de partie

Deux modes de jeu : **Construction** (gérer sa ville) et **Avatar**
(déplacer son personnage sur le plateau).

## Compilation & lancement

```bash
gcc -std=gnu99 bash-build.c -lm -o bash-build
./bash-build
```

Aucune dépendance externe, fonctionne sur Linux (la version finale ne dépend
plus de l'API Windows).

## Fichiers

| Fichier | Description |
|---|---|
| `bash-build.c` | Version la plus complète du jeu |
| `monopoly.c` | Première version du jeu |
| `sauvegarde-et-temps-wip.c` | Itération en cours : temps accéléré + sauvegarde |
| `load_and_save.c` | Module de sauvegarde/chargement |
| `fonction_kamikaze.c` | Prototype de fonction bonus |

## Équipe

- [lepseudo-prog](https://github.com/lepseudo-prog)
- [ManmanwAvecPlaisir](https://github.com/ManmanwAvecPlaisir)
- [thiasmaSan](https://github.com/thiasmaSan)
