#include <ArrayAllocate/ArrayAllocate.hpp>
#include <Setting.hpp>

void finalization() {
    Delte2D(A, 5);
    Delte1D(x_all);
    Delte1D(b);
}