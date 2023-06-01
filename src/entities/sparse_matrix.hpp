#ifndef SPARSE_MATRIX_HPP_INCLUDED
#define SPARSE_MATRIX_HPP_INCLUDED

#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include "base_matrix.hpp"
#include "distance.hpp"

using std::cout;
using std::endl;
using std::get;
using std::make_tuple;
using std::map;
using std::string;
using std::tuple;
using std::vector;

template <typename ItemType>
class SparseMatrix : public BaseMatrix<ItemType> {
   public:
    vector<map<int, ItemType>> matrix = vector<map<int, ItemType>>();
    int node_count = 0;
    ItemType placeholder;

    SparseMatrix(int node_count, ItemType placeholder) {
        this->node_count = node_count;
        this->placeholder = placeholder;
        matrix = vector<map<int, ItemType>>(node_count, map<int, ItemType>());
    }

    ItemType get_item(int row, int column) {
        auto it = matrix[row].find(column);
        if (it == matrix[row].end()) {
            return placeholder;
        } else {
            return it->second;
        }
    }
    void set_item(int row, int column, ItemType item) {
        if (item != placeholder) {
            matrix[row][column] = item;
        } else {
            auto it = matrix[row].find(column);
            if (it != matrix[row].end()) {
                matrix[row].erase(it);
            }
        }
    }
    int get_node_count() { return node_count; }
    vector<tuple<int, ItemType>> get_neighbors(int row) {
        auto neighbors = vector<tuple<int, ItemType>>();
        for (auto it = matrix[row].begin(); it != matrix[row].end(); it++) {
            neighbors.push_back(make_tuple(it->first, it->second));
        }
        return neighbors;
    }

    tuple<vector<int>, vector<ItemType>> get_neighbors_v2(int row) {
        auto neighbors_id = vector<int>();
        auto neighbors_item = vector<ItemType>();
        for (auto it = matrix[row].begin(); it != matrix[row].end(); it++) {
            neighbors_id.push_back(it->first);
            neighbors_item.push_back(it->second);
        }
        return make_tuple(neighbors_id, neighbors_item);
    }
};

#endif