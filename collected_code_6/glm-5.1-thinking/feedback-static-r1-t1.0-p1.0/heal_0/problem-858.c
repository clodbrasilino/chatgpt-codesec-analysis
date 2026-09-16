#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct ListOfLists {
    Node *list;
    struct ListOfLists *next;
} ListOfLists;

int count_and_square_lists(ListOfLists *head) {
    int count = 0;
    ListOfLists *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count * count;
}

void free_list(Node *head) {
    Node *current = head;
    Node *next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

void free_list_of_lists(ListOfLists *head) {
    ListOfLists *current = head;
    ListOfLists *next_lol;
    while (current != NULL) {
        next_lol = current->next;
        free_list(current->list);
        free(current);
        current = next_lol;
    }
}

int main(void) {
    ListOfLists *head = NULL;
    ListOfLists *tail = NULL;
    int num_lists = 3;

    for (int i = 0; i < num_lists; i++) {
        ListOfLists *new_lol = (ListOfLists *)malloc(sizeof(ListOfLists));
        if (new_lol == NULL) {
            free_list_of_lists(head);
            return EXIT_FAILURE;
        }
        new_lol->list = NULL;
        new_lol->next = NULL;

        if (head == NULL) {
            head = new_lol;
            tail = new_lol;
        } else {
            tail->next = new_lol;
            tail = new_lol;
        }
    }

    int result = count_and_square_lists(head);
    printf("%d\n", result);

    free_list_of_lists(head);

    return EXIT_SUCCESS;
}