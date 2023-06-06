#ifndef RUNNING_HPP_INCLUDED
#define RUNNING_HPP_INCLUDED

#include <string>

struct RunningArg {
    std::string input_edge_indices_path = "";
    std::string output_dir = "";
    std::string input_checkpoint_path = "";
    std::string output_file_mark = "";
    std::string mode = "sns";
    int k = 0;
    int thread_count = 4;
    int hop = 1;
};

#endif