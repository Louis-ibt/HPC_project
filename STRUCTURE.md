# HPC Project - Structure Organisationnelle

## Overview
Ce projet est organisé en **3 exercices principaux** correspondant au sujet du cours HPC à ESILV.

```
HPC_project/
├── Exercise1_Python/              # Algorithmes de graphes en Python
│   ├── 1_graph_properties/        # Détection de cycle, bipartite, vide, complet
│   ├── 2_tree_structures/         # Structures d'arbres et manipulations
│   └── 3_graph_visualization/     # Visualisation avec NetworkX
│
├── Exercise2_Parallel_MPI/        # Calcul parallèle avec MPI
│   ├── 1_basic_mpi/              # Exercice 1: Programme basique MPI
│   ├── 2_communication_deadlock/  # Exercice 2: Correction deadlock
│   ├── 3_communication_ring/      # Exercice 3: Anneau de communication
│   └── 4_pair_graph/             # Graphe de paires et stockage matrices
│
├── Exercise3_CPP/                 # Implémentation C++ avancée
│   ├── 1_graph_classes/          # Classes Graph, SubGraph, Tree
│   ├── 2_linear_algebra/         # Classes Vector et Matrix
│   ├── 3_dijkstra/               # Algorithme de Dijkstra
│   ├── tests/                    # Programmes de test (pp1, pp2, pp3)
│   └── Makefile                  # Compilation de tous les modules
│
├── Article/                       # Étude scientifique et comprendre Dijkstra
└── README.md                      # Documentation générale
```

---

## 📚 Exercise 1 - Python Graph Algorithms

### 1_graph_properties/
- Détection de **cycle** : fonction booléenne
- Propriétés de graphes : **bipartite**, **vide**, **complet**
- Implémentation et tests en Python
- Fichier: `exercise1.py`

### 2_tree_structures/
- Construction d'arbre de taille n (nœuds 1 à n)
- Visualisation avec NetworkX (6 plots différents)
- Échange de positions entre deux nœuds
- Fonction de plot générale et testable

### 3_graph_visualization/
- Plot circulaire d'un graphe G
- Visualisation du graphe avec 8 nœuds (p0 à p7)

---

## 🔄 Exercise 2 - Parallel Computing with MPI

### 1_basic_mpi/
- **Exercice 1 MPI**: Impression du rang r et parité pour chaque processus (1 ≤ p ≤ n)

### 2_communication_deadlock/
- **Exercice 2 MPI**: Correction de 2 erreurs de deadlock
  - Processus 0 envoie 100 au processus valeur
  - Processus 1 envoie 111 au processus 0

### 3_communication_ring/
- **Exercice 3 MPI**: Anneau de communication circulaire
  - Processus r reçoit 1000+(r-1) du processus r-1 (1 ≤ r ≤ n-1)
  - Processus 0 reçoit 1000+(n-1) du processus n-1
- Utilisation de **mpi4py**
- Fichier: `mpi_ring.py`

### 4_pair_graph/
- Stockage et plot du **graphe de paires Gp** d'ordre n
- Matrices : adjacency, incidence
- Listes : adjacency
- Fichiers de données:
  - `Gp_adjacency_matrix.txt`
  - `Gp_adjacency_list.txt`
  - `Gp_incidence_matrix.txt`

---

## 🔧 Exercise 3 - C++ Graph Classes & Algorithms

### 1_graph_classes/
- Classe **Graph** : Représentation de graphes
- Classe **SubGraph** : Sous-graphes
- Classe **Tree** : Arbres
- Opérations entre graphes
- Fichiers:
  - `graph_classes.hpp`
  - `ngraph.hpp`, `ngraph.h`, `ngraph.cpp`
  - `set_ops.hpp`

### 2_linear_algebra/
- Classe **Vector** : Vecteurs (basés sur Points)
- Classe **Matrix** : Matrices (basées sur Vecteurs)
- Surcharge d'opérateurs: `+`, `=`, `«`
- Fichier: `linear_algebra.hpp`

### 3_dijkstra/
- Implémentation de l'**algorithme de Dijkstra**
- Lecture des matrices/listes en C++
- Applications et tests

### tests/
- **pp1_test_graphs.cpp**: Test des classes Graph, SubGraph, Tree
- **pp2_test_linalg.cpp**: Test des classes Vector et Matrix
- **pp3_test_ngraph_dijkstra.cpp**: Test de Dijkstra

### Makefile
- Compilation de tous les modules
- Support multi-fichiers

---

## 📄 Article/
Étude scientifique : *"Pore-to-Darcy scale permeability upscaling for media with dynamic pore structure using graph theory"*
- Lien: https://www.sciencedirect.com/science/article/pii/S2590197424000260
- Rôle de l'algorithme de Dijkstra dans l'étude

---

## 🚀 Quick Navigation

| Tâche | Localisation |
|-------|-------------|
| Test détection de cycle | `Exercise1_Python/1_graph_properties/` |
| Test propriétés graphes | `Exercise1_Python/1_graph_properties/` |
| Créer et visualiser arbres | `Exercise1_Python/2_tree_structures/` |
| Graphe circulaire | `Exercise1_Python/3_graph_visualization/` |
| MPI basique | `Exercise2_Parallel_MPI/1_basic_mpi/` |
| Corriger deadlock | `Exercise2_Parallel_MPI/2_communication_deadlock/` |
| Anneau MPI | `Exercise2_Parallel_MPI/3_communication_ring/` |
| Graphe de paires | `Exercise2_Parallel_MPI/4_pair_graph/` |
| Classes C++ | `Exercise3_CPP/1_graph_classes/` |
| Vector/Matrix | `Exercise3_CPP/2_linear_algebra/` |
| Dijkstra | `Exercise3_CPP/3_dijkstra/` |
| Compiler tout | `Exercise3_CPP/Makefile` |

