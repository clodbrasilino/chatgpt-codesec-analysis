#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char* tuple[], size_t size, size_t max_str_len, const char* delimiter, size_t max_delim_len) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t total_len = 0;
    size_t delim_len = strnlen(delimiter, max_delim_len);

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        size_t item_len = strnlen(tuple[i], max_str_len);
        if (total_len > SIZE_MAX - item_len) {
            return NULL;
        }
        total_len += item_len;
        if (i < size - 1) {
            if (total_len > SIZE_MAX - delim_len) {
                return NULL;
            }
            total_len += delim_len;
        }
    }

    if (total_len == SIZE_MAX) {
        return NULL;
    }

    char* result = (char*)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t current_pos = 0;
    size_t remaining = total_len;

    for (size_t i = 0; i < size; i++) {
        size_t item_len = strnlen(tuple[i], max_str_len);
        if (item_len > remaining) {
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
         *  did you mean 'memcpy'?
         *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        errno_t err = memcpy_s(result + current_pos, remaining, tuple[i], item_len);
        if (err != 0) {
            free(result);
            return NULL;
        }
        current_pos += item_len;
        remaining -= item_len;
        
        if (i < size - 1) {
            if (delim_len > remaining) {
                free(result);
                return NULL;
            }
            err = memcpy_s(result + current_pos, remaining, delimiter, delim_len);
            if (err != 0) {
                free(result);
                return NULL;
            }
            current_pos += delim_len;
            remaining -= delim_len;
        }
    }

    if (remaining != 0) {
        free(result);
        return NULL;
    }

    result[current_pos] = '\0';
 /* Possible weaknesses found:
  *  'memcpy' declared here
  */

    return result;
}

int main(void) {
    const char* tuple[] = {"apple", "banana", "cherry"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = ", ";

    char* result = concatenate_tuple(tuple, size, 256, delimiter, 16);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}