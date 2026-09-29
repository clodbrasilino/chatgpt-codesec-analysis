#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next;
} List;

bool are_lists_equal(Node* head1, Node* head2) {
    Node* temp1 = head1;
    Node* temp2 = head2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->data != temp2->data) {
            return false;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return (temp1 == NULL && temp2 == NULL);
}

int count_unique_lists(List* list_of_lists) {
    if (list_of_lists == NULL) {
        return 0;
    }

    int unique_count = 0;
    List* current = list_of_lists;
    List* unique_lists = NULL;

    while (current != NULL) {
        bool is_unique = true;
        List* temp_unique = unique_lists;

        while (temp_unique != NULL) {
            if (are_lists_equal(current->head, temp_unique->head)) {
                is_unique = false;
                break;
            }
            temp_unique = temp_unique->next;
        }

        if (is_unique) {
            unique_count++;
            List* new_unique = (List*)malloc(sizeof(List));
            if (new_unique == NULL) {
                while (unique_lists != NULL) {
                    List* to_free = unique_lists;
                    unique_lists = unique_lists->next;
                    free(to_free);
                }
                return -1;
            }
            new_unique->head = current->head;
            new_unique->next = unique_lists;
            unique_lists = new_unique;
        }

        current = current->next;
    }

    while (unique_lists != NULL) {
        List* to_free = unique_lists;
        unique_lists = unique_lists->next;
        free(to_free);
    }

    return unique_count;
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node != NULL) {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}

List* create_list_node(Node* head) {
    List* new_list = (List*)malloc(sizeof(List));
    if (new_list != NULL) {
        new_list->head = head;
        new_list->next = NULL;
    }
    return new_list;
}

void free_inner_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void free_outer_list(List* list_of_lists) {
    while (list_of_lists != NULL) {
        List* temp = list_of_lists;
        list_of_lists = list_of_lists->next;
        free_inner_list(temp->head);
        free(temp);
    }
}

int main(void) {
    Node* list1 = create_node(1);
    if (list1 != NULL) {
        list1->next = create_node(2);
        if (list1->next == NULL) {
            free_inner_list(list1);
            return 1;
        }
    } else {
        return 1;
    }

    Node* list2 = create_node(1);
    if (list2 != NULL) {
        list2->next = create_node(2);
        if (list2->next == NULL) {
            free_inner_list(list1);
            free_inner_list(list2);
            return 1;
        }
    } else {
        free_inner_list(list1);
        return 1;
    }

    Node* list3 = create_node(3);
    if (list3 == NULL) {
        free_inner_list(list1);
        free_inner_list(list2);
        return 1;
    }

    List* outer_list = create_list_node(list1);
    if (outer_list != NULL) {
        outer_list->next = create_list_node(list2);
        if (outer_list->next != NULL) {
            outer_list->next->next = create_list_node(list3);
            if (outer_list->next->next == NULL) {
                free_outer_list(outer_list);
                free_inner_list(list3);
                return 1;
            }
        } else {
            free_outer_list(outer_list);
            free_inner_list(list2);
            free_inner_list(list3);
            return 1;
        }
    } else {
        free_inner_list(list1);
        free_inner_list(list2);
        free_inner_list(list3);
        return 1;
    }

    int unique = count_unique_lists(outer_list);
    if (unique != -1) {
        printf("%d\n", unique);
    }

    free_outer_list(outer_list);

    return 0;
}