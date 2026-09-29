#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    /* Possible weaknesses found:
     *  struct member 'Node::data' is never used. [unusedStructMember]
     */
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

int count_lists(List **lists, int num_lists) {
    int count = 0;
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] != NULL) {
            count++;
        }
    }
    return count;
}

int main(void) {
    List *lists[3];
    List list1 = {NULL};
    List list2 = {NULL};
    List list3 = {NULL};
    
    lists[0] = &list1;
    lists[1] = &list2;
    lists[2] = &list3;
    
    Node node1 = {1, NULL};
    Node node2 = {2, NULL};
    Node node3 = {3, NULL};
    
    list1.head = &node1;
    node1.next = &node2;
    list2.head = &node3;
    
    printf("Number of lists: %d\n", count_lists(lists, 3));
    
    lists[1] = NULL;
    printf("Number of lists after removing one: %d\n", count_lists(lists, 3));
    
    return 0;
}