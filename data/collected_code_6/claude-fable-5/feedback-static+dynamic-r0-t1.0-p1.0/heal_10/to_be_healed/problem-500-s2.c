#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN 4096U

char *concatenate_list(const char *const *list, size_t count)
{
    size_t total = 0;
    size_t i;
    size_t *lengths = NULL;
    size_t remaining;
    size_t capacity;
    char *result = NULL;
    char *pos = NULL;

    if (list == NULL) {
        return NULL;
    }

    if (count == 0) {
        result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    if (count > SIZE_MAX / sizeof(size_t)) {
        return NULL;
    }

    lengths = malloc(count * sizeof(size_t));
    if (lengths == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len;

        if (list[i] == NULL) {
            free(lengths);
            return NULL;
        }

        len = strnlen(list[i], MAX_STRING_LEN);
        if (len >= MAX_STRING_LEN) {
            free(lengths);
            return NULL;
        }

        if (len > SIZE_MAX - 1 - total) {
            free(lengths);
            return NULL;
        }

        lengths[i] = len;
        total += len;
    }

    capacity = total + 1;
    result = malloc(capacity);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    pos = result;
    remaining = total;
    for (i = 0; i < count; i++) {
        size_t verify_len;
        size_t used;

        used = (size_t)(pos - result);
        if (used > capacity - 1 || lengths[i] > (capacity - 1) - used) {
            free(lengths);
            free(result);
            return NULL;
        }

        if (lengths[i] > remaining) {
            free(lengths);
            free(result);
            return NULL;
        }

        verify_len = strnlen(list[i], MAX_STRING_LEN);
        if (verify_len != lengths[i]) {
            free(lengths);
            free(result);
            return NULL;
        }

        if (lengths[i] > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(pos, list[i], lengths[i]);
        }
        pos += lengths[i];
        remaining -= lengths[i];
    }

    if (remaining != 0) {
        free(lengths);
        free(result);
        return NULL;
    }

    if ((size_t)(pos - result) >= capacity) {
        free(lengths);
        free(result);
        return NULL;
    }

    *pos = '\0';

    free(lengths);
    return result;
}

int main(void)
{
    const char *const list[] = { "Hello", ", ", "world", "!" };
    size_t count = sizeof(list) / sizeof(list[0]);
    char *joined = concatenate_list(list, count);

    if (joined == NULL) {
        fprintf(stderr, "Concatenation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", joined) < 0) {
        free(joined);
        return EXIT_FAILURE;
    }

    free(joined);
    return EXIT_SUCCESS;
}