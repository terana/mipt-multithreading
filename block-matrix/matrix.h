template<class T>
class matrix {
public:
    matrix(size_t lines, size_t columns) : lines(lines), columns(columns) {
        bigbody = new T[lines * columns];
        body = new T *[lines];
        for (size_t i = 0; i < lines; i++) {
            body[i] = bigbody + i * columns;
        }
    }

    ~matrix() {
        delete[] body;
        delete[] bigbody;
    }

    T *operator()(size_t line, size_t col) {
        return body[line] + col;
    }

    T *operator()(size_t line, size_t col) const {
        return body[line] + col;
    }

    bool mul(matrix const &left, matrix const &right) {
        if (left.columns != right.lines) return false;
        if (lines != left.lines) return false;
        if (columns != right.columns) return false;
        for (size_t i = 0; i < lines; i++) {
            for (size_t j = 0; j < columns; j++) {
                T acc = (T) 0;
                for (size_t k = 0; k < left.columns; k++) {
                    acc += *left(i, k) * *right(k, j);
                }
                *(*this)(i, j) = acc;
            }
        }
        return true;
    }

private:
    T **body;
    T *bigbody;
    size_t lines, columns;
};

