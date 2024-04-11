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
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = NULL;
    return new_node;
}

void drop_empty(node **head) {
    node *temp = *head, *prev;
    while (temp != NULL && temp->value[0] == '\0') {
        *head = temp->next;  
        free(temp);
        temp = *head;
    }
    while (temp != NULL) {
        while (temp != NULL && temp->value[0] != '\0') {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) return;
        prev->next = temp->next;
        free(temp);
        temp = prev->next;
    }
}

int main() {
    node *head = create_node("key1", "value1");
    head->next = create_node("key2", "");
    head->next->next = create_node("key3", "value3");
    head->next->next->next = create_node("key4", "");

    drop_empty(&head);

    node *temp = head;
    while(temp != NULL) {
        printf("%s: %s\n", temp->key, temp->value);
        temp = temp->next;
    }

    return 0;
}