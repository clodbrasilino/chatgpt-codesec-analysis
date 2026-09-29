#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void list_free(Node *head);
void list_print(const Node *head);
int select_nth_items(const Node *head, int n, Node **result);

int main(void) {
    Node *list = NULL;
    Node *tail = NULL;
    Node *selected = NULL;
    Node *node = NULL;
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        node = malloc(sizeof(*node));
        if (!node) {
            list_free(list);
            return EXIT_FAILURE;
        }
        node->data = values[i];
        node->next = NULL;
        if (!list) {
            list = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    if (select_nth_items(list, 3, &selected) != 0) {
        list_free(list);
        list_free(selected);
        return EXIT_FAILURE;
    }

    list_print(list);
    list_print(selected);

    list_free(list);
    list_free(selected);
    return EXIT_SUCCESS;
}

void list_free(Node *head) {
    Node *next;

    while (head) {
        next = head->next;
        free(head);
        head = next;
    }
}

void list_print(const Node *head) {
    const Node *current;

    for (current = head; current; current = current->next) {
        printf("%d ", current->data);
    }
    printf("\n");
}

int select_nth_items(const Node *head, int n, Node **result) {
    Node *selected;
    Node *tail;
    Node *node;
    const Node *current;
    int position;

    if (!result) {
        return -1;
    }
    *result = NULL;
    if (n <= 0) {
        return -1;
    }
    if (!head) {
        return 0;
    }

    selected = NULL;
    tail = NULL;
    position = 1;

    for (current = head; current; current = current->next) {
        if (position == n) {
            node = malloc(sizeof(*node));
            if (!node) {
                list_free(selected);
                return -1;
            }
            node->data = current->data;
            node->next = NULL;
            if (!selected) {
                selected = node;
            } else {
                tail->next = node;
            }
            tail = node;
            position = 0;
        }
        position++;
    }

    *result = selected;
    return 0;
}