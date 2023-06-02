#ifndef SNS_HPP_INCLUDED
#define SNS_HPP_INCLUDED

#include <algorithm>
#include <atomic>
#include <future>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "distance.hpp"
#include "running_arg.hpp"
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

int compute_sns_parallel(EdgeIndices& edge_indices,
                         const std::vector<int>& isolated_nodes,
                         ThreadPool& thread_pool) {
    int node_count = edge_indices.node_count;
    std::vector<std::future<Distance>> results;
    std::atomic<int> current_part(1);

    while (current_part <= node_count) {
        if (std::find(isolated_nodes.begin(), isolated_nodes.end(),
                      current_part - 1) == isolated_nodes.end()) {
            // results.emplace_back(
            //     thread_pool.enqueue(compute_graph_distance_with_mask,
            //                         edge_indices, current_part - 1));
            results.emplace_back(
                thread_pool.enqueue(compute_graph_distance_with_mask_and_isolated_nodes,
                                    edge_indices, current_part - 1, isolated_nodes));
        } else {
            results.emplace_back(std::future<Distance>(std::async([](){return Distance(0, 0);})));
        }
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

    return node_id_with_max_graph_distance;
}

int compute_k_sns_parallel(std::ofstream& ofs,
                           int k,
                           EdgeIndices& edge_indices,
                           std::vector<int> isolated_nodes,
                           int thread_count) {
    int node_count = edge_indices.node_count;
    ThreadPool thread_pool(thread_count);

    for (size_t epoch = isolated_nodes.size(); epoch <= k; epoch++) {
        auto start = std::chrono::high_resolution_clock::now();
        auto node_id =
            compute_sns_parallel(edge_indices, isolated_nodes, thread_pool);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "Time: " << duration.count() / 1000000 << endl;

        cout << "Epoch:\t" << epoch << " " << node_id << endl;
        write_item(ofs, node_id);
        edge_indices.isolate(node_id);
        isolated_nodes.push_back(node_id);
    }

    return 0;
}

void run_sns(RunningArg running_arg) {
    auto&& read_result = read_edge_file(running_arg.input_edge_indices_path);
    auto edge_indices =
        EdgeIndices(std::get<0>(read_result), std::get<1>(read_result));

    auto isolated_nodes = std::vector<int>();
    if (running_arg.input_checkpoint_path != "") {
        isolated_nodes = read_vector(running_arg.input_checkpoint_path);
    }
    edge_indices.isolate(isolated_nodes);

    auto ofs = open(running_arg.output_dir,
                    generate_file_name(running_arg.output_file_mark, ".txt"));
    write_vector(ofs, isolated_nodes);

    compute_k_sns_parallel(ofs, running_arg.k, edge_indices, isolated_nodes,
                           running_arg.thread_count);
    ofs.close();
}

#endif