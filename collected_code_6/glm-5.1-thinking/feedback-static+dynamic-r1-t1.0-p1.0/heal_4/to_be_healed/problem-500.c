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

    size_t total_length = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t max_len = SIZE_MAX - total_length;
            total_length += strnlen(list[i], max_len);
        }
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char *current = result;
    size_t remaining = total_length + 1;
    for (size_t i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t len = strnlen(list[i], remaining - 1);
            size_t copy_len = (len < remaining) ? len : remaining;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(current, list[i], copy_len);
            current += copy_len;
            remaining -= copy_len;
        }
    }
    *current = '\0';

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