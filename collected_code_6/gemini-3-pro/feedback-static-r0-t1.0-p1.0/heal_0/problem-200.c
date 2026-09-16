#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int* find_max_indices(const int* list, size_t size, size_t* count) {
    if (list == NULL || size == 0 || count == NULL) {
        if (count != NULL) {
            *count = 0;
        }
        return NULL;
    }

    int max_val = INT_MIN;
    size_t local_count = 0;

    for (size_t i = 0; i < size; ++i) {
        if (list[i] > max_val) {
            max_val = list[i];
            local_count = 1;
        } else if (list[i] == max_val) {
            local_count++;
        }
    }

    int* indices = (int*)malloc(local_count * sizeof(int));
    if (indices == NULL) {
        *count = 0;
        return NULL;
    }

    size_t index_pos = 0;
    for (size_t i = 0; i < size; ++i) {
        if (list[i] == max_val) {
            indices[index_pos++] = (int)i;
        }
    }

    *count = local_count;
    return indices;
}

int main(void) {
    int list[] = {1, 5, 3, 5, 2, 5, 4};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t count = 0;

    int* max_indices = find_max_indices(list, size, &count);

    if (max_indices != NULL) {
        for (size_t i = 0; i < count; ++i) {
            printf("%d ", max_indices[i]);
        }
        printf("\n");

        free(max_indices);
    } else {
        printf("Error or no elements found.\n");
    }

    return 0;
}