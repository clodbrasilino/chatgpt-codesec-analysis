#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'DictEntry::key' is never used. [unusedStructMember]
     */
    const char *key;
    const char *value;
} DictEntry;

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

char **extract_unique_values(const DictEntry *dict, size_t dict_size, size_t *unique_count)
{
    char **unique_values;
    size_t count;
    size_t i;

    if (dict == NULL || unique_count == NULL) {
        return NULL;
    }

    *unique_count = 0;

    if (dict_size == 0) {
        return NULL;
    }

    unique_values = malloc(dict_size * sizeof(*unique_values));
    if (unique_values == NULL) {
        return NULL;
    }

    count = 0;
    for (i = 0; i < dict_size; i++) {
        if (dict[i].value == NULL) {
            continue;
        }
        if (!value_exists(unique_values, count, dict[i].value)) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(dict[i].value) + 1;
            unique_values[count] = malloc(len);
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
            memcpy(unique_values[count], dict[i].value, len);
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
    DictEntry dict[] = {
        {"key1", "apple"},
        {"key2", "banana"},
        {"key3", "apple"},
        {"key4", "cherry"},
        {"key5", "banana"},
        {"key6", "date"}
    };
    size_t dict_size = sizeof(dict) / sizeof(dict[0]);
    size_t unique_count = 0;
    char **unique_values;
    size_t i;

    unique_values = extract_unique_values(dict, dict_size, &unique_count);
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