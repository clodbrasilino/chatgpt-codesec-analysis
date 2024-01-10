#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void append(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    if (new_node == NULL) {
        return;
    }

    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    struct Node* last = *head_ref;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}

char* concatenateList(struct Node* head) {
    char* result = malloc(1); 

    if (result == NULL) {
        return result;
    }      
    result[0] = 0;  

    struct Node* current = head;
    
    while (current != NULL) {
        int size = snprintf(NULL, 0, "%d", current->data); 
        char* temp = realloc(result, strlen(result) + size + 2); 

        if (temp == NULL) {
            free(result);
            return NULL; 
        }
        result = temp;

        snprintf(result + strlen(result), size + 2, "%d", current->data); 
        current = current->next;
    }

    return result;
}

int main() {
    struct Node* head = NULL;

    append(&head, 1);
    append(&head, 2);
    append(&head, 3);

    char* concatenatedString = concatenateList(head);

    if (concatenatedString != NULL) {
        printf("%s\n", concatenatedString);
        free(concatenatedString);
    }

    return 0;
}