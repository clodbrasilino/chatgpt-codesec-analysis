#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 4096

static size_t safe_strlen(const char *str, size_t max_len);
char *concatenate_tuple(const char **tuple, size_t num_elements, const char *delimiter);

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *concatenate_tuple(const char **tuple, size_t num_elements, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || num_elements == 0) {
        return NULL;
    }

    size_t delim_len = safe_strlen(delimiter, MAX_STR_LEN);
    size_t total_length = 0;

    for (size_t i = 0; i < num_elements; ++i) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        size_t len = safe_strlen(tuple[i], MAX_STR_LEN);
        if (total_length > SIZE_MAX - len) {
            return NULL;
        }
        total_length += len;
    }

    if (num_elements > 1) {
        size_t delim_total = (num_elements - 1) * delim_len;
        if (total_length > SIZE_MAX - delim_total - 1) {
            return NULL;
        }
        total_length += delim_total;
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }
    total_length += 1;

    char *result = (char *)malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    char *current_pos = result;
    size_t remaining = total_length;
    result[0] = '\0';

    for (size_t i = 0; i < num_elements; ++i) {
        int written = snprintf(current_pos, remaining, "%s", tuple[i]);
        if (written < 0 || (size_t)written >= remaining) {
            free(result);
            return NULL;
        }
        current_pos += written;
        remaining -= (size_t)written;

        if (i < num_elements - 1) {
            written = snprintf(current_pos, remaining, "%s", delimiter);
            if (written < 0 || (size_t)written >= remaining) {
                free(result);
                return NULL;
            }
            current_pos += written;
            remaining -= (size_t)written;
        }
    }

    return result;
}

int main(void) {
    const char *my_tuple[] = {"apple", "banana", "cherry", "date"};
    size_t num_elements = sizeof(my_tuple) / sizeof(my_tuple[0]);
    const char *delimiter = ", ";

    char *result = concatenate_tuple(my_tuple, num_elements, delimiter);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
        result = NULL;
    } else {
        fprintf(stderr, "Error: Memory allocation failed or invalid input provided.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}