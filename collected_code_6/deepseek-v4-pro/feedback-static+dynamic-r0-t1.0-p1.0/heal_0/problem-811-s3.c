#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int first;
    int second;
} Tuple;

typedef struct TupleNode {
    Tuple data;
    struct TupleNode *next;
} TupleNode;

TupleNode *create_node(int first, int second) {
    TupleNode *new_node = (TupleNode *)malloc(sizeof(TupleNode));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data.first = first;
    new_node->data.second = second;
    new_node->next = NULL;
    return new_node;
}

void append_node(TupleNode **head, int first, int second) {
    TupleNode *new_node = create_node(first, second);
    if (new_node == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    TupleNode *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void free_list(TupleNode *head) {
    TupleNode *current = head;
    while (current != NULL) {
        TupleNode *temp = current;
        current = current->next;
        free(temp);
    }
}

int are_lists_identical(TupleNode *list1, TupleNode *list2) {
    TupleNode *current1 = list1;
    TupleNode *current2 = list2;
    
    while (current1 != NULL && current2 != NULL) {
        if (current1->data.first != current2->data.first ||
            current1->data.second != current2->data.second) {
            return 0;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    
    return current1 == NULL && current2 == NULL;
}

int main(void) {
    TupleNode *list1 = NULL;
    TupleNode *list2 = NULL;
    
    append_node(&list1, 1, 2);
    append_node(&list1, 3, 4);
    append_node(&list1, 5, 6);
    
    append_node(&list2, 1, 2);
    append_node(&list2, 3, 4);
    append_node(&list2, 5, 6);
    
    if (are_lists_identical(list1, list2)) {
        printf("Lists are identical\n");
    } else {
        printf("Lists are not identical\n");
    }
    
    free_list(list1);
    free_list(list2);
    
    return 0;
}