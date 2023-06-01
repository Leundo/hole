#ifndef BASE_MATRIX_HPP_INCLUDED
#define BASE_MATRIX_HPP_INCLUDED

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "distance.hpp"

using std::cout;
using std::endl;
using std::get;
using std::make_tuple;
using std::string;
using std::tuple;
using std::vector;

template<typename ItemType>
class BaseMatrix {
   public:
    virtual ItemType get_item(int row, int column) = 0;
    virtual void set_item(int row, int column, ItemType item) = 0;

    virtual int get_node_count() = 0;
    virtual vector<tuple<int, ItemType>> get_neighbors(int row) = 0;
    virtual tuple<vector<int>, vector<ItemType>> get_neighbors_v2(int row) = 0;
};

#endif