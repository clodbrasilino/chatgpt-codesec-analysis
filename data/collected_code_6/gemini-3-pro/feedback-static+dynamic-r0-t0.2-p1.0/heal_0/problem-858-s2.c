#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* next;
} Node;

typedef struct ListOfLists {
    Node* head;
    struct ListOfLists* next;
} ListOfLists;

long long count_and_square(ListOfLists* lol) {
    if (lol == NULL) {
        return 0;
    }

    long long count = 0;
    ListOfLists* current = lol;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count * count;
}

void free_list_of_lists(ListOfLists* lol) {
    ListOfLists* current_lol = lol;
    while (current_lol != NULL) {
        Node* current_node = current_lol->head;
        while (current_node != NULL) {
            Node* temp_node = current_node;
            current_node = current_node->next;
            free(temp_node);
        }
        ListOfLists* temp_lol = current_lol;
        current_lol = current_lol->next;
        free(temp_lol);
    }
}

int main(void) {
    ListOfLists* lol = malloc(sizeof(ListOfLists));
    if (lol == NULL) {
        return 1;
    }
    lol->head = NULL;
    
    lol->next = malloc(sizeof(ListOfLists));
    if (lol->next == NULL) {
        free_list_of_lists(lol);
        return 1;
    }
    lol->next->head = NULL;
    
    lol->next->next = malloc(sizeof(ListOfLists));
    if (lol->next->next == NULL) {
        free_list_of_lists(lol);
        return 1;
    }
    lol->next->next->head = NULL;
    lol->next->next->next = NULL;

    long long result = count_and_square(lol);
    printf("%lld\n", result);

    free_list_of_lists(lol);

    return 0;
}