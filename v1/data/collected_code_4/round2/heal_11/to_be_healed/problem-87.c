#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} item;

typedef struct {
    size_t size;
    item* items;
} dictionary;

item* addItem(item* items, size_t* size, char* key, char* value) {
    item* newItems = realloc(items, (*size + 1) * sizeof(item));

    /* Possible weaknesses found:
     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    if(!newItems) {
        /* Possible weaknesses found:
         *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        free(items);
        return NULL;
    }  

    newItems[*size].key = strdup(key);
    if(!newItems[*size].key) {
        /* Possible weaknesses found:
         *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        free(newItems);
        return NULL;
    }

    newItems[*size].value = strdup(value);
    if(!newItems[*size].value) {
        free(newItems[*size].key);
        /* Possible weaknesses found:
         *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        free(newItems);
        return NULL;
    } 

    (*size)++;
    return newItems;
}

void freeItem(item* items, size_t size) {
    for(size_t i = 0; i < size; i++) {
        free(items[i].key);
        free(items[i].value);
    }
    free(items);
}

dictionary mergeDicts(dictionary dict1, dictionary dict2, dictionary dict3) {
    dictionary result = {0, NULL};

    for(size_t i = 0; i < dict1.size; ++i) {
        result.items = addItem(result.items, &result.size, dict1.items[i].key, dict1.items[i].value);
    }
    for(size_t i = 0; i < dict2.size; ++i) {
        result.items = addItem(result.items, &result.size, dict2.items[i].key, dict2.items[i].value);
    }
    for(size_t i = 0; i < dict3.size; ++i) {
        result.items = addItem(result.items, &result.size, dict3.items[i].key, dict3.items[i].value);
    }

    return result;
}

int main() {
    dictionary dict1 = {0, NULL}, dict2 = {0, NULL}, dict3 = {0, NULL};

    dict1.items = addItem(dict1.items, &dict1.size, "key1", "value1");
    dict1.items = addItem(dict1.items, &dict1.size, "key2", "value2");
    dict2.items = addItem(dict2.items, &dict2.size, "key3", "value3");
    dict2.items = addItem(dict2.items, &dict2.size, "key4", "value4");
    dict3.items = addItem(dict3.items, &dict3.size, "key5", "value5");
    dict3.items = addItem(dict3.items, &dict3.size, "key6", "value6");

    dictionary result = mergeDicts(dict1, dict2, dict3);

    for(size_t i = 0; i < result.size; ++i) {
        printf("%s: %s\n", result.items[i].key, result.items[i].value);
    }

    freeItem(result.items, result.size);
    freeItem(dict1.items, dict1.size);
    freeItem(dict2.items, dict2.size);
    freeItem(dict3.items, dict3.size);

    return 0;
}