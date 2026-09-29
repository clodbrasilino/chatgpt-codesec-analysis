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

    if (size > SIZE_MAX / sizeof(size_t)) {
        return NULL;
    }

    size_t total_length = 0;
    size_t *lengths = malloc(size * sizeof(size_t));
    if (lengths == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t max_len = SIZE_MAX - total_length;
            const char *end = memchr(list[i], '\0', max_len);
            if (end == NULL) {
                free(lengths);
                return NULL;
            }
            size_t len = end - list[i];
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

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    char *current = result;
    for (size_t i = 0; i < size; i++) {
        if (lengths[i] > 0) {
            size_t remaining = total_length - (current - result);
            if (lengths[i] > remaining) {
                free(lengths);
                free(result);
                return NULL;
            }
            memcpy(current, list[i], lengths[i]);
            current += lengths[i];
        }
    }
    *current = '\0';

    free(lengths);
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