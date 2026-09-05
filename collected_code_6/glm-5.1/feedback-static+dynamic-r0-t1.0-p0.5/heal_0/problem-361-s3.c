#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

Node *remove_empty_lists(Node *head) {
    Node dummy;
    dummy.next = head;
    Node *prev = &dummy;
    Node *curr = head;

    while (curr != NULL) {
        Node *next_node = curr->next;
        if (curr->data == NULL) {
            prev->next = next_node;
            free(curr);
        } else {
            prev = curr;
        }
        curr = next_node;
    }

    return dummy.next;
}

Node *create_node(void *data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        Node *next_node = curr->next;
        free(curr);
        curr = next_node;
    }
}

int main(void) {
    Node *list1 = create_node((void *)"not empty");
    Node *list2 = create_node(NULL);
    Node *list3 = create_node((void *)"also not empty");
    Node *list4 = create_node(NULL);

    list1->next = list2;
    list2->next = list3;
    list3->next = list4;

    Node *head = list1;

    Node *curr = head;
    while (curr != NULL) {
        if (curr->data != NULL) {
            printf("%s -> ", (char *)curr->data);
        } else {
            printf("EMPTY -> ");
        }
        curr = curr->next;
    }
    printf("NULL\n");

    head = remove_empty_lists(head);

    curr = head;
    while (curr != NULL) {
        if (curr->data != NULL) {
            printf("%s -> ", (char *)curr->data);
        } else {
            printf("EMPTY -> ");
        }
        curr = curr->next;
    }
    printf("NULL\n");

    free_list(head);

    return 0;
}