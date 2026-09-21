#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

static size_t safe_strnlen(const char *s, size_t maxlen) {
    size_t len = 0;
    if (s == NULL) {
        return 0;
    }
    while (len < maxlen && s[len] != '\0') {
        len++;
    }
    return len;
}

char* concatenate_list(const char **list, size_t count) {
    size_t total_length = 0;
    size_t i;
    char *result;
    size_t offset = 0;

    if (list == NULL || count == 0) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len;
        if (list[i] == NULL) {
            return NULL;
        }
        
        len = safe_strnlen(list[i], SIZE_MAX - total_length);
        if (len == SIZE_MAX - total_length && list[i][len] != '\0') {
            return NULL;
        }
        
        if (total_length > SIZE_MAX - len) {
            return NULL;
        }
        
        total_length += len;
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    result = (char*)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len = safe_strnlen(list[i], total_length - offset);
        size_t remaining = total_length - offset;
        
        if (len > remaining) {
            free(result);
            return NULL;
        }
        
        if (len > 0) {
            if (offset + len > total_length) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + offset, list[i], len);
            offset += len;
        }
    }
    result[total_length] = '\0';

    return result;
}

int main(void) {
    const char *list[] = {"Hello", " ", "World", "!"};
    size_t count = sizeof(list) / sizeof(list[0]);
    char *concatenated;

    concatenated = concatenate_list(list, count);
    if (concatenated == NULL) {
        fprintf(stderr, "Error: Failed to concatenate strings\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", concatenated);

    free(concatenated);

    return EXIT_SUCCESS;
}