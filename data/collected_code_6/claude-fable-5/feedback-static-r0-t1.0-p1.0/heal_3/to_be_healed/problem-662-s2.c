#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_KEY_LEN 256

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

int dict_sort_list(Dictionary *dict, const char *key)
{
    size_t i;

    if (dict == NULL || key == NULL || dict->entries == NULL) {
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

static char *copy_key(const char *key, size_t key_len)
{
    char *key_copy;
    size_t dest_size;

    /* Possible weaknesses found:
     *  dest_size is assigned 'key_len+1' here.
     */
    dest_size = key_len + 1;
    key_copy = malloc(dest_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (key_copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'key_len>=dest_size' is always false
     *  Condition 'key_len>=dest_size' is always false [knownConditionTrueFalse]
     */
    if (key_len >= dest_size) {
        free(key_copy);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(key_copy, key, key_len);
    key_copy[key_len] = '\0';

    return key_copy;
}

static int *copy_values(const int *values, size_t count)
{
    int *values_copy;
    size_t dest_size;
    size_t i;

    if (count > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    dest_size = count * sizeof(int);
    values_copy = malloc(dest_size);
    if (values_copy == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        values_copy[i] = values[i];
    }

    return values_copy;
}

int dict_add(Dictionary *dict, const char *key, const int *values, size_t count)
{
    DictEntry *new_entries;
    char *key_copy;
    int *values_copy;
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

    if (dict->size >= SIZE_MAX / sizeof(DictEntry) - 1) {
        return -1;
    }

    key_copy = copy_key(key, key_len);
    if (key_copy == NULL) {
        return -1;
    }

    values_copy = copy_values(values, count);
    if (values_copy == NULL) {
        free(key_copy);
        return -1;
    }

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

    if (dict == NULL || dict->entries == NULL) {
        return;
    }

    for (i = 0; i < dict->size; i++) {
        if (dict->entries[i].key == NULL) {
            continue;
        }
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