#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

int count_lists(List* const* const lists, int num_lists) {
    if (lists == NULL) {
        return 0;
    }
    
    int count = 0;
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] != NULL) {
            count++;
        }
    }
    return count;
}

int main(void) {
    List* lists[5] = {NULL};
    
    List* list1 = (List*)malloc(sizeof(List));
    List* list2 = (List*)malloc(sizeof(List));
    List* list3 = (List*)malloc(sizeof(List));
    
    if (list1 == NULL || list2 == NULL || list3 == NULL) {
        free(list1);
        free(list2);
        free(list3);
        return 1;
    }
    
    list1->head = NULL;
    list2->head = NULL;
    list3->head = NULL;
    
    lists[0] = list1;
    lists[1] = NULL;
    lists[2] = list2;
    lists[3] = list3;
    lists[4] = NULL;
    
    int result = count_lists(lists, 5);
    printf("Number of lists: %d\n", result);
    
    free(list1);
    free(list2);
    free(list3);
    
    return 0;
}