#ifndef TEST_0_HPP_INCLUDED
#define TEST_0_HPP_INCLUDED

#include <iostream>
#include "bfs.hpp"
#include "file_manager.hpp"
#include "running_arg.hpp"
#include "sns.hpp"
#include "sp_tool.hpp"
#include "time_recorder.hpp"

using std::cout;
using std::endl;

void run_test_0(RunningArg running_arg) {
    auto&& read_result = read_edge_file(running_arg.input_edge_indices_path);
    auto edge_indices =
        EdgeIndices(std::get<0>(read_result), std::get<1>(read_result));

    auto isolated_nodes = std::vector<int>({1894, 1422, 582});
    edge_indices.isolate(isolated_nodes);
    
    cout << compute_graph_distance_with_mask_and_isolated_nodes(edge_indices, 2909, isolated_nodes).printed_string() << endl;
    cout << compute_graph_distance_with_mask_and_isolated_nodes(edge_indices, 2905, isolated_nodes).printed_string() << endl;

    cout << (compute_graph_distance_with_mask_and_isolated_nodes(edge_indices, 2909, isolated_nodes) < compute_graph_distance_with_mask_and_isolated_nodes(edge_indices, 2905, isolated_nodes)) << endl;
}

#endif