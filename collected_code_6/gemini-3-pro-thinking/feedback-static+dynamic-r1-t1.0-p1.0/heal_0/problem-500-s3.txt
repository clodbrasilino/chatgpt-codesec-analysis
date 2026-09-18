#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_strings(const char * const *list, size_t count);

char* concatenate_strings(const char * const *list, size_t count) {
    if (!list) {
        return NULL;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < count; ++i) {
        if (list[i]) {
            total_length += strlen(list[i]);
        }
    }

    char *result = malloc(total_length + 1);
    if (!result) {
        return NULL;
    }

    char *current = result;
    for (size_t i = 0; i < count; ++i) {
        if (list[i]) {
            size_t len = strlen(list[i]);
            memcpy(current, list[i], len);
            current += len;
        }
    }
    *current = '\0';

    return result;
}

int main(void) {
    const char * const list[] = {"This ", "is ", "a ", "concatenated ", "string."};
    size_t count = sizeof(list) / sizeof(list[0]);

    char *result = concatenate_strings(list, count);
    
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}