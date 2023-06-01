#ifndef ADJACENCY_MATRIX_HPP_INCLUDED
#define ADJACENCY_MATRIX_HPP_INCLUDED

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "dense_matrix.hpp"
#include "distance.hpp"

using std::cout;
using std::endl;
using std::get;
using std::make_tuple;
using std::string;
using std::tuple;
using std::vector;

class AdjacencyMatrix : public DenseMatrix<Distance> {
   public:
    AdjacencyMatrix() {}

    AdjacencyMatrix(vector<tuple<int, int>> edge_vector, int node_count): DenseMatrix<Distance>(node_count, Distance(1, 0)) {
        for (auto edge : edge_vector) {
            int source = get<0>(edge);
            int target = get<1>(edge);
            matrix[source][target] = Distance(0, 1);
        }
    }
};

#endif