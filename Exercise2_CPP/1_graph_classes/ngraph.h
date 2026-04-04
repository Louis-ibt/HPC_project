/**
 * ngraph.h  –  Header-only declaration extracted from ngraph.hpp
 *
 * This file contains only the class declaration / interface of NGraph::tGraph.
 * The implementation of out-of-line methods is in ngraph.cpp.
 *
 * Original source: ngraph.hpp  (NGraph library by J. Grosh)
 */

#ifndef NGRAPH_H_
#define NGRAPH_H_

#include <iostream>
#include <set>
#include <map>
#include <utility>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "set_ops.hpp"

namespace NGraph
{

template <typename T>
class tGraph
{
public:
    typedef T                                        vertex;
    typedef T                                        value_type;
    typedef std::pair<vertex, vertex>                edge;
    typedef std::set<vertex>                         vertex_set;
    typedef std::set<edge>                           edge_set;
    typedef std::pair<vertex_set, vertex_set>        in_out_edge_sets;
    typedef std::map<vertex, in_out_edge_sets>       adj_graph;

    typedef typename edge_set::iterator             edge_iterator;
    typedef typename edge_set::const_iterator       const_edge_iterator;
    typedef typename vertex_set::iterator           vertex_iterator;
    typedef typename vertex_set::const_iterator     const_vertex_iterator;
    typedef typename vertex_set::iterator           vertex_neighbor_iterator;
    typedef typename vertex_set::const_iterator     vertex_neighbor_const_iterator;

    enum line_type { VERTEX, EDGE, COMMENT, EMPTY };

private:
    adj_graph    G_;
    unsigned int num_edges_;
    bool         undirected_;

public:
    typedef typename adj_graph::iterator       iterator;
    typedef typename adj_graph::const_iterator const_iterator;
    typedef iterator                           node_iterator;
    typedef const_iterator                     const_node_iterator;

    // ── Constructors ──────────────────────────────────────────
    tGraph();
    explicit tGraph(std::istream &s);
    tGraph(const tGraph &B);
    explicit tGraph(const edge_set &E);

    // ── Basic queries ─────────────────────────────────────────
    unsigned int num_vertices() const { return G_.size(); }
    unsigned int num_nodes()    const { return G_.size(); }
    unsigned int num_edges()    const { return num_edges_; }

    bool is_undirected() const { return undirected_; }
    bool is_directed()   const { return !undirected_; }
    void set_undirected()      { undirected_ = true; }

    void clear();

    // ── Iteration ─────────────────────────────────────────────
    iterator       begin()       { return G_.begin(); }
    const_iterator begin() const { return G_.begin(); }
    iterator       end()         { return G_.end(); }
    const_iterator end()   const { return G_.end(); }

    // ── Find ──────────────────────────────────────────────────
    iterator       find(const vertex &a)       { return G_.find(a); }
    const_iterator find(const vertex &a) const { return G_.find(a); }

    // ── Neighbour access ──────────────────────────────────────
    const vertex_set &in_neighbors (const vertex &a) const { return (find(a))->second.first;  }
          vertex_set &in_neighbors (const vertex &a)       { return G_[a].first;  }
    const vertex_set &out_neighbors(const vertex &a) const { return  find(a)->second.second; }
          vertex_set &out_neighbors(const vertex &a)       { return G_[a].second; }

    vertex_neighbor_iterator       out_neighbors_begin(const vertex &a)       { return out_neighbors(a).begin(); }
    vertex_neighbor_const_iterator out_neighbors_begin(const vertex &a) const { return out_neighbors(a).begin(); }
    vertex_neighbor_iterator       out_neighbors_end  (const vertex &a)       { return out_neighbors(a).end(); }
    vertex_neighbor_const_iterator out_neighbors_end  (const vertex &a) const { return out_neighbors(a).end(); }

    // ── Degree ────────────────────────────────────────────────
    unsigned int in_degree (const vertex &a) const { return in_neighbors(a).size(); }
    unsigned int out_degree(const vertex &a) const { return out_neighbors(a).size(); }
    unsigned int degree    (const vertex &a) const;

    bool isolated(const vertex &a) const;

    // ── Mutation ──────────────────────────────────────────────
    void insert_vertex(const vertex &a) { G_[a]; }
    void insert_new_vertex_inout_list(const vertex &a,
                                      const vertex_set &IN,
                                      const vertex_set &OUT);
    void insert_edge        (const vertex &a, const vertex &b);
    void insert_edge        (const edge &E)          { insert_edge(E.first, E.second); }
    void insert_edge        (iterator pa, iterator pb);
    void insert_edge_noloop (const vertex &a, const vertex &b) { if (a != b) insert_edge(a,b); }
    void insert_edge_noloop (iterator pa, iterator pb)         { if (pa != pb) insert_edge(pa,pb); }
    void insert_undirected_edge(const vertex &a, const vertex &b) { (a<b)?insert_edge(a,b):insert_edge(b,a); }
    void insert_undirected_edge(const edge &E) { insert_undirected_edge(E.first, E.second); }

