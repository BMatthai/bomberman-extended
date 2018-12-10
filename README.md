**Bomberman 1**
- Note : 12/20

- Commentaire du prof :
Projet de bomberman en ASCII !!! C'était plutôt stylé même si l'interface paraît simpliste au premier abord. Le jeu en lui même est plutôt complet, il y a pas mal de fonctionnalités de gameplay implémentées. La seule qui manque est l'explosion en chaîne. Point le plus dommage, pas de réseau implémenté. Malus appliqué pour les retours de fonctions non vérifiées comme malloc, par exemple. Dans l'ensemble, c'était plutôt bien. Dommage que vous n'ayez pas pu voir les problématiques liées au développement en réseau.


**Backlog :**
- [x] Rendre le jeu existant plus stable
- [x] Explosion en chaîne des bombes
- [ ] Implémenter un nouvel affichage complet via SDL (WIP Bastien)
- [ ] ~~Améliorer l'affichage du jeu en ASCII~~ (Pas prio)
- [ ] Vérifier le retours des mallocs et gérer les erreurs
- [ ] Tester le retours des fonctions en général et gérer les erreurs
- [ ] Gérer les fuites de mémoires.
- [ ] Amélioration du Makefile : factoriser le fichier. Séparer les fichiers .o .h et .c dans des dossiers build, inc et src.
- [ ] ~~Refaire entièrement le menu de jeu (en SDL)~~
- [ ] Ajouter création de map aléatoires, cohérentes et qui ont un interêt d'un point de vue Gameplay (WIP Bastien)
- [ ] Créer une boucle de jeu qui ne dépend pas du CPU (WIP Bastien)
- [ ] ~~Améliorer IA / Refactoriser complêtement~~ (Pas prio)
- [ ] Implémenter réseau

