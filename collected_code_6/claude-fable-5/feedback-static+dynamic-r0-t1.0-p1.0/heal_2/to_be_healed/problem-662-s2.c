#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DICT_MAX_KEY_LEN 256

typedef struct {
    char *key;
    int *values;
    size_t count;
} DictEntry;

typedef struct {
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

static char *duplicate_key(const char *key)
{
    size_t len;
    char *copy;

    len = strnlen(key, DICT_MAX_KEY_LEN);
    if (len == DICT_MAX_KEY_LEN) {
        return NULL;
    }

    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, key, len);
    copy[len] = '\0';
    return copy;
}

int dict_sort_list(Dictionary *dict, const char *key)
{
    size_t i;

    if (dict == NULL || key == NULL) {
        return -1;
    }

    for (i = 0; i < dict->size; i++) {
        if (dict->entries[i].key != NULL &&
            strcmp(dict->entries[i].key, key) == 0) {
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

int dict_add(Dictionary *dict, const char *key, const int *values, size_t count)
{
    DictEntry *new_entries;
    char *key_copy;
    int *values_copy;

    if (dict == NULL || key == NULL || values == NULL || count == 0) {
        return -1;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    if (dict->size > SIZE_MAX / sizeof(DictEntry) - 1) {
        return -1;
    }

    key_copy = duplicate_key(key);
    if (key_copy == NULL) {
        return -1;
    }

    values_copy = malloc(count * sizeof(int));
    if (values_copy == NULL) {
        free(key_copy);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(values_copy, values, count * sizeof(int));

    new_entries = realloc(dict->entries, (dict->size + 1) * sizeof(DictEntry));
    if (new_entries == NULL) {
        free(key_copy);
        free(values_copy);
        return -1;
    }

    dict->entries = new_entries;
    dict->entries[dict->size].key = key_copy;
    dict->entries[dict->size].values = values_copy;
    dict->entries[dict->size].count = count;
    dict->size++;

    return 0;
}

void dict_free(Dictionary *dict)
{
    size_t i;

    if (dict == NULL) {
        return;
    }

    for (i = 0; i < dict->size; i++) {
        free(dict->entries[i].key);
        free(dict->entries[i].values);
    }
    free(dict->entries);
    dict->entries = NULL;
    dict->size = 0;
}

void dict_print(const Dictionary *dict)
{
    size_t i;
    size_t j;

    if (dict == NULL) {
        return;
    }

    for (i = 0; i < dict->size; i++) {
        printf("%s: [", dict->entries[i].key);
        for (j = 0; j < dict->entries[i].count; j++) {
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
    int numbers[] = { 42, 7, 19, 3, 88, 15 };
    int scores[] = { 90, 55, 73, 61 };

    if (dict_add(&dict, "numbers", numbers,
                 sizeof(numbers) / sizeof(numbers[0])) != 0) {
        fprintf(stderr, "Failed to add entry\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    if (dict_add(&dict, "scores", scores,
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