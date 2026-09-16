#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int count;
    /* Possible weaknesses found:
     *  struct member 'Tuple::elements' is never used. [unusedStructMember]
     */
    int *elements;
} Tuple;

int has_k_elements(Tuple t, int k) {
    return t.count == k;
}

int main() {
    Tuple t = {4, (int[]){1, 2, 3, 4}};
    int k = 4;
    if (has_k_elements(t, k)) {
        printf("Tuple has all %d elements.\n", k);
    } else {
        printf("Tuple does not have all %d elements.\n", k);
    }
    return 0;
}