#include <stdio.h>
#include <stdlib.h>

typedef struct IntNode {
    int data;
    struct IntNode *next;
} IntNode;

typedef struct Sublist {
    IntNode *head;
    struct Sublist *next;
} Sublist;

static IntNode *int_node_new(int data) {
    IntNode *node = (IntNode *)malloc(sizeof(*node));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

static int int_list_append(IntNode **head, int data) {
    IntNode *node = int_node_new(data);
    if (node == NULL) {
        return 0;
    }
    if (*head == NULL) {
        *head = node;
        return 1;
    }
    IntNode *tail = *head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = node;
    return 1;
}

static void int_list_free(IntNode *head) {
    while (head != NULL) {
        IntNode *next = head->next;
        free(head);
        head = next;
    }
}

static Sublist *sublist_new(IntNode *head) {
    Sublist *sublist = (Sublist *)malloc(sizeof(*sublist));
    if (sublist != NULL) {
        sublist->head = head;
        sublist->next = NULL;
    }
    return sublist;
}

static int sublist_list_append(Sublist **head, Sublist *sublist) {
    if (head == NULL || sublist == NULL) {
        return 0;
    }
    sublist->next = NULL;
    if (*head == NULL) {
        *head = sublist;
        return 1;
    }
    Sublist *tail = *head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = sublist;
    return 1;
}

static int sublist_is_within_range(const Sublist *sublist, int low, int high) {
    if (sublist == NULL) {
        return 1;
    }
    for (const IntNode *node = sublist->head; node != NULL; node = node->next) {
        if (node->data < low || node->data > high) {
            return 0;
        }
    }
    return 1;
}

void remove_sublists_outside_range(Sublist **head, int low, int high) {
    if (head == NULL || *head == NULL) {
        return;
    }
    Sublist *prev = NULL;
    Sublist *curr = *head;
    while (curr != NULL) {
        Sublist *next = curr->next;
        if (!sublist_is_within_range(curr, low, high)) {
            if (prev == NULL) {
                *head = next;
            } else {
                prev->next = next;
            }
            int_list_free(curr->head);
            free(curr);
        } else {
            prev = curr;
        }
        curr = next;
    }
}

static void sublist_list_free(Sublist *head) {
    while (head != NULL) {
        Sublist *next = head->next;
        int_list_free(head->head);
        free(head);
        head = next;
    }
}

static void sublist_list_print(const Sublist *head) {
    printf("[");
    for (const Sublist *sublist = head; sublist != NULL; sublist = sublist->next) {
        printf("[");
        for (const IntNode *node = sublist->head; node != NULL; node = node->next) {
            printf("%d", node->data);
            if (node->next != NULL) {
                printf(", ");
            }
        }
        printf("]");
        if (sublist->next != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

static Sublist *create_sublist_from_array(const int *values, int count) {
    IntNode *head = NULL;
    for (int i = 0; i < count; i++) {
        if (!int_list_append(&head, values[i])) {
            int_list_free(head);
            return NULL;
        }
    }
    Sublist *sublist = sublist_new(head);
    if (sublist == NULL) {
        int_list_free(head);
        return NULL;
    }
    return sublist;
}

static int append_sublist_from_array(Sublist **head, const int *values, int count) {
    Sublist *sublist = create_sublist_from_array(values, count);
    if (sublist == NULL) {
        return 0;
    }
    if (!sublist_list_append(head, sublist)) {
        int_list_free(sublist->head);
        free(sublist);
        return 0;
    }
    return 1;
}

int main(void) {
    Sublist *list = NULL;

    if (!append_sublist_from_array(&list, (int[]){1, 2, 3}, 3) ||
        !append_sublist_from_array(&list, (int[]){4, 5, 6}, 3) ||
        !append_sublist_from_array(&list, (int[]){7, 8, 9}, 3)) {
        sublist_list_free(list);
        return EXIT_FAILURE;
    }

    printf("Before: ");
    sublist_list_print(list);

    remove_sublists_outside_range(&list, 4, 6);

    printf("After:  ");
    sublist_list_print(list);

    sublist_list_free(list);
    return EXIT_SUCCESS;
}