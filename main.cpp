#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
using spt_ip = std::vector<std::string>;
using ip_pool_t = std::vector<spt_ip>;

spt_ip split(const std::string& str, char d) {
    spt_ip r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

// void filter(const spt_ip& ip, int one = -1, int two = -1, int three = -1,
//             int four = -1) {
//     bool got_it = false;
//     if ((one != -1 && std::stoi(ip[0])) == one ||
//         (two != -1 && std::stoi(ip[1]) == two) ||
//         (three != -1 && std::stoi(ip[2]) == three) ||
//         (four != -1 && std::stoi(ip[2]))) {
//     }
//     for (const auto& ip_part : ip) {
//         std::cout << ip_part;
//         if (ip_part != ip.back()) {
//             std::cout << ".";
//         }
//     }
//     std::cout << std::endl;
// }

int main([[maybe_unused]] int argc, [[maybe_unused]] char const* argv[]) {
    try {
        ip_pool_t ip_pool;

        for (std::string line; std::getline(std::cin, line);) {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        auto compare = [](const std::vector<std::string>& a,
                          const std::vector<std::string>& b) {
            assert(a.size() == 4 && b.size() == 4);
            auto GetWeight = [](const spt_ip& addr) {
                uint64_t res = (std::stoul(addr[0]) << 24) +
                               (std::stoul(addr[1]) << 16) +
                               (std::stoul(addr[2]) << 8) + std::stoul(addr[3]);
                return res;
            };

            uint32_t weight_a = GetWeight(a);
            uint32_t weight_b = GetWeight(b);
            return weight_a > weight_b;
        };

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), compare);

        for (const auto& ip : ip_pool) {
            for (const auto& ip_part : ip) {
                std::cout << ip_part;
                if (ip_part != ip.back()) {
                    std::cout << ".";
                }
            }
            std::cout << std::endl;
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
