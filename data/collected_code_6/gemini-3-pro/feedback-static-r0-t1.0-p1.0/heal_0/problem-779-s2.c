#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    size_t length;
    struct List* next;
} List;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List* create_list() {
    List* new_list = (List*)malloc(sizeof(List));
    if (!new_list) {
        exit(EXIT_FAILURE);
    }
    new_list->head = NULL;
    new_list->length = 0;
    new_list->next = NULL;
    return new_list;
}

void append_to_list(List* list, int data) {
    if (!list) return;
    
    Node* new_node = create_node(data);
    if (!list->head) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->length++;
}

bool are_lists_equal(const List* list1, const List* list2) {
    if (!list1 || !list2) return false;
    if (list1->length != list2->length) return false;

    Node* curr1 = list1->head;
    Node* curr2 = list2->head;

    while (curr1 && curr2) {
        if (curr1->data != curr2->data) return false;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    return true;
}

size_t count_unique_lists(List* head_of_lists) {
    if (!head_of_lists) return 0;

    size_t unique_count = 0;
    List* current = head_of_lists;

    while (current) {
        bool is_unique = true;
        List* checker = head_of_lists;

        while (checker != current) {
            if (are_lists_equal(checker, current)) {
                is_unique = false;
                break;
            }
            checker = checker->next;
        }

        if (is_unique) {
            unique_count++;
        }
        current = current->next;
    }

    return unique_count;
}

void free_list(List* list) {
    if (!list) return;
    Node* current_node = list->head;
    while (current_node) {
        Node* temp = current_node;
        current_node = current_node->next;
        free(temp);
    }
    free(list);
}

void free_all_lists(List* head_of_lists) {
    List* current_list = head_of_lists;
    while (current_list) {
        List* temp = current_list;
        current_list = current_list->next;
        free_list(temp);
    }
}

int main(void) {
    List* list1 = create_list();
    append_to_list(list1, 1);
    append_to_list(list1, 2);
    append_to_list(list1, 3);

    List* list2 = create_list();
    append_to_list(list2, 4);
    append_to_list(list2, 5);

    List* list3 = create_list();
    append_to_list(list3, 1);
    append_to_list(list3, 2);
    append_to_list(list3, 3);

    List* list4 = create_list();
    append_to_list(list4, 6);

    list1->next = list2;
    list2->next = list3;
    list3->next = list4;

    size_t unique_count = count_unique_lists(list1);
    printf("Number of unique lists: %zu\n", unique_count);

    free_all_lists(list1);

    return EXIT_SUCCESS;
}