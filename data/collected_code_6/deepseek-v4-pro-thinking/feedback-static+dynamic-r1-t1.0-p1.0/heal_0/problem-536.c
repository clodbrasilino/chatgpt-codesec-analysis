#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

const Node *nth_item(const Node *head, unsigned int n) {
    const Node *current = head;
    unsigned int index = 0;

    while (current != NULL) {
        if (index == n) {
            return current;
        }
        current = current->next;
        index++;
    }

    return NULL;
}

int main(void) {
    Node *head = NULL;
    Node *tail = NULL;
    int values[] = {10, 20, 30, 40, 50};
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        Node *new_node = malloc(sizeof(*new_node));
        if (new_node == NULL) {
            while (head != NULL) {
                Node *tmp = head;
                head = head->next;
                free(tmp);
            }
            return 1;
        }
        new_node->data = values[i];
        new_node->next = NULL;
        if (head == NULL) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
    }

    const Node *selected = nth_item(head, 2);
    if (selected != NULL) {
        printf("%d\n", selected->data);
    } else {
        printf("not found\n");
    }

    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }

    return 0;
}