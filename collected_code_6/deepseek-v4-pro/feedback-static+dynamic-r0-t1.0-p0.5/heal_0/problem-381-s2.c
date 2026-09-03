#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int *data;
    int size;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} List;

Node *create_node(int *data, int size) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) return NULL;
    node->data = data;
    node->size = size;
    node->next = NULL;
    return node;
}

void append_node(List *list, Node *node) {
    if (!list->head) {
        list->head = node;
        return;
    }
    Node *current = list->head;
    while (current->next) {
        current = current->next;
    }
    current->next = node;
}

void free_list(List *list) {
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
}

void sort_list_by_index(List *list, int index) {
    if (!list->head || !list->head->next) return;

    Node *sorted = NULL;
    Node *current = list->head;

    while (current) {
        Node *next = current->next;
        if (!sorted || sorted->data[index] >= current->data[index]) {
            current->next = sorted;
            sorted = current;
        } else {
            Node *temp = sorted;
            while (temp->next && temp->next->data[index] < current->data[index]) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    list->head = sorted;
}

void print_list(List *list) {
    Node *current = list->head;
    while (current) {
        printf("[");
        for (int i = 0; i < current->size; i++) {
            printf("%d", current->data[i]);
            if (i < current->size - 1) printf(", ");
        }
        printf("] ");
        current = current->next;
    }
    printf("\n");
}

int main() {
    List list = {0};

    int arr1[] = {3, 2, 1};
    int arr2[] = {1, 4, 2};
    int arr3[] = {2, 1, 3};
    int arr4[] = {0, 5, 4};

    int *data1 = (int *)malloc(3 * sizeof(int));
    int *data2 = (int *)malloc(3 * sizeof(int));
    int *data3 = (int *)malloc(3 * sizeof(int));
    int *data4 = (int *)malloc(3 * sizeof(int));

    if (!data1 || !data2 || !data3 || !data4) {
        free(data1);
        free(data2);
        free(data3);
        free(data4);
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        data1[i] = arr1[i];
        data2[i] = arr2[i];
        data3[i] = arr3[i];
        data4[i] = arr4[i];
    }

    append_node(&list, create_node(data1, 3));
    append_node(&list, create_node(data2, 3));
    append_node(&list, create_node(data3, 3));
    append_node(&list, create_node(data4, 3));

    printf("Before sorting by index 0:\n");
    print_list(&list);

    sort_list_by_index(&list, 0);

    printf("After sorting by index 0:\n");
    print_list(&list);

    free_list(&list);
    return 0;
}