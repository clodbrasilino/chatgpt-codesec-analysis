#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct List {
    struct Node* head;
    struct List* next;
};

int areListsEqual(struct Node* a, struct Node* b) {
    while (a != NULL && b != NULL) {
        if (a->data != b->data)
            return 0;
        a = a->next;
        b = b->next;
    }
    return (a == NULL && b == NULL);
}

int countUniqueLists(struct List* start) {
    int count = 0;
    struct List* ptr1 = start, *ptr2;
    while (ptr1 != NULL && ptr1->next != NULL) {
        ptr2 = ptr1;
        while (ptr2->next != NULL) {
            if (areListsEqual(ptr1->head, ptr2->next->head))
                break;
            ptr2 = ptr2->next;
        }
        if (ptr2->next == NULL)
            count++;
        ptr1 = ptr1->next;
    }
    if (ptr1 != NULL)
        count++;
    return count;
}

int main() {
    struct List* start = NULL;
    // Assume some code here that populates 'start' with a list of lists
    printf("Number of unique lists: %d\n", countUniqueLists(start));
    return 0;
}