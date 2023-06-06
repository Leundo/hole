#ifndef DEG_HPP_INCLUDED
#define DEG_HPP_INCLUDED

#include <algorithm>
#include <atomic>
#include <future>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "distance.hpp"
#include "file_manager.hpp"
#include "running_arg.hpp"
#include "sp_tool.hpp"
#include "thread_pool.hpp"

using std::cout;
using std::endl;

int compute_out_deg_parallel(EdgeIndices& edge_indices,
                             int hop,
                             const std::vector<int>& isolated_nodes,
                             ThreadPool& thread_pool) {
    int node_count = edge_indices.node_count;
    std::vector<std::future<int>> results;
    std::atomic<int> current_part(1);

    while (current_part <= node_count) {
        if (std::find(isolated_nodes.begin(), isolated_nodes.end(),
                      current_part - 1) == isolated_nodes.end()) {
            int root = current_part - 1;
            auto func = [&edge_indices, hop, root,
                         &isolated_nodes]() {
                return compute_out_degree_with_isolated_nodes(
                    edge_indices, root, hop, isolated_nodes);
            };
            results.emplace_back(thread_pool.enqueue(func));
        } else {
            results.emplace_back(
                std::future<int>(std::async([]() { return -1; })));
        }
        ++current_part;
    }
    int node_id_with_max_out_degree = 0;
    int max_out_degree = -1;
    for (size_t i = 0; i < results.size(); i++) {
        int result_degree = results[i].get();
        if (max_out_degree < result_degree) {
            max_out_degree = result_degree;
            node_id_with_max_out_degree = i;
        }
    }
    cout << node_id_with_max_out_degree << endl;
    cout << max_out_degree << endl;

    return node_id_with_max_out_degree;
}

int compute_k_out_deg_parallel(std::ofstream& ofs,
                               int k,
                               int hop,
                               EdgeIndices& edge_indices,
                               std::vector<int>& isolated_nodes,
                               int thread_count) {
    int node_count = edge_indices.node_count;
    ThreadPool thread_pool(thread_count);

    for (size_t epoch = isolated_nodes.size(); epoch <= k; epoch++) {
        auto start = std::chrono::high_resolution_clock::now();
        auto node_id = compute_out_deg_parallel(edge_indices, hop,
                                                isolated_nodes, thread_pool);
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

void run_deg(RunningArg running_arg) {
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
    compute_k_out_deg_parallel(ofs, running_arg.k, running_arg.hop, edge_indices,
                               isolated_nodes, running_arg.thread_count);

    // cout << compute_out_degree_with_isolated_nodes(edge_indices, 0, 2,
    // std::vector<int>({633})) << endl;

    ofs.close();
}

#endif