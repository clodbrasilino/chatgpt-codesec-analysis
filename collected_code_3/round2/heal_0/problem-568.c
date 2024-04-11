#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICTS 10
#define MAX_KEY_VALUE 100

typedef struct {
    char key[MAX_KEY_VALUE];
    char value[MAX_KEY_VALUE];
} Dictionary;

typedef struct {
    Dictionary dicts[MAX_DICTS];
    int size;
} DictList;

void initDictList(DictList *list) {
    list->size = 0;
}

void addDict(DictList *list, char *key, char *value) {
    if (list->size < MAX_DICTS) {
        strcpy(list->dicts[list->size].key, key);
        strcpy(list->dicts[list->size].value, value);
        list->size++;
    }
}

int main() {
    DictList list;
    initDictList(&list);
    addDict(&list, "key1", "value1");
    addDict(&list, "key2", "value2");
    addDict(&list, "key3", "value3");

    for (int i = 0; i < list.size; i++) {
        printf("Key: %s, Value: %s\n", list.dicts[i].key, list.dicts[i].value);
    }

    return 0;
}