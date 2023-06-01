#include <iostream>
#include <string>
#include <tuple>
#include "cxxopts.hpp"
#include "file_manager.hpp"
#include "test_0.hpp"

using std::cout;
using std::endl;

tuple<std::string, std::string> parse(int argc, const char* argv[]) {
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
    auto read_result = read_edge_file(std::get<0>(file_tuple));

    run_test_0(read_result);

    return 0;
}