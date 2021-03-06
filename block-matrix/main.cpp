#include <stdio.h>
#include <X86intrin.h>
#include <string>

#include "blockmatr.h"
#include "matrix.h"

using namespace std;

int main(int argc, char **argv) {
    const int ay = argc > 1 ? std::stoi(argv[1]) : 1000,
            ax = argc > 2 ? std::stoi(argv[2]) : 900,
            by = ax,
            bx = argc > 3 ? std::stoi(argv[3]) : 1200,
            cy = ay, cx = bx;

    blockmatrix<double> a(ay, ax), b(by, bx), c(cy, cx);
    matrix<double> d(ay, ax), e(by, bx), f(cy, cx);

    for (int i = 0; i < ay; i++) {
        for (int j = 0; j < ax; j++) {
            *a(i, j) = i * j;
            *d(i, j) = i * j;
        }
    }

    for (int i = 0; i < by; i++) {
        for (int j = 0; j < bx; j++) {
            *b(i, j) = i * j;
            *e(i, j) = i * j;
        }
    }

    {
        long long start = __rdtsc();
        c.mul(a, b);
        long long end = __rdtsc();
        double sum = 0;
        for (int i = 0; i < cy; i++) {
            for (int j = 0; j < cx; j++) {
                sum += *c(i, j);
            }
        }
        printf("blockmatrix: sum=%.0lf time=%.6f\n", sum, (end - start) / 1000000000.);
    }

    {
        long long start = __rdtsc();
        f.mul(d, e);
        long long end = __rdtsc();
        double sum = 0;
        for (int i = 0; i < cy; i++) {
            for (int j = 0; j < cx; j++) {
                sum += *f(i, j);
            }
        }
        printf("matrix:      sum=%.0lf time=%.6f\n", sum, (end - start) / 1000000000.);
    }
}
