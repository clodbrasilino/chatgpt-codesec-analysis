#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* key;
    struct Node* value;
    struct Node* next;
} Node;

Node* createNode(char* key, Node* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) {
        return NULL;
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

Node* convertListToDict(char** keys, Node** values, int size) {
    if(keys == NULL || values == NULL) {
        return NULL;
    }
    Node* head = NULL;
    Node* temp = NULL;

    for(int i = 0; i < size; i++) {
        if(head == NULL) {
            head = createNode(keys[i], values[i]);
            if(head == NULL) {
                return NULL;
            }
            temp = head;
        } else {
            temp->next = createNode(keys[i], values[i]);
            if(temp->next == NULL) {
                return NULL;
            }
            temp = temp->next;
        }
    }
    return head;
}

void printDict(Node* head) {
    Node* temp = head;
    while(temp != NULL) {
        printf("%s -> ", temp->key);
        Node* innerTemp = temp->value;

        while(innerTemp != NULL) {
            printf("%s -> ", innerTemp->key);
            innerTemp = innerTemp->next;
        }
        printf("NULL\n");
        temp = temp->next;
    }
}

int main() {
    Node* innerDict1 = convertListToDict((char*[]){"key1", "key2", NULL}, (Node*[]){NULL, NULL}, 2);
    Node* innerDict2 = convertListToDict((char*[]){"key3", "key4", NULL}, (Node*[]){NULL, NULL}, 2);
    Node* dict = convertListToDict((char*[]){"outerKey1", "outerKey2", NULL}, (Node*[]){innerDict1, innerDict2}, 2);

    if(dict == NULL) {
        return 1;
    }

    printDict(dict);

    return 0;
}