#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_tuple(const char* tuple[], size_t size, const char* delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t total_len = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delim_len = strlen(delimiter);

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
        if (item_len > 0) {
            size_t to_copy = item_len < remaining ? item_len : remaining;
            /* Possible weaknesses found:
             *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
             *  did you mean 'memcpy'?
             */
            memcpy_s(ptr, remaining, tuple[i], to_copy);
            ptr += to_copy;
            remaining -= to_copy;
        }
        
        if (i < size - 1 && remaining > 0) {
            size_t to_copy = delim_len < remaining ? delim_len : remaining;
            /* Possible weaknesses found:
             *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            memcpy_s(ptr, remaining, delimiter, to_copy);
            ptr += to_copy;
            remaining -= to_copy;
        }
    }

    if (remaining > 0) {
        *ptr = '\0';
    } else {
        result[total_len] = '\0';
    }

    return result;
}

int main(void) {
    const char* my_tuple[] = {"apple", "banana", "cherry"};
    size_t tuple_size = sizeof(my_tuple) / sizeof(my_tuple[0]);
    const char* delimiter = ", ";

    char* concatenated = concatenate_tuple(my_tuple, tuple_size, delimiter);
    
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
        concatenated = NULL;
    }

    return 0;
}