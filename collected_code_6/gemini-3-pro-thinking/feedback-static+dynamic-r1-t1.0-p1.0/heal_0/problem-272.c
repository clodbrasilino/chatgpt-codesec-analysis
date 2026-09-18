#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int front;
    int rear;
} TupleRecord;

int extract_rear_elements(const TupleRecord* records, size_t count, int** out_rears) {
    if (!records || !out_rears || count == 0) {
        return -1;
    }

    *out_rears = (int*)malloc(count * sizeof(int));
    if (!*out_rears) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        (*out_rears)[i] = records[i].rear;
    }

    return 0;
}

int main(void) {
    TupleRecord records[] = {
        {10, 15},
        {20, 25},
        {30, 35},
        {40, 45}
    };
    
    size_t count = sizeof(records) / sizeof(records[0]);
    int* rear_elements = NULL;

    if (extract_rear_elements(records, count, &rear_elements) != 0) {
        fprintf(stderr, "Failed to extract rear elements.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        printf("%d\n", rear_elements[i]);
    }

    free(rear_elements);
    rear_elements = NULL;

    return EXIT_SUCCESS;
}