//
// Created by Anastasiia on 06.01.2020.
//

#ifndef SORT_POOL_BITONIC_SORT_H
#define SORT_POOL_BITONIC_SORT_H

#include <vector>
#include <algorithm>

#include "thread_pool.h"

template<class T>
void bitonicMerge(std::vector <T> &a, typename std::vector<T>::iterator start, int count, bool ascending) {
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
void bitonicSort(std::vector <T> &a, typename std::vector<T>::iterator start, int count, bool ascending) {
    if (count < 2) {
        return;
    }

    int k = count / 2;
    bitonicSort(a, start, k, true);
    bitonicSort(a, start + k, k, false);

    bitonicMerge(a, start, count, ascending);
}

#endif //SORT_POOL_BITONIC_SORT_H
