#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* ConvertStringToList(char* str) {
    if(str == NULL){
        return NULL;
    }
    Node* head = NULL;
    Node* tail = NULL;
    while (*str != '\0') {
        Node* new_node = malloc(sizeof(Node));
        if(new_node == NULL) {
            /* Possible weaknesses found:
             *  Potential leak of memory pointed to by 'tail' [unix.Malloc]
             */
            return NULL;
        }
        new_node->data = *str;
        new_node->next = NULL;
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        /* Possible weaknesses found:
         *  expanded from macro 'NULL'
         */
        str++;
    }
    return head;
}

int main(){
    char str[] = "Hello";
    Node* head = ConvertStringToList(str);

    if(head == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    Node* current = head;
    while (current != NULL) {
        printf("%c ", current->data);
        current = current->next;
    }

    // Freeing memory
    current = head;
    /* Possible weaknesses found:
     *  expanded from macro '__DARWIN_NULL'
     */
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}