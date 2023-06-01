#ifndef GRAPH_COMPUTER_HPP_INCLUDED
#define GRAPH_COMPUTER_HPP_INCLUDED

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "base_matrix.hpp"
#include "distance.hpp"

using std::cout;
using std::endl;
using std::get;
using std::make_tuple;
using std::string;
using std::tuple;
using std::vector;

template <typename ItemType>
class GraphComputer {
   public:
    static vector<Distance> binary_dial(BaseMatrix<Distance>& matrix, int root) {
        int node_count = matrix.get_node_count();
        vector<Distance> distances =
            vector<Distance>(node_count, Distance(1, 0));
        vector<vector<int>> buckets =
            vector<vector<int>>(node_count, vector<int>());

        buckets[0] = vector<int>({root});

        for (int i = 0; i < node_count; i++) {
            auto nodes = buckets[i];
            for (int node : nodes) {
                if (distances[node] == Distance(1, 0)) {
                    distances[node] = Distance(0, i);
                    if (i < node_count - 1) {
                        auto neighbors = get<0>(matrix.get_neighbors_v2(node));
                        buckets[i + 1].insert(std::end(buckets[i + 1]), std::begin(neighbors), std::end(neighbors));
                    }
                }
            }
            buckets[i].clear();
        }

        // for (int i = 0; i < node_count; i++) {
        //     cout << distances[i].printed_string() << " ";
        // }
        // cout << endl;
        return distances;
    }
};

#endif