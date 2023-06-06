#ifndef SP_TOOL_INCLUDED
#define SP_TOOL_INCLUDED

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include <iterator>
#include "bfs.hpp"
#include "distance.hpp"
#include "edge_indices.hpp"

using std::cout;
using std::endl;

Distance sum_of_distances(const std::vector<int>& distances, int mask) {
    Distance distance = Distance(0, 0);
    for (int i = 0; i < distances.size(); i++) {
        if (i == mask) {
            continue;
        }
        if (distances[i] < 0) {
            distance.disconnected -= distances[i];
        } else {
            distance.connected += distances[i];
        }
    }
    return distance;
}

Distance compute_graph_distance_with_mask(EdgeIndices& edge_indices, int mask) {
    Distance graph_distance = Distance(0, 0);
    for (int row = 0; row < edge_indices.node_count; row++) {
        if (row != mask) {
            auto distances = naked_bfs(edge_indices, row, mask);
            graph_distance = graph_distance + sum_of_distances(distances, mask);
        }
    }
    return graph_distance;
}

Distance compute_graph_distance_with_mask_and_isolated_nodes(
    EdgeIndices& edge_indices,
    int mask,
    const std::vector<int>& isolated_nodes) {
    Distance graph_distance = Distance(0, 0);
    for (int row = 0; row < edge_indices.node_count; row++) {
        if (row != mask &&
            std::find(isolated_nodes.begin(), isolated_nodes.end(), row) ==
                isolated_nodes.end()) {
            auto distances = naked_bfs(edge_indices, row, mask);
            graph_distance = graph_distance + sum_of_distances(distances, mask);
        }
    }
    return graph_distance;
}

int compute_out_degree_with_isolated_nodes(
    const EdgeIndices& edge_indices,
    int root,
    int hop,
    const std::vector<int>& isolated_nodes) {
    int degree = 0;
    std::set<int> nodes = std::set<int>({root});
    auto curr_neighbors =
        std::make_shared<std::set<int>>(std::set<int>({root}));
    auto next_neighbors = std::make_shared<std::set<int>>(std::set<int>());
    for (int i = 0; i < hop; i++) {
        for (auto it = (*curr_neighbors).begin(); it != (*curr_neighbors).end();
             it++) {
            auto neighbors = edge_indices.matrix[*it];
            for (auto neighbor : neighbors) {
                if (std::find(isolated_nodes.begin(), isolated_nodes.end(),
                              neighbor) == isolated_nodes.end()) {
                    (*next_neighbors).insert(neighbor);
                }
            }
        }
        nodes.insert(std::begin(*next_neighbors), std::end(*next_neighbors));
        curr_neighbors.swap(next_neighbors);
        (*next_neighbors).clear();
    }
    // cout << "root: " << root << endl;
    // for (auto it = nodes.begin(); it != nodes.end(); it++) {
    //     cout << *it << endl;
    // }
    return int(nodes.size() - 1);
}

#endif