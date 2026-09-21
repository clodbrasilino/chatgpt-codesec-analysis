#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_list(char **list, size_t size) {
    size_t total_length = 1;
    size_t i;
    size_t current_len;

    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t len = strlen(list[i]);
            if (total_length > SIZE_MAX - len) {
                return NULL;
            }
            total_length += len;
        }
    }

    char *result = malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    current_len = 0;

    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t seg_len = strlen(list[i]);
            if (seg_len > 0 && current_len + seg_len < total_length) {
                memcpy(result + current_len, list[i], seg_len);
                current_len += seg_len;
            }
            result[current_len] = '\0';
        }
    }

    return result;
}

int main(void) {
    char *list[] = {"Hello", ", ", "world", "!"};
    size_t size = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(list, size);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    return 0;
}