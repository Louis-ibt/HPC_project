/**
 * linear_algebra.hpp
 * ==================
 * Class Point  – a 2-D (or 3-D) geometric point.
 * Class Vector – a mathematical vector implemented in terms of Point.
 * Class Matrix – a mathematical matrix implemented in terms of Vector rows.
 *
 * Operator overloads: +, =, <<
 */

#ifndef LINEAR_ALGEBRA_HPP_
#define LINEAR_ALGEBRA_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iomanip>

// ─────────────────────────────────────────────────────────────────────────────
// CLASS  Point
// ─────────────────────────────────────────────────────────────────────────────
class Point
{
public:
    double x, y, z;

    explicit Point(double x = 0.0, double y = 0.0, double z = 0.0)
        : x(x), y(y), z(z) {}

    Point operator+(const Point &o) const { return Point(x+o.x, y+o.y, z+o.z); }
    Point &operator=(const Point &o)      { x=o.x; y=o.y; z=o.z; return *this; }
    bool   operator==(const Point &o) const { return x==o.x && y==o.y && z==o.z; }

    friend std::ostream &operator<<(std::ostream &s, const Point &p)
    { return s << "(" << p.x << ", " << p.y << ", " << p.z << ")"; }
};

// ─────────────────────────────────────────────────────────────────────────────
// CLASS  Vector  (algebraic vector)
// ─────────────────────────────────────────────────────────────────────────────
class Vector
{
private:
    std::vector<double> data_;   // underlying storage
    std::size_t n_;

public:
    // ── Constructors ──────────────────────────────────────────
    explicit Vector(std::size_t n = 0, double val = 0.0)
        : data_(n, val), n_(n) {}

    /** Build a 3-D vector from a Point. */
    explicit Vector(const Point &p)
        : data_({p.x, p.y, p.z}), n_(3) {}

    Vector(std::initializer_list<double> il)
        : data_(il), n_(il.size()) {}

    Vector(const Vector &o) : data_(o.data_), n_(o.n_) {}

    // ── Access ────────────────────────────────────────────────
    std::size_t size() const { return n_; }

    double       &operator[](std::size_t i)       { return data_[i]; }
    const double &operator[](std::size_t i) const { return data_[i]; }

    // ── Arithmetic operators ──────────────────────────────────
    Vector operator+(const Vector &o) const
    {
        if (n_ != o.n_) throw std::length_error("Vector size mismatch in +");
        Vector result(n_);
        for (std::size_t i = 0; i < n_; i++) result[i] = data_[i] + o[i];
        return result;
    }

    Vector &operator=(const Vector &o)
    {
        data_ = o.data_;
        n_    = o.n_;
        return *this;
    }

    // ── Stream output ─────────────────────────────────────────
    friend std::ostream &operator<<(std::ostream &s, const Vector &v)
    {
        s << "[ ";
        for (std::size_t i = 0; i < v.n_; i++)
            s << std::setw(8) << std::fixed << std::setprecision(3) << v[i]
              << (i + 1 < v.n_ ? "  " : " ");
        return s << "]";
    }
};

// ─────────────────────────────────────────────────────────────────────────────
// CLASS  Matrix  (implemented in terms of Vector rows)
// ─────────────────────────────────────────────────────────────────────────────
class Matrix
{
private:
    std::vector<Vector> rows_;
    std::size_t nrows_, ncols_;

public:
    // ── Constructors ──────────────────────────────────────────
    Matrix(std::size_t rows, std::size_t cols, double val = 0.0)
        : rows_(rows, Vector(cols, val)), nrows_(rows), ncols_(cols) {}

    Matrix(const Matrix &o) : rows_(o.rows_), nrows_(o.nrows_), ncols_(o.ncols_) {}

    // ── Access ────────────────────────────────────────────────
    std::size_t num_rows() const { return nrows_; }
    std::size_t num_cols() const { return ncols_; }

    Vector       &operator[](std::size_t i)       { return rows_[i]; }
    const Vector &operator[](std::size_t i) const { return rows_[i]; }

    double       &at(std::size_t i, std::size_t j)       { return rows_[i][j]; }
    const double &at(std::size_t i, std::size_t j) const { return rows_[i][j]; }

    // ── Arithmetic operators ──────────────────────────────────
    Matrix operator+(const Matrix &o) const
    {
        if (nrows_ != o.nrows_ || ncols_ != o.ncols_)
            throw std::length_error("Matrix dimension mismatch in +");
        Matrix R(nrows_, ncols_);
        for (std::size_t i = 0; i < nrows_; i++) R[i] = rows_[i] + o[i];
        return R;
    }

    Matrix &operator=(const Matrix &o)
    {
        rows_  = o.rows_;
        nrows_ = o.nrows_;
        ncols_ = o.ncols_;
        return *this;
    }

    // ── Stream output ─────────────────────────────────────────
    friend std::ostream &operator<<(std::ostream &s, const Matrix &M)
    {
        s << "Matrix " << M.nrows_ << "x" << M.ncols_ << ":\n";
        for (std::size_t i = 0; i < M.nrows_; i++)
            s << "  " << M[i] << "\n";
        return s;
    }

    // ── Read integer matrix from a text file ──────────────────
    static Matrix read_int_file(const std::string &filename)
    {
        // Count rows / cols first pass
        std::ifstream f(filename);
        if (!f) throw std::runtime_error("Cannot open " + filename);
        std::vector<std::vector<int>> buf;
        std::string line;
        while (std::getline(f, line))
        {
            if (line.empty()) continue;
            std::istringstream iss(line);
            std::vector<int> row;
            int v; while (iss >> v) row.push_back(v);
            if (!row.empty()) buf.push_back(row);
        }
        if (buf.empty()) throw std::runtime_error("Empty file: " + filename);
        Matrix M(buf.size(), buf[0].size(), 0.0);
        for (std::size_t i = 0; i < buf.size(); i++)
            for (std::size_t j = 0; j < buf[i].size(); j++)
                M[i][j] = buf[i][j];
        return M;
    }
};

#endif // LINEAR_ALGEBRA_HPP_
