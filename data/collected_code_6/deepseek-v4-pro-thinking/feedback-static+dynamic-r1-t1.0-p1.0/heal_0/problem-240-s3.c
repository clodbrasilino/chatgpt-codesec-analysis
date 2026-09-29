#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void append_node(struct Node **head, int data);
void print_list(const struct Node *head);
void free_list(struct Node *head);
struct Node *replace_last_with_list(struct Node *list1, struct Node *list2);

int main(void) {
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;
    struct Node *result = NULL;

    append_node(&list1, 1);
    append_node(&list1, 2);
    append_node(&list1, 3);
    append_node(&list2, 10);
    append_node(&list2, 20);
    result = replace_last_with_list(list1, list2);
    print_list(result);
    free_list(result);

    list1 = NULL;
    list2 = NULL;
    append_node(&list1, 1);
    append_node(&list2, 10);
    append_node(&list2, 20);
    result = replace_last_with_list(list1, list2);
    print_list(result);
    free_list(result);

    list1 = NULL;
    append_node(&list1, 1);
    append_node(&list1, 2);
    result = replace_last_with_list(list1, NULL);
    print_list(result);
    free_list(result);

    list1 = NULL;
    list2 = NULL;
    append_node(&list2, 5);
    result = replace_last_with_list(NULL, list2);
    print_list(result);
    free_list(result);

    return 0;
}

void append_node(struct Node **head, int data) {
    struct Node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
    } else {
        struct Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void print_list(const struct Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void free_list(struct Node *head) {
    while (head != NULL) {
        struct Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

struct Node *replace_last_with_list(struct Node *list1, struct Node *list2) {
    if (list1 == NULL) {
        return list2;
    }

    struct Node *prev = NULL;
    struct Node *last = list1;

    while (last->next != NULL) {
        prev = last;
        last = last->next;
    }

    free(last);

    if (prev == NULL) {
        return list2;
    }

    prev->next = list2;
    return list1;
}