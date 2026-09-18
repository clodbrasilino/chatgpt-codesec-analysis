#include <stdio.h>
#include <stdlib.h>

struct InnerNode {
    int data;
    struct InnerNode* next;
};

struct OuterNode {
    struct InnerNode* inner_list;
    struct OuterNode* next;
};

size_t count_and_square_lists(const struct OuterNode* head) {
    size_t count = 0;
    const struct OuterNode* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count * count;
}

void free_inner_list(struct InnerNode* head) {
    struct InnerNode* current = head;
    while (current != NULL) {
        struct InnerNode* temp = current;
        current = current->next;
        free(temp);
    }
}

void free_outer_list(struct OuterNode* head) {
    struct OuterNode* current = head;
    while (current != NULL) {
        free_inner_list(current->inner_list);
        struct OuterNode* temp = current;
        current = current->next;
        free(temp);
    }
}

struct InnerNode* create_inner_node(int data) {
    struct InnerNode* node = (struct InnerNode*)malloc(sizeof(struct InnerNode));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

struct OuterNode* create_outer_node(struct InnerNode* inner_list) {
    struct OuterNode* node = (struct OuterNode*)malloc(sizeof(struct OuterNode));
    if (node != NULL) {
        node->inner_list = inner_list;
        node->next = NULL;
    }
    return node;
}

int main(void) {
    struct InnerNode* inner1 = create_inner_node(1);
    if (inner1 == NULL) {
        return EXIT_FAILURE;
    }
    
    inner1->next = create_inner_node(2);
    if (inner1->next == NULL) {
        free_inner_list(inner1);
        return EXIT_FAILURE;
    }

    struct InnerNode* inner2 = create_inner_node(3);
    if (inner2 == NULL) {
        free_inner_list(inner1);
        return EXIT_FAILURE;
    }

    struct OuterNode* head = create_outer_node(inner1);
    if (head == NULL) {
        free_inner_list(inner1);
        free_inner_list(inner2);
        return EXIT_FAILURE;
    }

    struct OuterNode* second_outer = create_outer_node(inner2);
    if (second_outer == NULL) {
        free_inner_list(inner2);
        free_outer_list(head);
        return EXIT_FAILURE;
    }
    head->next = second_outer;

    size_t squared_count = count_and_square_lists(head);
    printf("%zu\n", squared_count);

    free_outer_list(head);

    return EXIT_SUCCESS;
}