#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  uthash.h: No such file or directory
 *  'uthash.h' file not found
 */
#include "uthash.h"

typedef struct {
    int key;
    UT_hash_handle hh;
} Set;

void add_to_set(Set **set, int item) {
    Set *s = NULL;
    HASH_FIND_INT(*set, &item, s);
    if (s == NULL) {
        s = (Set *)malloc(sizeof(Set));
        if (s != NULL) {
            s->key = item;
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
    HASH_ITER(hh, set, current, tmp) {
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