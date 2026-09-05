#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

void sort_tuples(Tuple *tuples, size_t n, int (*lambda)(const Tuple *, const Tuple *)) {
    if (tuples == NULL || n == 0 || lambda == NULL) {
        return;
    }
    /* Possible weaknesses found:
     *  passing argument 4 of 'qsort' from incompatible pointer type [-Wincompatible-pointer-types]
     *  incompatible function pointer types passing 'int (*)(const Tuple *, const Tuple *)' to parameter of type 'int (* _Nonnull)(const void *, const void *)' [-Wincompatible-function-pointer-types]
     */
    qsort(tuples, n, sizeof(Tuple), lambda);
}

int main(void) {
    Tuple data[] = {{3, 1}, {1, 5}, {2, 2}, {5, 0}};
    size_t n = sizeof(data) / sizeof(data[0]);

    sort_tuples(data, n, NULL);

    int (*cmp_first)(const Tuple *, const Tuple *) = NULL;
    /* Possible weaknesses found:
     *  expected expression before 'int'
     *  expected ';' after expression
     *  call to undeclared function 'lambda'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  expected ';' before '{' token
     *  implicit declaration of function 'lambda' [-Wimplicit-function-declaration]
     *  expected expression
     */
    cmp_first = (int (*)(const Tuple *, const Tuple *))lambda(int a, int b) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'a'
         *  use of undeclared identifier 'b'
         */
        if (a < b) return -1;
        /* Possible weaknesses found:
         *  use of undeclared identifier 'a'
         *  use of undeclared identifier 'b'
         */
        if (a > b) return 1;
        return 0;
    /* Possible weaknesses found:
     *  expected ')'
     *  to match this '('
     *  expected expression
     */
    }((const Tuple *x, const Tuple *y) { return (x->a > y->a) - (x->a < y->a); });

    sort_tuples(data, n, cmp_first);

    for (size_t i = 0; i < n; i++) {
        printf("{%d, %d}\n", data[i].a, data[i].b);
    }

    return 0;
}