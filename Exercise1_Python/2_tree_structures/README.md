# 📁 Tree Structures

## Objectif
Construire, visualiser et manipuler des **structures d'arbres** en Python.

## À Faire

### 1️⃣ Construction d'Arbre
```python
def create_tree(n: int) -> Tree:
    """
    Crée un arbre de taille n avec nœuds labelisés 1 à n.
    
    Exemple: n=4
           1
          /|\
         2 3 4
    """
    pass
```

### 2️⃣ Visualisation avec NetworkX
```python
def plot_tree_variations(tree: Tree, n: int):
    """
    Génère 6 plots différents du même arbre:
    - Layout linéaire
    - Layout circulaire  
    - Layout hiérarchique
    - Layout spring-based
    - Layout radial
    - Layout personnalisé
    """
    pass
```

### 3️⃣ Échange de Nœuds
```python
def swap_nodes(tree: Tree, node1: int, node2: int) -> Tree:
    """
    Échange les positions de deux nœuds dans l'arbre.
    Voir Fig. b du sujet pour exemple.
    """
    pass
```

## 📝 Fichiers à Créer
- `tree_builder.py` - Création d'arbres
- `tree_visualization.py` - Plots et visualisations
- `tree_operations.py` - Opérations (swap, etc)
- `test_trees.py` - Tests complets

## ✅ Checklist
- [ ] Implémenter create_tree(n)
- [ ] Tester avec n=4, n=10, n=20
- [ ] Générer 6 visualisations différentes
- [ ] Implémenter échange de nœuds
- [ ] Tester swap sur diverses configurations
- [ ] Exporter images des plots
