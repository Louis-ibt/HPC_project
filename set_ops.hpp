#ifndef SET_OPS_HPP_
#define SET_OPS_HPP_

#include <set>
#include <algorithm>
#include <iterator>

namespace NGraph {

// Set union
template <typename T>
std::set<T> set_union(const std::set<T>& A, const std::set<T>& B)
{
    std::set<T> result;
    std::set_union(A.begin(), A.end(), B.begin(), B.end(),
                   std::inserter(result, result.begin()));
    return result;
}

// Set intersection
template <typename T>
std::set<T> set_intersection(const std::set<T>& A, const std::set<T>& B)
{
    std::set<T> result;
    std::set_intersection(A.begin(), A.end(), B.begin(), B.end(),
                          std::inserter(result, result.begin()));
    return result;
}

// Set difference
template <typename T>
std::set<T> set_difference(const std::set<T>& A, const std::set<T>& B)
{
    std::set<T> result;
    std::set_difference(A.begin(), A.end(), B.begin(), B.end(),
                        std::inserter(result, result.begin()));
    return result;
}

// Subset test
template <typename T>
bool is_subset(const std::set<T>& A, const std::set<T>& B)
{
    return std::includes(B.begin(), B.end(), A.begin(), A.end());
}

} // namespace NGraph

#endif // SET_OPS_HPP_
