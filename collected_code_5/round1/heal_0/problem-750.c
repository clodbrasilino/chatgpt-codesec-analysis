#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int a;
    int b;
} Tuple;

typedef struct Node {
    Tuple tuple;
    struct Node* next;
} Node;

Node* createNode(Tuple tuple) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if(newNode == NULL) {
        fprintf(stderr, "Failed to allocate memory for a new node.\n");
        exit(1);
    }
    newNode->tuple = tuple;
    newNode->next = NULL;
    return newNode;
}

Node* addTuple(Node* list, Tuple tuple) {
    if(list == NULL) {
        return createNode(tuple);
    }
    else { 
        Node* temp = list;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next =  createNode(tuple);
        return list;
    }
}

int main() {
    Node* list = NULL;

    Tuple tuple1;
    tuple1.a = 1;
    tuple1.b = 2;
    
    Tuple tuple2;
    tuple2.a = 3;
    tuple2.b = 4;

    list = addTuple(list, tuple1);
    list = addTuple(list, tuple2);

    Node* temp = list;
    while(temp != NULL) {
        printf("(%d, %d)\n", temp->tuple.a, temp->tuple.b);
        Node* toFree = temp;
        temp = temp->next;
        free(toFree);
    }

    return 0;
}