/**
 * pp3_test_ngraph_dijkstra.cpp
 * =============================
 * Principal Program 3:
 *   – Create graphs and subgraphs with NGraph::tGraph
 *   – Test operations between graphs (+, -, *)
 *   – Implement and test Dijkstra's algorithm on NGraph::Graph
 */

#include <iostream>
#include <fstream>
#include <map>
#include <limits>
#include <queue>
#include <functional>
#include "ngraph.h"

using namespace NGraph;

// ─────────────────────────────────────────────────────────────────────────────
// Dijkstra's algorithm on NGraph::Graph (unsigned int vertices)
// ─────────────────────────────────────────────────────────────────────────────
using WeightMap = std::map<Graph::edge, double>;

std::map<unsigned int, double> dijkstra(const Graph &G,
                                         unsigned int src,
                                         const WeightMap &W = {})
{
    using pq_t = std::pair<double, unsigned int>;
    const double INF = std::numeric_limits<double>::infinity();

    std::map<unsigned int, double> dist;
    for (Graph::const_iterator p = G.begin(); p != G.end(); p++)
        dist[Graph::node(p)] = INF;
    dist[src] = 0.0;

    std::priority_queue<pq_t, std::vector<pq_t>, std::greater<pq_t>> pq;
    pq.push({0.0, src});

    while (!pq.empty())
    {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        const Graph::vertex_set &out = G.out_neighbors(u);
        for (unsigned int v : out)
        {
            double w = 1.0;
            auto key = std::make_pair(u, v);
            if (W.count(key)) w = W.at(key);
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// ─────────────────────────────────────────────────────────────────────────────
int main()
{
    std::cout << "===========================================\n";
    std::cout << "  PP3 - NGraph operations + Dijkstra's algorithm   \n";
    std::cout << "===========================================\n\n";

    // -- Build graph G1 ----------------------------------------
    Graph G1;
    G1.insert_edge(1u, 2u); G1.insert_edge(1u, 3u);
    G1.insert_edge(2u, 4u); G1.insert_edge(3u, 4u);
    G1.insert_edge(4u, 5u);
    std::cout << "-- G1 -------------------------------------------\n";
    G1.print();

    // -- Build graph G2 ----------------------------------------
    Graph G2;
    G2.insert_edge(3u, 4u); G2.insert_edge(4u, 5u);
    G2.insert_edge(5u, 6u);
    std::cout << "\n-- G2 -------------------------------------------\n";
    G2.print();

    // -- Union ------------------------------------------------
    Graph GU = G1 + G2;
    std::cout << "\n-- G1 U G2 ----------------------------------------\n";
    GU.print();

    // -- Intersection -----------------------------------------
    Graph GI = G1 * G2;
    std::cout << "\n-- G1 ^ G2 ----------------------------------------\n";
    GI.print();

    // -- Difference -------------------------------------------
    Graph GD = G1 - G2;
    std::cout << "\n-- G1 \\ G2 ----------------------------------------\n";
    GD.print();

    // -- SubGraph induced by {2,3,4} ------------------------
    Graph::vertex_set sub_verts = {2u, 3u, 4u};
    Graph GSub = G1.subgraph(sub_verts);
    std::cout << "\n-- SubGraph G1[{2,3,4}] -------------------------\n";
    GSub.print();

    // -- Dijkstra on GU from vertex 1 -------------------------
    WeightMap W;
    W[{1u,2u}]=1.0; W[{1u,3u}]=4.0; W[{2u,4u}]=2.0;
    W[{3u,4u}]=1.0; W[{4u,5u}]=3.0; W[{5u,6u}]=1.0;
    W[{3u,4u}]=1.0; // shared edge

    auto dist = dijkstra(GU, 1u, W);
    std::cout << "\n-- Dijkstra from vertex 1 (G1 U G2 with weights) -------\n";
    for (auto &[v, d] : dist)
    {
        if (d == std::numeric_limits<double>::infinity())
            std::cout << "  dist[1 -> " << v << "] = INF\n";
        else
            std::cout << "  dist[1 -> " << v << "] = " << d << "\n";
    }

    // ── Read Gp adjacency list from file and run Dijkstra ────
    std::cout << "\n-- Gp adjacency list from file (if present) ----------\n";
    std::ifstream f("../../outputs/Exercise1_Python/Gp_adjacency_list.txt");
    if (f)
    {
        Graph Gp;
        std::string line;
        while (std::getline(f, line))
        {
            if (line.empty()) continue;
            // Format: "v: n1 n2 n3"
            std::size_t colon = line.find(':');
            if (colon == std::string::npos) continue;
            unsigned int u = std::stoul(line.substr(0, colon));
            std::istringstream iss(line.substr(colon + 1));
            unsigned int w;
            Gp.insert_vertex(u);
            while (iss >> w) Gp.insert_edge(u, w);
        }
        std::cout << "  Gp loaded: " << Gp.num_vertices() << " vertices, "
                  << Gp.num_edges() << " edges\n";
        auto dp = dijkstra(Gp, 1u);
        std::cout << "  Dijkstra from 1:\n";
        for (auto &[v,d] : dp)
            std::cout << "    dist[1->" << v << "] = " << d << "\n";
    }
    else
        std::cout << "  (file not found - skipping)\n";

    return 0;
}
