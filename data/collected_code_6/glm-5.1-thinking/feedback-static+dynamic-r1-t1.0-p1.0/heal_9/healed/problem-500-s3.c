#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate_list(size_t count, const char * const *list) {
    if (count > 0 && list == NULL) {
        return NULL;
    }

    size_t total_length = 0;

    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t max_search = SIZE_MAX - total_length;
            const char *end = memchr(list[i], '\0', max_search);
            if (end == NULL) {
                return NULL;
            }
            total_length += (size_t)(end - list[i]);
        }
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    size_t alloc_size = total_length + 1;
    char *result = malloc(alloc_size);

    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t max_search = alloc_size - offset;
            const char *end = memchr(list[i], '\0', max_search);
            if (end == NULL) {
                free(result);
                return NULL;
            }
            size_t len = end - list[i];
            memcpy(result + offset, list[i], len);
            offset += len;
        }
    }

    result[offset] = '\0';
    return result;
}

int main(void) {
    const char *list[] = {"Hello", ", ", "world", "!"};
    size_t count = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(count, list);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}