    bool remove_edge   (iterator pa, iterator pb);
    void remove_edge   (const vertex &a, const vertex &b);
    void remove_edge   (const edge &E)                  { remove_edge(E.first, E.second); }
    void remove_undirected_edge(const vertex &a, const vertex &b) { (a<b)?remove_edge(a,b):remove_edge(b,a); }
    void remove_undirected_edge(const edge &e) { remove_undirected_edge(e.first, e.second); }
    void remove_vertex (const vertex &a);
    void remove_vertex (iterator pa);
    void remove_vertex_set(const vertex_set &V);

    bool includes_vertex(const vertex &a) const { return (find(a) != G_.end()); }
    bool includes_edge  (const vertex &a, const vertex &b) const;
    bool includes_edge  (const edge &e) const { return includes_edge(e.first, e.second); }

    // ── Set operations ────────────────────────────────────────
    tGraph  &plus_eq(const tGraph &B);
    tGraph   plus   (const tGraph &B) const;
    tGraph   intersect(const tGraph &B) const;
    tGraph   minus  (const tGraph &B) const;
    tGraph   subgraph(const vertex_set &A) const;
    unsigned int subgraph_size(const vertex_set &A) const;
    double   subgraph_sparsity(const vertex_set &A) const;

    tGraph operator+(const tGraph &B)  const { return plus(B); }
    tGraph operator*(const tGraph &B)  const { return intersect(B); }
    tGraph operator-(const tGraph &B)  const { return minus(B); }
    tGraph &operator+=(const tGraph &B)     { return plus_eq(B); }

    // ── Absorb ────────────────────────────────────────────────
    void     absorb(iterator pa, iterator pb);
    void     absorb(vertex a, vertex b);
    iterator smart_absorb(iterator pa, iterator pb);
    vertex   smart_absorb(vertex a, vertex b);

    // ── Export ────────────────────────────────────────────────
    std::vector<edge> edge_list() const;
    void print() const;

    // ── Static helpers ────────────────────────────────────────
    static const vertex     &node(const_iterator p)         { return p->first; }
    static const vertex     &node(iterator p)               { return p->first; }
    static const vertex     &node(const_vertex_iterator p)  { return *p; }

    static const vertex_set &in_neighbors (const_iterator p) { return (p->second).first;  }
    static       vertex_set &in_neighbors (iterator p)       { return (p->second).first;  }
    static const vertex_set &out_neighbors(const_iterator p) { return (p->second).second; }
    static       vertex_set &out_neighbors(iterator p)       { return (p->second).second; }

    static const_vertex_iterator in_begin (const_iterator p) { return in_neighbors(p).begin(); }
    static const_vertex_iterator in_end   (const_iterator p) { return in_neighbors(p).end();   }
    static const_vertex_iterator out_begin(const_iterator p) { return out_neighbors(p).begin();}
    static vertex_iterator       out_begin(iterator p)       { return out_neighbors(p).begin();}

    static unsigned int num_edges  (const_iterator p) { return out_neighbors(p).size(); }
    static unsigned int num_edges  (iterator p)        { return out_neighbors(p).size(); }
    static unsigned int out_degree (const_iterator p)  { return (p->second).second.size(); }
    static unsigned int out_degree (iterator p)        { return (p->second).second.size(); }
    static unsigned int in_degree  (const_iterator p)  { return (p->second).first.size(); }
    static unsigned int in_degree  (iterator p)        { return (p->second).first.size(); }
    static unsigned int degree     (const_iterator p)  { return in_neighbors(p).size() + out_neighbors(p).size(); }
    static unsigned int degree     (iterator p)        { return in_neighbors(p).size() + out_neighbors(p).size(); }
    static bool isolated(const_iterator p) { return (in_degree(p)==0 && out_degree(p)==0); }
    static bool isolated(iterator p)       { return (in_degree(p)==0 && out_degree(p)==0); }

    // ── I/O ───────────────────────────────────────────────────
    static std::istream &read_line(std::istream &s, T &v1, T &v2,
                                   std::string &line, line_type &t);
};

// ── Convenience typedefs ──────────────────────────────────────
typedef tGraph<unsigned int> Graph;
typedef tGraph<int>          iGraph;
typedef tGraph<std::string>  sGraph;

// ── Free I/O operators (template definitions stay in header) ──
template <typename T>
std::istream &operator>>(std::istream &s, tGraph<T> &G)
{
    std::string line;
    T v1, v2;
    typename tGraph<T>::line_type t;
    while (tGraph<T>::read_line(s, v1, v2, line, t))
    {
        if      (t == tGraph<T>::VERTEX) G.insert_vertex(v1);
        else if (t == tGraph<T>::EDGE)   G.insert_edge(v1, v2);
    }
    return s;
}

template <typename T>
std::ostream &operator<<(std::ostream &s, const tGraph<T> &G)
{
    for (typename tGraph<T>::const_node_iterator p = G.begin(); p != G.end(); p++)
    {
        const typename tGraph<T>::vertex_set &out = tGraph<T>::out_neighbors(p);
        typename tGraph<T>::vertex v = p->first;
        if (out.size() == 0 && tGraph<T>::in_neighbors(p).size() == 0)
            s << v << "\n";
        else
            for (typename tGraph<T>::vertex_set::const_iterator q = out.begin();
                 q != out.end(); q++)
                s << v << " " << *q << "\n";
    }
    return s;
}

} // namespace NGraph

// Include the template implementation
#include "ngraph.cpp"

#endif // NGRAPH_H_
