#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[64];
    int value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
    size_t capacity;
} Dictionary;

int dict_init(Dictionary *dict, size_t initial_capacity) {
    if (dict == NULL || initial_capacity == 0) {
        return -1;
    }
    dict->entries = (DictEntry *)calloc(initial_capacity, sizeof(DictEntry));
    if (dict->entries == NULL) {
        return -1;
    }
    dict->size = 0;
    dict->capacity = initial_capacity;
    return 0;
}

void dict_free(Dictionary *dict) {
    if (dict != NULL) {
        free(dict->entries);
        dict->entries = NULL;
        dict->size = 0;
        dict->capacity = 0;
    }
}

int dict_add(Dictionary *dict, const char *key, int value) {
    if (dict == NULL || key == NULL || dict->size >= dict->capacity) {
        return -1;
    }
    size_t key_len = strlen(key);
    if (key_len >= sizeof(dict->entries[0].key)) {
        return -1;
    }
    strncpy(dict->entries[dict->size].key, key, sizeof(dict->entries[dict->size].key) - 1);
    dict->entries[dict->size].key[sizeof(dict->entries[dict->size].key) - 1] = '\0';
    dict->entries[dict->size].value = value;
    dict->size++;
    return 0;
}

int dict_filter(const Dictionary *src, Dictionary *dst, int (*predicate)(int)) {
    if (src == NULL || dst == NULL || predicate == NULL) {
        return -1;
    }
    if (dict_init(dst, src->size) != 0) {
        return -1;
    }
    for (size_t i = 0; i < src->size; i++) {
        if (predicate(src->entries[i].value)) {
            if (dict_add(dst, src->entries[i].key, src->entries[i].value) != 0) {
                dict_free(dst);
                return -1;
            }
        }
    }
    return 0;
}

int is_positive(int value) {
    return value > 0;
}

int is_even(int value) {
    return value % 2 == 0;
}

void dict_print(const Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    printf("{ ");
    for (size_t i = 0; i < dict->size; i++) {
        printf("\"%s\": %d", dict->entries[i].key, dict->entries[i].value);
        if (i < dict->size - 1) {
            printf(", ");
        }
    }
    printf(" }\n");
}

int main(void) {
    Dictionary dict;
    Dictionary filtered_positive;
    Dictionary filtered_even;

    if (dict_init(&dict, 10) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(&dict, "apple", 5) != 0 ||
        dict_add(&dict, "banana", -3) != 0 ||
        dict_add(&dict, "cherry", 8) != 0 ||
        dict_add(&dict, "date", 0) != 0 ||
        dict_add(&dict, "elderberry", -7) != 0 ||
        dict_add(&dict, "fig", 12) != 0) {
        fprintf(stderr, "Failed to add entries\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    printf("Original dictionary:\n");
    dict_print(&dict);

    if (dict_filter(&dict, &filtered_positive, is_positive) != 0) {
        fprintf(stderr, "Failed to filter dictionary\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    printf("\nFiltered (positive values):\n");
    dict_print(&filtered_positive);

    if (dict_filter(&dict, &filtered_even, is_even) != 0) {
        fprintf(stderr, "Failed to filter dictionary\n");
        dict_free(&dict);
        dict_free(&filtered_positive);
        return EXIT_FAILURE;
    }

    printf("\nFiltered (even values):\n");
    dict_print(&filtered_even);

    dict_free(&dict);
    dict_free(&filtered_positive);
    dict_free(&filtered_even);

    return EXIT_SUCCESS;
}