#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next_list;
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
    new_list->next_list = NULL;
    return new_list;
}

void append_node(List* list, int data) {
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
}

void append_list(List** head_list, List* new_list) {
    if (!head_list || !new_list) return;
    if (!*head_list) {
        *head_list = new_list;
    } else {
        List* current = *head_list;
        while (current->next_list) {
            current = current->next_list;
        }
        current->next_list = new_list;
    }
}

bool contains(Node* head, int value) {
    Node* current = head;
    while (current) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

List* find_common_elements(List* nested_lists) {
    List* common_elements = create_list();
    if (!nested_lists || !nested_lists->head) {
        return common_elements;
    }

    Node* current_item = nested_lists->head;
    while (current_item) {
        int val = current_item->data;
        bool is_common = true;
        
        List* current_list = nested_lists->next_list;
        while (current_list) {
            if (!contains(current_list->head, val)) {
                is_common = false;
                break;
            }
            current_list = current_list->next_list;
        }

        if (is_common && !contains(common_elements->head, val)) {
            append_node(common_elements, val);
        }

        current_item = current_item->next;
    }

    return common_elements;
}

void free_nodes(Node* head) {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

void free_nested_lists(List* head_list) {
    List* current = head_list;
    while (current) {
        List* next = current->next_list;
        free_nodes(current->head);
        free(current);
        current = next;
    }
}

void print_list(List* list) {
    if (!list || !list->head) {
        printf("Empty\n");
        return;
    }
    Node* current = list->head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    List* nested_lists = NULL;

    List* list1 = create_list();
    append_node(list1, 1);
    append_node(list1, 2);
    append_node(list1, 3);
    append_node(list1, 4);

    List* list2 = create_list();
    append_node(list2, 2);
    append_node(list2, 3);
    append_node(list2, 5);

    List* list3 = create_list();
    append_node(list3, 3);
    append_node(list3, 2);
    append_node(list3, 6);

    append_list(&nested_lists, list1);
    append_list(&nested_lists, list2);
    append_list(&nested_lists, list3);

    List* common = find_common_elements(nested_lists);

    print_list(common);

    free_nested_lists(nested_lists);
    free_nodes(common->head);
    free(common);

    return EXIT_SUCCESS;
}