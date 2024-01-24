#include <ArrayAllocate/ArrayAllocate.hpp>
#include <Setting.hpp>

void initialization() {
    /*determine the size of matrix*/
    unsigned int SIZE = Xnode * Ynode;

    /*allcate matrix A*/
    A = Allocate2D<double>(5, SIZE);

    /*allocate vector X*/
    x_all = Allocate1D<double>(SIZE + 2 * Xnode);
    x = x_all + Xnode;

    /*allocate vector b*/
    b = Allocate1D<double>(SIZE);
}