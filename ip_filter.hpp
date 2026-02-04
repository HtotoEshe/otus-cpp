#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using str_ip_t = std::vector<uint8_t>;
using ip_pool_t = std::vector<str_ip_t>;

std::ostream& operator<<(std::ostream& st, const str_ip_t& ip) {
    st << (int)ip[0] << "." << (int)ip[1] << "." << (int)ip[2] << "."
       << (int)ip[3] << std::endl;

    return st;
}

str_ip_t split(const std::string& str, char d) {
    str_ip_t r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(std::stoul(str.substr(start, stop - start)));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(std::stoul(str.substr(start)));

    return r;
}

ip_pool_t read_ip_pool() {
    ip_pool_t res;
    for (std::string line; std::getline(std::cin, line);) {
        std::stringstream ss(line);
        std::string ip_str;
        std::getline(ss, ip_str, '\t');
        res.emplace_back(split(ip_str, '.'));
    }

    return res;
}

template <typename T>
void filter_s(str_ip_t ip, T t, bool& res) {
    if (ip.empty()) {
        return;
    }
    res &= (t == ip[0]);
}

template <typename T>
void filter(str_ip_t ip, bool& res, T first) {
    filter_s(ip, first, res);
}

template <typename T, typename... Args>
void filter(str_ip_t ip, bool& res, T first, Args... args) {
    filter_s(ip, first, res);
    ip.erase(ip.begin());
    filter(ip, res, args...);
}

template <typename T>
bool filter_any(const str_ip_t& ip, T byte) {
    for (const auto& ip_part : ip) {
        if (ip_part == byte) {
            return true;
        }
    }
    return false;
}

void sort_ip_pool(ip_pool_t& ip_pool) {
    auto compare = [](const str_ip_t& a, const str_ip_t& b) {
        assert(a.size() == 4 && b.size() == 4);
        auto GetWeight = [](const str_ip_t& addr) {
            uint64_t res = (addr[0] << 24) + (addr[1] << 16) + (addr[2] << 8) +
                           addr[3];
            return res;
        };

        uint32_t weight_a = GetWeight(a);
        uint32_t weight_b = GetWeight(b);
        return weight_a > weight_b;
    };

    std::sort(ip_pool.begin(), ip_pool.end(), compare);
}