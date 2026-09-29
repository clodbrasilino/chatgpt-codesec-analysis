#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int *extract_contiguous(const int *list, size_t list_len, size_t start, size_t count) {
    if (list == NULL || count == 0) {
        return NULL;
    }

    if (start >= list_len) {
        return NULL;
    }

    if (list_len - start < count) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *result = (int *)malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, list + start, count * sizeof(int));

    return result;
}

int main(void) {
    int list[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    size_t list_len = sizeof(list) / sizeof(list[0]);
    size_t start = 2;
    size_t count = 4;

    int *extracted = extract_contiguous(list, list_len, start, count);
    if (extracted != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%d ", extracted[i]);
        }
        printf("\n");
        free(extracted);
    } else {
        printf("Extraction failed.\n");
    }

    const int *invalid_extract = extract_contiguous(list, list_len, 8, 5);
    if (invalid_extract == NULL) {
        printf("Out of bounds correctly rejected.\n");
    }

    return 0;
}