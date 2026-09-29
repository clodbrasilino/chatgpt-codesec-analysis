#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* convertToList(char* str) {
    if (str == NULL || *str == '\0') return NULL;
  
    Node *head = (Node *) malloc(sizeof(Node));
    if (head == NULL) return NULL;

    Node *temp = head;
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        temp->data = str[i];
        temp->next = (i < len - 1) ? (Node *) malloc(sizeof(Node)) : NULL;
        if (temp->next == NULL && i < len - 1) {
            Node *ptr = head;
            while (ptr) {
                Node *del = ptr;
                ptr = ptr->next;
                free(del);
            }
            return NULL;
        }
        temp = temp->next;
    }
    return head;
}

int main() {
    char str[] = "Hello World!";
    Node* list = convertToList(str);
  
    Node* temp = list;
    while(temp != NULL){
        printf("%c ", temp -> data);
        temp = temp -> next;
    }

    Node *ptr = list;
    while (ptr) {
        Node *del = ptr;
        ptr = ptr->next;
        free(del);
    }

    return 0;
}