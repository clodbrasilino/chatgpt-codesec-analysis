#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NestedEntry {
    char *outer_key;
    char *inner_key;
    int value;
} NestedEntry;

typedef struct NestedDict {
    NestedEntry *entries;
    size_t count;
} NestedDict;

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }
    len = strlen(src) + 1U;
    copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, src, len);
    return copy;
}

void free_nested_dict(NestedDict *dict)
{
    if (dict == NULL) {
        return;
    }
    if (dict->entries != NULL) {
        for (size_t i = 0; i < dict->count; i++) {
            free(dict->entries[i].outer_key);
            free(dict->entries[i].inner_key);
        }
        free(dict->entries);
    }
    free(dict);
}

NestedDict *convert_lists_to_nested_dict(const char **keys,
                                         const char **subkeys,
                                         const int *values,
                                         size_t count)
{
    NestedDict *dict;

    if (keys == NULL || subkeys == NULL || values == NULL || count == 0U) {
        return NULL;
    }

    dict = malloc(sizeof(NestedDict));
    if (dict == NULL) {
        return NULL;
    }

    dict->entries = calloc(count, sizeof(NestedEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }
    dict->count = count;

    for (size_t i = 0; i < count; i++) {
        dict->entries[i].outer_key = duplicate_string(keys[i]);
        dict->entries[i].inner_key = duplicate_string(subkeys[i]);
        dict->entries[i].value = values[i];
        if (dict->entries[i].outer_key == NULL ||
            dict->entries[i].inner_key == NULL) {
            free_nested_dict(dict);
            return NULL;
        }
    }

    return dict;
}

void print_nested_dict(const NestedDict *dict)
{
    if (dict == NULL || dict->entries == NULL) {
        return;
    }

    printf("[");
    for (size_t i = 0; i < dict->count; i++) {
        printf("{\"%s\": {\"%s\": %d}}",
               dict->entries[i].outer_key,
               dict->entries[i].inner_key,
               dict->entries[i].value);
        if (i + 1U < dict->count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    const char *ids[] = { "S001", "S002", "S003", "S004" };
    const char *names[] = { "Adina Park", "Leyton Marsh",
                            "Duncan Boyle", "Saim Richards" };
    const int scores[] = { 85, 98, 89, 92 };
    size_t count = sizeof(scores) / sizeof(scores[0]);
    NestedDict *dict;

    dict = convert_lists_to_nested_dict(ids, names, scores, count);
    if (dict == NULL) {
        fprintf(stderr, "Failed to build nested dictionary\n");
        return EXIT_FAILURE;
    }

    print_nested_dict(dict);
    free_nested_dict(dict);

    return EXIT_SUCCESS;
}