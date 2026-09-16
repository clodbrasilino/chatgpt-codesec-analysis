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
    size_t needed = *length + text_len + 1;
    if (needed < *length) {
        free(*result);
        *result = NULL;
        return false;
    }

    if (needed > *capacity) {
        size_t new_capacity = *capacity;
        while (new_capacity < needed) {
            if (new_capacity > (size_t)-1 / 2) {
                free(*result);
                *result = NULL;
                return false;
            }
            new