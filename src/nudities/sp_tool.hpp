#ifndef SP_TOOL_INCLUDED
#define SP_TOOL_INCLUDED

#include <functional>
#include <iostream>
#include <vector>
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
            auto distances = naked_binary_dial(edge_indices, row, mask);
            graph_distance = graph_distance + sum_of_distances(distances, mask);
        }
    }
    cout << graph_distance.printed_string() << endl;
    return graph_distance;
}

#endif