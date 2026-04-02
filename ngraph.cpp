/**
 * ngraph.cpp  –  Implementation of NGraph::tGraph out-of-line methods.
 *
 * Because tGraph is a class template, this file is #included by ngraph.h
 * and should NOT be compiled separately.  The guard below prevents
 * double-inclusion if someone accidentally compiles it directly.
 */

#ifndef NGRAPH_CPP_   // implementation guard (different from the .h guard)
#define NGRAPH_CPP_

// Do NOT #include "ngraph.h" here – it is always included before this file.

namespace NGraph
{

// ── Constructors ─────────────────────────────────────────────────────────────

template <typename T>
tGraph<T>::tGraph()
    : G_(), num_edges_(0), undirected_(false) {}

template <typename T>
tGraph<T>::tGraph(std::istream &s)
    : G_(), num_edges_(0), undirected_(false)
{ s >> *this; }

template <typename T>
tGraph<T>::tGraph(const tGraph &B)
    : G_(B.G_), num_edges_(B.num_edges_), undirected_(B.undirected_) {}

template <typename T>
tGraph<T>::tGraph(const edge_set &E)
    : G_(), num_edges_(0), undirected_(false)
{
    for (typename edge_set::const_iterator p = E.begin(); p != E.end(); p++)
        insert_edge(*p);
}

// ── clear ────────────────────────────────────────────────────────────────────

template <typename T>
void tGraph<T>::clear()
{
    G_.clear();
    num_edges_  = 0;
    undirected_ = false;
}

// ── degree / isolated ────────────────────────────────────────────────────────

template <typename T>
unsigned int tGraph<T>::degree(const vertex &a) const
{
    const_iterator p = find(a);
    if (p == end()) return 0;
    return tGraph<T>::degree(p);        // call static helper
}

template <typename T>
bool tGraph<T>::isolated(const vertex &a) const
{
    const_iterator p = find(a);
    if (p != end()) return isolated(p);
    return false;
}

// ── insert helpers ───────────────────────────────────────────────────────────

template <typename T>
void tGraph<T>::insert_new_vertex_inout_list(const vertex &a,
                                              const vertex_set &IN,
                                              const vertex_set &OUT)
{
    typename adj_graph::iterator p = find(a);
    if (p != G_.end())
        num_edges_ -= p->second.second.size();

    G_[a] = std::make_pair(IN, OUT);
    num_edges_ += OUT.size();
}

template <typename T>
void tGraph<T>::insert_edge(iterator pa, iterator pb)
{
    vertex a = node(pa);
    vertex b = node(pb);

    if (is_undirected())
    {
        vertex smallest = (a < b ? a : b);
        if (smallest == b) { std::swap(a,b); std::swap(pa,pb); }
    }
    unsigned int old_size = out_neighbors(pa).size();
    out_neighbors(pa).insert(b);
    in_neighbors (pb).insert(a);
    if (out_neighbors(pa).size() > old_size) num_edges_++;
}

template <typename T>
void tGraph<T>::insert_edge(const vertex &a, const vertex &b)
{
    iterator pa = find(a);
    if (pa == G_.end()) { insert_vertex(a); pa = find(a); }
    iterator pb = find(b);
    if (pb == G_.end()) { insert_vertex(b); pb = find(b); }
    insert_edge(pa, pb);
}

// ── remove helpers ───────────────────────────────────────────────────────────

template <typename T>
bool tGraph<T>::remove_edge(iterator pa, iterator pb)
{
    if (pa == end() || pb == end()) return false;
    vertex a = node(pa);
    vertex b = node(pb);
    if (is_undirected() && a > b) { std::swap(b,a); std::swap(pb,pa); }
    unsigned int old_size = out_neighbors(pa).size();
    out_neighbors(pa).erase(b);
    in_neighbors (pb).erase(a);
    if (out_neighbors(pa).size() < old_size) num_edges_--;
    return true;
}

template <typename T>
void tGraph<T>::remove_edge(const vertex &a, const vertex &b)
{
    iterator pa = find(a);
    if (pa == end()) return;
    iterator pb = find(b);
    if (pb == end()) return;
    remove_edge(pa, pb);
}

template <typename T>
void tGraph<T>::remove_vertex(iterator pa)
{
    vertex_set out_e = out_neighbors(pa);
    vertex_set in_e  = in_neighbors (pa);
    for (typename vertex_set::iterator p = out_e.begin(); p != out_e.end(); p++)
        remove_edge(pa, find(*p));
    for (typename vertex_set::iterator p = in_e.begin();  p != in_e.end();  p++)
        remove_edge(find(*p), pa);
    G_.erase(node(pa));
}

template <typename T>
void tGraph<T>::remove_vertex(const vertex &a)
{
    iterator pa = find(a);
    if (pa != G_.end()) remove_vertex(pa);
}

template <typename T>
void tGraph<T>::remove_vertex_set(const vertex_set &V)
{
    for (typename vertex_set::const_iterator p = V.begin(); p != V.end(); p++)
        remove_vertex(*p);
}

// ── includes_edge ────────────────────────────────────────────────────────────

template <typename T>
bool tGraph<T>::includes_edge(const vertex &a, const vertex &b) const
{
    if (!includes_vertex(a)) return false;
    const vertex_set &out = out_neighbors(a);
    return (out.find(b) != out.end());
}

// ── set operations ───────────────────────────────────────────────────────────

template <typename T>
tGraph<T> &tGraph<T>::plus_eq(const tGraph &B)
{
    for (const_iterator p = B.begin(); p != B.end(); p++)
    {
        const vertex &v  = node(p);
        insert_vertex(v);
        const vertex_set &out = out_neighbors(p);
        for (typename vertex_set::const_iterator q = out.begin(); q != out.end(); q++)
            insert_edge(v, *q);
    }
    return *this;
}

template <typename T>
tGraph<T> tGraph<T>::plus(const tGraph &B) const
{
    tGraph U(*this);
    U.plus_eq(B);
    return U;
}

template <typename T>
tGraph<T> tGraph<T>::intersect(const tGraph &B) const
{
    tGraph G;
    for (const_iterator p = begin(); p != end(); p++)
    {
        const vertex &v = node(p);
        if (B.includes_vertex(v)) G.insert_vertex(v);
        const vertex_set &out = out_neighbors(p);
        for (typename vertex_set::const_iterator q = out.begin(); q != out.end(); q++)
            if (B.includes_edge(v, *q)) G.insert_edge(v, *q);
    }
    return G;
}

template <typename T>
tGraph<T> tGraph<T>::minus(const tGraph &B) const
{
    tGraph G;
    for (const_iterator p = begin(); p != end(); p++)
    {
        const vertex &v = node(p);
        if (isolated(p))
        {
            if (!B.includes_vertex(v)) G.insert_vertex(v);
        }
        else
        {
            const vertex_set &out = out_neighbors(p);
            for (typename vertex_set::const_iterator q = out.begin(); q != out.end(); q++)
                if (!B.includes_edge(v, *q)) G.insert_edge(v, *q);
        }
    }
    return G;
}

template <typename T>
tGraph<T> tGraph<T>::subgraph(const vertex_set &A) const
{
    tGraph G;
    for (typename vertex_set::const_iterator p = A.begin(); p != A.end(); p++)
    {
        const_iterator t = find(*p);
        if (t != end())
        {
            vertex_set new_in  = NGraph::set_intersection(A, in_neighbors(t));
            vertex_set new_out = NGraph::set_intersection(A, out_neighbors(t));
            G.insert_new_vertex_inout_list(*p, new_in, new_out);
        }
    }
    return G;
}

template <typename T>
unsigned int tGraph<T>::subgraph_size(const vertex_set &A) const
{
    unsigned int cnt = 0;
    for (typename vertex_set::const_iterator p = A.begin(); p != A.end(); p++)
    {
        const_iterator pG = find(*p);
        if (pG != end())
        {
            const vertex_set &out = out_neighbors(pG);
            for (typename vertex_set::const_iterator q = out.begin(); q != out.end(); q++)
                if (A.count(*q)) cnt++;
        }
    }
    return cnt;
}

template <typename T>
double tGraph<T>::subgraph_sparsity(const vertex_set &A) const
{
    double N = A.size();
    double sp = (N == 1 ? 0.0 : subgraph_size(A) / (N * (N - 1)));
    if (is_undirected()) sp *= 2.0;
    return sp;
}

// ── absorb ───────────────────────────────────────────────────────────────────

template <typename T>
void tGraph<T>::absorb(iterator pa, iterator pb)
{
    if (pa == pb) return;
    remove_edge(pa, pb);
    {
        vertex_set b_out = out_neighbors(pb);
        for (typename vertex_set::iterator p = b_out.begin(); p != b_out.end(); p++)
        { iterator pi = find(*p); remove_edge(pb,pi); insert_edge(pa,pi); }
    }
    {
        vertex_set b_in = in_neighbors(pb);
        for (typename vertex_set::iterator p = b_in.begin(); p != b_in.end(); p++)
        { iterator pi = find(*p); remove_edge(pi,pb); insert_edge(pi,pa); }
    }
    remove_vertex(pb);
}

template <typename T>
void tGraph<T>::absorb(vertex a, vertex b)
{
    if (a == b) return;
    iterator pa = find(a); if (pa == end()) return;
    iterator pb = find(b); if (pb == end()) return;
    absorb(pa, pb);
}

template <typename T>
typename tGraph<T>::iterator tGraph<T>::smart_absorb(iterator pa, iterator pb)
{
    if (degree(pa) >= degree(pb)) { absorb(pa,pb); return pb; }
    else                          { absorb(pb,pa); return pb; }
}

template <typename T>
T tGraph<T>::smart_absorb(vertex a, vertex b)
{
    iterator pa = find(a); if (pa == end()) return b;
    iterator pb = find(b); if (pb == end()) return a;
    iterator pc = smart_absorb(pa, pb);
    return node(pc);
}

// ── edge_list ────────────────────────────────────────────────────────────────

template <typename T>
std::vector<typename tGraph<T>::edge> tGraph<T>::edge_list() const
{
    std::vector<edge> E;
    for (const_iterator p = begin(); p != end(); p++)
    {
        const vertex &a       = node(p);
        const vertex_set &out = out_neighbors(p);
        for (typename vertex_set::const_iterator t = out.begin(); t != out.end(); t++)
            E.push_back(edge(a, *t));
    }
    return E;
}

// ── print ────────────────────────────────────────────────────────────────────

template <typename T>
void tGraph<T>::print() const
{
    std::cerr << "# vertices: " << num_vertices() << "\n";
    std::cerr << "# edges:    " << num_edges()    << "\n";
    for (const_iterator p = G_.begin(); p != G_.end(); p++)
    {
        const vertex_set &out = out_neighbors(p);
        for (typename vertex_set::const_iterator q = out.begin(); q != out.end(); q++)
            std::cerr << p->first << "  -->  " << *q << "\n";
    }
    std::cerr << std::endl;
}

// ── read_line ────────────────────────────────────────────────────────────────

template <typename T>
std::istream &tGraph<T>::read_line(std::istream &s, T &v1, T &v2,
                                    std::string &line, line_type &t)
{
    while (getline(s, line) && line.size() < 1);
    if (s.eof()) { t = EMPTY; return s; }
    if (line[0] == '%' || line[0] == '#') { t = COMMENT; return s; }
    std::istringstream L(line);
    L >> v1;
    if (L.eof()) t = VERTEX;
    else { L >> v2; t = EDGE; }
    return s;
}

} // namespace NGraph

#endif // NGRAPH_CPP_
