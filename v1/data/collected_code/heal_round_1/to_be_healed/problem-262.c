#include<stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

struct Node{
    int data;
    struct Node* next;
};

void splitList(struct Node* head, int length_first_part){
    struct Node* temp = head;
    int count = 0;
    while(temp != NULL){
        count++;
        if(count == length_first_part){
            break;
        }
        temp = temp->next;
    }
    
    if(temp == NULL){
        return;
    }
    
    struct Node* new_head = temp->next;
    temp->next = NULL;
    
    struct Node* current = new_head;
    while(current->next != NULL){
        current = current->next;
    }
    
    current->next = head;
}

int main(){
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;
    struct Node* fourth = NULL;

    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));
    fourth = (struct Node*)malloc(sizeof(struct Node));

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'head' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    head->data = 1;
    head->next = second;
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'second' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    second->data = 2;
    second->next = third;
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'third' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    third->data = 3;
    third->next = fourth;
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'fourth' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    fourth->data = 4;
    fourth->next = NULL;

    splitList(head, 2);

    printf("First part of the list:\n");
    struct Node* temp = head;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\nSecond part of the list:\n");
    temp = second;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    
    return 0;
}