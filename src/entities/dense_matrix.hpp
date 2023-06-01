#ifndef DENSE_MATRIX_HPP_INCLUDED
#define DENSE_MATRIX_HPP_INCLUDED

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
class DenseMatrix : public BaseMatrix<ItemType> {
   public:
    vector<vector<ItemType>> matrix = vector<vector<ItemType>>();
    int node_count = 0;

    DenseMatrix() {}
    DenseMatrix(int node_count, ItemType placeholder) {
        this->node_count = node_count;
        matrix = vector<vector<ItemType>>(
            node_count, vector<ItemType>(node_count, placeholder));
    }

    ItemType get_item(int row, int column) { return matrix[row][column]; }
    void set_item(int row, int column, ItemType item) {
        matrix[row][column] = item;
    }
    int get_node_count() { return node_count; }
    vector<tuple<int, ItemType>> get_neighbors(int row) {
        auto neighbors = vector<tuple<int, ItemType>>();
        for (int column = 0; column < node_count; column++) {
            if (Distance::is_connected(matrix[row][column])) {
                neighbors.push_back(make_tuple(column, matrix[row][column]));
            }
        }
        return neighbors;
    }
    tuple<vector<int>, vector<ItemType>> get_neighbors_v2(int row) {
        auto neighbors_id = vector<int>();
        auto neighbors_item = vector<ItemType>();
        for (int column = 0; column < node_count; column++) {
            if (Distance::is_connected(matrix[row][column])) {
                neighbors_id.push_back(column);
                neighbors_item.push_back(matrix[row][column]);
            }
        }
        return make_tuple(neighbors_id, neighbors_item);
    }
};

#endif