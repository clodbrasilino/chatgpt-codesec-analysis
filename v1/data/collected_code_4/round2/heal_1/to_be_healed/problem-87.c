#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

typedef struct {
    char* key;
    char* value;
} item;

typedef struct {
    size_t size;
    item* items;
} dictionary;

item* addItem(item* items, size_t* size, char* key, char* value) {
    items = realloc(items, (*size + 1) * sizeof(item));
    /* Possible weaknesses found:
     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    if (!items) {
        exit(EXIT_FAILURE);
    }
    items[*size].key = strdup(key);
    items[*size].value = strdup(value);
    *size += 1;
    return items;
}

dictionary mergeDicts(dictionary dict1, dictionary dict2, dictionary dict3) {
    dictionary result = {0, NULL};
    for (size_t i = 0; i < dict1.size; ++i) {
        result.items = addItem(result.items, &result.size, dict1.items[i].key, dict1.items[i].value);
    }
    for (size_t i = 0; i < dict2.size; ++i) {
        result.items = addItem(result.items, &result.size, dict2.items[i].key, dict2.items[i].value);
    }
    for (size_t i = 0; i < dict3.size; ++i) {
        result.items = addItem(result.items, &result.size, dict3.items[i].key, dict3.items[i].value);
    }
    return result;
}

int main() {
    dictionary dict1 = {0, NULL};
    dict1.items = addItem(dict1.items, &dict1.size, "key1", "value1");
    dict1.items = addItem(dict1.items, &dict1.size, "key2", "value2");

    dictionary dict2 = {0, NULL};
    dict2.items = addItem(dict2.items, &dict2.size, "key3", "value3");
    dict2.items = addItem(dict2.items, &dict2.size, "key4", "value4");

    dictionary dict3 = {0, NULL};
    dict3.items = addItem(dict3.items, &dict3.size, "key5", "value5");
    dict3.items = addItem(dict3.items, &dict3.size, "key6", "value6");
    
    dictionary result = mergeDicts(dict1, dict2, dict3);

    for (size_t i = 0; i < result.size; ++i) {
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
         */
        printf("%s: %s\n", result.items[i].key, result.items[i].value);
    }
    return 0;
}