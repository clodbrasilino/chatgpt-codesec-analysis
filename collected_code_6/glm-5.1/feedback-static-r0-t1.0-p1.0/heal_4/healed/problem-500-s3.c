#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_list(char **list, size_t size) {
    size_t total_length = 1;
    size_t i;
    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t len = strlen(list[i]);
            if (total_length > SIZE_MAX - len) {
                return NULL;
            }
            total_length += len;
        }
    }

    char *result = (char *)malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t current_pos = 0;

    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t remaining = total_length - current_pos;
            size_t len = strnlen(list[i], remaining);
            if (len > 0 && current_pos + len <= total_length - 1) {
                memcpy(result + current_pos, list[i], len);
                current_pos += len;
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
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    return 0;
}