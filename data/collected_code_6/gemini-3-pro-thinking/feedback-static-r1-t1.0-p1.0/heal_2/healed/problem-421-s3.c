#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 4096

static size_t safe_strnlen(const char *str, size_t maxlen) {
    size_t len = 0;
    while (len < maxlen && str[len] != '\0') {
        len++;
    }
    return len;
}

char* concatenate_tuple(const char* const* tuple, size_t size, const char* delimiter) {
    size_t total_len = 0;
    size_t delim_len = 0;
    char* result = NULL;
    char* current = NULL;
    size_t i = 0;
    size_t remaining = 0;

    if (!tuple || !delimiter) {
        return NULL;
    }

    if (size == 0) {
        result = malloc(1);
        if (result) {
            result[0] = '\0';
        }
        return result;
    }

    delim_len = safe_strnlen(delimiter, MAX_STR_LEN);

    for (i = 0; i < size; ++i) {
        size_t len = 0;
        if (!tuple[i]) {
            return NULL;
        }
        len = safe_strnlen(tuple[i], MAX_STR_LEN);
        if (total_len > SIZE_MAX - len) {
            return NULL;
        }
        total_len += len;
    }

    if (size > 0) {
        size_t delim_total = 0;
        if (size - 1 > 0) {
            if (delim_len > SIZE_MAX / (size - 1)) {
                return NULL;
            }
            delim_total = delim_len * (size - 1);
        }
        if (total_len > SIZE_MAX - delim_total - 1) {
            return NULL;
        }
        total_len += delim_total + 1;
    }

    result = malloc(total_len);
    if (!result) {
        return NULL;
    }

    current = result;
    remaining = total_len;

    for (i = 0; i < size; ++i) {
        const char* src = tuple[i];
        while (*src != '\0' && remaining > 1) {
            *current++ = *src++;
            remaining--;
        }

        if (i < size - 1) {
            const char* d = delimiter;
            while (*d != '\0' && remaining > 1) {
                *current++ = *d++;
                remaining--;
            }
        }
    }
    *current = '\0';

    return result;
}

int main(void) {
    const char* my_tuple[] = {"apple", "banana", "cherry", "date"};
    size_t tuple_size = sizeof(my_tuple) / sizeof(my_tuple[0]);
    const char* delimiter = " | ";
    
    char* concatenated_string = concatenate_tuple(my_tuple, tuple_size, delimiter);

    if (concatenated_string) {
        printf("%s\n", concatenated_string);
        free(concatenated_string);
        concatenated_string = NULL;
    } else {
        fprintf(stderr, "Error: Memory allocation failed or invalid input provided.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}