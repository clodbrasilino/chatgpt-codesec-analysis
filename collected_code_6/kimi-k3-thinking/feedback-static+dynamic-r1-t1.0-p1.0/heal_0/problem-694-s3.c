#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[64];
    char value[64];
} DictEntry;

typedef struct {
    const DictEntry *entries;
    size_t count;
} Dictionary;

static char **extract_unique_values(const Dictionary *dict, size_t *unique_count)
{
    size_t i;
    size_t j;
    size_t k;
    size_t found;
    int is_duplicate;
    char **unique;

    if (dict == NULL || unique_count == NULL || dict->entries == NULL) {
        return NULL;
    }

    *unique_count = 0;

    if (dict->count == 0) {
        return NULL;
    }

    unique = malloc(dict->count * sizeof(char *));
    if (unique == NULL) {
        return NULL;
    }

    found = 0;
    for (i = 0; i < dict->count; i++) {
        is_duplicate = 0;
        for (j = 0; j < found; j++) {
            if (strcmp(unique[j], dict->entries[i].value) == 0) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            unique[found] = malloc(strlen(dict->entries[i].value) + 1);
            if (unique[found] == NULL) {
                for (k = 0; k < found; k++) {
                    free(unique[k]);
                }
                free(unique);
                return NULL;
            }
            strcpy(unique[found], dict->entries[i].value);
            found++;
        }
    }

    *unique_count = found;
    return unique;
}

int main(void)
{
    static const DictEntry entries[] = {
        {"a", "apple"},
        {"b", "banana"},
        {"c", "apple"},
        {"d", "cherry"},
        {"e", "banana"},
        {"f", "cherry"}
    };
    Dictionary dict;
    char **unique;
    size_t unique_count;
    size_t i;

    dict.entries = entries;
    dict.count = sizeof(entries) / sizeof(entries[0]);
    unique_count = 0;

    unique = extract_unique_values(&dict, &unique_count);
    if (unique == NULL) {
        fprintf(stderr, "Error: failed to extract unique values\n");
        return EXIT_FAILURE;
    }

    printf("Unique values:\n");
    for (i = 0; i < unique_count; i++) {
        printf("%s\n", unique[i]);
    }

    for (i = 0; i < unique_count; i++) {
        free(unique[i]);
    }
    free(unique);

    return EXIT_SUCCESS;
}