#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

int* extract_single_elements(Tuple* tuple_list, size_t tuple_count, size_t* out_count) {
    if (tuple_list == NULL || out_count == NULL || tuple_count == 0) {
        if (out_count) *out_count = 0;
        return NULL;
    }

    size_t capacity = tuple_count * 2;
    int* temp_elements = (int*)malloc(capacity * sizeof(int));
    if (temp_elements == NULL) {
        *out_count = 0;
        return NULL;
    }

    size_t num_elements = 0;
    for (size_t i = 0; i < tuple_count; i++) {
        temp_elements[num_elements++] = tuple_list[i].x;
        temp_elements[num_elements++] = tuple_list[i].y;
    }

    int* single_elements = (int*)malloc(capacity * sizeof(int));
    if (single_elements == NULL) {
        free(temp_elements);
        *out_count = 0;
        return NULL;
    }

    size_t single_count = 0;
    for (size_t i = 0; i < num_elements; i++) {
        int current = temp_elements[i];
        int count = 0;
        for (size_t j = 0; j < num_elements; j++) {
            if (temp_elements[j] == current) {
                count++;
            }
        }
        if (count == 1) {
            single_elements[single_count++] = current;
        }
    }

    free(temp_elements);
    *out_count = single_count;
    return single_elements;
}

int main(void) {
    Tuple tuples[] = {{1, 2}, {2, 3}, {4, 1}, {5, 6}};
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t out_count = 0;

    int* single_elements = extract_single_elements(tuples, tuple_count, &out_count);

    if (single_elements != NULL) {
        for (size_t i = 0; i < out_count; i++) {
            printf("%d ", single_elements[i]);
        }
        printf("\n");
        free(single_elements);
    }

    return 0;
}