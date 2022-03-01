#include "sle.hpp"

double *readFromFile(std::ifstream *file, int n) {
    double *eq = nullptr;
    eq = new double [n];
    int i = 0;
    while(!(*file).eof()) {
        (*file) >> eq[i];
        i++;
    }
    return eq;
}