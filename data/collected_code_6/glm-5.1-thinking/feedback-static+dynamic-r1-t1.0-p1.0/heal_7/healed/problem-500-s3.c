#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate_list(size_t count, const char * const *list) {
    if (count > 0 && list == NULL) {
        return NULL;
    }

    size_t total_length = 0;
    size_t *lengths = NULL;

    if (count > 0) {
        if (count > SIZE_MAX / sizeof(size_t)) {
            return NULL;
        }
        lengths = malloc(count * sizeof(size_t));
        if (lengths == NULL) {
            return NULL;
        }
    }

    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t len = strlen(list[i]);
            if (len > SIZE_MAX - total_length) {
                free(lengths);
                return NULL;
            }
            lengths[i] = len;
            total_length += len;
        } else {
            lengths[i] = 0;
        }
    }

    if (total_length == SIZE_MAX) {
        free(lengths);
        return NULL;
    }

    size_t alloc_size = total_length + 1;

    char *result = malloc(alloc_size);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < count; i++) {
        size_t len = lengths[i];
        if (len > 0) {
            if (len > alloc_size - offset) {
                free(result);
                free(lengths);
                return NULL;
            }
            memcpy(result + offset, list[i], len);
            offset += len;
        }
    }
    
    result[offset] = '\0';
    free(lengths);

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