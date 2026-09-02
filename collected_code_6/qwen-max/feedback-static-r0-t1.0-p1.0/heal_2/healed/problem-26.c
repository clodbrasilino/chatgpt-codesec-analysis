#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int k;
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
    Tuple tuple_list[] = {
        {3},
        {3},
        {3}
    };
    size_t count = sizeof(tuple_list) / sizeof(tuple_list[0]);
    int k = 3;

    if (check_all_k_elements(tuple_list, count, k)) {
        printf("All tuples have %d elements\n", k);
    } else {
        printf("Not all tuples have %d elements\n", k);
    }

    return 0;
}