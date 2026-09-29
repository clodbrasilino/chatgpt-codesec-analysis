#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node **split_list(Node *head, int n, int *out_count) {
    if (head == NULL || n <= 0 || out_count == NULL) {
        return NULL;
    }

    int len = 0;
    Node *curr = head;
    while (curr != NULL) {
        len++;
        curr = curr->next;
    }

    int chunk_count = (len + n - 1) / n;
    Node **chunks = malloc(chunk_count * sizeof(Node *));
    if (chunks == NULL) {
        return NULL;
    }

    curr = head;
    for (int i = 0; i < chunk_count; i++) {
        chunks[i] = curr;
        for (int j = 1; j < n && curr != NULL; j++) {
            curr = curr->next;
        }
        if (curr != NULL) {
            Node *next_chunk_head = curr->next;
            curr->next = NULL;
            curr = next_chunk_head;
        }
    }

    *out_count = chunk_count;
    return chunks;
}

void free_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
}

void print_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int main(void) {
    Node *head = create_node(1);
    if (head == NULL) {
        return 1;
    }
    
    Node *curr = head;
    for (int i = 2; i <= 7; i++) {
        Node *node = create_node(i);
        if (node == NULL) {
            free_list(head);
            return 1;
        }
        curr->next = node;
        curr = node;
    }

    int count = 0;
    Node **chunks = split_list(head, 3, &count);
    
    if (chunks != NULL) {
        for (int i = 0; i < count; i++) {
            print_list(chunks[i]);
            free_list(chunks[i]);
        }
        free(chunks);
    } else {
        free_list(head);
    }

    return 0;
}