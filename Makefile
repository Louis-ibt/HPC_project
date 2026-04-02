# Makefile – Exercise 2 C++ programs
# =====================================
# Compile with:   make
# Clean with:     make clean
# Run pp1:        ./pp1
# Run pp2:        ./pp2
# Run pp3:        ./pp3

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I.

# All targets
.PHONY: all clean

all: pp1 pp2 pp3

pp1: pp1_test_graphs.cpp graph_classes.hpp
	$(CXX) $(CXXFLAGS) -o pp1 pp1_test_graphs.cpp

pp2: pp2_test_linalg.cpp linear_algebra.hpp
	$(CXX) $(CXXFLAGS) -o pp2 pp2_test_linalg.cpp

# pp3 uses the template-only ngraph (ngraph.cpp is #included by ngraph.h)
pp3: pp3_test_ngraph_dijkstra.cpp ngraph.h ngraph.cpp set_ops.hpp
	$(CXX) $(CXXFLAGS) -o pp3 pp3_test_ngraph_dijkstra.cpp

clean:
	rm -f pp1 pp2 pp3
