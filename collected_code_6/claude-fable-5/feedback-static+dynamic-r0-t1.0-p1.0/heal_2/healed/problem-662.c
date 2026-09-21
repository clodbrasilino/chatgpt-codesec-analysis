#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_KEY_LEN 64

typedef struct DictEntry {
    char key[MAX_KEY_LEN];
    int *values;
    size_t count;
} DictEntry;

typedef struct Dictionary {
    DictEntry *entries;
    size_t size;
} Dictionary;

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

int dict_sort_list(Dictionary *dict, const char *key)
{
    if (dict == NULL || key == NULL || dict->entries == NULL) {
        return -1;
    }

    if (strnlen(key, MAX_KEY_LEN) >= MAX_KEY_LEN) {
        return -1;
    }

    for (size_t i = 0; i < dict->size; i++) {
        if (strncmp(dict->entries[i].key, key, MAX_KEY_LEN) == 0) {
            if (dict->entries[i].values == NULL || dict->entries[i].count == 0) {
                return -1;
            }
            qsort(dict->entries[i].values, dict->entries[i].count,
                  sizeof(int), compare_ints);
            return 0;
        }
    }
    return -1;
}

int dict_add_entry(Dictionary *dict, const char *key,
                   const int *values, size_t count)
{
    DictEntry *new_entries;
    DictEntry *entry;
    int *copy;
    size_t key_len;

    if (dict == NULL || key == NULL || values == NULL || count == 0) {
        return -1;
    }

    key_len = strnlen(key, MAX_KEY_LEN);
    if (key_len == 0 || key_len >= MAX_KEY_LEN) {
        return -1;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    copy = malloc(count * sizeof(int));
    if (copy == NULL) {
        return -1;
    }
    memcpy(copy, values, count * sizeof(int));

    if (dict->size >= SIZE_MAX / sizeof(DictEntry) - 1) {
        free(copy);
        return -1;
    }

    new_entries = realloc(dict->entries, (dict->size + 1) * sizeof(DictEntry));
    if (new_entries == NULL) {
        free(copy);
        return -1;
    }
    dict->entries = new_entries;

    entry = &dict->entries[dict->size];
    memset(entry->key, 0, sizeof(entry->key));

    if (key_len >= sizeof(entry->key)) {
        free(copy);
        return -1;
    }
    memcpy(entry->key, key, key_len);
    entry->key[key_len] = '\0';
    entry->values = copy;
    entry->count = count;
    dict->size++;
    return 0;
}

void dict_free(Dictionary *dict)
{
    if (dict == NULL) {
        return;
    }
    if (dict->entries != NULL) {
        for (size_t i = 0; i < dict->size; i++) {
            free(dict->entries[i].values);
            dict->entries[i].values = NULL;
        }
        free(dict->entries);
        dict->entries = NULL;
    }
    dict->size = 0;
}

void dict_print(const Dictionary *dict)
{
    if (dict == NULL || dict->entries == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->size; i++) {
        printf("%s: [", dict->entries[i].key);
        for (size_t j = 0; j < dict->entries[i].count; j++) {
            printf("%d", dict->entries[i].values[j]);
            if (j + 1 < dict->entries[i].count) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void)
{
    Dictionary dict = { NULL, 0 };
    int numbers[] = { 42, 7, 19, 3, 88, 1 };
    int scores[] = { 90, 55, 77, 100 };

    if (dict_add_entry(&dict, "numbers", numbers,
                       sizeof(numbers) / sizeof(numbers[0])) != 0) {
        fprintf(stderr, "Failed to add entry\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    if (dict_add_entry(&dict, "scores", scores,
                       sizeof(scores) / sizeof(scores[0])) != 0) {
        fprintf(stderr, "Failed to add entry\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    printf("Before sorting:\n");
    dict_print(&dict);

    if (dict_sort_list(&dict, "numbers") != 0) {
        fprintf(stderr, "Failed to sort list for key 'numbers'\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    if (dict_sort_list(&dict, "scores") != 0) {
        fprintf(stderr, "Failed to sort list for key 'scores'\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    printf("\nAfter sorting:\n");
    dict_print(&dict);

    dict_free(&dict);
    return EXIT_SUCCESS;
}