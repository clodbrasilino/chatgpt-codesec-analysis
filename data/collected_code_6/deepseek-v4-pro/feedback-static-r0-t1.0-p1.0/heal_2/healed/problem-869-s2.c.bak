#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int *data;
    int size;
    struct Node *next;
} Node;

Node *create_node(int *data, int size) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
        return NULL;
    }
    new_node->data = data;
    new_node->size = size;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

int is_within_range(const int *sublist, int size, int min_val, int max_val) {
    for (int i = 0; i < size; i++) {
        if (sublist[i] < min_val || sublist[i] > max_val) {
            return 0;
        }
    }
    return 1;
}

Node *remove_out_of_range(Node *head, int min_val, int max_val) {
    Node dummy;
    dummy.next = head;
    Node *prev = &dummy;
    Node *current = head;

    while (current) {
        Node *next = current->next;
        if (!is_within_range(current->data, current->size, min_val, max_val)) {
            prev->next = next;
            free(current->data);
            free(current);
        } else {
            prev = current;
        }
        current = next;
    }

    return dummy.next;
}

void print_list(const Node *head) {
    const Node *current = head;
    while (current) {
        printf("[");
        for (int i = 0; i < current->size; i++) {
            printf("%d", current->data[i]);
            if (i < current->size - 1) {
                printf(", ");
            }
        }
        printf("] ");
        current = current->next;
    }
    printf("\n");
}

int *copy_array(const int *src, int size) {
    int *copy = (int *)malloc(sizeof(int) * size);
    if (copy) {
        memcpy(copy, src, sizeof(int) * size);
    }
    return copy;
}

int main(void) {
    const int arr1[] = {1, 2, 3};
    const int arr2[] = {4, 5, 6};
    const int arr3[] = {7, 8, 9};
    const int arr4[] = {10, 11, 12};

    int *data1 = copy_array(arr1, 3);
    int *data2 = copy_array(arr2, 3);
    int *data3 = copy_array(arr3, 3);
    int *data4 = copy_array(arr4, 3);

    if (!data1 || !data2 || !data3 || !data4) {
        free(data1);
        free(data2);
        free(data3);
        free(data4);
        return 1;
    }

    Node *head = create_node(data1, 3);
    head->next = create_node(data2, 3);
    head->next->next = create_node(data3, 3);
    head->next->next->next = create_node(data4, 3);

    printf("Original list: ");
    print_list(head);

    head = remove_out_of_range(head, 1, 9);

    printf("Filtered list: ");
    print_list(head);

    free_list(head);

    return 0;
}