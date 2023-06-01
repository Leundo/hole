#ifndef EDGE_MATRIX_HPP_INCLUDED
#define EDGE_MATRIX_HPP_INCLUDED

#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include "sparse_matrix.hpp"
#include "distance.hpp"

using std::cout;
using std::endl;
using std::get;
using std::make_tuple;
using std::map;
using std::string;
using std::tuple;
using std::vector;

class EdgeMatrix : public SparseMatrix<Distance> {
   public:

    EdgeMatrix(vector<tuple<int, int>> edge_vector, int node_count): SparseMatrix<Distance>(node_count, Distance(1, 0)) {
        for (auto edge : edge_vector) {
            int source = get<0>(edge);
            int target = get<1>(edge);
            matrix[source][target] = Distance(0, 1);
        }
    }
};

#endif