#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    const char *key;
    const char *value;
} DictEntry;

typedef struct {
    DictEntry *entries;
    size_t size;
} Dictionary;

static int value_exists(char **values, size_t count, const char *value)
{
    size_t i;
    for (i = 0; i < count; i++) {
        if (strcmp(values[i], value) == 0) {
            return 1;
        }
    }
    return 0;
}

char **extract_unique_values(const Dictionary *dict, size_t *unique_count)
{
    char **unique_values;
    size_t i;
    size_t count = 0;

    if (dict == NULL || dict->entries == NULL || unique_count == NULL) {
        return NULL;
    }

    if (dict->size > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    unique_values = malloc(dict->size * sizeof(char *));
    if (unique_values == NULL) {
        return NULL;
    }

    for (i = 0; i < dict->size; i++) {
        const char *value = dict->entries[i].value;

        if (value == NULL) {
            continue;
        }

        if (!value_exists(unique_values, count, value)) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(value) + 1;

            unique_values[count] = malloc(len);
            if (unique_values[count] == NULL) {
                size_t j;
                for (j = 0; j < count; j++) {
                    free(unique_values[j]);
                }
                free(unique_values);
                return NULL;
            }

            snprintf(unique_values[count], len, "%s", value);
            count++;
        }
    }

    *unique_count = count;
    return unique_values;
}

void free_unique_values(char **values, size_t count)
{
    size_t i;

    if (values == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(values[i]);
    }
    free(values);
}

int main(void)
{
    Dictionary dict;
    DictEntry entries[] = {
        {"a", "apple"},
        {"b", "banana"},
        {"c", "apple"},
        {"d", "cherry"},
        {"e", "banana"},
        {"f", "cherry"}
    };
    char **unique_values;
    size_t unique_count = 0;
    size_t i;

    dict.entries = entries;
    dict.size = sizeof(entries) / sizeof(entries[0]);

    printf("Dictionary entries:\n");
    for (i = 0; i < dict.size; i++) {
        printf("%s -> %s\n", dict.entries[i].key, dict.entries[i].value);
    }

    unique_values = extract_unique_values(&dict, &unique_count);
    if (unique_values == NULL) {
        fprintf(stderr, "Error: failed to extract unique values\n");
        return EXIT_FAILURE;
    }

    printf("Unique values:\n");
    for (i = 0; i < unique_count; i++) {
        printf("%s\n", unique_values[i]);
    }

    free_unique_values(unique_values, unique_count);

    return EXIT_SUCCESS;
}