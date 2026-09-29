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

Node *replace_last_with_list(Node *head, Node *replacement)
{
    Node *current;

    if (head == NULL) {
        return replacement;
    }

    if (head->next == NULL) {
        free(head);
        return replacement;
    }

    current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = replacement;
    return head;
}

void print_list(const Node *head)
{
    const Node *current = head;

    if (current == NULL) {
        printf("(empty)\n");
        return;
    }

    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

void free_list(Node *head)
{
    Node *current = head;
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void)
{
    Node *list1 = NULL;
    Node *list2 = NULL;
    int i;

    for (i = 1; i <= 5; i++) {
        if (append_node(&list1, i * 10) != 0) {
            fprintf(stderr, "Failed to allocate memory for list1\n");
            free_list(list1);
            return EXIT_FAILURE;
        }
    }

    for (i = 1; i <= 3; i++) {
        if (append_node(&list2, i) != 0) {
            fprintf(stderr, "Failed to allocate memory for list2\n");
            free_list(list1);
            free_list(list2);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    print_list(list1);

    printf("Replacement list: ");
    print_list(list2);

    list1 = replace_last_with_list(list1, list2);
    list2 = NULL;

    printf("Resulting list: ");
    print_list(list1);

    free_list(list1);
    list1 = NULL;

    return EXIT_SUCCESS;
}