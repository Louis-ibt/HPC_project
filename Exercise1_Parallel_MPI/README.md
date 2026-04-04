# Exercise 2 - Parallel Computing with MPI

## Objectifs
Implémentation d'**algorithmes MPI** pour le calcul parallèle avec une analyse d'**efficacité**.

## Structure

### 📁 1_basic_mpi/
**Exercice 1 MPI - Programme basique**
- Chaque processus p (1 ≤ p ≤ n) imprime:
  - Son **numéro** (rank r)
  - S'il est **pair ou impair**

### 📁 2_communication_deadlock/
**Exercice 2 MPI - Correction de deadlock**
- Processus 0 envoie valeur 100 → processus valeur
- Processus 1 envoie valeur 111 → processus 0
- **Identifier et corriger 2 erreurs** liées aux deadlock

### 📁 3_communication_ring/
**Exercice 3 MPI - Anneau de communication**
- Implémentation avec **mpi4py**
- Processus r reçoit 1000+(r-1) du processus r-1 (1 ≤ r ≤ n-1)
- Processus 0 reçoit 1000+(n-1) du processus n-1

Fichier: `mpi_ring.py`

### 📁 4_pair_graph/
**Graphe de paires Gp**
- Stockage et visualisation du **graphe pair** Gp d'ordre n
- Calcul mathématique des matrices:
  - **Adjacency Matrix (A)**
  - **Incidence Matrix (I)**
  - **Adjacency Lists (L)**
- Lire les valeurs en C++ avec Class Matrix/Vector

Fichiers:
- `Gp_adjacency_matrix.txt`
- `Gp_adjacency_list.txt`
- `Gp_incidence_matrix.txt`

---

## ⚙️ Exécution des Exercices MPI

Pour chaque exercice, suivez ce protocole:

```bash
# Charger les modules de compilation
module load <compiler> <mpi>

# Exécuter avec nombre croissant de processus
mpirun -np 1 python exercise.py
mpirun -np 2 python exercise.py
mpirun -np 4 python exercise.py
mpirun -np 8 python exercise.py
...

# Analyser l'efficacité
# Réserver cores = max(processus MPI utilisés)
```

Pour les exercices 4, 5, 6 (si applicables):
- Exécuter avec **plusieurs jeux de données**
- Tracer les **courbes d'efficacité** vs nombre de processus

---

## 📝 Checklist

- [ ] Exercice 1: Programme basique MPI
- [ ] Exercice 2: Corriger deadlock
- [ ] Exercice 3: Anneau de communication (mpi4py)
- [ ] Exercice 4: Graphe pair Gp
- [ ] Calculer matrices A, I, L
- [ ] Créer visualisation graphe pair
- [ ] Tests d'efficacité MPI
- [ ] Analyser courbes d'efficacité

