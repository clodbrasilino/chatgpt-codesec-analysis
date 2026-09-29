#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} Pair;

typedef struct {
    Pair *pairs;
    int length;
} KeyValueDict;

void free_key_value_dict(KeyValueDict *dict) {
    for (int i = 0; i < dict->length; i++) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
}

KeyValueDict convert_to_dict(char **tuple, int length) {
    if (length % 2 != 0) return (KeyValueDict){NULL, 0};

    KeyValueDict dict;
    dict.length = length / 2;
    dict.pairs = malloc(dict.length * sizeof(Pair));
    if (dict.pairs == NULL) return (KeyValueDict){NULL, 0};

    for (int i = 0, j = 0; i < length; i += 2, j++) {
        int key_len = strlen(tuple[i]) + 1;
        int value_len = strlen(tuple[i + 1]) + 1;
        dict.pairs[j].key = malloc(key_len);
        dict.pairs[j].value = malloc(value_len);
        if (dict.pairs[j].key == NULL || dict.pairs[j].value == NULL) {
            free_key_value_dict(&dict);
            return (KeyValueDict){NULL, 0};
        }
        strcpy(dict.pairs[j].key, tuple[i]);
        strcpy(dict.pairs[j].value, tuple[i + 1]);
    }

    return dict;
}

void print_dict(KeyValueDict dict) {
    for (int i = 0; i < dict.length; i++) {
        printf("%s: %s\n", dict.pairs[i].key, dict.pairs[i].value);
    }
}

int main() {
    char *tuple[] = {"key1", "value1", "key2", "value2", "key3", "value3"};
    int length = sizeof(tuple) / sizeof(tuple[0]);

    KeyValueDict dict = convert_to_dict(tuple, length);
    if (dict.pairs == NULL) {
        printf("Failed to create dictionary.\n");
        return 1;
    }

    print_dict(dict);

    free_key_value_dict(&dict);
    return 0;
}