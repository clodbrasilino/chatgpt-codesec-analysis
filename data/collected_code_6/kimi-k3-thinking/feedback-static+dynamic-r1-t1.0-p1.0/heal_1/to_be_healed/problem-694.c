#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'DictEntry::key' is never used. [unusedStructMember]
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[50];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[50];
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

    unique_values = (char **)malloc(dict->size * sizeof(char *));
    if (unique_values == NULL) {
        return NULL;
    }

    for (i = 0; i < dict->size; i++) {
        if (!value_exists(unique_values, count, dict->entries[i].value)) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(dict->entries[i].value) + 1;
            unique_values[count] = (char *)malloc(len * sizeof(char));
            if (unique_values[count] == NULL) {
                size_t j;
                for (j = 0; j < count; j++) {
                    free(unique_values[j]);
                }
                free(unique_values);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(unique_values[count], dict->entries[i].value, len);
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