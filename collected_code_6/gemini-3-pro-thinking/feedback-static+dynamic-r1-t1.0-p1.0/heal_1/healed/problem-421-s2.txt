#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN 1048576

static size_t secure_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char* concatenate_tuple(const char *const tuple[], size_t size, const char *delimiter);

char* concatenate_tuple(const char *const tuple[], size_t size, const char *delimiter) {
    if ((tuple == NULL && size > 0) || delimiter == NULL) {
        return NULL;
    }

    if (size == 0) {
        char *empty_str = (char *)malloc(1);
        if (empty_str == NULL) {
            return NULL;
        }
        empty_str[0] = '\0';
        return empty_str;
    }

    size_t delimiter_len = secure_strlen(delimiter, MAX_STRING_LEN);
    size_t total_len = 0;

    for (size_t i = 0; i < size; ++i) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        size_t len = secure_strlen(tuple[i], MAX_STRING_LEN);
        if (SIZE_MAX - total_len < len) {
            return NULL;
        }
        total_len += len;
    }
    
    if (size > 1) {
        size_t delim_total = (size - 1) * delimiter_len;
        if (SIZE_MAX / (size - 1) < delimiter_len || SIZE_MAX - total_len < delim_total) {
            return NULL;
        }
        total_len += delim_total;
    }

    if (SIZE_MAX - total_len < 1) {
        return NULL;
    }
    total_len += 1;

    char *result = (char *)malloc(total_len);
    if (result == NULL) {
        return NULL;
    }

    char *current_ptr = result;
    size_t remaining = total_len;

    for (size_t i = 0; i < size; ++i) {
        size_t element_len = secure_strlen(tuple[i], MAX_STRING_LEN);
        
        if (element_len > remaining) {
            free(result);
            return NULL;
        }
        
        memcpy(current_ptr, tuple[i], element_len);
        current_ptr += element_len;
        remaining -= element_len;
        
        if (i < size - 1) {
            if (delimiter_len > remaining) {
                free(result);
                return NULL;
            }
            
            memcpy(current_ptr, delimiter, delimiter_len);
            current_ptr += delimiter_len;
            remaining -= delimiter_len;
        }
    }
    
    if (remaining < 1) {
        free(result);
        return NULL;
    }
    
    *current_ptr = '\0';

    return result;
}

int main(void) {
    const char *const my_tuple[] = {"apple", "banana", "cherry", "date"};
    size_t tuple_size = sizeof(my_tuple) / sizeof(my_tuple[0]);
    const char *delimiter = " - ";

    char *concatenated_string = concatenate_tuple(my_tuple, tuple_size, delimiter);
    
    if (concatenated_string != NULL) {
        printf("%s\n", concatenated_string);
        free(concatenated_string);
        concatenated_string = NULL;
    } else {
        fprintf(stderr, "Error processing tuple concatenation\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}