#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static size_t safe_strlen(const char *str) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < SIZE_MAX && str[len] != '\0') {
        len++;
    }
    return len;
}

static void* safe_memcpy(void *dest, const void *src, size_t n, size_t dest_capacity) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }
    if (n == 0) {
        return dest;
    }
    if (n > dest_capacity) {
        return NULL;
    }
    if (dest == src) {
        return dest;
    }
    if ((uintptr_t)dest < (uintptr_t)src + n && (uintptr_t)src < (uintptr_t)dest + n) {
        return memmove(dest, src, n);
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    return memcpy(dest, src, n);
}

char *concat_tuple(char **tuple, size_t size, const char *delimiter) {
    if (tuple == NULL || delimiter == NULL || size == 0) {
        return NULL;
    }

    size_t delim_length = safe_strlen(delimiter);
    size_t total_length = 0;

    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        size_t len = safe_strlen(tuple[i]);
        if (total_length > SIZE_MAX - len) {
            return NULL;
        }
        total_length += len;
        if (i < size - 1) {
            if (total_length > SIZE_MAX - delim_length) {
                return NULL;
            }
            total_length += delim_length;
        }
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    char *ptr = result;
    size_t remaining = total_length;

    for (size_t i = 0; i < size; i++) {
        size_t len = safe_strlen(tuple[i]);
        if (len > remaining) {
            free(result);
            return NULL;
        }
        if (safe_memcpy(ptr, tuple[i], len, remaining) == NULL) {
            free(result);
            return NULL;
        }
        ptr += len;
        remaining -= len;

        if (i < size - 1) {
            if (delim_length > remaining) {
                free(result);
                return NULL;
            }
            if (safe_memcpy(ptr, delimiter, delim_length, remaining) == NULL) {
                free(result);
                return NULL;
            }
            ptr += delim_length;
            remaining -= delim_length;
        }
    }

    *ptr = '\0';

    return result;
}

int main(void) {
    char *tuple[] = {"Hello", "world", "from", "C"};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    char *result = concat_tuple(tuple, size, " ");

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}