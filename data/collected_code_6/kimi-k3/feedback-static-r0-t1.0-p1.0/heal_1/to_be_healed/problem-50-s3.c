#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *head;
    size_t length;
} List;

List *create_list(void) {
    List *list = malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->length = 0;
    return list;
}

int append_node(List *list, int data) {
    if (list == NULL) {
        return -1;
    }
    ListNode *new_node = malloc(sizeof(ListNode));
    if (new_node == NULL) {
        return -1;
    }
    new_node->data = data;
    new_node->next = NULL;
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        ListNode *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->length++;
    return 0;
}

void free_list(List *list) {
    if (list == NULL) {
        return;
    }
    ListNode *current = list->head;
    while (current != NULL) {
        ListNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

List *find_min_length_list(List **lists, size_t num_lists) {
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }
    List *min_list = NULL;
    size_t min_length = SIZE_MAX;
    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i] != NULL && lists[i]->length < min_length) {
            min_length = lists[i]->length;
            min_list = lists[i];
        }
    }
    return min_list;
}

int main(void) {
    const size_t num_lists = 3;
    List **lists = malloc(num_lists * sizeof(List *));
    if (lists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < num_lists; i++) {
        lists[i] = NULL;
    }
    for (size_t i = 0; i < num_lists; i++) {
        lists[i] = create_list();
        if (lists[i] == NULL) {
            fprintf(stderr, "Failed to create list %zu\n", i);
            for (size_t j = 0; j < i; j++) {
                free_list(lists[j]);
            }
            free(lists);
            return EXIT_FAILURE;
        }
    }
    if (append_node(lists[0], 1) != 0 || append_node(lists[0], 2) != 0 ||
        append_node(lists[0], 3) != 0) {
        fprintf(stderr, "Failed to append to list 0\n");
        for (size_t i = 0; i < num_lists; i++) {
            free_list(lists[i]);
        }
        free(lists);
        return EXIT_FAILURE;
    }
    if (append_node(lists[1], 10) != 0 || append_node(lists[1], 20) != 0) {
        fprintf(stderr, "Failed to append to list 1\n");
        for (size_t i = 0; i < num_lists; i++) {
            free_list(lists[i]);
        }
        free(lists);
        return EXIT_FAILURE;
    }
    if (append_node(lists[2], 100) != 0) {
        fprintf(stderr, "Failed to append to list 2\n");
        for (size_t i = 0; i < num_lists; i++) {
            free_list(lists[i]);
        }
        free(lists);
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     *  Variable 'min_list' can be declared as pointer to const [constVariablePointer]
     */
    List *min_list = find_min_length_list(lists, num_lists);
    if (min_list != NULL) {
        printf("Minimum list length: %zu\n", min_list->length);
    } else {
        printf("No valid lists found\n");
    }
    for (size_t i = 0; i < num_lists; i++) {
        free_list(lists[i]);
    }
    free(lists);
    return EXIT_SUCCESS;
}