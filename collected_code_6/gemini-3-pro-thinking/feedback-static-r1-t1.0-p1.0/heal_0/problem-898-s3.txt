#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int* extract_elements(const int *source, size_t source_len, size_t start_index, size_t count) {
    if (source == NULL) {
        return NULL;
    }
    
    if (count == 0) {
        return NULL;
    }
    
    if (start_index >= source_len) {
        return NULL;
    }
    
    if (source_len - start_index < count) {
        return NULL;
    }

    int *extracted = (int *)malloc(count * sizeof(int));
    if (extracted == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        extracted[i] = source[start_index + i];
    }

    return extracted;
}

int main(void) {
    int original_list[] = {15, 22, 37, 41, 59, 64, 78, 83, 91};
    size_t source_len = sizeof(original_list) / sizeof(original_list[0]);
    
    size_t start_index = 2;
    size_t count = 4;

    int *result = extract_elements(original_list, source_len, start_index, count);

    if (result != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%d\n", result[i]);
        }
        free(result);
    }

    return 0;
}