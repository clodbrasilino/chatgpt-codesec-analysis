#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct ListOfLists {
    Node* list;
    struct ListOfLists* next;
} ListOfLists;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

ListOfLists* create_list_of_lists(Node* list) {
    ListOfLists* new_lol = (ListOfLists*)malloc(sizeof(ListOfLists));
    if (!new_lol) {
        exit(EXIT_FAILURE);
    }
    new_lol->list = list;
    new_lol->next = NULL;
    return new_lol;
}

void free_list(Node* head) {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

void free_list_of_lists(ListOfLists* head) {
    ListOfLists* current = head;
    while (current) {
        ListOfLists* next = current->next;
        free_list(current->list);
        free(current);
        current = next;
    }
}

ListOfLists* remove_empty_lists(ListOfLists* head) {
    ListOfLists* current = head;
    ListOfLists* prev = NULL;
    ListOfLists* new_head = head;

    while (current) {
        if (current->list == NULL) {
            if (prev == NULL) {
                new_head = current->next;
                free(current);
                current = new_head;
            } else {
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
    return new_head;
}

void print_list_of_lists(ListOfLists* head) {
    ListOfLists* current_lol = head;
    while (current_lol) {
        Node* current_node = current_lol->list;
        printf("[");
        while (current_node) {
            printf("%d", current_node->data);
            if (current_node->next) {
                printf(", ");
            }
            current_node = current_node->next;
        }
        printf("]\n");
        current_lol = current_lol->next;
    }
}

int main(void) {
    Node* list1 = create_node(1);
    list1->next = create_node(2);

    Node* list2 = NULL; 

    Node* list3 = create_node(3);
    list3->next = create_node(4);
    list3->next->next = create_node(5);

    Node* list4 = NULL;

    ListOfLists* lol = create_list_of_lists(list1);
    lol->next = create_list_of_lists(list2);
    lol->next->next = create_list_of_lists(list3);
    lol->next->next->next = create_list_of_lists(list4);

    lol = remove_empty_lists(lol);

    print_list_of_lists(lol);

    free_list_of_lists(lol);

    return 0;
}