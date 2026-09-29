#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *new_node(int data) {
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

Node **split_list(Node *head, int n, size_t *out_count) {
    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;
    if (head == NULL || n <= 0) {
        return NULL;
    }

    size_t count = 0;
    for (Node *cur = head; cur != NULL; cur = cur->next) {
        count++;
    }

    size_t chunks = (count + (size_t)n - 1) / (size_t)n;
    Node **result = malloc(chunks * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    Node *cur = head;
    for (size_t i = 0; i < chunks; i++) {
        result[i] = cur;
        for (int j = 1; j < n && cur != NULL; j++) {
            cur = cur->next;
        }
        if (cur != NULL) {
            Node *next = cur->next;
            cur->next = NULL;
            cur = next;
        }
    }

    *out_count = chunks;
    return result;
}

int main(void) {
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Node *head = NULL;
    Node *tail = NULL;

    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        Node *node = new_node(values[i]);
        if (node == NULL) {
            free_list(head);
            return 1;
        }
        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    size_t chunk_count = 0;
    Node **chunks = split_list(head, 3, &chunk_count);
    if (chunks == NULL) {
        free_list(head);
        return 1;
    }

    for (size_t i = 0; i < chunk_count; i++) {
        printf("Chunk %zu: ", i + 1);
        for (Node *cur = chunks[i]; cur != NULL; cur = cur->next) {
            printf("%d ", cur->data);
        }
        printf("\n");
    }

    for (size_t i = 0; i < chunk_count; i++) {
        free_list(chunks[i]);
    }
    free(chunks);

    return 0;
}