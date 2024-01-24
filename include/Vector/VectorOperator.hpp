#ifndef _VECTOROPERATOR_
#define _VECTOROPERATOR_
#include <utility>

template <class Type, class OP, class... VEC>
void VectorOperation(OP op, unsigned L, Type result, VEC... vec) {
    for (int i = 0; i < L; i++)
        result[i] = op(i, vec...);
}

template <class Type>
Type VectorDotVector(Type* a, Type* b, unsigned int L) {
    Type sum = 0;

    for (int i = 0; i < L; i++)
        sum += a[i] * b[i];

    return sum;
}

template <class Type>
Type VectorNorm(Type* a, unsigned int L) {
    return VectorDotVector(a, a, L);
}

#endif