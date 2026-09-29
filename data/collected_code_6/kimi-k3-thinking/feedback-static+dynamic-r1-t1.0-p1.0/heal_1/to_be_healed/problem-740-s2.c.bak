#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char *copy;
    size_t length;

    if (str == NULL) {
        return NULL;
    }

    length = strlen(str) + 1;
    copy = (char *)malloc(length);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, str, length);
    return copy;
}

void free_dictionary(Dictionary *dict)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (dict == NULL) {
        return;
    }

    if (dict->pairs != NULL) {
        for (i = 0; i < dict->size; i++) {
            free(dict->pairs[i].key);
            free(dict->pairs[i].value);
        }
        free(dict->pairs);
        dict->pairs = NULL;
    }

    dict->size = 0;
}

int tuple_to_dictionary(const char **tuple, size_t tuple_size, Dictionary *dict)
{
    size_t i;

    if (tuple == NULL || dict == NULL) {
        return -1;
    }

    dict->pairs = NULL;
    dict->size = 0;

    if (tuple_size % 2 != 0) {
        return -1;
    }

    dict->size = tuple_size / 2;

    if (dict->size == 0) {
        return 0;
    }

    dict->pairs = (KeyValuePair *)calloc(dict->size, sizeof(KeyValuePair));
    if (dict->pairs == NULL) {
        dict->size = 0;
        return -1;
    }

    for (i = 0; i < dict->size; i++) {
        dict->pairs[i].key = duplicate_string(tuple[i * 2]);
        dict->pairs[i].value = duplicate_string(tuple[i * 2 + 1]);
        if (dict->pairs[i].key == NULL || dict->pairs[i].value == NULL) {
            free_dictionary(dict);
            return -1;
        }
    }

    return 0;
}

void print_dictionary(const Dictionary *dict)
{
    size_t i;

    if (dict == NULL) {
        return;
    }

    for (i = 0; i < dict->size; i++) {
        printf("%s: %s\n", dict->pairs[i].key, dict->pairs[i].value);
    }
}

int main(void)
{
    const char *tuple[] = {"name", "Alice", "age", "30", "city", "New York"};
    size_t tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    Dictionary dict;

    if (tuple_to_dictionary(tuple, tuple_size, &dict) != 0) {
        fprintf(stderr, "Error: failed to convert tuple to dictionary\n");
        return EXIT_FAILURE;
    }

    print_dictionary(&dict);

    free_dictionary(&dict);

    return EXIT_SUCCESS;
}