#include <stdio.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

bool have_common_element(const Node* list1, const Node* list2) {
    if (!list1 || !list2) {
        return false;
    }

    const Node* current1 = list1;
    while (current1 != NULL) {
        const Node* current2 = list2;
        while (current2 != NULL) {
            if (current1->data == current2->data) {
                return true;
            }
            current2 = current2->next;
        }
        current1 = current1->next;
    }

    return false;
}

int main(void) {
    Node node1 = {1, NULL};
    Node node2 = {2, NULL};
    Node node3 = {3, NULL};
    
    node1.next = &node2;
    node2.next = &node3;

    Node node4 = {4, NULL};
    Node node5 = {2, NULL};
    Node node6 = {6, NULL};
    
    node4.next = &node5;
    node5.next = &node6;

    bool result = have_common_element(&node1, &node4);
    
    if (result) {
        printf("Lists have at least one common element.\n");
    } else {
        printf("Lists do not have any common elements.\n");
    }

    return 0;
}