#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node * next;
}Node;

Node * deleteEven(Node * head){
    Node * prev = NULL;
    Node * current = head;

    while(current != NULL){
        if(current->data % 2 == 0){
            if(prev != NULL){
                prev->next = current->next;
            }
            else{
                head = current->next;
            }
            Node * temp = current;
            current = current->next;
            free(temp);
        }
        else{
            prev = current;
            current = current->next;
        }
    }

    return head;
}

void printList(Node * head){
    Node * current = head;

    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }

    printf("\n");
}

int main(){
    Node * head = malloc(sizeof(Node));
    Node * second = malloc(sizeof(Node));
    Node * third = malloc(sizeof(Node));

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
    third->next = NULL;

    printList(head);

    head = deleteEven(head);

    printList(head);

    free(third);
    /* Possible weaknesses found:
     *  double-'free' of 'second' [CWE-415] [-Wanalyzer-double-free]
     */
    free(second);
    free(head);

    return 0;
}