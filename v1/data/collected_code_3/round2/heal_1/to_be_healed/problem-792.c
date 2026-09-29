#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

int countLists(List* lists[], int size) {
    int count = 0;
    for(int i = 0; i < size; i++) {
        if(lists[i] != NULL) {
            count++;
        }
    }
    return count;
}

int main() {
    List* lists[5];
    for(int i = 0; i < 5; i++) {
        lists[i] = NULL;
    }
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    lists[0] = (List*)malloc(sizeof(List));
    lists[2] = (List*)malloc(sizeof(List));
    lists[4] = (List*)malloc(sizeof(List));

    printf("Number of lists: %d\n", countLists(lists, 5));

    return 0;
}