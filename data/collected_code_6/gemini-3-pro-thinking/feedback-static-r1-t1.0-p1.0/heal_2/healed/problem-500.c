#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT_LEN 4096
#define MAX_TOTAL_LEN 1048576

static size_t get_safe_len(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char* concatenate_list(const char* const* list, size_t count) {
    size_t total_length = 0;
    char* result;
    char* current;
    size_t i, j;
    size_t len;
    size_t remaining;

    if (list == NULL && count > 0) {
        return NULL;
    }

    for (i = 0; i < count; ++i) {
        if (list[i] != NULL) {
            len = get_safe_len(list[i], MAX_ELEMENT_LEN);
            if (MAX_TOTAL_LEN - total_length < len) {
                return NULL;
            }
            total_length += len;
        }
    }

    result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    current = result;
    remaining = total_length + 1;

    for (i = 0; i < count; ++i) {
        if (list[i] != NULL) {
            len = get_safe_len(list[i], MAX_ELEMENT_LEN);
            if (len < remaining) {
                for (j = 0; j < len; ++j) {
                    current[j] = list[i][j];
                }
                current += len;
                remaining -= len;
            } else {
                free(result);
                return NULL;
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