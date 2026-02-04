#include "ip_filter.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char const* argv[]) {
    try {
        ip_pool_t ip_pool = read_ip_pool();

        sort_ip_pool(ip_pool);

        for (const auto& ip : ip_pool) {
            std::cout << ip;
        }
        for (const auto& ip : ip_pool) {
            bool res = true;
            filter(ip, res, 1);
            if (res) {
                std::cout << ip;
            }
        }
        for (const auto& ip : ip_pool) {
            bool res = true;
            filter(ip, res, 46, 70);
            if (res) {
                std::cout << ip;
            }
        }

        for (const auto& ip : ip_pool) {
            if (filter_any(ip, 46)) {
                std::cout << ip;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
