#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} DictItem;

typedef struct {
    int count;
    DictItem *items;
} Dictionary;

Dictionary* create_dictionary(int size) {
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->items = (DictItem*)malloc(size * sizeof(DictItem));
    return dict;
}

void free_dictionary(Dictionary *dict) {
    for (int i = 0; i < dict->count; ++i) {
        free(dict->items[i].key);
        free(dict->items[i].value);
    }
    free(dict->items);
    free(dict);
}

void add_item(Dictionary *dict, const char *key, const char *value) {
    if (dict->count >= (dict->items == NULL ? 0 : (sizeof(dict->items) / sizeof(DictItem)))) {
        dict->items = (DictItem*)realloc(dict->items, (dict->count + 1) * sizeof(DictItem));
    }
    dict->items[dict->count].key = strdup(key);
    /* Possible weaknesses found:
     *  Possible null pointer dereference: value [nullPointer]
     *  Dereferencing argument value that is null
     *  Null pointer dereference
     *  Null pointer dereference: value [ctunullpointer]
     */
    dict->items[dict->count].value = strdup(value);
    dict->count++;
}

void drop_empty_items(Dictionary *dict) {
    for (int i = 0; i < dict->count; ) {
        if (dict->items[i].value == NULL || strlen(dict->items[i].value) == 0) {
            free(dict->items[i].key);
            free(dict->items[i].value);
            if (i < dict->count - 1) {
                memmove(&dict->items[i], &dict->items[i + 1], (dict->count - i - 1) * sizeof(DictItem));
            }
            dict->count--;
        } else {
            i++;
        }
    }
}

int main() {
    Dictionary *my_dict = create_dictionary(5);
    add_item(my_dict, "first", "value1");
    add_item(my_dict, "second", "");
    add_item(my_dict, "third", "value3");
    /* Possible weaknesses found:
     *  Calling function add_item, 3rd argument is null
     *  Calling function 'add_item', 3rd argument 'NULL' value is 0
     */
    add_item(my_dict, "fourth", NULL);

    drop_empty_items(my_dict);

    for (int i = 0; i < my_dict->count; ++i) {
        printf("Key: %s, Value: %s\n", my_dict->items[i].key, my_dict->items[i].value);
    }

    free_dictionary(my_dict);
    return 0;
}