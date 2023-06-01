#ifndef DISTANCE_HPP_INCLUDED
#define DISTANCE_HPP_INCLUDED

#include <string>
#include <tuple>
#include <vector>
#include "string_processor.hpp"

using std::cout;
using std::endl;

class Distance {
   public:
    long long disconnected = 0;
    long long connected = 0;

    Distance() {}
    Distance(long long disconnected, long long connected) {
        this->disconnected = disconnected;
        this->connected = connected;
    }

    Distance operator+(const Distance& rhs) const {
        return Distance(disconnected + rhs.disconnected,
                        connected + rhs.connected);
    }

    bool operator==(const Distance& rhs) const {
        return disconnected == rhs.disconnected && connected == rhs.connected;
    }

    bool operator!=(const Distance& rhs) const {
        return disconnected != rhs.disconnected || connected != rhs.connected;
    }

    bool operator<(const Distance& rhs) const {
        if (disconnected != rhs.disconnected) {
            return disconnected < rhs.disconnected;
        } else {
            return connected < rhs.connected;
        }
    }

    std::string printed_string() {
        return string_format("(%d, %d)", disconnected, connected);
    }

    static bool is_disconnected(Distance distance) {
        return distance.disconnected > 0;
    }

    static bool is_connected(Distance distance) {
        return distance.disconnected == 0;
    }
};

#endif