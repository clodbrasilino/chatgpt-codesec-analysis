#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

static bool append_text(char **result, size_t *length, size_t *capacity, const char *text, size_t text_len) {
    if (text_len > (size_t)-1 - *length) {
        free(*result);
        *result = NULL;
        *length = 0;
        *capacity = 0;
        return false;
    }

    size_t needed = *length + text_len;
    if (needed == (size_t)-1) {
        free(*result);
        *result = NULL;
        *length = 0;
        *capacity = 0;
        return false;
    }
    needed += 1;

    if (needed > *capacity) {
        size_t new_capacity = *capacity;
        if (new_capacity == 0) {
            new_capacity = 1;
        }

        while (new_capacity < needed) {
            if (new_capacity > (size_t)-1 / 2) {
                new_capacity = needed;
                break;
            }
            new_capacity *= 2;
        }

        char *new_result = realloc(*result, new_capacity);
        if (new_result == NULL) {
            free(*result);
            *result = NULL;
            *length = 0;
            *capacity = 0;
            return false;
        }

        *result = new_result;
        *capacity = new_capacity;
    }

    if (text_len > *capacity - *length) {
        free(*result);
        *result = NULL;
        *length = 0;
        *capacity = 0;
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(*result + *length, text, text_len);
    *length += text_len;
    (*result)[*length] = '\0';

    return true;
}

int main(void) {
    char *text = NULL;
    size_t length = 0;
    size_t capacity = 0;
    Tuple tuple = {10, 20};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];

    snprintf(buffer, sizeof(buffer), "Tuple: %d, %d\n", tuple.first, tuple.second);

    if (!append_text(&text, &length, &capacity, buffer, strnlen(buffer, sizeof(buffer)))) {
        return 1;
    }

    if (!append_text(&text, &length, &capacity, "Appended.\n", 10)) {
        free(text);
        return 1;
    }

    printf("%s", text);
    free(text);

    return 0;
}