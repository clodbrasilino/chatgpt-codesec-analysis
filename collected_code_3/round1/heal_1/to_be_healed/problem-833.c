#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair* pairs;
    int size;
} Dictionary;

char** getKeys(Dictionary* dict) {
    char** keys = malloc(sizeof(char*) * dict->size);
    for(int i = 0; i < dict->size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'keys' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        keys[i] = dict->pairs[i].key;
    }
    return keys;
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

    char** keys = getKeys(&dict);
    for(int i = 0; i < dict.size; i++) {
        printf("%s\n", keys[i]);
    }

    free(keys);
    free(dict.pairs);

    return 0;
}