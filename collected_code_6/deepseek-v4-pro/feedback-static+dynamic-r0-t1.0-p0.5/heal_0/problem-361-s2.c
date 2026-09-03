#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    int size;
} List;

List *create_list(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

int list_append(List *list, void *data) {
    if (list == NULL) {
        return -1;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->data = data;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
    return 0;
}

void free_list(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

void remove_empty_lists(List *list_of_lists) {
    if (list_of_lists == NULL || list_of_lists->head == NULL) {
        return;
    }
    
    Node *current = list_of_lists->head;
    Node *prev = NULL;
    
    while (current != NULL) {
        List *inner_list = (List *)current->data;
        if (inner_list == NULL || inner_list->size == 0) {
            Node *to_remove = current;
            if (prev == NULL) {
                list_of_lists->head = current->next;
                current = current->next;
            } else {
                prev->next = current->next;
                current = current->next;
            }
            free(to_remove);
            list_of_lists->size--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

int main(void) {
    List *list_of_lists = create_list();
    if (list_of_lists == NULL) {
        return 1;
    }
    
    List *list1 = create_list();
    List *list2 = create_list();
    List *list3 = create_list();
    List *list4 = create_list();
    
    if (list1 == NULL || list2 == NULL || list3 == NULL || list4 == NULL) {
        free_list(list1);
        free_list(list2);
        free_list(list3);
        free_list(list4);
        free_list(list_of_lists);
        return 1;
    }
    
    int value1 = 10;
    int value2 = 20;
    int value3 = 30;
    
    list_append(list1, &value1);
    list_append(list1, &value2);
    list_append(list3, &value3);
    
    list_append(list_of_lists, list1);
    list_append(list_of_lists, list2);
    list_append(list_of_lists, list3);
    list_append(list_of_lists, list4);
    
    printf("Before removal: %d lists\n", list_of_lists->size);
    
    remove_empty_lists(list_of_lists);
    
    printf("After removal: %d lists\n", list_of_lists->size);
    
    Node *current = list_of_lists->head;
    while (current != NULL) {
        List *inner = (List *)current->data;
        printf("List size: %d\n", inner->size);
        current = current->next;
    }
    
    free_list(list1);
    free_list(list2);
    free_list(list3);
    free_list(list4);
    free_list(list_of_lists);
    
    return 0;
}