#ifndef TIME_RECORDER_HPP_INCLUDED
#define TIME_RECORDER_HPP_INCLUDED

#include <chrono>
#include <functional>
#include <iostream>

using std::cout;
using std::endl;

template <class F, class... Args>
auto run_and_print_time(F&& f, Args&&... args)
    -> std::invoke_result_t<F, Args...> {
    auto start = std::chrono::high_resolution_clock::now();
    auto result = std::bind(std::forward<F>(f), std::forward<Args>(args)...)();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    cout << "Time: " << duration.count() << endl;

    return result;
}

#endif