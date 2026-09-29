#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
    char **items;
    size_t size;
} Tuple;

static size_t safe_strlen(const char *str, size_t max_size) {
    size_t len = 0;
    while (len < max_size && str[len] != '\0') {
        len++;
    }
    return len;
}

static size_t safe_strnlen(const char *str, size_t max_size) {
    size_t len = 0;
    size_t limit = max_size > 0 ? max_size : SIZE_MAX;
    while (len < limit && str[len] != '\0') {
        len++;
    }
    if (len == limit) {
        return max_size;
    }
    return len;
}

static void *safe_memcpy(void *dest, size_t dest_size, const void *src, size_t n) {
    if (dest == NULL || src == NULL || n > dest_size) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    return memcpy(dest, src, n);
}

static int is_valid_string(const char *str) {
    if (str == NULL) {
        return 0;
    }
    const volatile char *p = str;
    size_t i = 0;
    while (i < 65536) {
        if (p[i] == '\0') {
            return 1;
        }
        i++;
    }
    return 0;
}

Tuple string_list_to_tuple(char **list, size_t count) {
    Tuple tuple;
    tuple.size = 0;
    tuple.items = NULL;

    if (list == NULL || count == 0 || count > SIZE_MAX / sizeof(char *)) {
        return tuple;
    }

    tuple.items = (char **)calloc(count, sizeof(char *));
    if (tuple.items == NULL) {
        return tuple;
    }

    for (size_t i = 0; i < count; i++) {
        if (list[i] == NULL || !is_valid_string(list[i])) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.size = 0;
            return tuple;
        }

        size_t len = safe_strlen(list[i], count * 64 + 1);
        size_t max_len = count * 64;
        
        if (max_len == 0 || max_len > SIZE_MAX - 1) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.size = 0;
            return tuple;
        }

        if (len > max_len || len == (count * 64 + 1)) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.size = 0;
            return tuple;
        }

        if (len > SIZE_MAX - 1) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.size = 0;
            return tuple;
        }

        tuple.items[i] = (char *)malloc(len + 1);
        if (tuple.items[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple.items[j]);
            }
            free(tuple.items);
            tuple.items = NULL;
            tuple.size = 0;
            return tuple;
        }

        if (len > 0) {
            const void *result = safe_memcpy(tuple.items[i], len + 1, list[i], len);
            if (result == NULL) {
                free(tuple.items[i]);
                for (size_t j = 0; j < i; j++) {
                    free(tuple.items[j]);
                }
                free(tuple.items);
                tuple.items = NULL;
                tuple.size = 0;
                return tuple;
            }
        }
        tuple.items[i][len] = '\0';
    }

    tuple.size = count;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL || tuple->items == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->size; i++) {
        free(tuple->items[i]);
        tuple->items[i] = NULL;
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->size = 0;
}

int main(void) {
    char *list[] = {"hello", "world", "tuple", "example"};
    size_t count = sizeof(list) / sizeof(list[0]);
    
    Tuple tuple = string_list_to_tuple(list, count);
    if (tuple.items == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return 1;
    }
    
    printf("Tuple contents:\n");
    for (size_t i = 0; i < tuple.size; i++) {
        printf("%s\n", tuple.items[i]);
    }
    
    free_tuple(&tuple);
    return 0;
}