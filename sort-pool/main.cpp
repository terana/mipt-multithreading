//
// Created by Anastasiia on 05.01.2020.
//

#include <iostream>
#include <vector>

#include "./thread_pool.h"
#include "./bitonic_sort.h"

int main() {
    ThreadPool pool(4);

    std::vector<int> a = {4, 6, 2, 8, 9, 1, 15, 3};
    for (auto &el : a) {
        std::cout << el << ' ';
    }
    std::cout << '\n';

    sort(a, true, pool);

    for (auto &el : a) {
        std::cout << el << ' ';
    }
    std::cout << '\n';
    return 0;
}
