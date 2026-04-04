/**
 * graph_classes.hpp
 * =================
 * Class Graph   – adjacency-list directed/undirected graph.
 * Class SubGraph – a view of a subset of a Graph's vertices.
 * Class Tree    – a rooted tree built on top of Graph.
 */

#ifndef GRAPH_CLASSES_HPP_
#define GRAPH_CLASSES_HPP_

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <string>

// ─────────────────────────────────────────────────────────────────────────────
// CLASS  Graph
// ─────────────────────────────────────────────────────────────────────────────
class Graph
{
public:
    using vertex   = int;
    using EdgeList = std::vector<std::pair<vertex,vertex>>;

protected:
    int n_;                                      // number of vertices
    std::map<vertex, std::set<vertex>> adj_;     // adjacency list
    bool directed_;

public:
    // ── Constructors ──────────────────────────────────────────
    explicit Graph(int n = 0, bool directed = true)
        : n_(n), directed_(directed)
    {
        for (int i = 0; i < n; i++) adj_[i];    // initialise empty adj lists
    }

    virtual ~Graph() = default;

    // ── Basic info ────────────────────────────────────────────
    int  num_vertices() const { return (int)adj_.size(); }
    int  num_edges()    const
    {
        int cnt = 0;
        for (auto &kv : adj_) cnt += (int)kv.second.size();
        return directed_ ? cnt : cnt / 2;
    }
    bool is_directed()   const { return  directed_; }
    bool is_undirected() const { return !directed_; }

    // ── Mutation ──────────────────────────────────────────────
    void add_vertex(vertex v)             { adj_[v]; n_++; }
    void add_edge(vertex u, vertex v)
    {
        adj_[u].insert(v);
        if (!directed_) adj_[v].insert(u);
    }
    void remove_edge(vertex u, vertex v)
    {
        adj_[u].erase(v);
        if (!directed_) adj_[v].erase(u);
    }

    // ── Queries ───────────────────────────────────────────────
    bool has_vertex(vertex v) const { return adj_.count(v) > 0; }
    bool has_edge  (vertex u, vertex v) const
    {
        auto it = adj_.find(u);
        return it != adj_.end() && it->second.count(v) > 0;
    }
    const std::set<vertex> &neighbors(vertex v) const { return adj_.at(v); }

    // ── All edges as a list ───────────────────────────────────
    EdgeList edge_list() const
    {
        EdgeList el;
        for (auto &kv : adj_)
            for (vertex w : kv.second)
                if (directed_ || kv.first <= w)
                    el.push_back({kv.first, w});
        return el;
    }

    // ── DFS cycle detection (directed) ───────────────────────
    bool is_cyclic() const
    {
        enum Color { WHITE, GRAY, BLACK };
        std::map<vertex, Color> col;
        for (auto &kv : adj_) col[kv.first] = WHITE;

        std::function<bool(vertex)> dfs = [&](vertex u) -> bool
        {
            col[u] = GRAY;
            for (vertex w : adj_.at(u))
            {
                if (col[w] == GRAY)           return true;
                if (col[w] == WHITE && dfs(w)) return true;
            }
            col[u] = BLACK;
            return false;
        };
        for (auto &kv : adj_)
            if (col[kv.first] == WHITE && dfs(kv.first)) return true;
        return false;
    }

    // ── BFS bipartite check ───────────────────────────────────
    bool is_bipartite() const
    {
        std::map<vertex,int> colour;
        for (auto &kv : adj_)
        {
            if (colour.count(kv.first)) continue;
            std::queue<vertex> q;
            q.push(kv.first);
            colour[kv.first] = 0;
            while (!q.empty())
            {
                vertex u = q.front(); q.pop();
                for (vertex w : adj_.at(u))
                {
                    if (!colour.count(w)) { colour[w] = 1 - colour[u]; q.push(w); }
                    else if (colour[w] == colour[u]) return false;
                }
            }
        }
        return true;
    }

