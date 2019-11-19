**Bomberman 1**
- Note : 12/20

- Commentaire du prof :
Projet de bomberman en ASCII !!! C'était plutôt stylé même si l'interface paraît simpliste au premier abord. Le jeu en lui même est plutôt complet, il y a pas mal de fonctionnalités de gameplay implémentées. La seule qui manque est l'explosion en chaîne. Point le plus dommage, pas de réseau implémenté. Malus appliqué pour les retours de fonctions non vérifiées comme malloc, par exemple. Dans l'ensemble, c'était plutôt bien. Dommage que vous n'ayez pas pu voir les problématiques liées au développement en réseau.


**Backlog :**
- [x] Rendre le jeu existant plus stable
- [x] Explosion en chaîne des bombes
- [x] Ajouter création de map aléatoires en se basant sur l'algorithme de Kruskal.
- [x] Implémenter un nouvel affichage en utilisant SDL (A améliorer)
- [x] Séparer les fichiers .o .h et .c dans des dossiers build, include et src.
- [x] Créer le menu de jeu (A améliorer)
- [ ] Factoriser Makefile.
- [ ] Faire en sorte que ça compile avec SDL sous Linux et Windows
- [ ] Créer une boucle de jeu qui ne dépend pas du CPU

- [ ] Faire un audit de performance CPU et/ou RAM, et optimiser
- [ ] Analyse Portabilité : voir comment rendre le jeu compatible Windows sans enlever la compatibilité OSX
- [ ] Analyse Distribution : voir comment faire la distribution

- [ ] ~~Implémenter réseau~~ __(Pas prio)__
- [ ] ~~Vérifier le retours des mallocs et gérer les erreurs~~ __(Pas prio)__
- [ ] ~~Tester le retours des fonctions en général et gérer les erreurs~~ __(Pas prio)__
- [ ] ~~Gérer les fuites de mémoires.~~ __(Pas prio)__
- [ ] ~~Améliorer IA / Refactoriser complêtement~~ __(Pas prio)__
