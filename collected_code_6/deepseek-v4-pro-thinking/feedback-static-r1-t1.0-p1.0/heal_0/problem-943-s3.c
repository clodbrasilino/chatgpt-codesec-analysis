#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data);
int append_node(Node **head, int data);
Node *combine_sorted_lists(Node *list1, Node *list2);
void print_list(const Node *head);
void free_list(Node *head);

int main(void) {
    Node *list1 = NULL;
    Node *list2 = NULL;
    int values1[] = {1, 3, 5};
    int values2[] = {2, 4, 6};
    size_t i;

    for (i = 0; i < sizeof(values1) / sizeof(values1[0]); ++i) {
        if (!append_node(&list1, values1[i])) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(list1);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < sizeof(values2) / sizeof(values2[0]); ++i) {
        if (!append_node(&list2, values2[i])) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(list1);
            free_list(list2);
            return EXIT_FAILURE;
        }
    }

    printf("List 1: ");
    print_list(list1);
    printf("List 2: ");
    print_list(list2);

    Node *combined = combine_sorted_lists(list1, list2);

    printf("Combined: ");
    print_list(combined);

    free_list(combined);
    return EXIT_SUCCESS;
}

Node *create_node(int data) {
    Node *new_node = malloc(sizeof(*new_node));
    if (new_node != NULL) {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}

int append_node(Node **head, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return 0;
    }

    if (*head == NULL) {
        *head = new_node;
        return 1;
    }

    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return 1;
}

Node *combine_sorted_lists(Node *list1, Node *list2) {
    Node dummy = {0, NULL};
    Node *tail = &dummy;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data <= list2->data) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    if (list1 != NULL) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }

    return dummy.next;
}

void print_list(const Node *head) {
    while (head != NULL) {
        printf("%d", head->data);
        head = head->next;
        if (head != NULL) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}