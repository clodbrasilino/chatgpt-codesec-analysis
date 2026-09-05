#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[64];
    int *values;
    size_t count;
    size_t capacity;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t count;
    size_t capacity;
} Dictionary;

static int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

static Dictionary *dict_create(size_t capacity) {
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->entries = calloc(capacity, sizeof(DictEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }
    dict->count = 0;
    dict->capacity = capacity;
    return dict;
}

static void dict_free(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    if (dict->entries != NULL) {
        for (size_t i = 0; i < dict->count; i++) {
            free(dict->entries[i].values);
        }
        free(dict->entries);
    }
    free(dict);
}

static int dict_add(Dictionary *dict, const char *key, const int *values, size_t count) {
    if (dict == NULL || key == NULL || values == NULL || count == 0) {
        return -1;
    }
    if (dict->count >= dict->capacity) {
        return -1;
    }
    DictEntry *entry = &dict->entries[dict->count];
    entry->values = malloc(count * sizeof(int));
    if (entry->values == NULL) {
        return -1;
    }
    strncpy(entry->key, key, sizeof(entry->key) - 1);
    entry->key[sizeof(entry->key) - 1] = '\0';
    memcpy(entry->values, values, count * sizeof(int));
    entry->count = count;
    entry->capacity = count;
    dict->count++;
    return 0;
}

static DictEntry *dict_find(Dictionary *dict, const char *key) {
    if (dict == NULL || key == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < dict->count; i++) {
        if (strcmp(dict->entries[i].key, key) == 0) {
            return &dict->entries[i];
        }
    }
    return NULL;
}

static int dict_sort_list(Dictionary *dict, const char *key) {
    DictEntry *entry = dict_find(dict, key);
    if (entry == NULL || entry->values == NULL || entry->count == 0) {
        return -1;
    }
    qsort(entry->values, entry->count, sizeof(int), compare_ints);
    return 0;
}

static void dict_print_entry(const DictEntry *entry) {
    if (entry == NULL) {
        return;
    }
    printf("%s: [", entry->key);
    for (size_t i = 0; i < entry->count; i++) {
        printf("%d", entry->values[i]);
        if (i + 1 < entry->count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    Dictionary *dict = dict_create(8);
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    const int values1[] = {42, 7, 19, 73, 3, 58};
    const int values2[] = {10, -4, 33, 8, 0, -21};

    if (dict_add(dict, "numbers", values1, 6) != 0) {
        fprintf(stderr, "Failed to add entry\n");
        dict_free(dict);
        return EXIT_FAILURE;
    }
    if (dict_add(dict, "scores", values2, 6) != 0) {
        fprintf(stderr, "Failed to add entry\n");
        dict_free(dict);
        return EXIT_FAILURE;
    }

    printf("Before sorting:\n");
    for (size_t i = 0; i < dict->count; i++) {
        dict_print_entry(&dict->entries[i]);
    }

    if (dict_sort_list(dict, "numbers") != 0) {
        fprintf(stderr, "Failed to sort 'numbers'\n");
    }
    if (dict_sort_list(dict, "scores") != 0) {
        fprintf(stderr, "Failed to sort 'scores'\n");
    }

    printf("After sorting:\n");
    for (size_t i = 0; i < dict->count; i++) {
        dict_print_entry(&dict->entries[i]);
    }

    dict_free(dict);
    return EXIT_SUCCESS;
}