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
        ListNode *runner = collection->head;
        
        while (runner != current) {
            if (compare_lists(runner->list, current->list)) {
                is_unique = 0;
                break;
            }
            runner = runner->next;
        }
        
        if (is_unique) {
            count++;
        }
        
        current = current->next;
    }
    
    return count;
}

ListNode *create_node(int *data, size_t len) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) return NULL;
    
    node->list = (List *)malloc(sizeof(List));
    if (node->list == NULL) {
        free(node);
        return NULL;
    }
    
    node->list->data = (int *)malloc(len * sizeof(int));
    if (node->list->data == NULL) {
        free(node->list);
        free(node);
        return NULL;
    }
    
    memcpy(node->list->data, data, len * sizeof(int));
    node->list->len = len;
    node->next = NULL;
    
    return node;
}

void free_collection(ListCollection *collection) {
    ListNode *current = collection->head;
    while (current != NULL) {
        ListNode *next = current->next;
        free(current->list->data);
        free(current->list);
        free(current);
        current = next;
    }
    collection->head = NULL;
}

int main(void) {
    ListCollection collection;
    collection.head = NULL;
    
    int a1[] = {1, 2, 3};
    int a2[] = {4, 5};
    int a3[] = {1, 2, 3};
    int a4[] = {7};
    int a5[] = {4, 5};
    
    ListNode *n1 = create_node(a1, 3);
    if (n1 != NULL) {
        n1->next = collection.head;
        collection.head = n1;
    }
    
    ListNode *n2 = create_node(a2, 2);
    if (n2 != NULL) {
        n2->next = collection.head;
        collection.head = n2;
    }
    
    ListNode *n3 = create_node(a3, 3);
    if (n3 != NULL) {
        n3->next = collection.head;
        collection.head = n3;
    }
    
    ListNode *n4 = create_node(a4, 1);
    if (n4 != NULL) {
        n4->next = collection.head;
        collection.head = n4;
    }
    
    ListNode *n5 = create_node(a5, 2);
    if (n5 != NULL) {
        n5->next = collection.head;
        collection.head = n5;
    }
    
    size_t unique_count = count_unique_lists(&collection);
    printf("%zu\n", unique_count);
    
    free_collection(&collection);
    
    return 0;
}