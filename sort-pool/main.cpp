//
// Created by Anastasiia on 05.01.2020.
//

#include <iostream>
#include <vector>
#include <X86intrin.h>

#include "./thread_pool.h"
#include "./bitonic_sort.h"

int main(int argc, char **argv) {
    const int n_threads = argc > 1 ? std::stoi(argv[1]) : 4;

    ThreadPool pool(n_threads);

    const int max_array_size = 1 << 20;
    std::cout << "n_threads\tarray_size\ttime\n";
    for (int size = 8; size < max_array_size; size = size << 1) {
        std::vector<int> a(size);
        std::generate(a.begin(), a.end(), [] { return std::rand(); });

        long long start = __rdtsc();
        sort(a, true, pool);
        long long end = __rdtsc();

        std::cout << n_threads << '\t' << size << '\t' << end - start << '\n';
    }

    return 0;
}
