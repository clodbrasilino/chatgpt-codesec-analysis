#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int *data;
    int size;
    struct Node *next;
} Node;

typedef struct {
    int *data;
    int size;
} MergedResult;

Node *create_node(const int *data, int size) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->size = size;
    new_node->data = (int *)malloc(sizeof(int) * (size_t)size);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    if (data != NULL) {
        for (int i = 0; i < size; i++) {
            new_node->data[i] = data[i];
        }
    }
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, Node **tail, const int *data, int size) {
    Node *new_node = create_node(data, size);
    if (new_node == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = new_node;
        *tail = new_node;
    } else {
        (*tail)->next = new_node;
        *tail = new_node;
    }
}

int merge_first_last(const Node *head, MergedResult *result) {
    if (head == NULL || result == NULL) {
        return 0;
    }
    
    const Node *last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    
    int total_size = head->size + last->size;
    result->data = (int *)malloc(sizeof(int) * (size_t)total_size);
    if (result->data == NULL) {
        return 0;
    }
    
    result->size = total_size;
    
    for (int i = 0; i < head->size; i++) {
        result->data[i] = head->data[i];
    }
    for (int i = 0; i < last->size; i++) {
        result->data[head->size + i] = last->data[i];
    }
    
    return 1;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}

int main(void) {
    Node *head = NULL;
    Node *tail = NULL;
    
    const int arr1[] = {1, 2, 3};
    const int arr2[] = {4, 5};
    const int arr3[] = {6, 7, 8, 9};
    
    append_node(&head, &tail, arr1, 3);
    append_node(&head, &tail, arr2, 2);
    append_node(&head, &tail, arr3, 4);
    
    if (head == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }
    
    MergedResult merged = {NULL, 0};
    if (merge_first_last(head, &merged)) {
        printf("Merged first and last lists: ");
        for (int i = 0; i < merged.size; i++) {
            printf("%d ", merged.data[i]);
        }
        printf("\n");
        free(merged.data);
    } else {
        fprintf(stderr, "Merge operation failed\n");
        free_list(head);
        return 1;
    }
    
    free_list(head);
    return 0;
}