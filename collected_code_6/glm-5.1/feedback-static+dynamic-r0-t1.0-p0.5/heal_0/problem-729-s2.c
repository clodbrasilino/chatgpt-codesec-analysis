#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

struct Node *add_lists(struct Node *list1, struct Node *list2) {
    struct Node dummy;
    dummy.next = NULL;
    struct Node *tail = &dummy;
    int carry = 0;

    while (list1 != NULL || list2 != NULL || carry != 0) {
        int sum = carry;
        if (list1 != NULL) {
            sum += list1->data;
            list1 = list1->next;
        }
        if (list2 != NULL) {
            sum += list2->data;
            list2 = list2->next;
        }
        carry = sum / 10;
        struct Node *new_node = create_node(sum % 10);
        tail->next = new_node;
        tail = tail->next;
    }

    return dummy.next;
}

void free_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    struct Node *list1 = create_node(9);
    list1->next = create_node(9);
    list1->next->next = create_node(9);

    struct Node *list2 = create_node(1);
    list2->next = create_node(1);

    struct Node *result = add_lists(list1, list2);

    struct Node *current = result;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    free_list(list1);
    free_list(list2);
    free_list(result);

    return 0;
}