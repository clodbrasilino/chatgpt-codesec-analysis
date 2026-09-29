#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValue {
    char *key;
    int value;
    struct KeyValue *next;
} KeyValue;

typedef struct {
    KeyValue *head;
} Dictionary;

void dict_init(Dictionary *dict) {
    dict->head = NULL;
}

void dict_add(Dictionary *dict, const char *key, int value) {
    KeyValue *new_pair = (KeyValue *)malloc(sizeof(KeyValue));
    if (new_pair == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_pair->key = (char *)malloc(strlen(key) + 1);
    if (new_pair->key == NULL) {
        free(new_pair);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_pair->key, key);
    new_pair->value = value;
    new_pair->next = dict->head;
    dict->head = new_pair;
}

int sum_dictionary(const Dictionary *dict) {
    int sum = 0;
    KeyValue *current = dict->head;
    while (current != NULL) {
        sum += current->value;
        current = current->next;
    }
    return sum;
}

void dict_free(Dictionary *dict) {
    KeyValue *current = dict->head;
    while (current != NULL) {
        KeyValue *next = current->next;
        free(current->key);
        free(current);
        current = next;
    }
    dict->head = NULL;
}

int main(void) {
    Dictionary dict;
    dict_init(&dict);
    
    dict_add(&dict, "apple", 5);
    dict_add(&dict, "banana", 3);
    dict_add(&dict, "orange", 7);
    dict_add(&dict, "grape", 2);
    
    int total = sum_dictionary(&dict);
    printf("Sum of all items: %d\n", total);
    
    dict_free(&dict);
    
    return 0;
}