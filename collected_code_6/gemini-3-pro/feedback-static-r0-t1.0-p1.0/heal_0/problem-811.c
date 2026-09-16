#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node* next;
} Node;

bool are_identical(const Node* list1, const Node* list2) {
    while (list1 != NULL && list2 != NULL) {
        if (list1->data.x != list2->data.x || list1->data.y != list2->data.y) {
            return false;
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    return list1 == NULL && list2 == NULL;
}

Node* create_node(int x, int y) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data.x = x;
    new_node->data.y = y;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next_node = current->next;
        free(current);
        current = next_node;
    }
}

int main(void) {
    Node* list1 = create_node(1, 2);
    if (list1 == NULL) return 1;
    list1->next = create_node(3, 4);
    if (list1->next == NULL) {
        free_list(list1);
        return 1;
    }

    Node* list2 = create_node(1, 2);
    if (list2 == NULL) {
        free_list(list1);
        return 1;
    }
    list2->next = create_node(3, 4);
    if (list2->next == NULL) {
        free_list(list1);
        free_list(list2);
        return 1;
    }

    if (are_identical(list1, list2)) {
        printf("Lists are identical.\n");
    } else {
        printf("Lists are not identical.\n");
    }

    free_list(list1);
    free_list(list2);

    return 0;
}