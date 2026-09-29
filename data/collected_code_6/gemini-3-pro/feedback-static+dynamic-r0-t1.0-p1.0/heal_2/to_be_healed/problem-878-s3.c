#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

bool check_tuple_size(const Tuple *tuple, size_t k) {
    if (tuple == NULL) {
        return false;
    }
    return tuple->size == k;
}

void print_tuple(const Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    printf("(");
    for (size_t i = 0; i < tuple->size; i++) {
        printf("%d", tuple->elements[i]);
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    int data1[] = {1, 2, 3};
    Tuple tuple1 = {data1, 3};
    
    int data2[] = {1, 2, 3, 4};
    Tuple tuple2 = {data2, 4};

    size_t k = 3;

    if (check_tuple_size(&tuple1, k)) {
        printf("Tuple1 contains exactly %zu elements: ", k);
        print_tuple(&tuple1);
    } else {
        printf("Tuple1 does not contain exactly %zu elements.\n", k);
    }

    if (check_tuple_size(&tuple2, k)) {
        printf("Tuple2 contains exactly %zu elements: ", k);
        print_tuple(&tuple2);
    } else {
        /* Possible weaknesses found:
         *  printf format string requires 1 parameter but only 0 are given. [wrongPrintfScanfArgNum]
         */
        printf("Tuple2 does not contain exactly %zu elements. It contains: ");
        print_tuple(&tuple2);
    }

    return 0;
}