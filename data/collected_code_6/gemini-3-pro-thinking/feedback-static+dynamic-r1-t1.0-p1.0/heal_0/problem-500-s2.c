#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_strings(const char **list, size_t count);

char *concatenate_strings(const char **list, size_t count) {
    size_t total_length = 0;
    char *result = NULL;
    char *current = NULL;
    size_t i = 0;

    if (list == NULL && count > 0) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t len = strlen(list[i]);
            if (total_length + len < total_length) {
                return NULL;
            }
            total_length += len;
        }
    }

    if (total_length == (size_t)-1) {
        return NULL;
    }

    result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    current = result;
    for (i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t len = strlen(list[i]);
            memcpy(current, list[i], len);
            current += len;
        }
    }
    *current = '\0';

    return result;
}

int main(void) {
    const char *my_list[] = {"This ", "is ", "a ", "concatenated ", "string."};
    size_t count = sizeof(my_list) / sizeof(my_list[0]);
    char *result = NULL;

    result = concatenate_strings(my_list, count);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
        result = NULL;
    } else {
        fprintf(stderr, "Failed to concatenate strings.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}