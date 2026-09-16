#include <stdio.h>
#include <stdlib.h>

int* find_max_indices(const int* list, size_t length, size_t* out_count) {
    if (list == NULL || length == 0 || out_count == NULL) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    int max_val = list[0];
    size_t count = 1;

    for (size_t i = 1; i < length; ++i) {
        if (list[i] > max_val) {
            max_val = list[i];
            count = 1;
        } else if (list[i] == max_val) {
            count++;
        }
    }

    int* indices = (int*)malloc(count * sizeof(int));
    if (indices == NULL) {
        *out_count = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < length; ++i) {
        if (list[i] == max_val) {
            indices[index++] = (int)i;
        }
    }

    *out_count = count;
    return indices;
}

int main(void) {
    int list[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9};
    size_t length = sizeof(list) / sizeof(list[0]);
    size_t count = 0;

    int* max_indices = find_max_indices(list, length, &count);

    if (max_indices != NULL) {
        for (size_t i = 0; i < count; ++i) {
            printf("%d ", max_indices[i]);
        }
        printf("\n");
        free(max_indices);
    }

    return 0;
}