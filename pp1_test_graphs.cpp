/**
 * pp1_test_graphs.cpp
 * ====================
 * Principal Program 1: Test Graph, SubGraph, Tree classes.
 */

#include <iostream>
#include "graph_classes.hpp"

int main()
{
    std::cout << "═══════════════════════════════════════\n";
    std::cout << "  PP1 – Graph / SubGraph / Tree tests  \n";
    std::cout << "═══════════════════════════════════════\n\n";

    // ── 1. Directed Graph ─────────────────────────────────────
    std::cout << "── Directed Graph ──────────────────────\n";
    Graph G(5, true);
    G.add_edge(0, 1); G.add_edge(1, 2); G.add_edge(2, 3);
    G.add_edge(3, 4); G.add_edge(4, 2);  // creates a cycle
    G.print();
    std::cout << "  is_cyclic   = " << std::boolalpha << G.is_cyclic()    << "\n";
    std::cout << "  is_bipartite= " << G.is_bipartite() << "\n";
    std::cout << "  is_empty    = " << G.is_empty()     << "\n";
    std::cout << "  is_complete = " << G.is_complete()  << "\n\n";

    // ── 2. Undirected Graph ───────────────────────────────────
    std::cout << "── Undirected Bipartite Graph ──────────\n";
    Graph H(4, false);
    H.add_edge(0, 2); H.add_edge(0, 3);
    H.add_edge(1, 2); H.add_edge(1, 3);
    H.print();
    std::cout << "  is_bipartite= " << H.is_bipartite() << "\n\n";

    // ── 3. SubGraph ───────────────────────────────────────────
    std::cout << "── SubGraph {0,1,2} of G ───────────────\n";
    SubGraph SG(G, {0, 1, 2});
    SG.print();
    std::cout << "\n";

    // ── 4. Tree ───────────────────────────────────────────────
    std::cout << "── Tree n=7 ────────────────────────────\n";
    Tree T(7);
    T.print();
    std::cout << "\n  After swap_nodes(2, 4):\n";
    T.swap_nodes(2, 4);
    T.print();

    return 0;
}
