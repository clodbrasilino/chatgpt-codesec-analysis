#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct list {
    Node* head;
    struct list* next;
} List;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List* createList(Node* node) {
    List* newList = (List*)malloc(sizeof(List));
    newList->head = node;
    newList->next = NULL;
    return newList;
}

int compareLists(Node* a, Node* b) {
    while(a != NULL && b != NULL) {
        if(a->data != b->data)
            return 0;
        a = a->next;
        b = b->next;
    }
    if(a != NULL || b != NULL)
        return 0;
    return 1;
}

int countUniqueLists(List* list) {
    int count = 0;
    for(List* i = list; i != NULL; i = i->next) {
        int isUnique = 1;
        for(List* j = list; j != i; j = j->next) {
            if(compareLists(i->head, j->head)) {
                isUnique = 0;
                break;
            }
        }
        if(isUnique)
            count++;
    }
    return count;
}

int main() {
    Node* a = createNode(1);
    a->next = createNode(2);
    a->next->next = createNode(3);

    Node* b = createNode(1);
    b->next = createNode(2);
    b->next->next = createNode(3);

    Node* c = createNode(4);
    c->next = createNode(5);
    c->next->next = createNode(6);

    List* list = createList(a);
    list->next = createList(b);
    list->next->next = createList(c);

    printf("%d\n", countUniqueLists(list));

    return 0;
}