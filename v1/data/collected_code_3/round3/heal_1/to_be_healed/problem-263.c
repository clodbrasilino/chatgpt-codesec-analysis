#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* key;
    char* value;
} Item;

typedef struct {
    Item* items;
    int size;
    int capacity;
} Dictionary;

Dictionary* createDictionary() {
    Dictionary* dictionary = malloc(sizeof(Dictionary));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'dictionary' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    dictionary->items = malloc(sizeof(Item) * 10);
    dictionary->size = 0;
    dictionary->capacity = 10;
    return dictionary;
}

void add(Dictionary* dictionary, char* key, char* value) {
    if (dictionary->size == dictionary->capacity) {
        dictionary->capacity *= 2;
        dictionary->items = realloc(dictionary->items, sizeof(Item) * dictionary->capacity);
    }
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*dictionary.items + (long unsigned int)*dictionary.size * 16' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    dictionary->items[dictionary->size].key = key;
    dictionary->items[dictionary->size].value = value;
    dictionary->size++;
}

Dictionary* merge(Dictionary* dict1, Dictionary* dict2) {
    Dictionary* merged = createDictionary();
    for (int i = 0; i < dict1->size; i++) {
        add(merged, dict1->items[i].key, dict1->items[i].value);
    }
    for (int i = 0; i < dict2->size; i++) {
        add(merged, dict2->items[i].key, dict2->items[i].value);
    }
    return merged;
}

void printDictionary(Dictionary* dictionary) {
    for (int i = 0; i < dictionary->size; i++) {
        printf("%s: %s\n", dictionary->items[i].key, dictionary->items[i].value);
    }
}

int main() {
    Dictionary* dict1 = createDictionary();
    add(dict1, "key1", "value1");
    add(dict1, "key2", "value2");

    Dictionary* dict2 = createDictionary();
    add(dict2, "key3", "value3");
    add(dict2, "key4", "value4");

    Dictionary* merged = merge(dict1, dict2);
    printDictionary(merged);

    free(dict1->items);
    free(dict1);
    free(dict2->items);
    free(dict2);
    free(merged->items);
    free(merged);

    return 0;
}