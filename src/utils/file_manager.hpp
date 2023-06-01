#ifndef FILE_MANAFER_HPP_INCLUDED
#define FILE_MANAFER_HPP_INCLUDED

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include "string_processor.hpp"

using std::cout;
using std::endl;

std::tuple<std::vector<std::tuple<int, int>>, int> read_edge_file(
    std::string file_path) {
    std::filesystem::path url(file_path);
    if (!std::filesystem::exists(url)) {
        return make_tuple(std::vector<std::tuple<int, int>>(), 0);
    } else {
        std::ifstream edge_file(url);
        std::ostringstream str_stream;
        str_stream << edge_file.rdbuf();
        std::string text = str_stream.str();
        auto lines = split(text, "\n");

        std::vector<std::tuple<int, int>> edge_vector;
        int node_count = 0;
        for (auto line : lines) {
            auto words = split(line, " ");
            int source = stoi(words[0]);
            int target = stoi(words[1]);
            node_count = std::max(node_count, std::max(source, target));
            edge_vector.push_back(std::make_tuple(source, target));
        }
        return std::make_tuple(edge_vector, node_count + 1);
    }
}

#endif