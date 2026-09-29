#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct ListOfLists {
    Node *inner_list;
    struct ListOfLists *next;
} ListOfLists;

Node* create_node(int data);
ListOfLists* create_list_of_lists_node(Node *inner_list);
void free_inner_list(Node *head);
void free_list_of_lists(ListOfLists *head);
void remove_empty_lists(ListOfLists **head);
void print_list_of_lists(const ListOfLists *head);

Node* create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

ListOfLists* create_list_of_lists_node(Node *inner_list) {
    ListOfLists *new_node = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->inner_list = inner_list;
    new_node->next = NULL;
    return new_node;
}

void free_inner_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

void free_list_of_lists(ListOfLists *head) {
    while (head != NULL) {
        ListOfLists *temp = head;
        head = head->next;
        free_inner_list(temp->inner_list);
        free(temp);
    }
}

void remove_empty_lists(ListOfLists **head) {
    if (!head || !*head) {
        return;
    }

    ListOfLists *current = *head;
    ListOfLists *prev = NULL;

    while (current != NULL) {
        if (current->inner_list == NULL) {
            ListOfLists *temp = current;
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void print_list_of_lists(const ListOfLists *head) {
    const ListOfLists *current = head;
    while (current != NULL) {
        const Node *inner = current->inner_list;
        if (!inner) {
            printf("[]\n");
        } else {
            printf("[");
            while (inner != NULL) {
                printf("%d", inner->data);
                if (inner->next) {
                    printf(", ");
                }
                inner = inner->next;
            }
            printf("]\n");
        }
        current = current->next;
    }
}

int main(void) {
    Node *list1 = create_node(1);
    list1->next = create_node(2);

    Node *list2 = NULL;

    Node *list3 = create_node(3);
    list3->next = create_node(4);
    list3->next->next = create_node(5);

    Node *list4 = NULL;

    ListOfLists *head = create_list_of_lists_node(list1);
    head->next = create_list_of_lists_node(list2);
    head->next->next = create_list_of_lists_node(list3);
    head->next->next->next = create_list_of_lists_node(list4);

    remove_empty_lists(&head);

    print_list_of_lists(head);

    free_list_of_lists(head);

    return EXIT_SUCCESS;
}