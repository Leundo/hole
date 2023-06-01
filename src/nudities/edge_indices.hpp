#ifndef EDGE_INDICES_HPP_INCLUDED
#define EDGE_INDICES_HPP_INCLUDED

#include <iostream>
#include <vector>
#include "distance.hpp"

using std::cout;
using std::endl;

class EdgeIndices {
   public:
    int node_count = 0;
    std::vector<std::vector<int>> matrix = std::vector<std::vector<int>>();

    EdgeIndices(std::vector<std::tuple<int, int>> edge_vector, int node_count) {
        this->node_count = node_count;
        matrix = std::vector<std::vector<int>>(node_count, std::vector<int>());
        for (auto edge : edge_vector) {
            int source = std::get<0>(edge);
            int target = std::get<1>(edge);
            matrix[source].push_back(target);
        }
    }
};

#endif