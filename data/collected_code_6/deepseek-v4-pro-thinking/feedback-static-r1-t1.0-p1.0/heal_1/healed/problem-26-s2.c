#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    int *data;
    size_t len;
} Tuple;

bool all_tuples_have_k_elements(const Tuple *tuple_list, size_t list_size, size_t k) {
    if (tuple_list == NULL) {
        return list_size == 0;
    }

    for (size_t i = 0; i < list_size; ++i) {
        if (tuple_list[i].len != k) {
            return false;
        }
        if (k > 0 && tuple_list[i].data == NULL) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};

    const Tuple tuple_list[] = {
        { a, 3 },
        { b, 3 }
    };

    if (all_tuples_have_k_elements(tuple_list, 2, 3)) {
        printf("true\n");
        return 0;
    }

    printf("false\n");
    return 1;
}