
#include <ArrayAllocate/ArrayAllocate.hpp>
#include <Vector/SpMV.hpp>
#include <Vector/VectorOperator.hpp>
#include <cmath>
#include <iostream>
void CG(double** A,
        double* x,
        double* b,
        unsigned int Xnode,
        unsigned int Ynode) {
    std::cout << "Begin to calculate Ax=b using CG method" << std::endl;

    unsigned int LEN = Xnode * Ynode;

    /*declar paramters*/
    double* r = Allocate1D<double>(LEN);
    double* r_tmp = Allocate1D<double>(LEN);
    double* tmp = Allocate1D<double>(LEN);
    double* p_all = Allocate1D<double>(LEN + 2 * Xnode);
    double* p = p_all + Xnode;

    for (int i = 0; i < LEN; i++) {
        r[i] = x[i] = 0;
    }

    /*initializition*/
    /*tmp=A*x0*/
    SpMV<double>(A, x - Xnode, tmp, LEN, Xnode);
    /*r0=b-tmp*/
    VectorOperation([](int i, auto a, auto b) { return a[i] - b[i]; }, LEN, r,
                    b, tmp);
    /*p0=r0*/
    VectorOperation([](int i, auto a) { return a[i]; }, LEN, p, r);

    int iteration = 0;
    while (true) {
        iteration++;

        auto tmp_v = VectorNorm(r, LEN);

        SpMV(A, p - Xnode, tmp, LEN, Xnode);

        auto alpha = tmp_v / VectorDotVector(p, tmp, LEN);

        /* x_k+1=x_k+alpha*p */
        VectorOperation(
            [alpha](int i, auto a, auto b) { return a[i] + alpha * b[i]; }, LEN,
            x, x, p);

        /* r_tmp=r-alpha*tmp */
        VectorOperation(
            [alpha](int i, auto a, auto b) { return a[i] - alpha * b[i]; }, LEN,
            r_tmp, r, tmp);

        auto beta = VectorNorm(r_tmp, LEN) / VectorNorm(r, LEN);

        /* p=r_tmp+beta*p */
        VectorOperation(
            [beta](int i, auto a, auto b) { return a[i] + beta * b[i]; }, LEN,
            p, r_tmp, p);

        /* r_tmp=r */
        VectorOperation([](int i, auto a) { return a[i]; }, LEN, r, r_tmp);

        /*the loop exit condition*/
        if (iteration % 10 == 0)
            std::cout << "Iterator " << iteration << ": \t the absolute err is "
                      << std::sqrt(VectorNorm(r, LEN)) << std::endl;

        if (std::sqrt(VectorNorm(r, LEN)) < 1.e-6) {
            std::cout << "The CG process has been Convergent, and CG method is "
                         "completed!"
                      << std::endl;
            break;
        }
    }

    Delte1D(r);
    Delte1D(r_tmp);
    Delte1D(tmp);
    Delte1D(p_all);
}