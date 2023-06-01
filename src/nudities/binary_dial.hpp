#ifndef BINARY_DIAL_HPP_INCLUDED
#define BINARY_DIAL_HPP_INCLUDED

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "edge_indices.hpp"
#include "distance.hpp"

using std::cout;
using std::endl;
using std::get;
using std::make_tuple;
using std::string;
using std::tuple;
using std::vector;


vector<int> naked_binary_dial(const EdgeIndices& edge_indices, int root, int mask) {
    int node_count = edge_indices.node_count;
    vector<int> distances = vector<int>(node_count, -1);
    vector<vector<int>> buckets =
        vector<vector<int>>(node_count, vector<int>());

    buckets[0] = vector<int>({root});

    for (int i = 0; i < node_count; i++) {
        for (int node : buckets[i]) {
            if (distances[node] == -1 && node != mask) {
                distances[node] = i;
                if (i < node_count - 1) {
                    auto neighbors = edge_indices.matrix[node];
                    buckets[i + 1].insert(std::end(buckets[i + 1]),
                                          std::begin(neighbors),
                                          std::end(neighbors));
                }
            }
        }
        buckets[i].clear();
    }
    return distances;
}


#endif