#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} StringTuple;

static char *safe_strdup(const char *s) {
    char *copy;
    size_t len;
    
    if (s == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(s);
    
    copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, s, len);
    }
    copy[len] = '\0';
    return copy;
}

static void cleanup_items(char **items, size_t count) {
    size_t i;
    if (items == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(items[i]);
    }
    free(items);
}

StringTuple tuple_concat(const StringTuple *a, const StringTuple *b) {
    StringTuple result;
    size_t i;
    size_t total_count;

    if (a == NULL || b == NULL) {
        result.items = NULL;
        result.count = 0;
        return result;
    }

    total_count = a->count + b->count;
    if (total_count < a->count || total_count < b->count) {
        result.items = NULL;
        result.count = 0;
        return result;
    }

    result.count = total_count;
    if (result.count == 0) {
        result.items = NULL;
        return result;
    }

    result.items = (char **)malloc(result.count * sizeof(char *));
    if (result.items == NULL) {
        result.count = 0;
        return result;
    }

    for (i = 0; i < a->count; i++) {
        if (a->items[i] == NULL) {
            cleanup_items(result.items, i);
            result.items = NULL;
            result.count = 0;
            return result;
        }
        result.items[i] = safe_strdup(a->items[i]);
        if (result.items[i] == NULL) {
            cleanup_items(result.items, i);
            result.items = NULL;
            result.count = 0;
            return result;
        }
    }

    for (i = 0; i < b->count; i++) {
        size_t index = a->count + i;
        if (b->items[i] == NULL) {
            cleanup_items(result.items, index);
            result.items = NULL;
            result.count = 0;
            return result;
        }
        result.items[index] = safe_strdup(b->items[i]);
        if (result.items[index] == NULL) {
            cleanup_items(result.items, index);
            result.items = NULL;
            result.count = 0;
            return result;
        }
    }

    return result;
}

void tuple_free(StringTuple *tuple) {
    if (tuple != NULL) {
        cleanup_items(tuple->items, tuple->count);
        tuple->items = NULL;
        tuple->count = 0;
    }
}

int main(void) {
    char *items_a[] = {"hello", "world"};
    char *items_b[] = {"foo", "bar", "baz"};
    StringTuple a = {items_a, 2};
    StringTuple b = {items_b, 3};
    StringTuple result;
    size_t i;

    result = tuple_concat(&a, &b);

    if (result.items == NULL) {
        fprintf(stderr, "Failed to concatenate tuples\n");
        return 1;
    }

    for (i = 0; i < result.count; i++) {
        printf("%s\n", result.items[i]);
    }

    tuple_free(&result);

    return 0;
}