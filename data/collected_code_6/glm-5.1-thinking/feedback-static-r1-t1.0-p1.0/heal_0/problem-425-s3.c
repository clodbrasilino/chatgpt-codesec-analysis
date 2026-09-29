#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct List {
    struct Node *head;
    struct List *next;
};

int count_sublists_containing(struct List *lists, int target) {
    int count = 0;
    struct List *current_list = lists;
    while (current_list != NULL) {
        struct Node *current_node = current_list->head;
        while (current_node != NULL) {
            if (current_node->data == target) {
                count++;
                break;
            }
            current_node = current_node->next;
        }
        current_list = current_list->next;
    }
    return count;
}

struct Node *create_node(int data) {
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

struct List *create_list(struct Node *head) {
    struct List *list = malloc(sizeof(struct List));
    if (list == NULL) {
        exit(EXIT_FAILURE);
    }
    list->head = head;
    list->next = NULL;
    return list;
}

void free_lists(struct List *lists) {
    struct List *current_list = lists;
    while (current_list != NULL) {
        struct Node *current_node = current_list->head;
        while (current_node != NULL) {
            struct Node *temp_node = current_node;
            current_node = current_node->next;
            free(temp_node);
        }
        struct List *temp_list = current_list;
        current_list = current_list->next;
        free(temp_list);
    }
}

int main(void) {
    struct Node *n1 = create_node(1);
    n1->next = create_node(2);
    struct Node *n2 = create_node(3);
    n2->next = create_node(4);
    struct Node *n3 = create_node(2);
    n3->next = create_node(5);

    struct List *l1 = create_list(n1);
    struct List *l2 = create_list(n2);
    struct List *l3 = create_list(n3);

    l1->next = l2;
    l2->next = l3;

    int target = 2;
    int result = count_sublists_containing(l1, target);
    printf("%d\n", result);

    free_lists(l1);

    return 0;
}