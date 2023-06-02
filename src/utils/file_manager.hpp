#ifndef FILE_MANAFER_HPP_INCLUDED
#define FILE_MANAFER_HPP_INCLUDED

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
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

std::vector<int> read_vector(std::string file_path) {
    std::filesystem::path url(file_path);
    if (!std::filesystem::exists(url)) {
        return std::vector<int>();
    } else {
        std::ifstream edge_file(url);
        std::ostringstream str_stream;
        str_stream << edge_file.rdbuf();
        std::string text = str_stream.str();
        auto lines = split(text, "\n");

        auto result_vector = std::vector<int>();
        for (auto line : lines) {
            if (line != "") {
                result_vector.push_back(stoi(line));
            }
        }
        return result_vector;
    }
}

std::ofstream open(std::string file_dir, std::string file_name) {
    std::ofstream ofs;
    std::filesystem::path fs_file_dir(file_dir);
    std::filesystem::path fs_file_name(file_name);
    std::filesystem::path file_path = fs_file_dir / fs_file_name;

    ofs.open(file_path, std::ios::out);
    return ofs;
}

template <typename T>
void write_vector(std::ofstream& ofs, const std::vector<T>& vec) {
    for (auto item : vec) {
        ofs << item << endl;
    }
}

template <typename T>
void write_item(std::ofstream& ofs, const T& item) {
    ofs << item << endl;
}

std::string generate_file_name(std::string base, std::string suffix) {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    return base + "_" +
           string_format("%d-%d-%d|%d:%d:%d", (now->tm_year + 1900),
                         (now->tm_mon + 1), now->tm_mday, now->tm_hour,
                         now->tm_min, now->tm_sec) +
           suffix;
}

#endif