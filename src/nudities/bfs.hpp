#ifndef BFS_HPP_INCLUDED
#define BFS_HPP_INCLUDED

#include <iostream>
#include <memory>
#include <vector>
#include "distance.hpp"
#include "edge_indices.hpp"

using std::cout;
using std::endl;

std::vector<int> naked_bfs(const EdgeIndices& edge_indices,
                           int root,
                           int mask) {
    int node_count = edge_indices.node_count;
    std::vector<int> distances = std::vector<int>(node_count, -1);

    auto curr_bucket =
        std::make_shared<std::vector<int>>(std::vector<int>({root}));
    auto next_bucket = std::make_shared<std::vector<int>>(std::vector<int>());

    for (int i = 0; i < node_count; i++) {
        for (int node : *curr_bucket) {
            if (distances[node] == -1 && node != mask) {
                distances[node] = i;
                if (i < node_count - 1) {
                    auto neighbors = edge_indices.matrix[node];
                    (*next_bucket)
                        .insert(std::end(*next_bucket), std::begin(neighbors),
                                std::end(neighbors));
                }
            }
        }
        curr_bucket.swap(next_bucket);
        (*next_bucket).clear();
    }
    return distances;
}

#endif