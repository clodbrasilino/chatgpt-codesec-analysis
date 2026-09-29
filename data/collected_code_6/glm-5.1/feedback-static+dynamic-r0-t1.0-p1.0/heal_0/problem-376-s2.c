#include <stdio.h>
#include <stdlib.h>

int* remove_duplicates(const int* tuple, size_t size, int custom_value, size_t* out_size) {
    if (tuple == NULL || out_size == NULL) {
        return NULL;
    }

    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    size_t* counts = (size_t*)calloc(size, sizeof(size_t));
    if (counts == NULL) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        counts[i] = 1;
        for (size_t j = 0; j < size; j++) {
            if (i != j && tuple[i] == tuple[j]) {
                counts[i]++;
            }
        }
    }

    *out_size = size;
    for (size_t i = 0; i < size; i++) {
        if (counts[i] > 1) {
            result[i] = custom_value;
        } else {
            result[i] = tuple[i];
        }
    }

    free(counts);
    return result;
}

int main(void) {
    int tuple[] = {1, 2, 3, 2, 4, 1, 5};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    size_t out_size;
    
    int* result = remove_duplicates(tuple, size, -1, &out_size);
    
    if (result != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}