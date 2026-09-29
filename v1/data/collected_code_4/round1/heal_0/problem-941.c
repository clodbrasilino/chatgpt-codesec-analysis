#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node_t;

typedef struct Tuple {
    int a;
    int b;
} Tuple_t;

int countUntilTuple(Node_t* head) {
    int count = 0;
    Node_t* current = head;

    while (current != NULL) {
        if (current->data == sizeof(Tuple_t)) {
            break;
        }
        count++;
        current = current->next;
    }
    return count;
}

int main() {
    Node_t* n1 = (Node_t*)malloc(sizeof(Node_t));
    Node_t* n2 = (Node_t*)malloc(sizeof(Node_t));
    Node_t* n3 = (Node_t*)malloc(sizeof(Node_t));
    
    if(n1 == NULL || n2 == NULL || n3 == NULL) {
        printf("Memory not allocated.");
        exit(0);
    }

    n1->data = sizeof(int);
    n1->next = n2;
    n2->data = sizeof(char);
    n2->next = n3;
    n3->data = sizeof(Tuple_t);
    n3->next = NULL;

    int count = countUntilTuple(n1);
    printf("Count of elements until a tuple element: %d\n", count);

    free(n1);
    free(n2);
    free(n3);
    
    return 0;
}