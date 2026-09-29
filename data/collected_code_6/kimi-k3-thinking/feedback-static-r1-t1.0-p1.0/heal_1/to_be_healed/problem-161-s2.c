#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int append_node(Node **head, int data)
{
    Node *new_node;
    Node *current;

    if (head == NULL) {
        return -1;
    }

    new_node = create_node(data);
    if (new_node == NULL) {
        return -1;
    }

    if (*head == NULL) {
        *head = new_node;
        return 0;
    }

    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return 0;
}

int list_contains(const Node *head, int value)
{
    const Node *current = head;
    while (current != NULL) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void remove_elements(Node **head, const Node *remove_list)
{
    Node *current;
    Node *prev;
    Node *temp;

    if (head == NULL || *head == NULL || remove_list == NULL) {
        return;
    }

    current = *head;
    prev = NULL;

    while (current != NULL) {
        if (list_contains(remove_list, current->data)) {
            temp = current;
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            free(temp);
            temp = NULL;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void print_list(const Node *head)
{
    const Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node **head)
{
    Node *current;
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node *temp;

    if (head == NULL) {
        return;
    }

    current = *head;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
        temp = NULL;
    }
    *head = NULL;
}

int main(void)
{
    Node *list1 = NULL;
    Node *list2 = NULL;
    int values1[] = {1, 2, 3, 4, 5, 6, 7};
    int values2[] = {2, 4, 6};
    size_t i;

    for (i = 0; i < sizeof(values1) / sizeof(values1[0]); i++) {
        if (append_node(&list1, values1[i]) != 0) {
            fprintf(stderr, "Error: memory allocation failed\n");
            free_list(&list1);
            free_list(&list2);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < sizeof(values2) / sizeof(values2[0]); i++) {
        if (append_node(&list2, values2[i]) != 0) {
            fprintf(stderr, "Error: memory allocation failed\n");
            free_list(&list1);
            free_list(&list2);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    print_list(list1);

    printf("Elements to remove: ");
    print_list(list2);

    remove_elements(&list1, list2);

    printf("Resulting list: ");
    print_list(list1);

    free_list(&list1);
    free_list(&list2);

    return EXIT_SUCCESS;
}