    bool is_empty()    const { return num_edges() == 0; }
    bool is_complete() const
    {
        int n = num_vertices();
        int expected = directed_ ? n*(n-1) : n*(n-1)/2;
        return num_edges() == expected;
    }

    // ── Dijkstra shortest paths from source ──────────────────
    std::map<vertex, double> dijkstra(vertex src,
        const std::map<std::pair<vertex,vertex>, double> &weights = {}) const
    {
        using pq_node = std::pair<double, vertex>;
        std::map<vertex, double> dist;
        for (auto &kv : adj_) dist[kv.first] = std::numeric_limits<double>::infinity();
        dist[src] = 0.0;

        std::priority_queue<pq_node, std::vector<pq_node>, std::greater<pq_node>> pq;
        pq.push({0.0, src});

        while (!pq.empty())
        {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (vertex v : adj_.at(u))
            {
                double w = 1.0;   // default unit weight
                auto key = std::make_pair(u, v);
                if (weights.count(key)) w = weights.at(key);
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    // ── Print ─────────────────────────────────────────────────
    virtual void print(std::ostream &os = std::cout) const
    {
        os << (directed_ ? "Directed" : "Undirected")
           << " Graph  |V|=" << num_vertices()
           << "  |E|=" << num_edges() << "\n";
        for (auto &kv : adj_)
        {
            os << "  " << kv.first << " -> { ";
            for (vertex w : kv.second) os << w << " ";
            os << "}\n";
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Graph &G)
    { G.print(os); return os; }
};

// ─────────────────────────────────────────────────────────────────────────────
// CLASS  SubGraph
// ─────────────────────────────────────────────────────────────────────────────
class SubGraph : public Graph
{
private:
    const Graph   &parent_;
    std::set<int>  vertex_subset_;

public:
    SubGraph(const Graph &parent, const std::set<int> &subset)
        : Graph(0, parent.is_directed()), parent_(parent), vertex_subset_(subset)
    {
        // Add only vertices in subset
        for (int v : subset) adj_[v];
        // Add only edges whose both endpoints are in subset
        for (int u : subset)
        {
            if (!parent.has_vertex(u)) continue;
            for (int w : parent.neighbors(u))
                if (subset.count(w)) add_edge(u, w);
        }
    }

    void print(std::ostream &os = std::cout) const override
    {
        os << "SubGraph of parent  |V_sub|=" << num_vertices()
           << "  |E_sub|=" << num_edges() << "\n";
        Graph::print(os);
    }
};

// ─────────────────────────────────────────────────────────────────────────────
// CLASS  Tree  (rooted binary tree – heap indexing)
// ─────────────────────────────────────────────────────────────────────────────
class Tree : public Graph
{
private:
    int root_;

public:
    explicit Tree(int n)
        : Graph(n, true /*directed*/), root_(1)
    {
        // Re-build with 1-based nodes
        adj_.clear();
        for (int i = 1; i <= n; i++) adj_[i];
        for (int i = 1; i <= n; i++)
        {
            int left = 2*i, right = 2*i+1;
            if (left  <= n) add_edge(i, left);
            if (right <= n) add_edge(i, right);
        }
    }

    int root() const { return root_; }

    /** Swap the labels of two nodes (relabels all edges). */
    void swap_nodes(int u, int v)
    {
        if (u == v) return;
        // Collect all edges, rename u↔v
        auto el = edge_list();
        adj_.clear();
        for (int i = 1; i <= n_; i++) adj_[i];
        for (auto &[a, b] : el)
        {
            int na = (a == u ? v : (a == v ? u : a));
            int nb = (b == u ? v : (b == v ? u : b));
            add_edge(na, nb);
        }
    }

    void print(std::ostream &os = std::cout) const override
    {
        os << "Tree  root=" << root_
           << "  |V|=" << num_vertices()
           << "  |E|=" << num_edges() << "\n";
        Graph::print(os);
    }
};

#endif // GRAPH_CLASSES_HPP_
