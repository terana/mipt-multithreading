#include "block.h"

template<class T>
class blockmatrix {
    using block_t = block<T>;

public:
    blockmatrix(size_t lines, size_t columns) : lines(lines), columns(columns) {
        block_lines = lines / blocksize + (lines % blocksize ? 1 : 0);
        block_columns = columns / blocksize + (columns % blocksize ? 1 : 0);

        bigbody = new block_t[block_lines * block_columns];
        body = new block_t *[block_lines];
        for (size_t i = 0; i < block_lines; i++) {
            body[i] = bigbody + i * block_columns;
        }
    }

    ~blockmatrix() {
        delete[] body;
        delete[] bigbody;
    }

    T *operator()(size_t line, size_t col) {
        return (*(body[line / blocksize] + col / blocksize))(line % blocksize, col % blocksize);
    }

    T *operator()(size_t line, size_t col) const {
        return (*(body[line / blocksize] + col / blocksize))(line % blocksize, col % blocksize);
    }

    bool mul(blockmatrix const &left, blockmatrix const &right) {
        if (left.columns != right.lines) return false;
        if (lines != left.lines) return false;
        if (columns != right.columns) return false;

        for (size_t i = 0; i < block_lines; i++) {
            for (size_t j = 0; j < block_columns; j++) {
                block_t acc;
                for (size_t k = 0; k < left.block_columns; k++) {
                    acc.mul(*left.block(i, k), *right.block(k, j));
                    this->block(i, j)->add(*this->block(i, j), acc);
                }
            }
        }
        return true;
    }

private:
    block_t **body;
    block_t *bigbody;
    size_t lines, columns, block_lines, block_columns;

    block_t *block(size_t block_line, size_t block_col) {
        return body[block_line] + block_col;
    }

    block_t *block(size_t block_line, size_t block_col) const {
        return body[block_line] + block_col;
    }
};

