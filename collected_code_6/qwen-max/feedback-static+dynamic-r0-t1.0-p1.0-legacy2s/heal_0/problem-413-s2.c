#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple* create_tuple_list(int size) {
    return (Tuple*)malloc(size * sizeof(Tuple));
}

void free_tuple_list(Tuple* list) {
    free(list);
}

int get_nth_element(Tuple* list, int n, int* result) {
    if (n < 0 || !list) {
        return -1;
    }
    *result = list[n].first;
    return 0;
}

int main() {
    Tuple* tuple_list = create_tuple_list(5);
    if (!tuple_list) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    tuple_list[0] = (Tuple){10, 20};
    tuple_list[1] = (Tuple){30, 40};
    tuple_list[2] = (Tuple){50, 60};
    tuple_list[3] = (Tuple){70, 80};
    tuple_list[4] = (Tuple){90, 100};

    int result;
    int index = 2;
    if (get_nth_element(tuple_list, index, &result) == 0) {
        printf("The %dth element is: %d\n", index + 1, result);
    } else {
        fprintf(stderr, "Failed to get the %dth element\n", index + 1);
    }

    free_tuple_list(tuple_list);
    return 0;
}