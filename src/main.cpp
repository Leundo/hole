#include <chrono>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "adjacency_matrix.hpp"
#include "binary_dial.hpp"
#include "cxxopts.hpp"
#include "distance.hpp"
#include "edge_matrix.hpp"
#include "file_manager.hpp"
#include "graph_computer.hpp"

using std::cout;
using std::endl;
using std::get;
using std::make_tuple;
using std::string;
using std::tuple;
using std::vector;

tuple<string, string> parse(int argc, const char* argv[]) {
    std::string inputFileName = "";
    std::string ouputFileName = "";

    cxxopts::Options options("Hole", "A hole.");
    options.add_options()("h,help", "Help")("i,input", "Input file",
                                            cxxopts::value<std::string>())(
        "o,output", "Output file", cxxopts::value<std::string>());

    try {
        auto result = options.parse(argc, argv);
        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return make_tuple(inputFileName, ouputFileName);
        }

        if (result.count("input")) {
            inputFileName = result["input"].as<std::string>();
            std::cout << "Input file: " << inputFileName << std::endl;
        }

        if (result.count("output")) {
            ouputFileName = result["output"].as<std::string>();
            std::cout << "Output file: " << ouputFileName << std::endl;
        }

        std::cout << std::endl;
        return make_tuple(inputFileName, ouputFileName);
    } catch (const cxxopts::OptionException& e) {
        std::cout << "error parsing options: " << e.what() << std::endl;
        exit(1);
    }
}

int main(int argc, const char* argv[]) {
    auto file_tuple = parse(argc, argv);
    auto read_result = read_edge_file(get<0>(file_tuple));

    // ----------
    // auto adjacency_matrix =
    //     AdjacencyMatrix(get<0>(read_result), get<1>(read_result));
    // cout << adjacency_matrix.get_item(0, 633).printed_string() << endl;
    // ----------

    // ----------
    // auto edge_matrix = EdgeMatrix(get<0>(read_result), get<1>(read_result));
    // for (int i = 0; i < edge_matrix.node_count; i++) {
    //     auto start = std::chrono::high_resolution_clock::now();

    //     GraphComputer<Distance>::binary_dial(edge_matrix, 0);

    //     auto stop = std::chrono::high_resolution_clock::now();
    //     auto duration =
    //     std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //     cout << duration.count() << endl;
    // }
    // ----------

    auto edge_indices = EdgeIndices(get<0>(read_result), get<1>(read_result));
    for (int i = 0; i < edge_indices.node_count; i++) {
        auto start = std::chrono::high_resolution_clock::now();

        auto distances = naked_binary_dial(edge_indices, i);

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        // for (auto distance: distances) {
        //     cout << distance << " ";
        // }
        // cout << endl;
        cout << duration.count() << endl;
    }

    return 0;
}