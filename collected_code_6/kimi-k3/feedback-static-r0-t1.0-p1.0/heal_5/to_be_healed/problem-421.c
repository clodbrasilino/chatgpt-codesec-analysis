#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    char **elements;
    size_t count;
} Tuple;

static bool is_valid_string(const char *str, size_t max_len) {
    if (str == NULL) {
        return false;
    }
    size_t i;
    for (i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            return true;
        }
    }
    return false;
}

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static bool safe_memcpy(char *dest, const char *src, size_t len, size_t dest_size) {
    if (dest == NULL || src == NULL) {
        return false;
    }
    if (len > dest_size) {
        return false;
    }
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, src, len);
    }
    return true;
}

char *tuple_join(const Tuple *tuple, const char *delimiter)
{
    size_t total_length;
    size_t delimiter_length;
    size_t i;
    char *result;
    char *current;
    const size_t MAX_STRING_LEN = 1024 * 1024;
    const size_t MAX_TOTAL_LEN = 10 * 1024 * 1024;

    if (tuple == NULL || delimiter == NULL) {
        return NULL;
    }

    if (!is_valid_string(delimiter, MAX_STRING_LEN)) {
        return NULL;
    }

    if (tuple->count == 0 || tuple->elements == NULL) {
        result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    if (tuple->count > SIZE_MAX / 2) {
        return NULL;
    }

    delimiter_length = safe_strlen(delimiter, MAX_STRING_LEN);
    total_length = 1;

    for (i = 0; i < tuple->count; i++) {
        size_t element_length;
        
        if (tuple->elements[i] == NULL) {
            return NULL;
        }
        
        if (!is_valid_string(tuple->elements[i], MAX_STRING_LEN)) {
            return NULL;
        }
        
        element_length = safe_strlen(tuple->elements[i], MAX_STRING_LEN);
        
        if (total_length > SIZE_MAX - element_length) {
            return NULL;
        }
        total_length += element_length;
        
        if (i > 0) {
            if (total_length > SIZE_MAX - delimiter_length) {
                return NULL;
            }
            total_length += delimiter_length;
        }
        
        if (total_length > MAX_TOTAL_LEN) {
            return NULL;
        }
    }

    result = malloc(total_length);
    if (result == NULL) {
        return NULL;
    }

    current = result;
    for (i = 0; i < tuple->count; i++) {
        size_t element_length;
        size_t remaining;

        if (i > 0) {
            remaining = total_length - (size_t)(current - result);
            if (delimiter_length >= remaining) {
                free(result);
                return NULL;
            }
            if (!safe_memcpy(current, delimiter, delimiter_length, remaining)) {
                free(result);
                return NULL;
            }
            current += delimiter_length;
        }

        element_length = safe_strlen(tuple->elements[i], MAX_STRING_LEN);
        remaining = total_length - (size_t)(current - result);
        
        if (element_length >= remaining) {
            free(result);
            return NULL;
        }
        
        if (!safe_memcpy(current, tuple->elements[i], element_length, remaining)) {
            free(result);
            return NULL;
        }
        current += element_length;
    }

    if ((size_t)(current - result) >= total_length) {
        free(result);
        return NULL;
    }
    
    *current = '\0';
    return result;
}

int main(void)
{
    char *data[] = {"apple", "banana", "cherry", "date"};
    Tuple tuple = {data, 4};
    char *joined;

    joined = tuple_join(&tuple, ", ");
    if (joined == NULL) {
        fprintf(stderr, "Failed to join tuple elements\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", joined);
    free(joined);

    return EXIT_SUCCESS;
}