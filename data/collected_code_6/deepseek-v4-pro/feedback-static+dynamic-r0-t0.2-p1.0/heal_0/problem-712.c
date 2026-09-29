#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next;
} List;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List* create_list() {
    List* new_list = (List*)malloc(sizeof(List));
    if (new_list == NULL) {
        return NULL;
    }
    new_list->head = NULL;
    new_list->next = NULL;
    return new_list;
}

void append_node(List* list, int data) {
    Node* new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    if (list->head == NULL) {
        list->head = new_node;
        return;
    }
    Node* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void append_list(List** head, List* new_list) {
    if (*head == NULL) {
        *head = new_list;
        return;
    }
    List* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_list;
}

int lists_equal(List* list1, List* list2) {
    Node* current1 = list1->head;
    Node* current2 = list2->head;
    
    while (current1 != NULL && current2 != NULL) {
        if (current1->data != current2->data) {
            return 0;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    
    return current1 == NULL && current2 == NULL;
}

void free_list(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

void free_all_lists(List* head) {
    List* current = head;
    while (current != NULL) {
        List* temp = current;
        current = current->next;
        free_list(temp);
    }
}

List* remove_duplicates(List* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    List* current = head;
    while (current != NULL) {
        List* runner = current;
        while (runner->next != NULL) {
            if (lists_equal(current, runner->next)) {
                List* duplicate = runner->next;
                runner->next = duplicate->next;
                free_list(duplicate);
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
    
    return head;
}

void print_lists(List* head) {
    List* current = head;
    while (current != NULL) {
        Node* node = current->head;
        printf("[");
        while (node != NULL) {
            printf("%d", node->data);
            if (node->next != NULL) {
                printf(", ");
            }
            node = node->next;
        }
        printf("]");
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

int main() {
    List* list_of_lists = NULL;
    
    List* list1 = create_list();
    append_node(list1, 1);
    append_node(list1, 2);
    append_node(list1, 3);
    append_list(&list_of_lists, list1);
    
    List* list2 = create_list();
    append_node(list2, 4);
    append_node(list2, 5);
    append_list(&list_of_lists, list2);
    
    List* list3 = create_list();
    append_node(list3, 1);
    append_node(list3, 2);
    append_node(list3, 3);
    append_list(&list_of_lists, list3);
    
    List* list4 = create_list();
    append_node(list4, 6);
    append_list(&list_of_lists, list4);
    
    List* list5 = create_list();
    append_node(list5, 4);
    append_node(list5, 5);
    append_list(&list_of_lists, list5);
    
    printf("Original list of lists:\n");
    print_lists(list_of_lists);
    
    list_of_lists = remove_duplicates(list_of_lists);
    
    printf("After removing duplicates:\n");
    print_lists(list_of_lists);
    
    free_all_lists(list_of_lists);
    
    return 0;
}