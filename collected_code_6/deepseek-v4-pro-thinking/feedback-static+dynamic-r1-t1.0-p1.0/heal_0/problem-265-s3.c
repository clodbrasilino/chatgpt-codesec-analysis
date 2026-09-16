#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

int append_node(Node **head, int data);
Node **split_list(Node *head, size_t n, size_t *out_count);
void free_list(Node *head);

int append_node(Node **head, int data) {
    Node *node = malloc(sizeof(*node));
    if (!node) {
        return 0;
    }
    node->data = data;
    node->next = NULL;
    if (*head == NULL) {
        *head = node;
    } else {
        Node *cur = *head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = node;
    }
    return 1;
}

Node **split_list(Node *head, size_t n, size_t *out_count) {
    if (out_count != NULL) {
        *out_count = 0;
    }
    if (n == 0 || head == NULL) {
        return NULL;
    }

    size_t len = 0;
    for (Node *cur = head; cur != NULL; cur = cur->next) {
        len++;
    }

    size_t chunk_count = (len + n - 1) / n;
    Node **chunks = malloc(sizeof(*chunks) * chunk_count);
    if (chunks == NULL) {
        return NULL;
    }

    Node *current = head;
    for (size_t i = 0; i < chunk_count; i++) {
        chunks[i] = current;
        for (size_t j = 0; j + 1 < n && current != NULL; j++) {
            current = current->next;
        }
        if (current != NULL) {
            Node *next = current->next;
            current->next = NULL;
            current = next;
        }
    }

    if (out_count != NULL) {
        *out_count = chunk_count;
    }
    return chunks;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    Node *head = NULL;
    for (int i = 1; i <= 10; i++) {
        if (!append_node(&head, i)) {
            free_list(head);
            return 1;
        }
    }

    size_t count = 0;
    Node **chunks = split_list(head, 3, &count);
    if (chunks == NULL) {
        free_list(head);
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        for (Node *cur = chunks[i]; cur != NULL; cur = cur->next) {
            printf("%d ", cur->data);
        }
        printf("\n");
    }

    for (size_t i = 0; i < count; i++) {
        free_list(chunks[i]);
    }
    free(chunks);

    return 0;
}