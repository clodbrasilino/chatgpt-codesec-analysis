#include <stdio.h>
#include <stdlib.h>

size_t* find_min_indices(const int* list, size_t size, size_t* out_count) {
    if (list == NULL || out_count == NULL || size == 0) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    int min_val = list[0];
    size_t count = 1;

    for (size_t i = 1; i < size; ++i) {
        if (list[i] < min_val) {
            min_val = list[i];
            count = 1;
        } else if (list[i] == min_val) {
            count++;
        }
    }

    size_t* indices = (size_t*)malloc(count * sizeof(size_t));
    if (indices == NULL) {
        *out_count = 0;
        return NULL;
    }

    size_t index_pos = 0;
    for (size_t i = 0; i < size; ++i) {
        if (list[i] == min_val) {
            indices[index_pos] = i;
            index_pos++;
        }
    }

    *out_count = count;
    return indices;
}

int main(void) {
    const int data[] = {8, 3, 5, 3, 9, 7, 3, 10};
    size_t size = sizeof(data) / sizeof(data[0]);
    size_t count = 0;

    size_t* indices = find_min_indices(data, size, &count);

    if (indices != NULL) {
        for (size_t i = 0; i < count; ++i) {
            printf("%zu\n", indices[i]);
        }
        free(indices);
        indices = NULL;
    }

    return 0;
}