#ifndef EDGE_INDICES_HPP_INCLUDED
#define EDGE_INDICES_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>
#include "distance.hpp"

using std::cout;
using std::endl;

class EdgeIndices {
   public:
    int node_count = 0;
    std::vector<std::vector<int>> matrix = std::vector<std::vector<int>>();

    EdgeIndices(const std::vector<std::tuple<int, int>>& edge_vector, const int& node_count) {
        this->node_count = node_count;
        matrix = std::vector<std::vector<int>>(node_count, std::vector<int>());
        for (auto edge : edge_vector) {
            int source = std::get<0>(edge);
            int target = std::get<1>(edge);
            matrix[source].push_back(target);
        }
    }

    void isolate(const std::vector<int>& nodes) {
        for (size_t source = 0; source < matrix.size(); source++) {
            if (std::find(nodes.begin(), nodes.end(), source) != nodes.end()) {
                matrix[source].clear();
            } else {
                matrix[source].erase(
                    std::remove_if(
                        matrix[source].begin(),
                        matrix[source].end(),
                        [&nodes](const int& target) {
                            return std::find(nodes.begin(), nodes.end(), target) != nodes.end();
                        }
                    ),
                    matrix[source].end()
                );
            }
        }
    }

    void isolate(const int& node) {
        for (size_t source = 0; source < matrix.size(); source++) {
            if (source == node) {
                matrix[source].clear();
            } else {
                matrix[source].erase(
                    std::remove_if(
                        matrix[source].begin(),
                        matrix[source].end(),
                        [&node](const int& target) {
                            return target == node;
                        }
                    ),
                    matrix[source].end()
                );
            }
        }
    }
};

#endif