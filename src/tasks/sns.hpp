#ifndef SNS_HPP_INCLUDED
#define SNS_HPP_INCLUDED

#include <atomic>
#include <future>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "distance.hpp"
#include "sp_tool.hpp"
#include "thread_pool.hpp"

using std::cout;
using std::endl;

int compute_sns(EdgeIndices& edge_indices) {
    Distance max_graph_distance = Distance(0, 0);
    int node_with_max_graph_distance = 0;

    for (int mask = 0; mask < edge_indices.node_count; mask++) {
        Distance graph_distance =
            compute_graph_distance_with_mask(edge_indices, mask);
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

int run_sns_parallel(EdgeIndices& edge_indices, int thread_count) {
    int node_count = edge_indices.node_count;
    ThreadPool thread_pool(thread_count);
    std::vector<std::future<Distance>> results;
    std::atomic<int> current_part(1);

    while (current_part <= node_count) {
        results.emplace_back(thread_pool.enqueue(
            compute_graph_distance_with_mask, edge_indices, current_part - 1));
        ++current_part;
    }

    int node_id_with_max_graph_distance = 0;
    Distance max_graph_distance = Distance(0, 0);
    for (size_t i = 0; i < results.size(); i++) {
        Distance result_distance = results[i].get();
        if (max_graph_distance < result_distance) {
            max_graph_distance = result_distance;
            node_id_with_max_graph_distance = i;
        }
    }
    cout << node_id_with_max_graph_distance << endl;
    cout << max_graph_distance.printed_string() << endl;
    return 0;
}

#endif