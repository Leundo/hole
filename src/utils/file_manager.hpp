#ifndef FILE_MANAFER_HPP_INCLUDED
#define FILE_MANAFER_HPP_INCLUDED

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include "string_processor.hpp"

using std::cout;
using std::endl;
using std::get;
using std::make_tuple;
using std::string;
using std::tuple;
using std::vector;

tuple<vector<tuple<int, int>>, int> read_edge_file(string file_path) {
    std::filesystem::path url(file_path);
    if (!std::filesystem::exists(url)) {
        return make_tuple(vector<tuple<int, int>>(), 0);
    } else {
        std::ifstream edge_file(url);
        std::ostringstream str_stream;
        str_stream << edge_file.rdbuf();
        string text = str_stream.str();
        auto lines = split(text, "\n");

        vector<tuple<int, int>> edge_vector;
        int node_count = 0;
        for (auto line : lines) {
            auto words = split(line, " ");
            int source = stoi(words[0]);
            int target = stoi(words[1]);
            node_count = std::max(node_count, std::max(source, target));
            edge_vector.push_back(make_tuple(source, target));
        }
        return make_tuple(edge_vector, node_count + 1);
    }
}

#endif