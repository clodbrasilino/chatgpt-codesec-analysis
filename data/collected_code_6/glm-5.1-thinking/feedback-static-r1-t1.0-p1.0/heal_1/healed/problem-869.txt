#include <stdio.h>
#include <stdlib.h>

typedef struct InnerNode {
    int data;
    struct InnerNode *next;
} InnerNode;

typedef struct OuterNode {
    InnerNode *head;
    struct OuterNode *next;
} OuterNode;

int get_length(InnerNode *head) {
    int length = 0;
    InnerNode *current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

void free_inner_list(InnerNode *head) {
    InnerNode *current = head;
    while (current != NULL) {
        InnerNode *temp = current;
        current = current->next;
        free(temp);
    }
}

OuterNode* remove_sublists_outside_range(OuterNode *head, int min_range, int max_range) {
    OuterNode *current = head;
    OuterNode *prev = NULL;
    OuterNode *new_head = head;

    while (current != NULL) {
        int length = get_length(current->head);
        OuterNode *next_node = current->next;

        if (length < min_range || length > max_range) {
            if (prev == NULL) {
                new_head = next_node;
            } else {
                prev->next = next_node;
            }

            free_inner_list(current->head);
            free(current);
        } else {
            prev = current;
        }
        current = next_node;
    }

    return new_head;
}

InnerNode* create_inner_node(int data) {
    InnerNode *node = malloc(sizeof(InnerNode));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

OuterNode* create_outer_node(InnerNode *head) {
    OuterNode *node = malloc(sizeof(OuterNode));
    if (node == NULL) {
        return NULL;
    }
    node->head = head;
    node->next = NULL;
    return node;
}

void free_outer_list(OuterNode *head) {
    OuterNode *current = head;
    while (current != NULL) {
        OuterNode *temp = current;
        current = current->next;
        free_inner_list(temp->head);
        free(temp);
    }
}

void print_lists(OuterNode *head) {
    OuterNode *outer = head;
    while (outer != NULL) {
        InnerNode *inner = outer->head;
        printf("[");
        while (inner != NULL) {
            printf("%d", inner->data);
            inner = inner->next;
            if (inner != NULL) {
                printf(", ");
            }
        }
        printf("]\n");
        outer = outer->next;
    }
}

int main(void) {
    InnerNode *n1 = create_inner_node(1);
    if (n1 != NULL) { n1->next = create_inner_node(2); }
    if (n1 != NULL && n1->next != NULL) { n1->next->next = create_inner_node(3); }

    InnerNode *n2 = create_inner_node(4);
    if (n2 != NULL) { n2->next = create_inner_node(5); }

    InnerNode *n3 = create_inner_node(6);
    if (n3 != NULL) { n3->next = create_inner_node(7); }
    if (n3 != NULL && n3->next != NULL) { n3->next->next = create_inner_node(8); }
    if (n3 != NULL && n3->next != NULL && n3->next->next != NULL) { n3->next->next->next = create_inner_node(9); }

    OuterNode *outer_list = create_outer_node(n1);
    if (outer_list != NULL) {
        outer_list->next = create_outer_node(n2);
        if (outer_list->next != NULL) {
            outer_list->next->next = create_outer_node(n3);
        }
    }

    printf("Original:\n");
    print_lists(outer_list);

    int min_range = 2;
    int max_range = 3;
    outer_list = remove_sublists_outside_range(outer_list, min_range, max_range);

    printf("\nAfter removing sublists outside range [%d, %d]:\n", min_range, max_range);
    print_lists(outer_list);

    free_outer_list(outer_list);

    return 0;
}