#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int count;
} StringFreq;

static char *duplicate_string(const char *s, size_t max_len) {
    if (s == NULL || max_len == 0) {
        return NULL;
    }
    size_t len = strnlen(s, max_len);
    if (len == max_len) {
        return NULL;
    }
    len++;
    char *copy = malloc(len);
    if (copy != NULL) {
        int written = snprintf(copy, len, "%s", s);
        if (written < 0 || (size_t)written >= len) {
            free(copy);
            return NULL;
        }
    }
    return copy;
}

static void free_string_freqs(StringFreq *freqs, size_t count) {
    if (freqs == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(freqs[i].str);
    }
    free(freqs);
}

char *second_most_frequent(char **sequence, size_t size, size_t max_str_len) {
    if (sequence == NULL || size < 2 || max_str_len == 0) {
        return NULL;
    }

    StringFreq *freqs = calloc(size, sizeof(StringFreq));
    if (freqs == NULL) {
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < size; i++) {
        if (sequence[i] == NULL) {
            continue;
        }

        int found = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (strcmp(freqs[j].str, sequence[i]) == 0) {
                freqs[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            freqs[unique_count].str = duplicate_string(sequence[i], max_str_len);
            if (freqs[unique_count].str == NULL) {
                free_string_freqs(freqs, unique_count);
                return NULL;
            }
            freqs[unique_count].count = 1;
            unique_count++;
        }
    }

    if (unique_count < 2) {
        free_string_freqs(freqs, unique_count);
        return NULL;
    }

    int first_idx = -1;
    int second_idx = -1;

    for (size_t i = 0; i < unique_count; i++) {
        if (first_idx == -1 || freqs[i].count > freqs[first_idx].count) {
            second_idx = first_idx;
            first_idx = (int)i;
        } else if (second_idx == -1 || freqs[i].count > freqs[second_idx].count) {
            second_idx = (int)i;
        }
    }

    char *result = NULL;
    if (second_idx != -1) {
        result = duplicate_string(freqs[second_idx].str, max_str_len);
    }

    free_string_freqs(freqs, unique_count);
    return result;
}

int main(void) {
    char *sequence[] = {
        "apple", "banana", "apple", "cherry",
        "banana", "apple", "cherry", "banana"
    };
    size_t size = sizeof(sequence) / sizeof(sequence[0]);
    size_t max_str_len = 256;

    char *result = second_most_frequent(sequence, size, max_str_len);
    if (result != NULL) {
        printf("Second most frequent: %s\n", result);
        free(result);
    } else {
        printf("No second most frequent string found\n");
    }

    return 0;
}