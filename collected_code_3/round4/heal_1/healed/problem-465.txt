#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *key;
    char *value;
    struct node *next;
} node;

node *create_node(char *key, char *value) {
    node *new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL){
        return NULL;
    }

    new_node->key = strdup(key);
    if(new_node->key == NULL){
        free(new_node);
        return NULL;
    }
    
    new_node->value = strdup(value);
    if(new_node->value == NULL){
        free(new_node->key);
        free(new_node);
        return NULL;
    }
    
    new_node->next = NULL;
    return new_node;
}

void drop_empty(node **head) {
    node *temp = *head, *prev;
    while (temp != NULL && (temp->value == NULL || temp->value[0] == '\0')) {
        *head = temp->next;
        free(temp->key);
        free(temp->value);
        free(temp);
        temp = *head;
    }
    while (temp != NULL) {
        while (temp != NULL && (temp->value == NULL || temp->value[0] != '\0')) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) return;
        prev->next = temp->next;
        free(temp->key);
        free(temp->value);
        free(temp);
        temp = prev->next;
    }
}

int main() {
    node *head = create_node("key1", "value1");
    node *temp = create_node("key2", "");
    if(temp == NULL || head == NULL){
        return 1;
    }
    head->next = temp;
    
    temp = create_node("key3", "value3");
    if(temp == NULL){
        return 1;
    }
    head->next->next = temp;
    
    temp = create_node("key4", "");
    if(temp == NULL){
        return 1;
    }
    head->next->next->next = temp;

    drop_empty(&head);

    temp = head;
    while(temp != NULL) {
        printf("%s: %s\n", temp->key, temp->value);
        temp = temp->next;
    }

    return 0;
}