#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* create_node(int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (!new_node) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int append_node(struct Node** head, int data) {
    if (!head) {
        return -1;
    }

    struct Node* new_node = create_node(data);
    if (!new_node) {
        return -1;
    }

    if (!*head) {
        *head = new_node;
        return 0;
    }

    struct Node* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
    return 0;
}

void free_list(struct Node* head) {
    while (head) {
        struct Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

int replace_last_with_list(struct Node** head1, struct Node* head2) {
    if (!head1 || !*head1) {
        return -1;
    }

    if ((*head1)->next == NULL) {
        free(*head1);
        *head1 = head2;
        return 0;
    }

    struct Node* current = *head1;
    while (current->next->next) {
        current = current->next;
    }

    free(current->next);
    current->next = head2;

    return 0;
}

void print_list(const struct Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    if (append_node(&list1, 1) != 0 || append_node(&list1, 2) != 0 || append_node(&list1, 3) != 0) {
        free_list(list1);
        return EXIT_FAILURE;
    }

    if (append_node(&list2, 4) != 0 || append_node(&list2, 5) != 0) {
        free_list(list1);
        free_list(list2);
        return EXIT_FAILURE;
    }

    if (replace_last_with_list(&list1, list2) != 0) {
        free_list(list1);
        free_list(list2);
        return EXIT_FAILURE;
    }

    print_list(list1);
    free_list(list1);

    return EXIT_SUCCESS;
}