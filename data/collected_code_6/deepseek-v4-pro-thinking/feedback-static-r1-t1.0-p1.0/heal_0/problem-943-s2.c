#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *create_node(int data);
int append_node(struct ListNode **head, int data);
int merge_sorted_lists(const struct ListNode *a, const struct ListNode *b, struct ListNode **result);
void free_list(struct ListNode *head);
void print_list(const struct ListNode *head);

int main(void) {
    struct ListNode *list1 = NULL;
    struct ListNode *list2 = NULL;
    struct ListNode *merged = NULL;

    if (!append_node(&list1, 1) ||
        !append_node(&list1, 3) ||
        !append_node(&list1, 5)) {
        free_list(list1);
        free_list(list2);
        return EXIT_FAILURE;
    }

    if (!append_node(&list2, 2) ||
        !append_node(&list2, 4) ||
        !append_node(&list2, 6)) {
        free_list(list1);
        free_list(list2);
        return EXIT_FAILURE;
    }

    if (!merge_sorted_lists(list1, list2, &merged)) {
        free_list(list1);
        free_list(list2);
        return EXIT_FAILURE;
    }

    print_list(merged);

    free_list(merged);
    free_list(list1);
    free_list(list2);
    return EXIT_SUCCESS;
}

struct ListNode *create_node(int data) {
    struct ListNode *node = malloc(sizeof *node);
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

int append_node(struct ListNode **head, int data) {
    struct ListNode *node;
    struct ListNode *current;

    if (head == NULL) {
        return 0;
    }

    node = create_node(data);
    if (node == NULL) {
        return 0;
    }

    if (*head == NULL) {
        *head = node;
    } else {
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }

    return 1;
}

int merge_sorted_lists(const struct ListNode *a, const struct ListNode *b, struct ListNode **result) {
    struct ListNode **tail;
    int value;
    struct ListNode *node;

    if (result == NULL) {
        return 0;
    }

    *result = NULL;
    tail = result;

    while (a != NULL && b != NULL) {
        if (a->data <= b->data) {
            value = a->data;
            a = a->next;
        } else {
            value = b->data;
            b = b->next;
        }

        node = create_node(value);
        if (node == NULL) {
            free_list(*result);
            *result = NULL;
            return 0;
        }

        *tail = node;
        tail = &node->next;
    }

    while (a != NULL) {
        node = create_node(a->data);
        if (node == NULL) {
            free_list(*result);
            *result = NULL;
            return 0;
        }

        *tail = node;
        tail = &node->next;
        a = a->next;
    }

    while (b != NULL) {
        node = create_node(b->data);
        if (node == NULL) {
            free_list(*result);
            *result = NULL;
            return 0;
        }

        *tail = node;
        tail = &node->next;
        b = b->next;
    }

    return 1;
}

void free_list(struct ListNode *head) {
    while (head != NULL) {
        struct ListNode *next = head->next;
        free(head);
        head = next;
    }
}

void print_list(const struct ListNode *head) {
    while (head != NULL) {
        printf("%d", head->data);
        head = head->next;
        if (head != NULL) {
            printf(" ");
        }
    }
    printf("\n");
}