# 📁 Graph Properties

## Objectif
Implémenter et tester **3 algorithmes indépendants** pour vérifier les propriétés d'un graphe.

## À Faire

### 1️⃣ Détection de Cycle
```python
def is_cyclic(graph: Graph) -> bool:
    """
    Détermine si le graphe G est cyclique.
    Retourne: True si cyclique, False sinon
    """
    pass
```

### 2️⃣ Propriétés Indépendantes
Implémenter 3 fonctions indépendantes:

```python
def is_bipartite(graph: Graph) -> bool:
    """Vérifier si le graphe est bipartite"""
    pass

def is_empty(graph: Graph) -> bool:
    """Vérifier si le graphe est vide (pas d'arêtes)"""
    pass

def is_complete(graph: Graph) -> bool:
    """Vérifier si le graphe est complet"""
    pass
```

## 📝 Fichiers à Créer
- `exercise1.py` - Implémentations principales
- `test_cycle.py` - Tests de détection de cycle
- `test_bipartite.py` - Tests bipartite
- `test_empty.py` - Tests vide
- `test_complete.py` - Tests complet
- `test_graphs.txt` - Graphes d'exemple (optional)

## ✅ Checklist
- [ ] Implémenter is_cyclic()
- [ ] Implémenter is_bipartite()
- [ ] Implémenter is_empty()
- [ ] Implémenter is_complete()
- [ ] Tester chaque fonction avec 5+ cas de test
- [ ] Valider les algorithmes avec NetworkX si temps
