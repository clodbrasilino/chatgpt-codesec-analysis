#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} LinkedList;

LinkedList *create_list(void) {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

int append(LinkedList *list, int value) {
    if (list == NULL) {
        return -1;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->data = value;
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

void free_list(LinkedList *list) {
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

int count_sublists_containing_element(LinkedList **lists, int num_lists, int element) {
    if (lists == NULL || num_lists <= 0) {
        return 0;
    }
    
    int count = 0;
    for (int i = 0; i < num_lists; i++) {
        if (lists[i] == NULL) {
            continue;
        }
        Node *current = lists[i]->head;
        while (current != NULL) {
            if (current->data == element) {
                count++;
                break;
            }
            current = current->next;
        }
    }
    return count;
}

int main(void) {
    LinkedList **lists = (LinkedList **)malloc(3 * sizeof(LinkedList *));
    if (lists == NULL) {
        return 1;
    }
    
    for (int i = 0; i < 3; i++) {
        lists[i] = create_list();
        if (lists[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free_list(lists[j]);
            }
            free(lists);
            return 1;
        }
    }
    
    append(lists[0], 1);
    append(lists[0], 2);
    append(lists[0], 3);
    
    append(lists[1], 4);
    append(lists[1], 5);
    
    append(lists[2], 2);
    append(lists[2], 6);
    append(lists[2], 7);
    
    int result = count_sublists_containing_element(lists, 3, 2);
    printf("%d\n", result);
    
    for (int i = 0; i < 3; i++) {
        free_list(lists[i]);
    }
    free(lists);
    
    return 0;
}