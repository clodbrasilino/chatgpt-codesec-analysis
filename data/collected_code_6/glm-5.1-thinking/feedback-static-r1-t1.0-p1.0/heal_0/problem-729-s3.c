#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *create_node(int value) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
}

Node *add_lists(const Node *list1, const Node *list2) {
    Node dummy;
    dummy.next = NULL;
    Node *tail = &dummy;

    const Node *p1 = list1;
    const Node *p2 = list2;

    while (p1 != NULL || p2 != NULL) {
        int sum = 0;
        if (p1 != NULL) {
            sum += p1->value;
            p1 = p1->next;
        }
        if (p2 != NULL) {
            sum += p2->value;
            p2 = p2->next;
        }

        Node *new_node = create_node(sum);
        if (new_node == NULL) {
            Node *curr = dummy.next;
            while (curr != NULL) {
                Node *temp = curr;
                curr = curr->next;
                free(temp);
            }
            return NULL;
        }

        tail->next = new_node;
        tail = new_node;
    }

    return dummy.next;
}

Node *build_list(const int *arr, size_t size) {
    Node dummy;
    dummy.next = NULL;
    Node *tail = &dummy;

    for (size_t i = 0; i < size; i++) {
        Node *node = create_node(arr[i]);
        if (node == NULL) {
            Node *curr = dummy.next;
            while (curr != NULL) {
                Node *temp = curr;
                curr = curr->next;
                free(temp);
            }
            return NULL;
        }
        tail->next = node;
        tail = node;
    }
    return dummy.next;
}

void free_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        Node *temp = curr;
        curr = curr->next;
        free(temp);
    }
}

void print_list(const Node *head) {
    const Node *curr = head;
    while (curr != NULL) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");
}

int main(void) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6, 7};

    Node *list1 = build_list(arr1, sizeof(arr1) / sizeof(arr1[0]));
    Node *list2 = build_list(arr2, sizeof(arr2) / sizeof(arr2[0]));

    if (list1 == NULL || list2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_list(list1);
        free_list(list2);
        return 1;
    }

    Node *result = add_lists(list1, list2);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free_list(list1);
        free_list(list2);
        return 1;
    }

    print_list(result);

    free_list(list1);
    free_list(list2);
    free_list(result);

    return 0;
}