#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

Node *create_node(int val) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->val = val;
    node->next = NULL;
    return node;
}

Node *build_list(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return NULL;
    }
    Node *head = create_node(arr[0]);
    if (head == NULL) {
        return NULL;
    }
    Node *current = head;
    for (size_t i = 1; i < size; i++) {
        Node *new_node = create_node(arr[i]);
        if (new_node == NULL) {
            while (head != NULL) {
                Node *temp = head;
                head = head->next;
                free(temp);
            }
            return NULL;
        }
        current->next = new_node;
        current = new_node;
    }
    return head;
}

Node *remove_odd(Node *head) {
    while (head != NULL && head->val % 2 != 0) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
    if (head == NULL) {
        return NULL;
    }
    Node *current = head;
    while (current->next != NULL) {
        if (current->next->val % 2 != 0) {
            Node *temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
    return head;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    Node *list = build_list(arr, size);
    if (list == NULL) {
        return EXIT_FAILURE;
    }
    print_list(list);
    list = remove_odd(list);
    print_list(list);
    free_list(list);
    return EXIT_SUCCESS;
}