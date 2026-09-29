#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_KEY_LEN 64
#define MAX_VALUE_LEN 64

typedef struct Entry {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[MAX_KEY_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char value[MAX_VALUE_LEN];
    struct Entry *next;
} Entry;

typedef struct Dictionary {
    Entry *head;
    size_t count;
} Dictionary;

Dictionary *dict_create(void);
bool dict_insert(Dictionary *dict, const char *key, const char *value);
bool dict_is_empty(const Dictionary *dict);
void dict_destroy(Dictionary *dict);

Dictionary *dict_create(void)
{
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    dict->count = 0;
    return dict;
}

bool dict_insert(Dictionary *dict, const char *key, const char *value)
{
    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }

    size_t key_len = strnlen(key, MAX_KEY_LEN);
    size_t value_len = strnlen(value, MAX_VALUE_LEN);

    if (key_len == 0 || key_len >= MAX_KEY_LEN || value_len >= MAX_VALUE_LEN) {
        return false;
    }

    Entry *entry = malloc(sizeof(Entry));
    if (entry == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(entry->key, key, key_len);
    entry->key[key_len] = '\0';

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(entry->value, value, value_len);
    entry->value[value_len] = '\0';

    entry->next = dict->head;
    dict->head = entry;
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
    Entry *current = dict->head;
    while (current != NULL) {
        Entry *next = current->next;
        free(current);
        current = next;
    }
    dict->head = NULL;
    dict->count = 0;
    free(dict);
}

int main(void)
{
    Dictionary *dict = dict_create();
    if (dict == NULL) {
        fprintf(stderr, "Failed to allocate dictionary\n");
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