#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate_list(const char *list[], size_t size) {
    if (list == NULL || size == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t *lens = malloc(size * sizeof(size_t));
    if (lens == NULL) {
        return NULL;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t len = strlen(list[i]);
            if (len > SIZE_MAX - total_length) {
                free(lens);
                return NULL;
            }
            total_length += len;
            lens[i] = len;
        } else {
            lens[i] = 0;
        }
    }

    if (total_length == SIZE_MAX) {
        free(lens);
        return NULL;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        free(lens);
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < size; i++) {
        if (lens[i] > 0) {
            size_t len = lens[i];
            if (len > total_length - offset) {
                free(result);
                free(lens);
                return NULL;
            }
            memcpy(result + offset, list[i], len);
            offset += len;
        }
    }
    
    result[offset] = '\0';
    free(lens);

    return result;
}

int main(void) {
    const char *my_list[] = {"Hello", ", ", "world", "!"};
    size_t size = sizeof(my_list) / sizeof(my_list[0]);

    char *concatenated = concatenate_list(my_list, size);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    }

    const char *empty_list[] = {NULL};
    char *empty_concat = concatenate_list(empty_list, 0);
    if (empty_concat != NULL) {
        printf("Empty: %s\n", empty_concat);
        free(empty_concat);
    }

    return 0;
}