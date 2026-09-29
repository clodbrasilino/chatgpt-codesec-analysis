#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} List;

List* createList() {
    return (List*)malloc(sizeof(List));
}

void addNode(List *list, int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *temp = list->head;
        /* Possible weaknesses found:
         * UBSan: member access within misaligned address 0xbebebebebebebebe for type 'Node' (aka 'struct Node'), which requires 8 byte alignment
         * ASan: SEGV
         * UBSan: load of misaligned address 0xbebebebebebebec6 for type 'struct Node *', which requires 8 byte alignment
         */
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int sublistCount(List *list, int target) {
    int count = 0;
    for (Node *curr = list->head; curr != NULL; curr = curr->next) {
        if (curr->data == target) {
            count++;
        }
    }
    return count;
}

int main() {
    List *list = createList();
    if (list == NULL) {
        return -1;
    }

    addNode(list, 1);
    addNode(list, 2);
    addNode(list, 3);
    addNode(list, 2);
    addNode(list, 4);
    addNode(list, 2);

    int target = 2;
    int count = sublistCount(list, target);
    printf("Number of sublists containing %d: %d\n", target, count);

    Node *curr = list->head;
    while (curr != NULL) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);

    return 0;
}