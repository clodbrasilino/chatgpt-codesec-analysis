#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_STR_LEN 4096

typedef struct {
    char *key;
    char *value;
} Pair;

typedef struct {
    Pair *pairs;
    size_t count;
    size_t capacity;
} Dict;

static char *duplicate_string(const char *src) {
    if (src == NULL) {
        return NULL;
    }
    size_t len = strnlen(src, MAX_STR_LEN);
    if (len >= MAX_STR_LEN) {
        return NULL;
    }
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}

static bool dict_init(Dict *d) {
    if (d == NULL) {
        return false;
    }
    d->pairs = NULL;
    d->count = 0;
    d->capacity = 0;
    return true;
}

static bool dict_add(Dict *d, const char *key, const char *value) {
    if (d == NULL || key == NULL || value == NULL) {
        return false;
    }
    if (d->count == d->capacity) {
        size_t new_capacity = (d->capacity == 0) ? 4 : d->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(Pair)) {
            return false;
        }
        Pair *tmp = realloc(d->pairs, new_capacity * sizeof(Pair));
        if (tmp == NULL) {
            return false;
        }
        d->pairs = tmp;
        d->capacity = new_capacity;
    }
    char *key_copy = duplicate_string(key);
    if (key_copy == NULL) {
        return false;
    }
    char *value_copy = duplicate_string(value);
    if (value_copy == NULL) {
        free(key_copy);
        return false;
    }
    d->pairs[d->count].key = key_copy;
    d->pairs[d->count].value = value_copy;
    d->count++;
    return true;
}

static void dict_free(Dict *d) {
    if (d == NULL) {
        return;
    }
    for (size_t i = 0; i < d->count; i++) {
        free(d->pairs[i].key);
        free(d->pairs[i].value);
    }
    free(d->pairs);
    d->pairs = NULL;
    d->count = 0;
    d->capacity = 0;
}

static bool all_dicts_empty(const Dict *dicts, size_t num_dicts) {
    if (dicts == NULL) {
        return true;
    }
    for (size_t i = 0; i < num_dicts; i++) {
        if (dicts[i].count > 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Dict list_a[3];
    Dict list_b[3];
    size_t i;

    for (i = 0; i < 3; i++) {
        if (!dict_init(&list_a[i]) || !dict_init(&list_b[i])) {
            fprintf(stderr, "Initialization failed\n");
            return EXIT_FAILURE;
        }
    }

    if (all_dicts_empty(list_a, 3)) {
        printf("List A: all dictionaries are empty\n");
    } else {
        printf("List A: not all dictionaries are empty\n");
    }

    if (!dict_add(&list_b[1], "name", "alice")) {
        fprintf(stderr, "Failed to add entry\n");
        for (i = 0; i < 3; i++) {
            dict_free(&list_a[i]);
            dict_free(&list_b[i]);
        }
        return EXIT_FAILURE;
    }

    if (all_dicts_empty(list_b, 3)) {
        printf("List B: all dictionaries are empty\n");
    } else {
        printf("List B: not all dictionaries are empty\n");
    }

    for (i = 0; i < 3; i++) {
        dict_free(&list_a[i]);
        dict_free(&list_b[i]);
    }

    return EXIT_SUCCESS;
}