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

int main(void) {
    int data1[] = {1, 2, 3};
    Tuple tuple1 = {data1, 3};
    
    int data2[] = {1, 2, 3, 4};
    Tuple tuple2 = {data2, 4};

    size_t k = 3;

    if (check_tuple_size(&tuple1, k)) {
        printf("Tuple1 contains exactly %zu elements.\n", k);
    } else {
        printf("Tuple1 does not contain exactly %zu elements.\n", k);
    }

    if (check_tuple_size(&tuple2, k)) {
        printf("Tuple2 contains exactly %zu elements.\n", k);
    } else {
        printf("Tuple2 does not contain exactly %zu elements.\n", k);
    }

    return 0;
}