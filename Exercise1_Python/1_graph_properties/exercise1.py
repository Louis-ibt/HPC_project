"""
Exercise 1 – Graph Algorithms in Python
========================================
Topics covered:
  1. Cycle detection in a directed graph (DFS-based)
  2. Bipartite / Empty / Complete checks for an undirected graph
  3. Binary-tree structure of size n, plotting and node-swap
  4. Circular plot of a ring graph G (p0..p8)
  5. Pair-graph Gp: storage, plot, adjacency matrix A,
     incidence matrix I, adjacency list L
  6. MPI communication-ring (mpi4py) -> see mpi_ring.py
"""

import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
from collections import defaultdict, deque
from pathlib import Path

OUTPUT_DIR = Path(__file__).parent.parent.parent / "outputs" / "Exercise1_Python"
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

# =============================================================
# 1. CYCLE DETECTION
# =============================================================
def is_cyclic(G: nx.DiGraph) -> bool:
    WHITE, GRAY, BLACK = 0, 1, 2
    color = {v: WHITE for v in G.nodes()}
    def dfs(u):
        color[u] = GRAY
        for v in G.successors(u):
            if color[v] == GRAY: return True
            if color[v] == WHITE and dfs(v): return True
        color[u] = BLACK
        return False
    return any(dfs(u) for u in G.nodes() if color[u] == 0)

print("=" * 55)
print("1. CYCLE DETECTION")
print(f"  Acyclic → {is_cyclic(nx.DiGraph([(1,2),(2,3),(3,4)]))}")   # False
print(f"  Cyclic  → {is_cyclic(nx.DiGraph([(1,2),(2,3),(3,1)]))}")   # True

# =============================================================
# 2. BIPARTITE / EMPTY / COMPLETE
# =============================================================
def is_bipartite_check(H):
    colour = {}
    for start in H.nodes():
        if start in colour: continue
        queue = [start]; colour[start] = 0
        while queue:
            u = queue.pop(0)
            for v in H.neighbors(u):
                if v not in colour: colour[v] = 1-colour[u]; queue.append(v)
                elif colour[v] == colour[u]: return False
    return True

def is_empty_graph(H):    return H.number_of_edges() == 0
def is_complete_graph(H): n=H.number_of_nodes(); return H.number_of_edges()==n*(n-1)//2

print("\n2. BIPARTITE / EMPTY / COMPLETE")
print(f"  K_2,2 bipartite → {is_bipartite_check(nx.Graph([(1,3),(1,4),(2,3),(2,4)]))}")
H_empty = nx.Graph(); H_empty.add_nodes_from([1,2,3])
print(f"  Empty (3 nodes) → {is_empty_graph(H_empty)}")
print(f"  K5 complete     → {is_complete_graph(nx.complete_graph(5))}")
print(f"  C4 bipartite    → {is_bipartite_check(nx.cycle_graph(4))}")
print(f"  C5 bipartite    → {is_bipartite_check(nx.cycle_graph(5))}")

# =============================================================
# 3. BINARY TREE + ALL LABELED TREES PLOT + NODE SWAP
# =============================================================
def build_tree(n):
    T = nx.DiGraph(); T.add_nodes_from(range(1, n+1))
    for i in range(1, n+1):
        if 2*i   <= n: T.add_edge(i, 2*i)
        if 2*i+1 <= n: T.add_edge(i, 2*i+1)
    return T

def all_labeled_trees(n, max_trees=None):
    results = []
    def build(k, current):
        if max_trees and len(results) >= max_trees: return
        if k > n: results.append(dict(current)); return
        for parent in range(1, k):
            if max_trees and len(results) >= max_trees: return
            current[k] = parent; build(k+1, current); del current[k]
    build(2, {}); return results

def build_tree_from_parents(parents, n):
    T = nx.DiGraph(); T.add_nodes_from(range(1, n+1))
    for child, parent in parents.items(): T.add_edge(parent, child)
    return T

def bfs_layout(T, root=1):
    levels = defaultdict(list); visited = {root}; queue = deque([(root, 0)])
    while queue:
        node, depth = queue.popleft(); levels[depth].append(node)
        for child in T.successors(node):
            if child not in visited: visited.add(child); queue.append((child, depth+1))
    pos = {}
    for depth, nodes in levels.items():
        for i, node in enumerate(nodes): pos[node] = (i - len(nodes)/2.0, -depth)
    return pos

def plot_all_labeled_trees(n, max_show=6):
    trees = all_labeled_trees(n, max_trees=max_show)
    fig, axes = plt.subplots(1, len(trees), figsize=(2.5*len(trees), 4))
    if len(trees) == 1: axes = [axes]
    fig.suptitle(f"All labeled rooted trees  n={n}  ({len(trees)} shown)", fontsize=12)
    for ax, parents in zip(axes, trees):
        T = build_tree_from_parents(parents, n); pos = bfs_layout(T)
        nx.draw(T, pos, ax=ax, with_labels=True, node_color="white",
                edgecolors="black", node_size=500, arrows=True, arrowstyle="->", font_size=11)
        ax.axis("off")
    plt.tight_layout()
    plt.savefig(OUTPUT_DIR / f"tree_all_labeled_n{n}.png", dpi=120, bbox_inches="tight")
    plt.close(); print(f"  Saved tree_all_labeled_n{n}.png")

def swap_nodes(T, u, v):
    return nx.relabel_nodes(T, {u: v, v: u})

print("\n3. BINARY TREE")
T4 = build_tree(4)
print(f"  T(4) edges: {list(T4.edges())}")
plot_all_labeled_trees(4)    # all 6 labeled trees of size 4
plot_all_labeled_trees(10)   # first 6 of many trees of size 10

