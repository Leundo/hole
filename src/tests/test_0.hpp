#ifndef TEST_0_HPP_INCLUDED
#define TEST_0_HPP_INCLUDED

#include <iostream>
#include "running_arg.hpp"
#include "file_manager.hpp"
#include "bfs.hpp"
#include "time_recorder.hpp"
#include "sp_tool.hpp"
#include "sns.hpp"

using std::cout;
using std::endl;

void run_test_0(RunningArg running_arg) {
    auto&& read_result = read_edge_file(running_arg.input_edge_indices_path);
    auto edge_indices = EdgeIndices(std::get<0>(read_result), std::get<1>(read_result));

    // cout << sum_of_distances(run_and_print_time(naked_binary_dial, edge_indices, 1, -1), -1).printed_string() << endl;
    // cout << sum_of_distances(run_and_print_time(naked_bfs, edge_indices, 1, -1), -1).printed_string() << endl;
    // cout << sum_of_distances(run_and_print_time(naked_binary_dial, edge_indices, 1, -1), -1).printed_string() << endl;

    // cout << run_and_print_time(compute_graph_distance_with_mask, edge_indices, 0).printed_string() << endl;

    // cout << run_and_print_time(compute_sns, edge_indices) << endl;

    // run_and_print_time(run_sns_parallel, edge_indices, 20);

    // cout << read_vector("../logs/test.txt")[1] << endl;
    // cout << generate_file_name("abc", ".txt") << endl;

    // auto ofs = open("../logs", "abc_2023-6-2|10:33:21.txt");
    // write_vector(ofs, std::vector<int>({0, 1, 2}));
    // write_item(ofs, 123);

}

#endif