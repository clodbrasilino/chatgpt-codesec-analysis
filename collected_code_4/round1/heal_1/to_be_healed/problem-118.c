#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* convertToList(char* str) {
    if (str == NULL || *str == '\0') return NULL;
  
    Node *head = malloc(sizeof(Node));
    if (head == NULL) return NULL;
    
    Node *temp = head;
    for (size_t i = 0; i < strlen(str); i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'temp' [CWE-690] [-Wanalyzer-possible-null-dereference]
         *  dereference of NULL 'temp' [CWE-476] [-Wanalyzer-null-dereference]
         */
        temp->data = str[i];
        temp->next = i < strlen(str) - 1 ? malloc(sizeof(Node)) : NULL;
        if (i < strlen(str) - 1 && temp->next == NULL) {
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
        /* Possible weaknesses found:
         *  use of uninitialized value '*temp.data' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        printf("%c ", temp -> data);
        temp = temp -> next;
    }

    // free memory
    Node *ptr = list;
    while (ptr) {
        Node *del = ptr;
        ptr = ptr->next;
        free(del);
    }

    return 0;
}