#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t len;
} List;

typedef struct ListNode {
    List *list;
    struct ListNode *next;
} ListNode;

typedef struct {
    ListNode *head;
} ListCollection;

int compare_lists(const List *a, const List *b) {
    if (a == NULL && b == NULL) return 1;
    if (a == NULL || b == NULL) return 0;
    if (a->len != b->len) return 0;
    for (size_t i = 0; i < a->len; i++) {
        if (a->data[i] != b->data[i]) return 0;
    }
    return 1;
}

size_t count_unique_lists(ListCollection *collection) {
    size_t count = 0;
    ListNode *current = collection->head;
    while (current != NULL) {
        int is_unique = 1;
        ListNode *checker = collection->head;
        while (checker != current) {
            if (compare_lists(current->list, checker->list)) {
                is_unique = 0;
                break;
            }
            checker = checker->next;
        }
        if (is_unique) {
            count++;
        }
        current = current->next;
    }
    return count;
}

void free_list_collection(ListCollection *collection) {
    ListNode *current = collection->head;
    while (current != NULL) {
        ListNode *next = current->next;
        free(current->list->data);
        free(current->list);
        free(current);
        current = next;
    }
}

ListNode *create_list_node(int *data, size_t len) {
    ListNode *node = malloc(sizeof(ListNode));
    if (node == NULL) return NULL;
    
    List *list = malloc(sizeof(List));
    if (list == NULL) {
        free(node);
        return NULL;
    }
    
    list->data = malloc(len * sizeof(int));
    if (list->data == NULL) {
        free(list);
        free(node);
        return NULL;
    }
    
    memcpy(list->data, data, len * sizeof(int));
    list->len = len;
    node->list = list;
    node->next = NULL;
    return node;
}

void append_list(ListCollection *collection, int *data, size_t len) {
    ListNode *node = create_list_node(data, len);
    if (node == NULL) return;
    
    if (collection->head == NULL) {
        collection->head = node;
    } else {
        ListNode *current = collection->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

int main(void) {
    ListCollection collection = {NULL};
    
    int a[] = {1, 2, 3};
    int b[] = {4, 5};
    int c[] = {1, 2, 3};
    int d[] = {7};
    int e[] = {4, 5};
    
    append_list(&collection, a, 3);
    append_list(&collection, b, 2);
    append_list(&collection, c, 3);
    append_list(&collection, d, 1);
    append_list(&collection, e, 2);
    
    size_t unique_count = count_unique_lists(&collection);
    printf("%zu\n", unique_count);
    
    free_list_collection(&collection);
    return 0;
}