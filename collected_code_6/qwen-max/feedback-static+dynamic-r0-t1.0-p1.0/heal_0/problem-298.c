#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *sublist;
} Node;

Node* create_node(int value, Node *next, Node *sublist) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = next;
    new_node->sublist = sublist;
    return new_node;
}

int is_element_in_list(Node *head, int value) {
    while (head != NULL) {
        if (head->value == value) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

void find_nested_elements(Node *main_list, Node *search_list) {
    while (main_list != NULL) {
        if (is_element_in_list(search_list, main_list->value)) {
            printf("%d\n", main_list->value);
        }
        if (main_list->sublist != NULL) {
            find_nested_elements(main_list->sublist, search_list);
        }
        main_list = main_list->next;
    }
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        if (temp->sublist != NULL) {
            free_list(temp->sublist);
        }
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *sublist1 = create_node(4, create_node(5, NULL, NULL), NULL);
    Node *sublist2 = create_node(6, create_node(7, NULL, NULL), NULL);

    Node *list1 = create_node(1, create_node(2, create_node(3, NULL, sublist1), NULL), NULL);
    Node *list2 = create_node(2, create_node(8, create_node(9, NULL, sublist2), NULL), NULL);

    Node *search_list = create_node(2, create_node(4, create_node(6, create_node(8, NULL, NULL), NULL), NULL), NULL);

    find_nested_elements(list1, search_list);
    find_nested_elements(list2, search_list);

    free_list(list1);
    free_list(list2);
    free_list(search_list);

    return 0;
}