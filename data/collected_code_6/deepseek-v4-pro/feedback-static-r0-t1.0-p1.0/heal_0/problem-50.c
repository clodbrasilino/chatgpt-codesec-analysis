#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int length;
} LinkedList;

LinkedList* create_list() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->length = 0;
    return list;
}

void append(LinkedList* list, int data) {
    if (list == NULL) {
        return;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return;
    }
    new_node->data = data;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->length++;
}

void free_list(LinkedList* list) {
    if (list == NULL) {
        return;
    }
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

LinkedList* find_min_length_list(LinkedList** lists, int count) {
    if (lists == NULL || count <= 0) {
        return NULL;
    }
    
    LinkedList* min_list = NULL;
    int min_length = -1;
    
    for (int i = 0; i < count; i++) {
        if (lists[i] == NULL) {
            continue;
        }
        if (min_list == NULL || lists[i]->length < min_length) {
            min_list = lists[i];
            min_length = lists[i]->length;
        }
    }
    
    return min_list;
}

int main() {
    LinkedList* list1 = create_list();
    LinkedList* list2 = create_list();
    LinkedList* list3 = create_list();
    
    if (list1 == NULL || list2 == NULL || list3 == NULL) {
        free_list(list1);
        free_list(list2);
        free_list(list3);
        return 1;
    }
    
    append(list1, 1);
    append(list1, 2);
    
    append(list2, 3);
    
    append(list3, 4);
    append(list3, 5);
    append(list3, 6);
    
    LinkedList* lists[] = {list1, list2, list3};
    LinkedList* min_list = find_min_length_list(lists, 3);
    
    if (min_list != NULL) {
        printf("%d\n", min_list->length);
    }
    
    free_list(list1);
    free_list(list2);
    free_list(list3);
    
    return 0;
}