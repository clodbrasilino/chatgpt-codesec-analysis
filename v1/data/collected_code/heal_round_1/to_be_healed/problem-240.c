#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void replaceLastElement(struct Node** head1, struct Node* head2) {
    struct Node* temp = *head1;
    
    if(temp == NULL) {
        *head1 = head2;
        return;
    }
    
    while(temp->next != NULL) {
        temp = temp->next;
    }
    
    temp->next = head2;
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    
    // Create the first linked list
    head1 = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'head1' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    head1->data = 1;
    head1->next = NULL;
    
    struct Node* second1 = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'second1' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    second1->data = 2;
    second1->next = NULL;
    
    struct Node* third1 = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'third1' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    third1->data = 3;
    third1->next = NULL;
    
    head1->next = second1;
    second1->next = third1;
    
    // Create the second linked list
    head2 = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'head2' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    head2->data = 4;
    head2->next = NULL;
    
    struct Node* second2 = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'second2' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    second2->data = 5;
    second2->next = NULL;
    
    struct Node* third2 = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'third2' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    third2->data = 6;
    third2->next = NULL;
    
    head2->next = second2;
    second2->next = third2;
    
    // Replace the last element of the first list with the second list
    replaceLastElement(&head1, head2);
    
    // Test the result
    struct Node* temp = head1;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    
    return 0;
}