# 📁 Basic MPI - Exercise 1

## Exercice 1 MPI
**Objectif**: Chaque processus affiche son rang et sa parité.

## À Faire

```python
"""
Pour n processus (1 ≤ p ≤ n):
- Chaque processus p affiche:
  1. Son numéro de rang (r)
  2. S'il est pair ou impair
  
Exemple avec 4 processus:
  Processus 0 (pair)
  Processus 1 (impair)
  Processus 2 (pair)
  Processus 3 (impair)
"""
```

## 📝 Fichiers à Créer
- `mpi_exercise1.py` - Programme principal avec mpi4py

## 🔧 Compilation & Exécution

```bash
# Charger les modules
module load python/mpi4py
module load compiler/gnu
module load mpi/openmpi

# Exécuter
mpirun -np 1 python mpi_exercise1.py
mpirun -np 2 python mpi_exercise1.py
mpirun -np 4 python mpi_exercise1.py
mpirun -np 8 python mpi_exercise1.py

# Analyser l'efficacité
# temps_1p / (np * temps_np)
```

## ✅ Checklist
- [ ] Implémenter initialisation MPI
- [ ] Get rank et number of processes
- [ ] Afficher rank et parité
- [ ] Tester avec np=1,2,4,8,16
- [ ] Calculer efficacité MPI
- [ ] Documenter résultats

