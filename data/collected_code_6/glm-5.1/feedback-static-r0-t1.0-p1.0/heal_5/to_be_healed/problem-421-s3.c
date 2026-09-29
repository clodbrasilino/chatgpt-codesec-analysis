#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* tuple_concat(const char** tuple, size_t size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t total_len = 0;
    size_t delim_len = strnlen(delimiter, SIZE_MAX);

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        total_len += strnlen(tuple[i], SIZE_MAX);
        if (i < size - 1) {
            total_len += delim_len;
        }
    }

    char* result = (char*)malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }

    char* ptr = result;
    size_t remaining = total_len + 1;

    for (size_t i = 0; i < size; i++) {
        size_t item_len = strnlen(tuple[i], SIZE_MAX);
        size_t bytes_to_copy = item_len < remaining ? item_len : remaining;
        if (bytes_to_copy > 0) {
            /* Possible weaknesses found:
             *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
             *  did you mean 'memcpy'?
             */
            memcpy_s(ptr, remaining, tuple[i], bytes_to_copy);
            ptr += bytes_to_copy;
            remaining -= bytes_to_copy;
        }
        
        if (i < size - 1) {
            bytes_to_copy = delim_len < remaining ? delim_len : remaining;
            if (bytes_to_copy > 0) {
                /* Possible weaknesses found:
                 *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 */
                memcpy_s(ptr, remaining, delimiter, bytes_to_copy);
                ptr += bytes_to_copy;
                remaining -= bytes_to_copy;
            }
        }
    }

    *ptr = '\0';

    return result;
}

int main(void) {
    const char* tuple[] = {"C", "is", "a", "powerful", "language"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    const char* delimiter = "-";

    char* concatenated = tuple_concat(tuple, size, delimiter);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
        concatenated = NULL;
    }

    return 0;
}