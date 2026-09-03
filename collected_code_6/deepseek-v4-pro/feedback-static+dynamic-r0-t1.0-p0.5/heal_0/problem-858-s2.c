#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    int is_list;
} List;

int count_lists_and_square(List *list) {
    if (list == NULL) {
        return 0;
    }
    
    int count = 0;
    Node *current = list->head;
    
    while (current != NULL) {
        if (current->data != NULL && ((List *)current->data)->is_list) {
            count++;
        }
        current = current->next;
    }
    
    return count * count;
}

List *create_list(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->is_list = 1;
    return list;
}

Node *create_node(void *data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void append_node(List *list, void *data) {
    if (list == NULL) {
        return;
    }
    
    Node *node = create_node(data);
    if (node == NULL) {
        return;
    }
    
    if (list->head == NULL) {
        list->head = node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

void free_list(List *list) {
    if (list == NULL) {
        return;
    }
    
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int main(void) {
    List *outer_list = create_list();
    if (outer_list == NULL) {
        return 1;
    }
    
    List *inner_list1 = create_list();
    List *inner_list2 = create_list();
    List *inner_list3 = create_list();
    
    if (inner_list1 == NULL || inner_list2 == NULL || inner_list3 == NULL) {
        free_list(outer_list);
        free_list(inner_list1);
        free_list(inner_list2);
        free_list(inner_list3);
        return 1;
    }
    
    append_node(outer_list, inner_list1);
    append_node(outer_list, inner_list2);
    append_node(outer_list, inner_list3);
    
    int result = count_lists_and_square(outer_list);
    printf("%d\n", result);
    
    free_list(inner_list1);
    free_list(inner_list2);
    free_list(inner_list3);
    free_list(outer_list);
    
    return 0;
}