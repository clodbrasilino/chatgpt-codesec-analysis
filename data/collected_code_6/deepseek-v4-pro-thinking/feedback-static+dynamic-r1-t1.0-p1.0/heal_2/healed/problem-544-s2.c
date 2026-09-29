#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

static bool append_text(char **result, size_t *length, size_t *capacity, const char *text, size_t text_len) {
    size_t needed = *length + text_len + 1;
    if (needed < *length) {
        free(*result);
        *result = NULL;
        return false;
    }

    if (needed > *capacity) {
        size_t new_capacity = *capacity;
        if (new_capacity == 0) {
            new_capacity = 1;
        }
        while (new_capacity < needed) {
            if (new_capacity > (size_t)-1 / 2) {
                free(*result);
                *result = NULL;
                return false;
            }
            new_capacity *= 2;
        }

        char *new_result = realloc(*result, new_capacity);
        if (!new_result) {
            free(*result);
            *result = NULL;
            return false;
        }
        *result = new_result;
        *capacity = new_capacity;
    }

    if (*length + text_len + 1 > *capacity) {
        free(*result);
        *result = NULL;
        return false;
    }

    memcpy(*result + *length, text, text_len);
    (*result)[*length + text_len] = '\0';
    *length += text_len;
    return true;
}

int main(void) {
    char *str = NULL;
    size_t len = 0;
    size_t cap = 0;

    if (!append_text(&str, &len, &cap, "Hello", 5)) {
        return 1;
    }
    if (!append_text(&str, &len, &cap, " World", 6)) {
        free(str);
        return 1;
    }

    printf("%s\n", str);
    free(str);
    return 0;
}