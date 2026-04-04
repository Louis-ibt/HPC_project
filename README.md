# HPC Project – Graph Algorithms & Parallel Computing

An academic project exploring graph algorithms, parallel processing, and C++ implementations as part of the ESILV HPC curriculum.

---

## 📁 Project Structure

```
HPC_project/
├── Exercise1_Python/              # Graph algorithms & visualization
│   └── 1_graph_properties/
│       └── exercise1.py           # Main Python implementation
├── Exercise1_Parallel_MPI/        # Parallel MPI exercises
│   └── 3_communication_ring/
│       └── mpi_ring.py            # MPI ring topology
├── Exercise2_CPP/                 # C++ implementations
│   ├── 1_graph_classes/
│   ├── 2_linear_algebra/
│   ├── 3_dijkstra/
│   ├── tests/                     # C++ test programs
│   └── Makefile
├── outputs/                       # 📊 All generated outputs (organized by exercise)
│   ├── Exercise1_Python/          # Python-generated graphs & matrices
│   ├── Exercise1_Parallel_MPI/    # MPI output & logs
│   └── Exercise2_CPP/             # Compiled binaries & test results
├── Article/                       # Course materials & documentation
└── README.md                      # This file
```

---

## 🚀 Quick Start

### Prerequisites
- Python 3.8+ with `networkx`, `matplotlib`, `numpy`
- C++17 compiler (g++, clang, or MSVC)
- Make (for building C++ exercises)
- MPI library (mpi4py for Python, OpenMPI/MPICH for C++)

### Running the Exercises

#### Exercise 1: Python Graph Algorithms
```bash
python Exercise1_Python/1_graph_properties/exercise1.py
```
**Outputs saved to:** `outputs/Exercise1_Python/`
- Graph visualizations (PNG files)
- Adjacency/incidence matrices (TXT files)

#### Exercise 2: Parallel MPI Ring
```bash
mpiexec -n 8 python Exercise1_Parallel_MPI/3_communication_ring/mpi_ring.py
```
**Outputs saved to:** `outputs/Exercise1_Parallel_MPI/`

#### Exercise 3: C++ Graph Classes & Dijkstra
```bash
cd Exercise2_CPP
g++ -std=c++17 -Wall -O2 -I./1_graph_classes -o pp1 tests/pp1_test_graphs.cpp
g++ -std=c++17 -Wall -O2 -I./2_linear_algebra -o pp2 tests/pp2_test_linalg.cpp
g++ -std=c++17 -Wall -O2 -I./1_graph_classes  -o pp3 tests/pp3_test_ngraph_dijkstra.cpp

.\pp1
.\pp2
.\pp3
```
**Outputs saved to:** `outputs/Exercise2_CPP/`

---

## 📊 Generated Files

All output files are **automatically organized** by exercise type in the `outputs/` directory:

### Exercise1_Python Outputs
- **tree_6plots.png** – Binary tree visualization (multiple views)
- **tree_swap.png** – Before/after node swap
- **ring_graph.png** – Ring topology (9 nodes)
- **pair_graph.png** – Pair-graph structure
- **Gp_adjacency_matrix.txt** – Graph adjacency matrix (used by C++ tests)
- **Gp_incidence_matrix.txt** – Graph incidence matrix
- **Gp_adjacency_list.txt** – Graph adjacency list

### Data Flow
```
Exercise1_Python/exercise1.py
    ↓
savefig() → outputs/Exercise1_Python/*.png
savetxt() → outputs/Exercise1_Python/*.txt
    ↓
Exercise2_CPP/tests/*.cpp (reads these files)
```

---

## 🛠️ Key Features

### 1. Cycle Detection (Directed Graphs)
- DFS-based cycle detection algorithm
- Tests on acyclic vs cyclic graphs

### 2. Graph Properties (Undirected Graphs)
- Bipartite checking (BFS 2-coloring)
- Empty graph detection
- Complete graph detection

### 3. Binary Tree Operations
- Build complete binary tree with heap indexing
- Tree layout algorithm (top-down hierarchical)
- Node swap operations

### 4. Ring Topology
- 9-node directed ring (p0 → p1 → ... → p8 → p0)
- Circular visualization

### 5. Pair-Graph (Gp)
- Chain with skip edges
- Cross/No-Cross vertex pattern
- Multiple representations:
  - Adjacency matrix
  - Incidence matrix
  - Adjacency list

### 6. Linear Algebra (C++)
- Point, Vector, Matrix classes
- Operator overloading (+, =, <<)
- Matrix file I/O

### 7. Dijkstra's Algorithm (C++)
- Shortest path computation
- Weighted undirected graphs
- Uses output from Exercise 1

---

## 📝 Notes

### Why outputs/ Directory?
- **Organization:** Keeps project root clean
- **Scalability:** Easy to find results without clutter
- **Parallel Execution:** Multiple runs won't overwrite files
- **Git-Friendly:** Single `.gitignore` rule for all outputs

### File Paths
Scripts use relative paths from the project root:
```python
OUTPUT_DIR = Path(__file__).parent.parent.parent / "outputs" / "Exercise1_Python"
```

Always run scripts from the **project root directory**.

### C++ File Access
C++ tests read from outputs directory:
```cpp
Matrix A = Matrix::read_int_file("../../outputs/Exercise1_Python/Gp_adjacency_matrix.txt");
```

---

## 📚 Related Files

- **STRUCTURE.md** – Detailed project structure documentation
- **Article/** – Course materials and theory
- **LICENSE** – Project license

---

## ✅ Verification

To verify the setup is working:

```bash
# 1. Run Python exercise
python Exercise1_Python/1_graph_properties/exercise1.py

# 2. Check outputs were created
ls outputs/Exercise1_Python/

# 3. Build and test C++
cd Exercise2_CPP && make && make test

# 4. Verify C++ can read Python outputs
./bin/pp2_test_linalg
```

All outputs should be in organized subdirectories, not cluttering the root.