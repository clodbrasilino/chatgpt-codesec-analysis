#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int value) {
    if (*head == NULL) {
        *head = create_node(value);
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = create_node(value);
    }
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

Node** split_list(Node *head, int n, int *list_count) {
    if (n <= 0 || head == NULL) {
        *list_count = 0;
        return NULL;
    }

    Node **lists = (Node **)malloc(sizeof(Node *) * 100);
    *list_count = 0;

    Node *current = head;
    int index = 0;
    while (current != NULL) {
        if (index % n == 0) {
            lists[*list_count] = current;
            (*list_count)++;
        }
        if (index % n == n - 1) {
            Node *temp = current->next;
            current->next = NULL;
            current = temp;
        } else {
            current = current->next;
        }
        index++;
    }

    return lists;
}

int main() {
    Node *head = NULL;
    for (int i = 1; i <= 12; i++) {
        append_node(&head, i);
    }

    int list_count;
    int n = 3;
    Node **lists = split_list(head, n, &list_count);

    for (int i = 0; i < list_count; i++) {
        print_list(lists[i]);
    }

    for (int i = 0; i < list_count; i++) {
        Node *current = lists[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(lists);

    return 0;
}