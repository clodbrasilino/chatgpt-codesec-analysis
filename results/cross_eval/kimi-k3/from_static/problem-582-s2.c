#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_KEY_SIZE 100
#define MAX_VALUE_SIZE 100

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    size_t size;
} Dictionary;

void initDictionary(Dictionary *dict) {
    if (dict != NULL) {
        dict->head = NULL;
        dict->size = 0;
    }
}

bool isEmpty(const Dictionary *dict) {
    if (dict == NULL) {
        return true;
    }
    return (dict->head == NULL && dict->size == 0);
}

bool insert(Dictionary *dict, const char *key, const char *value) {
    if (dict == NULL || key == NULL || value == NULL) {
        return false;
    }
    
    size_t key_len = strnlen(key, MAX_KEY_SIZE);
    if (key_len == 0 || key_len >= MAX_KEY_SIZE) {
        return false;
    }
    
    size_t value_len = strnlen(value, MAX_VALUE_SIZE);
    if (value_len == 0 || value_len >= MAX_VALUE_SIZE) {
        return false;
    }
    
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        return false;
    }
    
    newNode->key = (char *)malloc(key_len + 1);
    if (newNode->key == NULL) {
        free(newNode);
        return false;
    }
    snprintf(newNode->key, key_len + 1, "%s", key);
    
    newNode->value = (char *)malloc(value_len + 1);
    if (newNode->value == NULL) {
        free(newNode->key);
        free(newNode);
        return false;
    }
    snprintf(newNode->value, value_len + 1, "%s", value);
    
    newNode->next = dict->head;
    dict->head = newNode;
    dict->size++;
    
    return true;
}

void freeDictionary(Dictionary *dict) {
    if (dict == NULL) {
        return;
    }
    
    Node *current = dict->head;
    Node *next;
    
    while (current != NULL) {
        next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
    
    dict->head = NULL;
    dict->size = 0;
}

int main(void) {
    Dictionary dict;
    initDictionary(&dict);
    
    if (isEmpty(&dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }
    
    if (!insert(&dict, "name", "John")) {
        fprintf(stderr, "Failed to insert element\n");
        freeDictionary(&dict);
        return EXIT_FAILURE;
    }
    
    if (isEmpty(&dict)) {
        printf("Dictionary is empty\n");
    } else {
        printf("Dictionary is not empty\n");
    }
    
    freeDictionary(&dict);
    
    return EXIT_SUCCESS;
}