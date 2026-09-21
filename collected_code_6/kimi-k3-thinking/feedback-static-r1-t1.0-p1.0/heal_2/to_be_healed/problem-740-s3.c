#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    size_t size;
} Dictionary;

static char *duplicate_string(const char *str)
{
    size_t len;
    char *copy;

    if (str == NULL) {
        return NULL;
    }
    len = strnlen(str, MAX_STRING_LENGTH);
    if (len == MAX_STRING_LENGTH) {
        return NULL;
    }
    copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, str, len);
    copy[len] = '\0';
    return copy;
}

int tuple_to_dictionary(const char *tuple[], size_t tuple_size, Dictionary *dict)
{
    size_t i;
    size_t j;

    if (tuple == NULL || dict == NULL) {
        return -1;
    }
    dict->pairs = NULL;
    dict->size = 0;
    if (tuple_size % 2 != 0) {
        return -1;
    }
    if (tuple_size == 0) {
        return 0;
    }
    dict->pairs = (KeyValuePair *)calloc(tuple_size / 2, sizeof(KeyValuePair));
    if (dict->pairs == NULL) {
        return -1;
    }
    for (i = 0; i < tuple_size / 2; i++) {
        dict->pairs[i].key = duplicate_string(tuple[2 * i]);
        dict->pairs[i].value = duplicate_string(tuple[2 * i + 1]);
        if (dict->pairs[i].key == NULL || dict->pairs[i].value == NULL) {
            for (j = 0; j <= i; j++) {
                free(dict->pairs[j].key);
                free(dict->pairs[j].value);
            }
            free(dict->pairs);
            dict->pairs = NULL;
            dict->size = 0;
            return -1;
        }
    }
    dict->size = tuple_size / 2;
    return 0;
}

void free_dictionary(Dictionary *dict)
{
    size_t i;

    if (dict == NULL) {
        return;
    }
    for (i = 0; i < dict->size; i++) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
    dict->pairs = NULL;
    dict->size = 0;
}

void print_dictionary(const Dictionary *dict)
{
    size_t i;

    if (dict == NULL) {
        return;
    }
    printf("{");
    for (i = 0; i < dict->size; i++) {
        printf("'%s': '%s'", dict->pairs[i].key, dict->pairs[i].value);
        if (i + 1 < dict->size) {
            printf(", ");
        }
    }
    printf("}\n");
}

int main(void)
{
    const char *tuple[] = {"a", "1", "b", "2", "c", "3"};
    const size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    Dictionary dict;

    if (tuple_to_dictionary(tuple, tuple_size, &dict) != 0) {
        fprintf(stderr, "Error: failed to convert tuple to dictionary\n");
        return EXIT_FAILURE;
    }
    print_dictionary(&dict);
    free_dictionary(&dict);
    return EXIT_SUCCESS;
}