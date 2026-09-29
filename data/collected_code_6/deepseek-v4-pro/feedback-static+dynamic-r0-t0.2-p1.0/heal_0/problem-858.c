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

int count_lists_and_square(List *list_of_lists) {
    if (list_of_lists == NULL) {
        return 0;
    }
    
    int count = 0;
    Node *current = list_of_lists->head;
    
    while (current != NULL) {
        if (current->data != NULL) {
            count++;
        }
        current = current->next;
    }
    
    return count * count;
}

List *create_list() {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

int append_to_list(List *list, void *data) {
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

int main() {
    List *list_of_lists = create_list();
    if (list_of_lists == NULL) {
        return 1;
    }
    
    List *list1 = create_list();
    List *list2 = create_list();
    List *list3 = create_list();
    
    if (list1 == NULL || list2 == NULL || list3 == NULL) {
        free_list(list1);
        free_list(list2);
        free_list(list3);
        free_list(list_of_lists);
        return 1;
    }
    
    if (append_to_list(list_of_lists, list1) != 0 ||
        append_to_list(list_of_lists, list2) != 0 ||
        append_to_list(list_of_lists, list3) != 0) {
        free_list(list1);
        free_list(list2);
        free_list(list3);
        free_list(list_of_lists);
        return 1;
    }
    
    int result = count_lists_and_square(list_of_lists);
    printf("%d\n", result);
    
    free_list(list1);
    free_list(list2);
    free_list(list3);
    free_list(list_of_lists);
    
    return 0;
}