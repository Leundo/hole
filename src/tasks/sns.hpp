#ifndef SNS_HPP_INCLUDED
#define SNS_HPP_INCLUDED

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "binary_dial.hpp"
#include "distance.hpp"

using std::cout;
using std::endl;
using std::get;
using std::make_tuple;
using std::string;
using std::tuple;
using std::vector;

Distance compute_graph_distance_with_mask(EdgeIndices& edge_indices, int mask) {
    Distance graph_distance = Distance(0, 0);
    for (int row = 0; row < edge_indices.node_count; row++) {
        if (row != mask) {
            auto distances = naked_binary_dial(edge_indices, row, mask);
            graph_distance = graph_distance + sum_of_distances(distances, mask);
        }
    }
    return graph_distance;
}

int compute_sns(EdgeIndices& edge_indices) {
    Distance max_graph_distance = Distance(0, 0);
    int node_with_max_graph_distance = 0;

    for (int mask = 0; mask < edge_indices.node_count; mask++) {
        Distance graph_distance = compute_graph_distance_with_mask(edge_indices, mask);
        if (max_graph_distance < graph_distance) {
            max_graph_distance = graph_distance;
            node_with_max_graph_distance = mask;
        }
        cout << graph_distance.printed_string() << " " << mask << endl;
    }

    return node_with_max_graph_distance;
}

int compute_sns_parallel(EdgeIndices& edge_indices) {
    int node_with_max_graph_distance = 0;

    return node_with_max_graph_distance;
}

#endif