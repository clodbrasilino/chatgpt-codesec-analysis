#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VALUE_LENGTH 256

typedef struct {
    const char *value;
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
    char **unique;

    if (dict == NULL || unique_count == NULL || dict->entries == NULL) {
        return NULL;
    }

    *unique_count = 0;

    if (dict->count == 0) {
        return NULL;
    }

    unique = malloc(dict->count * sizeof(*unique));
    if (unique == NULL) {
        return NULL;
    }

    found = 0;
    for (i = 0; i < dict->count; i++) {
        const char *value = dict->entries[i].value;
        size_t value_length;
        int is_duplicate = 0;

        if (value == NULL) {
            continue;
        }

        for (j = 0; j < found; j++) {
            if (strncmp(unique[j], value, MAX_VALUE_LENGTH) == 0) {
                is_duplicate = 1;
                break;
            }
        }

        if (is_duplicate) {
            continue;
        }

        value_length = strnlen(value, MAX_VALUE_LENGTH);
        unique[found] = malloc(value_length + 1);
        if (unique[found] == NULL) {
            for (k = 0; k < found; k++) {
                free(unique[k]);
            }
            free(unique);
            return NULL;
        }
        memcpy(unique[found], value, value_length);
        unique[found][value_length] = '\0';
        found++;
    }

    *unique_count = found;
    return unique;
}

int main(void)
{
    static const DictEntry entries[] = {
        {"apple"},
        {"banana"},
        {"apple"},
        {"cherry"},
        {"banana"},
        {"cherry"}
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