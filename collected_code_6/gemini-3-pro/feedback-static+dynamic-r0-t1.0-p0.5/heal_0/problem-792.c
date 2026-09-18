#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct ListOfLists {
    Node* head;
    struct ListOfLists* next;
} ListOfLists;

size_t count_lists(const ListOfLists* lol) {
    size_t count = 0;
    while (lol != NULL) {
        count++;
        lol = lol->next;
    }
    return count;
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

ListOfLists* create_list_of_lists(Node* head) {
    ListOfLists* new_lol = (ListOfLists*)malloc(sizeof(ListOfLists));
    if (new_lol == NULL) {
        exit(EXIT_FAILURE);
    }
    new_lol->head = head;
    new_lol->next = NULL;
    return new_lol;
}

void free_all(ListOfLists* lol) {
    while (lol != NULL) {
        Node* current_node = lol->head;
        while (current_node != NULL) {
            Node* temp_node = current_node;
            current_node = current_node->next;
            free(temp_node);
        }
        ListOfLists* temp_lol = lol;
        lol = lol->next;
        free(temp_lol);
    }
}

int main(void) {
    Node* list1 = create_node(1);
    list1->next = create_node(2);

    Node* list2 = create_node(3);

    ListOfLists* lol = create_list_of_lists(list1);
    lol->next = create_list_of_lists(list2);

    size_t total_lists = count_lists(lol);
    printf("%zu\n", total_lists);

    free_all(lol);

    return EXIT_SUCCESS;
}