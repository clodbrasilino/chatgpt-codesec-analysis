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
    if(newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List* createList(Node* node) {
    List* newList = (List*)malloc(sizeof(List));
    if(newList == NULL){
        return NULL;
    }
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
    Node* b = createNode(2);
    Node* c = createNode(3);

    if(a == NULL || b == NULL || c == NULL) {
        return -1;
    }

    a->next = b;
    b->next = c;

    Node* d = createNode(4);
    Node* e = createNode(5);
    Node* f = createNode(6);

    if(d == NULL || e == NULL || f == NULL) {
        return -1;
    }

    d->next = e;
    e->next = f;

    List* list = createList(a);
    List* list2 = createList(d);

    if(list == NULL || list2 == NULL) {
        return -1;
    }

    list->next = list2;

    printf("%d\n", countUniqueLists(list));

    return 0;
}