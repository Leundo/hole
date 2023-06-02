#ifndef RUNNING_HPP_INCLUDED
#define RUNNING_HPP_INCLUDED

#include <string>

struct RunningArg {
    std::string input_edge_indices_path = "";
    std::string output_dir = "";
    std::string input_checkpoint_path = "";
    std::string output_file_mark = "";
    int k = 0;
    int thread_count = 4;
};

#endif