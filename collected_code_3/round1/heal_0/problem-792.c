#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

int countLists(List** lists, int numLists) {
    int count = 0;
    for(int i = 0; i < numLists; i++) {
        if(lists[i] != NULL) {
            count++;
        }
    }
    return count;
}

int main() {
    int numLists = 5;
    List* lists[5] = {NULL, NULL, NULL, NULL, NULL};

    printf("Number of lists: %d\n", countLists(lists, numLists));

    return 0;
}