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

void print_list(Node *head) {
    Node *current = head;
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

int main(void) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int arr3[] = {7, 8, 9};
    int arr4[] = {10, 11, 12};

    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    size_t size4 = sizeof(arr4) / sizeof(arr4[0]);

    size_t alloc1 = size1 * sizeof(int);
    size_t alloc2 = size2 * sizeof(int);
    size_t alloc3 = size3 * sizeof(int);
    size_t alloc4 = size4 * sizeof(int);

    int *data1 = (int *)malloc(alloc1);
    int *data2 = (int *)malloc(alloc2);
    int *data3 = (int *)malloc(alloc3);
    int *data4 = (int *)malloc(alloc4);

    if (!data1 || !data2 || !data3 || !data4) {
        free(data1);
        free(data2);
        free(data3);
        free(data4);
        return 1;
    }

    if (memcpy(data1, arr1, alloc1) != data1) {
        free(data1);
        free(data2);
        free(data3);
        free(data4);
        return 1;
    }
    if (memcpy(data2, arr2, alloc2) != data2) {
        free(data1);
        free(data2);
        free(data3);
        free(data4);
        return 1;
    }
    if (memcpy(data3, arr3, alloc3) != data3) {
        free(data1);
        free(data2);
        free(data3);
        free(data4);
        return 1;
    }
    if (memcpy(data4, arr4, alloc4) != data4) {
        free(data1);
        free(data2);
        free(data3);
        free(data4);
        return 1;
    }

    Node *head = create_node(data1, size1);
    if (!head) {
        free(data1);
        free(data2);
        free(data3);
        free(data4);
        return 1;
    }
    Node *node2 = create_node(data2, size2);
    if (!node2) {
        free(data2);
        free(data3);
        free(data4);
        free_list(head);
        return 1;
    }
    Node *node3 = create_node(data3, size3);
    if (!node3) {
        free(data3);
        free(data4);
        free_list(head);
        free(node2);
        return 1;
    }
    Node *node4 = create_node(data4, size4);
    if (!node4) {
        free(data4);
        free_list(head);
        free(node2);
        free(node3);
        return 1;
    }
    head->next = node2;
    node2->next = node3;
    node3->next = node4;

    printf("Original list: ");
    print_list(head);

    head = remove_out_of_range(head, 1, 9);

    printf("Filtered list: ");
    print_list(head);

    free_list(head);

    return 0;
}