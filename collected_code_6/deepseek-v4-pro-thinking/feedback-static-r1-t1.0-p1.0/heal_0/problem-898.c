#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int *extract_elements(const int *list, size_t list_size, size_t start, size_t count) {
    if (list == NULL || list_size == 0 || start >= list_size || count == 0 || count > list_size - start) {
        return NULL;
    }
    if (count > SIZE_MAX / sizeof(*list)) {
        return NULL;
    }
    int *result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }
    memcpy(result, list + start, count * sizeof(*result));
    return result;
}

int main(void) {
    int list[] = {10, 20, 30, 40, 50, 60};
    size_t start = 2;
    size_t count = 3;
    int *extracted = extract_elements(list, sizeof(list) / sizeof(list[0]), start, count);

    if (extracted == NULL) {
        fprintf(stderr, "Error: unable to extract elements\n");
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%d ", extracted[i]);
    }
    printf("\n");

    free(extracted);
    return 0;
}