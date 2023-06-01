#ifndef TEST_0_HPP_INCLUDED
#define TEST_0_HPP_INCLUDED

#include <iostream>
#include "file_manager.hpp"
#include "binary_dial.hpp"
#include "bfs.hpp"
#include "time_recorder.hpp"
#include "sp_tool.hpp"
#include "sns.hpp"

using std::cout;
using std::endl;

void run_test_0(tuple<vector<tuple<int, int>>, int> read_result) {
    auto edge_indices = EdgeIndices(get<0>(read_result), get<1>(read_result));

    // cout << sum_of_distances(run_and_print_time(naked_binary_dial, edge_indices, 1, -1), -1).printed_string() << endl;
    // cout << sum_of_distances(run_and_print_time(naked_bfs, edge_indices, 1, -1), -1).printed_string() << endl;
    // cout << sum_of_distances(run_and_print_time(naked_binary_dial, edge_indices, 1, -1), -1).printed_string() << endl;

    // cout << run_and_print_time(compute_graph_distance_with_mask, edge_indices, 0).printed_string() << endl;

    // cout << run_and_print_time(compute_sns, edge_indices) << endl;

    run_sns_parallel(edge_indices, 4);
}

#endif