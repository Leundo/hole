#include <iostream>
#include <string>
#include <tuple>
#include "cxxopts.hpp"
#include "file_manager.hpp"
#include "running_arg.hpp"
#include "sns.hpp"
#include "deg.hpp"
#include "test_0.hpp"

using std::cout;
using std::endl;

struct RunningArg parse(int argc, const char* argv[]) {
    auto running_arg = RunningArg();

    cxxopts::Options options("Hole", "A hole.");
    options.add_options()("h,help", "Help")("e,edge", "Input Edge Indices Path",
                                            cxxopts::value<std::string>())(
        "o,output", "Output Dir", cxxopts::value<std::string>())(
        "c,checkpoint", "Input Checkpoint Path", cxxopts::value<std::string>())(
        "m,mark", "Output File Mark", cxxopts::value<std::string>())(
        "k,knum", "K Number", cxxopts::value<int>())("t,thread", "Thread Count",
                                                  cxxopts::value<int>());

    try {
        auto result = options.parse(argc, argv);
        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return running_arg;
        }

        if (result.count("edge")) {
            running_arg.input_edge_indices_path =
                result["edge"].as<std::string>();
            std::cout << "Input Edge Indices Path:\t"
                      << running_arg.input_edge_indices_path << std::endl;
        }

        if (result.count("output")) {
            running_arg.output_dir = result["output"].as<std::string>();
            std::cout << "Output Dir:\t\t\t" << running_arg.output_dir
                      << std::endl;
        }

        if (result.count("checkpoint")) {
            running_arg.input_checkpoint_path =
                result["checkpoint"].as<std::string>();
            std::cout << "Input Checkpoint Path:\t"
                      << running_arg.input_checkpoint_path << std::endl;
        }

        if (result.count("mark")) {
            running_arg.output_file_mark = result["mark"].as<std::string>();
            std::cout << "Output File Mark:\t\t" << running_arg.output_file_mark
                      << std::endl;
        }

        if (result.count("knum")) {
            running_arg.k = result["knum"].as<int>();
            std::cout << "K Number:\t\t" << running_arg.k
                      << std::endl;
        }

        if (result.count("thread")) {
            running_arg.thread_count = result["thread"].as<int>();
            std::cout << "Thread Count:\t\t" << running_arg.thread_count
                      << std::endl;
        }

        std::cout << std::endl;
        return running_arg;
    } catch (const cxxopts::OptionException& e) {
        std::cout << "error parsing options: " << e.what() << std::endl;
        exit(1);
    }
}

int main(int argc, const char* argv[]) {
    auto running_arg = parse(argc, argv);

    // run_test_0(running_arg);
    // run_sns(running_arg);
    run_deg(running_arg);

    return 0;
}