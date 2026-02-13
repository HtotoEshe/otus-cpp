#pragma once

#include <cstdint>
#include <iostream>
#include <list>
#include <string>
#include <vector>

template <typename T>
void print_val(T&& t) {
    uint8_t* bytes = reinterpret_cast<uint8_t*>(&t);
    for (int i = sizeof(t) - 1; i >= 0; i--) {
        std::cout << (int)bytes[i];
        if (i != 0) {
            std::cout << ".";
        } else {
            std::cout << "\n";
        }
    }
};

template <typename T>
void print_container(T&& t) {
    size_t counter = 0;
    for (const auto& it : t) {
        std::cout << (int)it;
        if (counter < t.size() - 1) std::cout << '.';
        counter++;
    }
    std::cout << "\n";
}

template <typename T>
void print_string(T&& t) {
    std::cout << t << std::endl;
}

namespace filter_vector {
template <typename T>
auto print_ip(T&& container, int) -> decltype(container.size()) {
    print_container(container);
    return 0;
}

template <typename T>
void print_ip(T&& container, long) {
    print_val(container);
}
}  // namespace filter_vector

namespace filter_string {
template <typename T>
auto print_ip(T&& container, int) -> decltype(container.c_str()) {
    print_string(container);
    return 0;
}

template <typename T>
void print_ip(T&& container, long) {
    filter_vector::print_ip(container, int{});
}
}  // namespace filter_string

namespace filter_list {
template <typename T>
auto print_ip(T&& container, int) -> decltype(container.sort()) {
    print_container(container);
}

template <typename T>
void print_ip(T&& container, long) {
    filter_string::print_ip(container, int{});
}
}  // namespace filter_list

template <typename T>
void print_ip(T&& container) {
    filter_list::print_ip(container, int{});
}