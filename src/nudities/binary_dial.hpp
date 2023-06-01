#ifndef BINARY_DIAL_HPP_INCLUDED
#define BINARY_DIAL_HPP_INCLUDED

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

class EdgeIndices {
   public:
    int node_count = 0;
    vector<vector<int>> matrix = vector<vector<int>>();

    EdgeIndices(vector<tuple<int, int>> edge_vector, int node_count) {
        this->node_count = node_count;
        matrix = vector<vector<int>>(node_count, vector<int>());
        for (auto edge : edge_vector) {
            int source = get<0>(edge);
            int target = get<1>(edge);
            matrix[source].push_back(target);
        }
    }
};

vector<int> naked_binary_dial(EdgeIndices& edge_indices, int root, int mask) {
    int node_count = edge_indices.node_count;
    vector<int> distances = vector<int>(node_count, -1);
    vector<vector<int>> buckets =
        vector<vector<int>>(node_count, vector<int>());

    buckets[0] = vector<int>({root});

    for (int i = 0; i < 100; i++) {
        auto nodes = buckets[i];
        for (int node : nodes) {
            if (distances[node] == -1 && node != mask) {
                distances[node] = i;
                if (i < node_count - 1) {
                    auto neighbors = edge_indices.matrix[node];
                    buckets[i + 1].insert(std::end(buckets[i + 1]),
                                          std::begin(neighbors),
                                          std::end(neighbors));
                }
            }
        }
        buckets[i].clear();
    }
    return distances;
}

Distance sum_of_distances(const vector<int>& distances, int mask) {
    Distance distance = Distance(0, 0);
    for (int i = 0; i < distances.size(); i++) {
        if (i == mask) {
            continue;
        }
        if (distances[i] < 0) {
            distance.disconnected -= distances[i];
        } else {
            distance.connected += distances[i];
        }
    }
    return distance;
}



#endif