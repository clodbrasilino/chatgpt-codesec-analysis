#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    /* Possible weaknesses found:
     *  unknown type name 'UT_hash_handle'
     */
    UT_hash_handle hh;
} Set;

void add_to_set(Set **set, int item) {
    Set *s = NULL;
    /* Possible weaknesses found:
     *  call to undeclared function 'HASH_FIND_INT'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'HASH_FIND_INT' [-Wimplicit-function-declaration]
     */
    HASH_FIND_INT(*set, &item, s);
    if (s == NULL) {
        s = (Set *)malloc(sizeof(Set));
        if (s != NULL) {
            s->key = item;
            /* Possible weaknesses found:
             *  call to undeclared function 'HASH_ADD_INT'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  each undeclared identifier is reported only once for each function it appears in
             *  'key' undeclared (first use in this function)
             *  use of undeclared identifier 'key'
             *  implicit declaration of function 'HASH_ADD_INT' [-Wimplicit-function-declaration]
             */
            HASH_ADD_INT(*set, key, s);
        }
    }
}

Set* tuples_to_set(const int *tuples, size_t length) {
    Set *set = NULL;
    for (size_t i = 0; i < length; ++i) {
        add_to_set(&set, tuples[i]);
    }
    return set;
}

void print_set(Set *set) {
    Set *current, *tmp;
    /* Possible weaknesses found:
     *  implicit declaration of function 'HASH_ITER' [-Wimplicit-function-declaration]
     *  call to undeclared function 'HASH_ITER'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  expected ';' after expression
     *  expected ';' before '{' token
     *  'hh' undeclared (first use in this function)
     *  use of undeclared identifier 'hh'
     */
    HASH_ITER(hh, set, current, tmp) {
        /* Possible weaknesses found:
         *  Uninitialized variable: current->key [uninitvar]
         */
        printf("%d ", current->key);
    }
    printf("\n");
}

void free_set(Set *set) {
    Set *current, *tmp;
    /* Possible weaknesses found:
     *  call to undeclared function 'HASH_ITER'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  expected ';' after expression
     *  expected ';' before '{' token
     *  'hh' undeclared (first use in this function)
     *  use of undeclared identifier 'hh'
     */
    HASH_ITER(hh, set, current, tmp) {
        /* Possible weaknesses found:
         *  call to undeclared function 'HASH_DEL'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        HASH_DEL(set, current);
        free(current);
    }
}

int main() {
    int tuples[] = {1, 2, 3, 4, 5, 1, 2, 3};
    size_t length = sizeof(tuples) / sizeof(tuples[0]);

    Set *set = tuples_to_set(tuples, length);
    print_set(set);

    free_set(set);
    return 0;
}