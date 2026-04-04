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
  6. MPI communication-ring (mpi4py)
"""

import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
import os
from pathlib import Path

# Setup output directory
OUTPUT_DIR = Path(__file__).parent.parent.parent / "outputs" / "Exercise1_Python"
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

# ─────────────────────────────────────────────────────────────
# 1. CYCLE DETECTION  (directed graph)
# ─────────────────────────────────────────────────────────────

def is_cyclic(G: nx.DiGraph) -> bool:
    """Return True if directed graph G contains a cycle (DFS coloring)."""
    WHITE, GRAY, BLACK = 0, 1, 2
    color = {v: WHITE for v in G.nodes()}

    def dfs(u):
        color[u] = GRAY
        for v in G.successors(u):
            if color[v] == GRAY:      # back-edge → cycle
                return True
            if color[v] == WHITE and dfs(v):
                return True
        color[u] = BLACK
        return False

    return any(dfs(u) for u in G.nodes() if color[u] == 0)


# ─── Tests ───────────────────────────────────────────────────
print("=" * 55)
print("1. CYCLE DETECTION")
G_acyclic = nx.DiGraph([(1, 2), (2, 3), (3, 4)])
G_cyclic  = nx.DiGraph([(1, 2), (2, 3), (3, 1)])
print(f"  Acyclic graph → is_cyclic = {is_cyclic(G_acyclic)}")  # False
print(f"  Cyclic  graph → is_cyclic = {is_cyclic(G_cyclic)}")   # True


# ─────────────────────────────────────────────────────────────
# 2. BIPARTITE / EMPTY / COMPLETE  (undirected graph H)
# ─────────────────────────────────────────────────────────────

def is_bipartite_check(H: nx.Graph) -> bool:
    """2-colour BFS; returns True when H is bipartite."""
    colour = {}
    for start in H.nodes():
        if start in colour:
            continue
        queue = [start]
        colour[start] = 0
        while queue:
            u = queue.pop(0)
            for v in H.neighbors(u):
                if v not in colour:
                    colour[v] = 1 - colour[u]
                    queue.append(v)
                elif colour[v] == colour[u]:
                    return False
    return True


def is_empty_graph(H: nx.Graph) -> bool:
    """Empty graph ⟺ no edges at all."""
    return H.number_of_edges() == 0


def is_complete_graph(H: nx.Graph) -> bool:
    """Complete graph ⟺ every pair of distinct vertices is connected."""
    n = H.number_of_nodes()
    return H.number_of_edges() == n * (n - 1) // 2


# ─── Tests ───────────────────────────────────────────────────
print("\n2. BIPARTITE / EMPTY / COMPLETE")
H_bipartite = nx.Graph([(1, 3), (1, 4), (2, 3), (2, 4)])
H_empty     = nx.Graph(); H_empty.add_nodes_from([1, 2, 3])
H_complete  = nx.complete_graph(5)
H_cycle4    = nx.cycle_graph(4)   # C4 – bipartite
H_cycle5    = nx.cycle_graph(5)   # C5 – not bipartite

print(f"  Bipartite K_{{2,2}} → {is_bipartite_check(H_bipartite)}")   # True
print(f"  Empty (3 nodes)   → {is_empty_graph(H_empty)}")             # True
print(f"  Complete K5       → {is_complete_graph(H_complete)}")        # True
print(f"  C4 bipartite      → {is_bipartite_check(H_cycle4)}")         # True
print(f"  C5 bipartite      → {is_bipartite_check(H_cycle5)}")         # False


# ─────────────────────────────────────────────────────────────
# 3. BINARY TREE OF SIZE n  +  PLOT  +  NODE SWAP
# ─────────────────────────────────────────────────────────────

def build_tree(n: int) -> nx.DiGraph:
    """
    Build a complete binary tree whose nodes are labelled 1..n.
    Node i has children 2i and 2i+1 (standard heap indexing).
    """
    T = nx.DiGraph()
    T.add_nodes_from(range(1, n + 1))
    for i in range(1, n + 1):
        left, right = 2 * i, 2 * i + 1
        if left  <= n: T.add_edge(i, left)
        if right <= n: T.add_edge(i, right)
    return T


def tree_layout(T: nx.DiGraph) -> dict:
    """Top-down hierarchical layout for a rooted binary tree."""
    pos = {}
    root = 1
    def _set_pos(v, depth, left, right):
        mid = (left + right) / 2
        pos[v] = (mid, -depth)
        children = list(T.successors(v))
        if len(children) == 2:
            _set_pos(children[0], depth + 1, left,       mid)
            _set_pos(children[1], depth + 1, mid, right)
        elif len(children) == 1:
            _set_pos(children[0], depth + 1, left, right)
    _set_pos(root, 0, 0, 2 ** int(np.log2(len(T)) + 1))
    return pos


def plot_all_trees(n: int):
    """Generate 6 subplots showing the same tree for n=4 (or n)."""
    T = build_tree(n)
    pos = tree_layout(T)
    fig, axes = plt.subplots(2, 3, figsize=(14, 7))
    fig.suptitle(f"Binary tree T(n={n}) – 6 views", fontsize=14)
    for ax in axes.flat:
        nx.draw(T, pos, ax=ax, with_labels=True,
                node_color="skyblue", node_size=600,
                arrows=True, font_size=10)
    plt.tight_layout()
    plt.savefig(OUTPUT_DIR / "tree_6plots.png", dpi=100)
    plt.close()
    print(f"  Saved tree_6plots.png  (n={n})")


def swap_nodes(T: nx.DiGraph, u, v) -> nx.DiGraph:
    """
    Interchange labels u and v everywhere in T.
    Returns a new graph with relabelled nodes.
    """
    mapping = {u: v, v: u}
    return nx.relabel_nodes(T, mapping)


# ─── Tests ───────────────────────────────────────────────────
print("\n3. BINARY TREE")
T4 = build_tree(4)
print(f"  T(4) edges: {list(T4.edges())}")
plot_all_trees(4)
plot_all_trees(10)

T4_swapped = swap_nodes(T4, 2, 4)
print(f"  After swap(2,4): edges = {sorted(T4_swapped.edges())}")

# Plot before/after swap
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 4))
fig.suptitle("Node swap: T(4) before and after swap(2, 4)")
pos4 = tree_layout(T4)
pos4s = tree_layout(T4_swapped)
nx.draw(T4,        pos4,  ax=ax1, with_labels=True, node_color="lightgreen",
        node_size=700, arrows=True)
ax1.set_title("Original")
nx.draw(T4_swapped, pos4s, ax=ax2, with_labels=True, node_color="lightsalmon",
        node_size=700, arrows=True)
ax2.set_title("After swap(2, 4)")
plt.tight_layout()
plt.savefig(OUTPUT_DIR / "tree_swap.png", dpi=100)
plt.close()
print("  Saved tree_swap.png")


# ─────────────────────────────────────────────────────────────
# 4. CIRCULAR PLOT  – ring graph G (p0..p8)
# ─────────────────────────────────────────────────────────────

print("\n4. CIRCULAR RING GRAPH (p0..p8)")
nodes_ring = [f"p{i}" for i in range(9)]
edges_ring = [(f"p{i}", f"p{(i+1) % 9}") for i in range(9)]
G_ring = nx.DiGraph()
G_ring.add_nodes_from(nodes_ring)
G_ring.add_edges_from(edges_ring)

pos_circ = nx.circular_layout(G_ring)
plt.figure(figsize=(6, 6))
nx.draw_circular(G_ring, with_labels=True, labels={n: n for n in G_ring.nodes()},
                 node_color="gold", node_size=700,
                 arrows=True, font_size=11, font_weight="bold")
plt.title("Ring graph G (circular layout)")
plt.tight_layout()
plt.savefig(OUTPUT_DIR / "ring_graph.png", dpi=100)
plt.close()
print("  Saved ring_graph.png")


# ─────────────────────────────────────────────────────────────
# 5. PAIR-GRAPH  Gp  of order n
# ─────────────────────────────────────────────────────────────
#
#  Pattern: Cross – NoCross – Cross – NoCross – … – Cross
#  A "cross" vertex at position k connects to k+1 (chain edge)
#  AND to the next cross vertex (skip edge).
#  A "no-cross" vertex only connects to the next vertex in the chain.
#
#  Vertices 1..n; cross positions: 1, 3, 5, … (1-indexed odd positions)
#  Each cross vertex i also adds edge i → i+2 (skip to next cross).
# ─────────────────────────────────────────────────────────────

def build_pair_graph(n: int) -> nx.Graph:
    """Build Gp: chain 1-2-3-…-n plus skip-edges between consecutive crosses."""
    Gp = nx.Graph()
    Gp.add_nodes_from(range(1, n + 1))
    for i in range(1, n):
        Gp.add_edge(i, i + 1)           # chain edge
    # cross vertices are at odd positions 1, 3, 5, …
    for i in range(1, n - 1, 2):        # skip edge from each cross
        Gp.add_edge(i, i + 2)
    return Gp


def adjacency_matrix(Gp: nx.Graph) -> np.ndarray:
    return nx.to_numpy_array(Gp, nodelist=sorted(Gp.nodes()), dtype=int)


def incidence_matrix(Gp: nx.Graph) -> np.ndarray:
    nodes = sorted(Gp.nodes())
    edges = list(Gp.edges())
    n, m  = len(nodes), len(edges)
    idx   = {v: i for i, v in enumerate(nodes)}
    I     = np.zeros((n, m), dtype=int)
    for j, (u, v) in enumerate(edges):
        I[idx[u], j] = 1
        I[idx[v], j] = 1
    return I


def adjacency_list(Gp: nx.Graph) -> dict:
    return {v: sorted(Gp.neighbors(v)) for v in sorted(Gp.nodes())}


# ─── Tests ───────────────────────────────────────────────────
print("\n5. PAIR-GRAPH Gp")
n_gp = 10
Gp   = build_pair_graph(n_gp)
A    = adjacency_matrix(Gp)
I_mat= incidence_matrix(Gp)
L    = adjacency_list(Gp)

print(f"  n={n_gp}  |V|={Gp.number_of_nodes()}  |E|={Gp.number_of_edges()}")
print("  Adjacency Matrix A:\n", A)
print(f"  Incidence Matrix I ({I_mat.shape[0]}x{I_mat.shape[1]}):\n", I_mat)
print("  Adjacency List L:")
for v, nbrs in L.items():
    print(f"    {v}: {nbrs}")

# Save A, I, L as text files for the C++ reader
np.savetxt(OUTPUT_DIR / "Gp_adjacency_matrix.txt",  A,     fmt="%d")
np.savetxt(OUTPUT_DIR / "Gp_incidence_matrix.txt",  I_mat, fmt="%d")
with open(OUTPUT_DIR / "Gp_adjacency_list.txt", "w") as f:
    for v, nbrs in L.items():
        f.write(f"{v}: {' '.join(map(str, nbrs))}\n")
print("  Saved Gp_adjacency_matrix.txt / Gp_incidence_matrix.txt / Gp_adjacency_list.txt")

# Plot Gp
pos_gp = {i: (i, 0) for i in range(1, n_gp + 1)}
cross_nodes = list(range(1, n_gp + 1, 2))
other_nodes = [v for v in Gp.nodes() if v not in cross_nodes]
plt.figure(figsize=(12, 3))
nx.draw_networkx_nodes(Gp, pos_gp, nodelist=cross_nodes, node_color="tomato",
                       node_size=700, label="Cross")
nx.draw_networkx_nodes(Gp, pos_gp, nodelist=other_nodes, node_color="steelblue",
                       node_size=700, label="No-Cross")
nx.draw_networkx_edges(Gp, pos_gp, arrows=False)
nx.draw_networkx_labels(Gp, pos_gp, font_size=10)
plt.legend()
plt.title(f"Pair-graph Gp (n={n_gp})")
plt.axis("off")
plt.tight_layout()
plt.savefig(OUTPUT_DIR / "pair_graph.png", dpi=100)
plt.close()
print("  Saved pair_graph.png")


# ─────────────────────────────────────────────────────────────
# 6. MPI COMMUNICATION RING  (mpi4py)
# ─────────────────────────────────────────────────────────────
# NOTE: This section is saved as a separate file `mpi_ring.py`
#       because it must be launched with  mpirun -n <N> python mpi_ring.py
# ─────────────────────────────────────────────────────────────

print(f"\nAll exercises completed.  Output files saved to:")
print(f"  {OUTPUT_DIR}")
for fname in ["tree_6plots.png", "tree_swap.png", "ring_graph.png",
              "pair_graph.png",
              "Gp_adjacency_matrix.txt",
              "Gp_incidence_matrix.txt",
              "Gp_adjacency_list.txt"]:
    print(f"  • {fname}")
