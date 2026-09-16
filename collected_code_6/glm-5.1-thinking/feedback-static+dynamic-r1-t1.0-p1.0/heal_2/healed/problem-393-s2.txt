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

int get_length(const struct Node *head) {
    int length = 0;
    const struct Node *current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

const struct List *find_max_length_list(const struct List *lists) {
    if (lists == NULL) {
        return NULL;
    }
    
    const struct List *max_list = lists;
    int max_length = get_length(lists->head);
    const struct List *current = lists->next;
    
    while (current != NULL) {
        int current_length = get_length(current->head);
        if (current_length > max_length) {
            max_length = current_length;
            max_list = current;
        }
        current = current->next;
    }
    
    return max_list;
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

void free_nodes(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

void free_lists(struct List *lists) {
    struct List *current = lists;
    while (current != NULL) {
        struct List *next = current->next;
        free_nodes(current->head);
        free(current);
        current = next;
    }
}

int main(void) {
    struct Node *n1 = create_node(1);
    n1->next = create_node(2);
    n1->next->next = create_node(3);

    struct Node *n2 = create_node(4);
    n2->next = create_node(5);

    struct Node *n3 = create_node(6);
    n3->next = create_node(7);
    n3->next->next = create_node(8);
    n3->next->next->next = create_node(9);

    struct List *l1 = create_list(n1);
    struct List *l2 = create_list(n2);
    struct List *l3 = create_list(n3);
    
    l1->next = l2;
    l2->next = l3;

    const struct List *max_list = find_max_length_list(l1);
    if (max_list != NULL) {
        printf("Max length list starts with node data: %d\n", max_list->head->data);
        printf("Length of max list: %d\n", get_length(max_list->head));
    }

    free_lists(l1);

    return 0;
}