
#include <omp.h>
#include <Setting.hpp>
#include <iostream>

void initialization();
void finalization();
void assemble();
void CG(double** A,
        double* x,
        double* b,
        unsigned int Xnode,
        unsigned int Ynode);
void Output();

int main() {
    initialization();
    assemble();

    auto t0 = omp_get_wtime();
    CG(A, x, b, Xnode, Ynode);
    auto t1 = omp_get_wtime();

    Output();
    std::cout << "Runing time is " << t1 - t0 << "s" << std::endl;
    finalization();
    return 0;
}