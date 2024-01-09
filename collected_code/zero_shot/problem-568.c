#include <stdio.h>
#include <stdlib.h>

typedef struct dictionary {
    struct dictionary* next;
} Dictionary;

Dictionary* createList(int num) {
    Dictionary* head = (Dictionary*)malloc(sizeof(Dictionary));
    Dictionary* current = head;
    
    for (int i = 0; i < num - 1; i++) {
        current->next = (Dictionary*)malloc(sizeof(Dictionary));
        current = current->next;
    }
    
    current->next = NULL;
    
    return head;
}

int main() {
    int num = 5;
    Dictionary* list = createList(num);
    
    // Do something with the list
    
    // Free the memory
    Dictionary* current = list;
    Dictionary* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    return 0;
}