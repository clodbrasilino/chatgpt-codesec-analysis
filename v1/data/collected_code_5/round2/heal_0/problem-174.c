#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct dict {
    char key[MAX_SIZE];
    char value[MAX_SIZE];
    struct dict *next;
} Dict;

Dict *create_node(char *key, char *value) {
    Dict *new_node = malloc(sizeof(Dict));
    if(new_node == NULL) {
        printf("Memory allocation failed.\n");
        exit(0);
    }

    strcpy(new_node->key, key);
    strcpy(new_node->value, value);
    new_node->next = NULL;

    return new_node;
}

void insert(Dict **dictionary, char *key, char *value) {
    Dict *new_node = create_node(key, value);

    if(!(*dictionary)) {
        *dictionary = new_node;
    } else {
        Dict *temp = *dictionary;
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void print_dictionary(Dict *dictionary){
    while(dictionary) {
        printf("Key: %s Value: %s\n", dictionary->key, dictionary->value);
        dictionary = dictionary->next;
    }
}

int main(){
    Dict *dictionary = NULL;

    insert(&dictionary, "mango", "yellow");
    insert(&dictionary, "apple", "red");
    insert(&dictionary, "banana", "yellow");
    insert(&dictionary, "grape", "green");

    print_dictionary(dictionary);
    return 0;
}