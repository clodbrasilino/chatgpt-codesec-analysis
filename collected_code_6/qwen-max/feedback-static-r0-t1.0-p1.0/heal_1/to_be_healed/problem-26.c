#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int k;
    /* Possible weaknesses found:
     *  struct member 'Tuple::elements' is never used. [unusedStructMember]
     *  initialized flexible array member 'elements' is here
     */
    int elements[];
} Tuple;

int check_all_k_elements(const Tuple *tuple, size_t count, int k) {
    for (size_t i = 0; i < count; ++i) {
        if (tuple[i].k != k) {
            return 0;
        }
    }
    return 1;
}

int main() {
    /* Possible weaknesses found:
     *  non-static initialization of a flexible array member
     *  (near initialization for 'tuple_list[1]')
     *  (near initialization for 'tuple_list[0]')
     *  (near initialization for 'tuple_list[2]')
     *  initialization of flexible array member is not allowed
     */
    Tuple tuple_list[] = {{3, 1, 2, 3}, {3, 3, 1, 2}, {3, 2, 3, 1}};
    /* Possible weaknesses found:
     *  invalid application of 'sizeof' to an incomplete type 'Tuple[]'
     */
    size_t count = sizeof(tuple_list) / sizeof(tuple_list[0]);
    int k = 3;

    if (check_all_k_elements(tuple_list, count, k)) {
        printf("All tuples have %d elements\n", k);
    } else {
        printf("Not all tuples have %d elements\n", k);
    }

    return 0;
}