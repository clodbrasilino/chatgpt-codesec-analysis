#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 16

typedef struct Entry {
    char *key;
    char *value;
    struct Entry *next;
} Entry;

typedef struct Dictionary {
    Entry *buckets[TABLE_SIZE];
    size_t count;
} Dictionary;

Dictionary *dict_create(void)
{
    Dictionary *dict = calloc(1, sizeof(Dictionary));
    return dict;
}

static unsigned long hash_string(const char *str)
{
    unsigned long hash = 5381UL;
    int c;

    while ((c = (unsigned char)*str++) != 0) {
        hash = ((hash << 5) + hash) + (unsigned long)c;
    }
    return hash;
}

bool dict_insert(Dictionary *dict, const char *key, const char *value)
{
    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }

    Entry *entry = malloc(sizeof(Entry));
    if (entry == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    entry->key = malloc(strlen(key) + 1);
    if (entry->key == NULL) {
        free(entry);
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(entry->key, key);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    entry->value = malloc(strlen(value) + 1);
    if (entry->value == NULL) {
        free(entry->key);
        free(entry);
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(entry->value, value);

    size_t index = (size_t)(hash_string(key) % TABLE_SIZE);
    entry->next = dict->buckets[index];
    dict->buckets[index] = entry;
    dict->count++;

    return true;
}

bool dict_is_empty(const Dictionary *dict)
{
    if (dict == NULL) {
        return true;
    }
    return dict->count == 0;
}

void dict_destroy(Dictionary *dict)
{
    if (dict == NULL) {
        return;
    }

    for (size_t i = 0; i < TABLE_SIZE; i++) {
        Entry *current = dict->buckets[i];
        while (current != NULL) {
            Entry *next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            current = next;
        }
        dict->buckets[i] = NULL;
    }
    free(dict);
}

int main(void)
{
    Dictionary *dict = dict_create();
    if (dict == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_is_empty(dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }

    if (!dict_insert(dict, "name", "Alice")) {
        fprintf(stderr, "Failed to insert entry\n");
        dict_destroy(dict);
        return EXIT_FAILURE;
    }

    if (dict_is_empty(dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }

    dict_destroy(dict);
    return EXIT_SUCCESS;
}