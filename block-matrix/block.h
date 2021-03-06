//
// Created by Anastasiia on 02.01.2020.
//

#ifndef BLOCK_MATRIX_BLOCK_H
#define BLOCK_MATRIX_BLOCK_H

#include <stdio.h>

/* On my laptop, I can fit 3 matrices of double (8 Bytes) of size
 * 36x36    into L1 cache (32768 B)
 * 104x104  into L2 cache (262144 B)
 * 362x362  into L3 cache (3145728 B)
 */
const size_t blocksize = 36;

template<class T>
class block {
public:
    block() : block(blocksize, blocksize) {}

    block(size_t lines, size_t columns) : lines(lines), columns(columns) {
        bigbody = new T[lines * columns];
        body = new T *[lines];
        for (size_t i = 0; i < lines; i++) {
            body[i] = bigbody + i * columns;
        }
    }

    ~block() {
        delete[] body;
        delete[] bigbody;
    }

    T *operator()(size_t line, size_t col) {
        return body[line] + col;
    }

    T *operator()(size_t line, size_t col) const {
        return body[line] + col;
    }

    bool mul(block const &left, block const &right) {
        if (left.columns != right.lines) return false;
        if (lines != left.lines) return false;
        if (columns != right.columns) return false;

        /* Uncomment this and the line below,
         * if you want to transpose the block before multiplying. */
        // block right_tr;
        // right_tr.transpose(right);



        for (size_t i = 0; i < lines; i++) {
            for (size_t j = 0; j < columns; j++) {
                T acc = (T) 0;
                for (size_t k = 0; k < left.columns; k++) {
                    // acc += *left(i, k) * *right_tr(j, k);
                    acc += *left(i, k) * *right(k, j);
                }
                *(*this)(i, j) = acc;
            }
        }
        return true;
    }

    bool add(block const &left, block const &right) {
        if (left.columns != right.columns) return false;
        if (left.lines != right.lines) return false;
        if (lines != left.lines) return false;
        if (columns != left.columns) return false;

        for (size_t i = 0; i < lines; i++) {
            for (size_t j = 0; j < columns; j++) {
                *(*this)(i, j) = *left(i, j) + *right(i, j);
            }
        }
        return true;
    }

    bool transpose(block const &b) {
        if (b.columns != columns) return false;
        if (b.lines != lines) return false;

        for (size_t i = 0; i < lines; i++) {
            for (size_t j = 0; j < columns; j++) {
                *(*this)(i, j) = *b(j, i);
            }
        }
        return true;
    }

private:
    T **body;
    T *bigbody;
    size_t lines, columns;
};

#endif //BLOCK_MATRIX_BLOCK_H
