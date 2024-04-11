#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair* pairs;
    size_t size;
} Dictionary;

Dictionary* createDictionary(size_t size) {
    Dictionary* dict = malloc(sizeof(Dictionary));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'dict' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    dict->pairs = malloc(size * sizeof(KeyValuePair));
    dict->size = size;
    return dict;
}

void setPair(Dictionary* dict, size_t index, char* key, char* value) {
    if (index >= dict->size) {
        return;
    }
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*dict.pairs + index * 16' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    dict->pairs[index].key = key;
    dict->pairs[index].value = value;
}

char* getPair(Dictionary* dict, size_t index) {
    if (index >= dict->size) {
        return NULL;
    }
    return dict->pairs[index].value;
}

void freeDictionary(Dictionary* dict) {
    free(dict->pairs);
    free(dict);
}

int main() {
    Dictionary* dict = createDictionary(3);
    setPair(dict, 0, "key1", "value1");
    setPair(dict, 1, "key2", "value2");
    setPair(dict, 2, "key3", "value3");

    printf("%s\n", getPair(dict, 0));
    printf("%s\n", getPair(dict, 1));
    printf("%s\n", getPair(dict, 2));

    freeDictionary(dict);
    return 0;
}