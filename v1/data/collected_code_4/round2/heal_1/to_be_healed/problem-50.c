#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

struct Node {
    int data;
    struct Node* next;
};

typedef struct List {
    struct Node* head;
    int size;
} List;

List* createList() {
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    List* newList = (List*) malloc(sizeof(List));
    newList->head = NULL;
    newList->size = 0;
    return newList;
}

/* Possible weaknesses found:
 *  unknown type name 'Node'; use 'struct' keyword to refer to the type
 */
Node* createNode(int data) {
    /* Possible weaknesses found:
     *  unknown type name 'Node'; use 'struct' keyword to refer to the type
     *  each undeclared identifier is reported only once for each function it appears in
     *  'Node' undeclared (first use in this function)
     *  expected expression before ')' token
     */
    Node* newNode = (Node*) malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  request for member 'data' in something not a structure or union
     */
    newNode->data = data;
    /* Possible weaknesses found:
     *  request for member 'next' in something not a structure or union
     */
    newNode->next = NULL;
    return newNode;
}

void addNode(List* list, int data) {
    /* Possible weaknesses found:
     *  unknown type name 'Node'; use 'struct' keyword to refer to the type
     */
    Node* newNode = createNode(data);
    /* Possible weaknesses found:
     *  request for member 'next' in something not a structure or union
     */
    newNode->next = list->head;
    /* Possible weaknesses found:
     *  assignment to 'struct Node *' from incompatible pointer type 'int *' [-Wincompatible-pointer-types]
     */
    list->head = newNode;
    list->size++;
}

List* findShortestList(List** lists, int size) {
    if(size == 0) return NULL;
    List* shortestList = lists[0];
    for(int i = 1; i < size; i++) {
        if(lists[i]->size < shortestList->size) {
            shortestList = lists[i];
        }
    }
    return shortestList;
}

int main() {
    int numLists = 3;
    List* lists[numLists];
    
    for(int i = 0; i < numLists; i++) {
        lists[i] = createList();
        for(int j = i; j < 5; j++) {
            addNode(lists[i], j);
        }
    }
    
    List* shortestList = findShortestList(lists, numLists);
    printf("Shortest list size: %d\n", shortestList->size);
    
    for(int i = 0; i < numLists; i++) {
        /* Possible weaknesses found:
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
         */
        free(lists[i]);
    }

    return 0;
}