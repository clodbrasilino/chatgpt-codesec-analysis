#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 4096

static size_t safe_strnlen(const char *s, size_t maxlen);
char* concatenate_strings(const char * const *list, size_t count);

static size_t safe_strnlen(const char *s, size_t maxlen) {
    const char *p = (const char *)memchr(s, '\0', maxlen);
    if (p) {
        return (size_t)(p - s);
    }
    return maxlen;
}

char* concatenate_strings(const char * const *list, size_t count) {
    if (!list) {
        return NULL;
    }

    size_t total_length = 0;
    size_t *lens = NULL;
    
    if (count > 0) {
        lens = (size_t *)malloc(count * sizeof(size_t));
        if (!lens) {
            return NULL;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (list[i]) {
            size_t len = safe_strnlen(list[i], MAX_STR_LEN);
            if (SIZE_MAX - total_length < len) {
                free(lens);
                return NULL;
            }
            lens[i] = len;
            total_length += len;
        } else {
            lens[i] = 0;
        }
    }

    char *result = (char *)malloc(total_length + 1);
    if (!result) {
        free(lens);
        return NULL;
    }

    char *current = result;
    size_t remaining = total_length + 1;

    for (size_t i = 0; i < count; ++i) {
        if (list[i] && lens[i] > 0) {
            if (lens[i] >= remaining) {
                free(result);
                free(lens);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(current, list[i], lens[i]);
            current += lens[i];
            remaining -= lens[i];
        }
    }
    *current = '\0';

    free(lens);
    return result;
}

int main(void) {
    const char * const list[] = {"This ", "is ", "a ", "concatenated ", "string."};
    size_t count = sizeof(list) / sizeof(list[0]);

    char *result = concatenate_strings(list, count);
    
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}