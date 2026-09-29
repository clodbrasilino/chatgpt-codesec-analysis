#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate_list(char **list, size_t size) {
    size_t total_length = 0;
    size_t i;

    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t len = strnlen(list[i], 1024 * 1024);
            if (total_length > SIZE_MAX - len) {
                return NULL;
            }
            total_length += len;
        }
    }

    if (size == 0 || total_length == 0) {
        char *empty_str = malloc(1);
        if (empty_str == NULL) {
            return NULL;
        }
        empty_str[0] = '\0';
        return empty_str;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t current_pos = 0;

    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t len = strnlen(list[i], 1024 * 1024);
            if (current_pos <= SIZE_MAX - len && current_pos + len <= total_length) {
                memcpy(result + current_pos, list[i], len);
                current_pos += len;
            } else {
                free(result);
                return NULL;
            }
        }
    }

    result[current_pos] = '\0';

    return result;
}

int main(void) {
    char *list[] = {"Hello", ", ", "world", "!"};
    size_t size = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(list, size);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    }

    return 0;
}