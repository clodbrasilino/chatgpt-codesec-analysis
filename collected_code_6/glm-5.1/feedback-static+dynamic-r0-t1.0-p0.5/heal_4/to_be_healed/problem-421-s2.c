#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char* tuple[], size_t size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t total_length = 0;
    size_t delimiter_length = strnlen(delimiter, SIZE_MAX);

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        total_length += strnlen(tuple[i], SIZE_MAX);
        if (i < size - 1) {
            total_length += delimiter_length;
        }
    }

    char* result = (char*)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char* ptr = result;
    size_t remaining = total_length + 1;

    for (size_t i = 0; i < size; i++) {
        size_t item_len = strnlen(tuple[i], remaining);
        size_t bytes_to_copy = item_len < remaining ? item_len : remaining - 1;
        if (bytes_to_copy > 0) {
            /* Possible weaknesses found:
             *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
             *  did you mean 'memcpy'?
             *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            memcpy_s(ptr, remaining, tuple[i], bytes_to_copy);
            ptr += bytes_to_copy;
            remaining -= bytes_to_copy;
        }
        
        if (i < size - 1 && remaining > 1) {
            size_t delim_bytes = delimiter_length < remaining ? delimiter_length : remaining - 1;
            if (delim_bytes > 0) {
                /* Possible weaknesses found:
                 *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 */
                memcpy_s(ptr, remaining, delimiter, delim_bytes);
                ptr += delim_bytes;
                remaining -= delim_bytes;
            }
        }
    }

    *ptr = '\0';

    return result;
}

int main(void) {
    const char* tuple[] = {"apple", "banana", "cherry"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = ", ";

    char* result = concatenate_tuple(tuple, size, delimiter);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}