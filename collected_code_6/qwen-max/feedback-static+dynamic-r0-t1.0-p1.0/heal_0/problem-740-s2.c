#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    int length;
} Dictionary;

Dictionary* tuple_to_dict(char **tuple, int n) {
    if (n % 2 != 0) return NULL;
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    dict->length = n / 2;
    dict->pairs = (KeyValuePair *)malloc(dict->length * sizeof(KeyValuePair));
    if (!dict->pairs) {
        free(dict);
        return NULL;
    }
    for (int i = 0; i < n; i += 2) {
        dict->pairs[i / 2].key = strdup(tuple[i]);
        dict->pairs[i / 2].value = strdup(tuple[i + 1]);
        if (!dict->pairs[i / 2].key || !dict->pairs[i / 2].value) {
            while (i-- > 0) {
                free(dict->pairs[i / 2].key);
                free(dict->pairs[i / 2].value);
            }
            free(dict->pairs);
            free(dict);
            return NULL;
        }
    }
    return dict;
}

void dict_free(Dictionary *dict) {
    for (int i = 0; i < dict->length; ++i) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
    free(dict);
}

int main() {
    char *tuple[] = {"key1", "value1", "key2", "value2", "key3", "value3"};
    int n = 6;
    Dictionary *dict = tuple_to_dict(tuple, n);
    if (dict) {
        for (int i = 0; i < dict->length; ++i) {
            printf("Key: %s, Value: %s\n", dict->pairs[i].key, dict->pairs[i].value);
        }
        dict_free(dict);
    } else {
        fprintf(stderr, "Failed to create dictionary.\n");
    }
    return 0;
}