#include <stdio.h>
#include <stdlib.h>

struct Node {
    /* Possible weaknesses found:
     *  struct member 'Node::data' is never used. [unusedStructMember]
     */
    int data;
    struct Node* next;
};

struct List {
    struct Node* head;
};

int countLists(struct List** lists, int numLists) {
    if (lists == NULL) {
        return 0;
    }
    
    int count = 0;
    for (int i = 0; i < numLists; i++) {
        if (lists[i] != NULL) {
            count++;
        }
    }
    
    return count;
}

void freeNode(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }
}

void freeLists(struct List** lists, int numLists) {
    if (lists == NULL) {
        return;
    }
    
    for (int i = 0; i < numLists; i++) {
        if (lists[i] != NULL) {
            freeNode(lists[i]->head);
            free(lists[i]);
            lists[i] = NULL;
        }
    }
    free(lists);
}

int main() {
    int numLists = 5;
    struct List** lists = (struct List**)malloc(numLists * sizeof(struct List*));
    if (lists == NULL) {
        return 1;
    }

    for (int i = 0; i < numLists; i++) {
        lists[i] = (struct List*)malloc(sizeof(struct List));
        if (lists[i] == NULL) {
            freeLists(lists, i);
            return 1;
        }
        lists[i]->head = NULL;
    }

    int listCount = countLists(lists, numLists);
    printf("Number of lists: %d\n", listCount);

    freeLists(lists, numLists);

    return 0;
}