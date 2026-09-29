#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* stringToList(char* str) {
    if(str == NULL)
        return NULL;
    Node* head = malloc(sizeof(Node));
    if(head == NULL)
        return NULL;
    head->data = str[0];  

    Node* current = head;
    size_t length = strlen(str);
    
    for(size_t i = 1; i < length; i++) {
        Node* newNode = malloc(sizeof(Node));
        if(newNode == NULL)
            return NULL;
        newNode->data = str[i];
        current->next = newNode;
        current = newNode;
    }
    current->next = NULL;
    return head;
}

void freeList(Node* head) {
    Node* tmp;
    while(head != NULL) {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

int main() {
    char myString[] = "Hello World!";
    Node* list = stringToList(myString);
    
    if(list == NULL) {
        printf("Fail to convert string to list due to insufficient memory\n");
        return -1;
    }

    Node* current = list;
    while(current != NULL){
        printf("%c", current->data);
        current = current->next;
    }
    printf("\n");
    freeList(list);
    return 0;
}