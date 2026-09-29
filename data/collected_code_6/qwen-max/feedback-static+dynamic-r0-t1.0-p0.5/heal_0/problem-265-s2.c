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
    Node *new_node = create_node(value);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

Node** split_list(Node *head, int n, int *count) {
    *count = 0;
    if (n <= 0 || head == NULL) {
        return NULL;
    }

    Node **lists = (Node **)malloc(sizeof(Node *) * (n + 1));
    for (int i = 0; i < n + 1; ++i) {
        lists[i] = NULL;
    }

    Node *current = head;
    int index = 0;
    while (current != NULL) {
        append_node(&lists[index], current->value);
        if (index == n - 1) {
            index = 0;
        } else {
            index++;
        }
        current = current->next;
    }

    *count = n + 1;
    return lists;
}

int main() {
    Node *head = NULL;
    for (int i = 1; i <= 10; ++i) {
        append_node(&head, i);
    }

    print_list(head);

    int count;
    Node **lists = split_list(head, 3, &count);

    for (int i = 0; i < count; ++i) {
        print_list(lists[i]);
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