//
// Created by Anastasiia on 06.01.2020.
//

#ifndef SORT_POOL_BITONIC_SORT_H_
#define SORT_POOL_BITONIC_SORT_H_

#include <vector>
#include <algorithm>

#include "./thread_pool.h"

template<class T>
void bitonicMerge(std::vector <T> &a, typename std::vector<T>::iterator start,
                  int count, bool ascending) {
    if (count < 2) {
        return;
    }

    int k = count / 2;
    for (int i = 0; i < k; ++i) {
        if (ascending == (*(start + i) > *(start + i + k))) {
            std::iter_swap(start + i, start + i + k);
        }
    }

    bitonicMerge(a, start, k, ascending);
    bitonicMerge(a, start + k, k, ascending);
}

template<class T>
void bitonicSort(std::vector <T> &a, typename std::vector<T>::iterator start,
                 int count, bool ascending, ThreadPool &pool) {
    if (count < 2) {
        return;
    }

    int k = count / 2;
    bitonicSort(a, start, k, true, pool);
    bitonicSort(a, start + k, k, false, pool);

    std::future<void> res = pool.enqueue([&] {
        bitonicMerge(a, start, count, ascending);
    });
    res.wait();
}

template<class T>
void sort(std::vector <T> &array, bool ascending, ThreadPool &pool) {
    bitonicSort(array, array.begin(), array.size(), ascending, pool);
}

#endif  // SORT_POOL_BITONIC_SORT_H_
