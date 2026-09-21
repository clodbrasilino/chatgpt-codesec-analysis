#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 4096

static size_t safe_strlen(const char *s, size_t max) {
    const char *p = memchr(s, '\0', max);
    return p ? (size_t)(p - s) : max;
}

char* concatenate_list(const char* const* list, size_t count) {
    size_t total_length = 0;
    char* result;
    char* current;
    size_t i;
    size_t j;
    size_t len;
    size_t remaining;

    if (list == NULL && count > 0) {
        return NULL;
    }

    for (i = 0; i < count; ++i) {
        if (list[i] != NULL) {
            len = safe_strlen(list[i], MAX_STR_LEN);
            if (SIZE_MAX - total_length < len) {
                return NULL;
            }
            total_length += len;
        }
    }

    if (SIZE_MAX - total_length < 1) {
        return NULL;
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    current = result;
    remaining = total_length + 1;

    for (i = 0; i < count; ++i) {
        if (list[i] != NULL) {
            len = safe_strlen(list[i], MAX_STR_LEN);
            if (len >= remaining) {
                len = remaining - 1;
            }
            if (len > 0) {
                for (j = 0; j < len; ++j) {
                    current[j] = list[i][j];
                }
                current += len;
                remaining -= len;
            }
        }
    }
    *current = '\0';

    return result;
}

int main(void) {
    const char* elements[] = {"Concatenating ", "a ", "list ", "of ", "strings ", "safely."};
    size_t count = sizeof(elements) / sizeof(elements[0]);
    char* concatenated_string;

    concatenated_string = concatenate_list(elements, count);

    if (concatenated_string != NULL) {
        printf("%s\n", concatenated_string);
        free(concatenated_string);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Error: Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }
}