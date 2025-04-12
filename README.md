# 42sh

`42sh` est une réimplémentation d'un shell Unix conforme à une partie des spécifications de `tcsh`. Ce projet a été réalisé dans le cadre du module `Shell Programming` d'Epitech, avec pour objectif de reproduire le fonctionnement d’un shell avancé : parsing, exécution, gestion des pipes, redirections, variables d’environnement, historique, et bien plus.

## Fonctionnalités

- [x] Exécution de commandes binaires avec ou sans chemin
- [x] Gestion des pipes (`|`) et des redirections (`>`, `<`, `>>`, `<<`)
- [ ] Gestion des variables d’environnement
- [x] Implémentation de built-ins (`cd`, `setenv`, `unsetenv`, `exit`, ...)
- [ ] Parsing avancé et traitement syntaxique
- [ ] Mode interactif avec prompt
- [ ] Gestion des erreurs et des signaux
- [x] Système de test unitaire

## Compilation

Pour compiler le shell, il suffit d'utiliser `make` à la racine du projet :

```bash
make
```

## Usage

### Lancement normal

```bash
./42sh
```

Cela lance le shell en mode interactif. Vous pouvez alors exécuter des commandes comme dans un terminal classique.

### Lancement en mode debug

```bash
make debug
./42sh
```

Le mode debug compile le projet avec les symboles de debug pour une utilisation avec `gdb` ou tout autre débogueur.

### Exécution des tests unitaires

```bash
make tests-run
```

Cette commande lance l'ensemble des tests automatisés présents dans le projet. Les tests sont basés sur la librairie [Criterion](https://criterion.readthedocs.io).

### Nettoyage complet

```bash
make fclean
```

Supprime tous les fichiers objets, les exécutables, et les fichiers générés par la compilation.

## Structure du projet

```
42sh/
├── .github/workflows   # Github actions
├── include/            # Fichiers headers
├── lib/                # Librairies éventuelles
├── src/                # Code source du shell
├── tests/              # Tests unitaires
├── .gitignore          # Fichiers ignorés
├── Makefile            # Script de compilation
└── README.md
```

## Auteurs

Projet réalisé par [@Akinator31](https://github.com/Akinator31), [@Nogo4](https://github.com/Nogo4), [@Tictacgame](https://github.com/tictacgame) et [@Arkcadia](https://github.com/Arkcadia), de la promotion Epitech 2029.
