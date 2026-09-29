#include <stdio.h>
#include <stdlib.h>

typedef struct tuple {
    int a;
    int b;
} Tuple;

typedef struct node {
    Tuple data;
    struct node* next;
} Node;

Node* add_tuple_to_list(Node* head, Tuple t) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = t;
    new_node->next = head;
    return new_node;
}

int main() {
    Node* head = NULL;
    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};
    Tuple t3 = {5, 6};

    head = add_tuple_to_list(head, t1);
    if (head == NULL) {
        return -1;
    }

    head = add_tuple_to_list(head, t2);
    if (head == NULL) {
        return -1;
    }
    
    head = add_tuple_to_list(head, t3);
    if (head == NULL) {
        return -1;
    }

    Node* temp = head;
    while(temp != NULL) {
        printf("(%d, %d)\n", temp->data.a, temp->data.b);
        temp = temp->next;
    }

    return 0;
}