#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    char *value;
} Tuple;

static size_t safe_strlen(const char *s, size_t max_len) {
    if (s == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static int check_add_overflow(size_t a, size_t b, size_t *result) {
    if (a > SIZE_MAX - b) {
        return -1;
    }
    *result = a + b;
    return 0;
}

char *flatten_tuples(const Tuple *tuples, size_t count, const char *separator) {
    if (tuples == NULL || separator == NULL || count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / 2) {
        return NULL;
    }

    size_t sep_len = safe_strlen(separator, 4096);
    size_t total_len = 0;

    for (size_t i = 0; i < count; i++) {
        if (tuples[i].key == NULL || tuples[i].value == NULL) {
            return NULL;
        }

        size_t key_len = safe_strlen(tuples[i].key, 4096);
        size_t value_len = safe_strlen(tuples[i].value, 4096);

        if (key_len == 0 || value_len == 0) {
            return NULL;
        }

        if (check_add_overflow(total_len, key_len, &total_len) != 0) {
            return NULL;
        }
        if (check_add_overflow(total_len, value_len, &total_len) != 0) {
            return NULL;
        }

        if (i < count - 1) {
            if (check_add_overflow(total_len, sep_len, &total_len) != 0) {
                return NULL;
            }
        }
    }

    if (check_add_overflow(total_len, 1, &total_len) != 0) {
        return NULL;
    }

    char *result = malloc(total_len);
    if (result == NULL) {
        return NULL;
    }

    char *ptr = result;
    size_t remaining = total_len;

    for (size_t i = 0; i < count; i++) {
        size_t key_len = safe_strlen(tuples[i].key, 4096);
        if (key_len >= remaining) {
            free(result);
            return NULL;
        }
        memcpy(ptr, tuples[i].key, key_len);
        ptr += key_len;
        remaining -= key_len;

        size_t value_len = safe_strlen(tuples[i].value, 4096);
        if (value_len >= remaining) {
            free(result);
            return NULL;
        }
        memcpy(ptr, tuples[i].value, value_len);
        ptr += value_len;
        remaining -= value_len;

        if (i < count - 1) {
            if (sep_len >= remaining) {
                free(result);
                return NULL;
            }
            memcpy(ptr, separator, sep_len);
            ptr += sep_len;
            remaining -= sep_len;
        }
    }

    *ptr = '\0';
    return result;
}

int main(void) {
    Tuple tuples[] = {
        {"name", "John"},
        {"age", "30"},
        {"city", "NYC"}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);

    char *flattened = flatten_tuples(tuples, count, ", ");
    if (flattened == NULL) {
        fprintf(stderr, "Error: Failed to flatten tuples\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", flattened);

    free(flattened);
    return EXIT_SUCCESS;
}