T4_swapped = swap_nodes(T4, 2, 4)
print(f"  After swap(2,4): {sorted(T4_swapped.edges())}")

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 4))
fig.suptitle("Node swap: T(4) before and after swap(2,4)")
nx.draw(T4,         bfs_layout(T4),         ax=ax1, with_labels=True,
        node_color="lightgreen",  node_size=700, arrows=True); ax1.set_title("Original")
nx.draw(T4_swapped, bfs_layout(T4_swapped), ax=ax2, with_labels=True,
        node_color="lightsalmon", node_size=700, arrows=True); ax2.set_title("After swap(2,4)")
plt.tight_layout()
plt.savefig(OUTPUT_DIR / "tree_swap.png", dpi=100); plt.close()
print("  Saved tree_swap.png")

# =============================================================
# 4. CIRCULAR RING GRAPH (p0..p8)
# =============================================================
print("\n4. CIRCULAR RING GRAPH")
G_ring = nx.DiGraph()
G_ring.add_nodes_from([f"p{i}" for i in range(9)])
G_ring.add_edges_from([(f"p{i}", f"p{(i+1)%9}") for i in range(9)])
plt.figure(figsize=(6, 6))
nx.draw_circular(G_ring, with_labels=True, node_color="gold",
                 node_size=700, arrows=True, font_size=11, font_weight="bold")
plt.title("Ring graph G (circular layout)")
plt.tight_layout()
plt.savefig(OUTPUT_DIR / "ring_graph.png", dpi=100); plt.close()
print("  Saved ring_graph.png")

# =============================================================
# 5. PAIR-GRAPH Gp
#
# Two rows: Top row = odd nodes (1,3,5,...,n-1)
#           Bottom row = even nodes (2,4,6,...,n)
# Column k holds nodes (2k-1, 2k).
# Odd columns (k=1,3,5,...) = Cross: vertical + 2 diagonals forming X
# Even columns (k=2,4,6,...) = No-Cross: vertical only
# Horizontal chain connects adjacent columns (top-to-top, bottom-to-bottom)
# =============================================================

def build_pair_graph(n: int) -> nx.Graph:
    assert n % 2 == 0, "n must be even"
    Gp = nx.Graph(); Gp.add_nodes_from(range(1, n+1))
    cols = n // 2
    for k in range(1, cols):
        tl, bl, tr, br = 2*k-1, 2*k, 2*k+1, 2*k+2
        Gp.add_edge(tl, tr); Gp.add_edge(bl, br)   # horizontal chain
        if k % 2 == 1:                               # Cross: add diagonals
            Gp.add_edge(tl, br); Gp.add_edge(bl, tr)
    for k in range(1, cols+1):
        Gp.add_edge(2*k-1, 2*k)                     # vertical per column
    return Gp

def adjacency_matrix(Gp):
    return nx.to_numpy_array(Gp, nodelist=sorted(Gp.nodes()), dtype=int)

def incidence_matrix(Gp):
    nodes = sorted(Gp.nodes()); edges = list(Gp.edges())
    idx = {v: i for i, v in enumerate(nodes)}
    I = np.zeros((len(nodes), len(edges)), dtype=int)
    for j, (u, v) in enumerate(edges): I[idx[u],j]=1; I[idx[v],j]=1
    return I

def adjacency_list(Gp):
    return {v: sorted(Gp.neighbors(v)) for v in sorted(Gp.nodes())}

print("\n5. PAIR-GRAPH Gp")
n_gp = 12
Gp = build_pair_graph(n_gp)
A = adjacency_matrix(Gp); I_mat = incidence_matrix(Gp); L = adjacency_list(Gp)
print(f"  n={n_gp}  |V|={Gp.number_of_nodes()}  |E|={Gp.number_of_edges()}")
print("  Adjacency Matrix A:\n", A)
print(f"  Incidence Matrix I ({I_mat.shape[0]}x{I_mat.shape[1]}):\n", I_mat)
print("  Adjacency List L:")
for v, nbrs in L.items(): print(f"    {v}: {nbrs}")

np.savetxt(OUTPUT_DIR / "Gp_adjacency_matrix.txt", A,     fmt="%d")
np.savetxt(OUTPUT_DIR / "Gp_incidence_matrix.txt", I_mat, fmt="%d")
with open(OUTPUT_DIR / "Gp_adjacency_list.txt", "w") as f:
    for v, nbrs in L.items(): f.write(f"{v}: {' '.join(map(str,nbrs))}\n")
print("  Saved Gp_adjacency_matrix.txt / Gp_incidence_matrix.txt / Gp_adjacency_list.txt")

# Plot Gp
pos_gp = {}
for k in range(1, n_gp//2 + 1):
    pos_gp[2*k-1] = (k, 1)   # top row
    pos_gp[2*k]   = (k, 0)   # bottom row
plt.figure(figsize=(max(8, n_gp), 3))
nx.draw_networkx_nodes(Gp, pos_gp, node_color="white", edgecolors="black", node_size=700)
nx.draw_networkx_edges(Gp, pos_gp)
nx.draw_networkx_labels(Gp, pos_gp, font_size=10, font_weight="bold")
# Labels centered under each pair of adjacent columns (the X or no-X region)
cols = n_gp // 2
for k in range(1, cols):   # between column k and column k+1
    x_center = k + 0.5
    label = "Cross" if k % 2 == 1 else "No Cross"
    plt.text(x_center, -0.3, label, ha="center", fontsize=8)
plt.axis("off"); plt.title(f"Pair graph Gp  (n={n_gp})")
plt.tight_layout()
plt.savefig(OUTPUT_DIR / "pair_graph.png", dpi=120, bbox_inches="tight")
plt.close(); print("  Saved pair_graph.png")

print("\nDone. Run MPI ring with:  mpirun -n <N> python mpi_ring.py")