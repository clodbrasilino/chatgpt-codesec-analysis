#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t safe_strnlen(const char *s, size_t maxlen) {
    size_t len = 0;
    while (len < maxlen && s[len] != '\0') {
        len++;
    }
    return len;
}

char* concatenate_tuple(const char** tuple, size_t tuple_size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || tuple_size == 0) {
        return NULL;
    }

    size_t max_str_len = 8192;
    size_t total_length = 0;
    size_t delimiter_length = safe_strnlen(delimiter, max_str_len);

    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            size_t len = safe_strnlen(tuple[i], max_str_len);
            if (total_length > (size_t)-1 - len) {
                return NULL;
            }
            total_length += len;
        }
    }

    size_t delim_total = delimiter_length * (tuple_size - 1);
    if (total_length > (size_t)-1 - delim_total - 1) {
        return NULL;
    }
    total_length += delim_total + 1;

    char* result = (char*)malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;

    for (size_t i = 0; i < tuple_size; ++i) {
        if (tuple[i] != NULL) {
            size_t len = safe_strnlen(tuple[i], max_str_len);
            if (total_length - offset > len) {
                memcpy(result + offset, tuple[i], len);
                offset += len;
            }
        }
        if (i < tuple_size - 1) {
            if (total_length - offset > delimiter_length) {
                memcpy(result + offset, delimiter, delimiter_length);
                offset += delimiter_length;
            }
        }
    }
    
    result[offset] = '\0';

    return result;
}

int main(void) {
    const char* tuple[] = {"apple", "banana", "cherry", "date"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = ", ";

    char* concatenated_string = concatenate_tuple(tuple, tuple_size, delimiter);

    if (concatenated_string != NULL) {
        printf("%s\n", concatenated_string);
        free(concatenated_string);
    } else {
        fprintf(stderr, "Failed to concatenate tuple.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}