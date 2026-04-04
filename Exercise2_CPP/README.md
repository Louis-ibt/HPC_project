# Exercise 3 - C++ Graph Classes & Linear Algebra

## Objectifs
Implémenter des **classes C++** robustes pour graphes, algèbre linéaire et algorithmes avancés.

## Structure

### 📁 1_graph_classes/
**Classes de graphes en C++**
- Classe **Graph**: Représentation complète de graphe
- Classe **SubGraph**: Opérations sur sous-graphes
- Classe **Tree**: Structures d'arbres
- Opérations entre graphes
- Surcharge d'opérateurs

Fichiers:
- `graph_classes.hpp`
- `ngraph.hpp`, `ngraph.h`, `ngraph.cpp`
- `set_ops.hpp`

### 📁 2_linear_algebra/
**Classes d'algèbre linéaire**
- Classe **Vector**: Vecteurs (basés sur Points)
- Classe **Matrix**: Matrices (basées sur Vecteurs)
- Surcharge d'opérateurs:
  - `+` (addition)
  - `=` (assignation)
  - `«` (insertion/affichage)

Fichier: `linear_algebra.hpp`

### 📁 3_dijkstra/
**Algorithme de Dijkstra**
- Implémentation de Dijkstra sur graphes
- Lecture des matrices/listes depuis fichiers
- Calcul de chemins plus courts

### 📁 tests/
**Programmes de test principaux**
- **pp1_test_graphs.cpp**
  - Test des classes Graph, SubGraph, Tree
  - Opérations entre graphes
  - Méthodes d'accès et modification

- **pp2_test_linalg.cpp**
  - Test des classes Vector et Matrix
  - Surcharge d'opérateurs (+, =, «)
  - Opérations mathématiques

- **pp3_test_ngraph_dijkstra.cpp**
  - Test de l'algorithme de Dijkstra
  - Construction de graphe complexe
  - Vérification d'optimalité des chemins

---

## 🔨 Compilation

Utiliser le **Makefile** à la racine de Exercise3_CPP/:

```bash
cd Exercise3_CPP/
make                 # Compiler tout
make clean          # Nettoyer les fichiers objets
make help           # Afficher les options disponibles
```

---

## 📋 Tâches Principales

### Part 1: Partage du fichier ngraph.hpp
- [ ] Charger `ngraph.hpp`
- [ ] Créer `ngraph.h` (header)
- [ ] Créer `ngraph.cpp` (implémentation)
- [ ] Compiler

### Part 2: Programme de test complet
- [ ] Créer graphe complet
- [ ] Tester opérations graphe/sous-graphe
- [ ] Tester méthodes de graphe
- [ ] Vérifier les résultats

### Part 3: Implémentation Dijkstra
- [ ] Coder l'algorithme
- [ ] Tester sur plusieurs graphes
- [ ] Valider les chemins plus courts
- [ ] Comparer avec résultats connus

---

## 📄 Étude Scientifique

📖 **Fichier**: `../Article/`

Lire et comprendre: *"Pore-to-Darcy scale permeability upscaling for media with dynamic pore structure using graph theory"*

Questions:
- Comment Dijkstra intervient dans l'étude?
- Quels sont les chemins critiques identifiés?
- Comment la théorie des graphes s'applique au problème physique?

---

## 🎯 Checklist

- [ ] Classes Graph, SubGraph, Tree implémentées
- [ ] Classes Vector, Matrix implémentées
- [ ] Surcharge d'opérateurs (+, =, «)
- [ ] Makefile compile sans erreurs
- [ ] pp1: Tests des classes de graphes
- [ ] pp2: Tests de Vector et Matrix
- [ ] pp3: Implémentation et test de Dijkstra
- [ ] Lire et analyser l'article scientifique

