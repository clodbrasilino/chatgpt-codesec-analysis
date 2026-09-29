#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair* pairs;
    size_t size;
} Dictionary;

int isKeyInDictionary(Dictionary* dict, const char* key) {
    for (size_t i = 0; i < dict->size; i++) {
        if (strcmp(dict->pairs[i].key, key) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    Dictionary dict;
    dict.size = 3;
    dict.pairs = malloc(sizeof(KeyValuePair) * dict.size);
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'dict.pairs' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    dict.pairs[0].key = "key1";
    dict.pairs[0].value = "value1";
    dict.pairs[1].key = "key2";
    dict.pairs[1].value = "value2";
    dict.pairs[2].key = "key3";
    dict.pairs[2].value = "value3";

    printf("%s\n", isKeyInDictionary(&dict, "key2") ? "Key found" : "Key not found");
    printf("%s\n", isKeyInDictionary(&dict, "key4") ? "Key found" : "Key not found");

    free(dict.pairs);

    return 0;
}