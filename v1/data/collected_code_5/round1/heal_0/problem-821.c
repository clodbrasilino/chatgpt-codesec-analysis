#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* key;
    char* value;
} DictItem;

typedef struct {
    DictItem* items;
    size_t size;
} Dictionary;

Dictionary* create_dictionary(size_t size){
    Dictionary* dictionary = malloc(sizeof(Dictionary));
    if(dictionary == NULL){
        printf("Memory not allocated.\n");
        exit(0);
    }
    dictionary->items = malloc(sizeof(DictItem) * size);
    if(dictionary->items == NULL){
        free(dictionary);
        printf("Memory not allocated.\n");
        exit(0);
    }
    dictionary->size = size;
    return dictionary;
}

void add_item(Dictionary* dict, char* key, char* value, int index){
    dict->items[index].key = key;
    dict->items[index].value = value;
}

Dictionary* merge_dictionaries(Dictionary* dict1, Dictionary* dict2){
    size_t newSize = dict1->size + dict2->size;
    Dictionary* mergedDict = create_dictionary(newSize);

    for(size_t i = 0; i < dict1->size; i++){
        add_item(mergedDict, dict1->items[i].key, dict1->items[i].value, i);
    }

    for(size_t i = 0; i < dict2->size; i++){
        add_item(mergedDict, dict2->items[i].key, dict2->items[i].value, i + dict1->size);
    }

    return mergedDict;
}

void print_dictionary(Dictionary* dict){
    for(size_t i = 0; i < dict->size; i++){
        printf("Key: %s Value: %s\n", dict->items[i].key, dict->items[i].value);
    }
}

void free_dictionary(Dictionary* dict){
    free(dict->items);
    free(dict);
}

int main(){
    Dictionary* dict1 = create_dictionary(2);
    add_item(dict1, "Key1", "Value1", 0);
    add_item(dict1, "Key2", "Value2", 1);

    Dictionary* dict2 = create_dictionary(2);
    add_item(dict2, "Key3", "Value3", 0);
    add_item(dict2, "Key4", "Value4", 1);

    Dictionary* merged = merge_dictionaries(dict1, dict2);
    print_dictionary(merged);

    free_dictionary(dict1);
    free_dictionary(dict2);
    free_dictionary(merged);

    return 0;
}