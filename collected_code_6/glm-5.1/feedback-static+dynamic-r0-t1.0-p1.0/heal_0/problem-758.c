#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int *data;
    size_t length;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    size_t size;
} ListOfLists;

void init_list_of_lists(ListOfLists *lol) {
    lol->head = NULL;
    lol->size = 0;
}

bool lists_equal(Node *a, Node *b) {
    if (a->length != b->length) {
        return false;
    }
    for (size_t i = 0; i < a->length; i++) {
        if (a->data[i] != b->data[i]) {
            return false;
        }
    }
    return true;
}

bool is_unique(ListOfLists *lol, Node *target) {
    Node *current = lol->head;
    while (current != NULL) {
        if (lists_equal(current, target)) {
            return false;
        }
        current = current->next;
    }
    return true;
}

void append_list(ListOfLists *lol, int *data, size_t length) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = (int *)malloc(length * sizeof(int));
    if (new_node->data == NULL) {
        free(new_node);
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < length; i++) {
        new_node->data[i] = data[i];
    }
    new_node->length = length;
    new_node->next = lol->head;
    lol->head = new_node;
    lol->size++;
}

size_t count_unique_lists(ListOfLists *lol) {
    size_t unique_count = 0;
    Node *current = lol->head;
    ListOfLists unique_lol;
    init_list_of_lists(&unique_lol);
    
    while (current != NULL) {
        if (is_unique(&unique_lol, current)) {
            append_list(&unique_lol, current->data, current->length);
            unique_count++;
        }
        current = current->next;
    }
    
    Node *cleanup = unique_lol.head;
    while (cleanup != NULL) {
        Node *next = cleanup->next;
        free(cleanup->data);
        free(cleanup);
        cleanup = next;
    }
    
    return unique_count;
}

void free_list_of_lists(ListOfLists *lol) {
    Node *current = lol->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

int main(void) {
    ListOfLists lol;
    init_list_of_lists(&lol);
    
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5};
    int list3[] = {1, 2, 3};
    int list4[] = {6};
    int list5[] = {4, 5};
    
    append_list(&lol, list1, sizeof(list1) / sizeof(list1[0]));
    append_list(&lol, list2, sizeof(list2) / sizeof(list2[0]));
    append_list(&lol, list3, sizeof(list3) / sizeof(list3[0]));
    append_list(&lol, list4, sizeof(list4) / sizeof(list4[0]));
    append_list(&lol, list5, sizeof(list5) / sizeof(list5[0]));
    
    size_t unique = count_unique_lists(&lol);
    printf("%zu\n", unique);
    
    free_list_of_lists(&lol);
    
    return 0;
}