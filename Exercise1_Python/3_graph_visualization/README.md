# 📁 Graph Visualization

## Objectif
Visualiser des graphes avec **layouts circulaires** dans NetworkX.

## À Faire

### Plot Circulaire
Créer une visualisation circulaire pour un graphe G avec 8 nœuds (p0 à p7):

```python
import networkx as nx
import matplotlib.pyplot as plt

def circular_plot_graph():
    """
    Graphe G:
    • p7  • p8   • p0
    • p1  • p2   • p3
    • p4  • p5   • p6
    
    Afficher en arrangement circulaire
    """
    pass
```

## Configuration du Graphe
- **Nœuds**: p0, p1, p2, ..., p7 (8 nœuds)
- **Disposition**: Circulaire (circular layout)
- **Arêtes**: À définir selon le sujet
- **Annotations**: Afficher les labels des nœuds

## 📝 Fichiers à Créer
- `circular_graph.py` - Plot circulaire principal
- `graph_visualization_utils.py` - Utilitaires
- `test_visualization.py` - Tests

## 📊 Paramètres à Ajuster
- Taille des nœuds
- Couleurs des nœuds/arêtes
- Épaisseur des arêtes
- Taille des labels
- Arrangement circulaire

## ✅ Checklist
- [ ] Créer graphe avec 8 nœuds (p0-p7)
- [ ] Implémenter circular_plot
- [ ] Tester différentes configurations d'arêtes
- [ ] Exporter l'image du graphe
- [ ] Documenter la structure du graphe
