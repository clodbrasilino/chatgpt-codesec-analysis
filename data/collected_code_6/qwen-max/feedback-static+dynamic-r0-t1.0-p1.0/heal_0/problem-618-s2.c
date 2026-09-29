#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int value;
    struct List* next;
} List;

List* create_node(int value) {
    List* new_node = (List*)malloc(sizeof(List));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void append_to_list(List** head, int value) {
    List* new_node = create_node(value);
    if (*head == NULL) {
        *head = new_node;
    } else {
        List* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

List* divide_lists(List* list1, List* list2) {
    List* result = NULL;
    while (list1 != NULL && list2 != NULL) {
        if (list1->value % list2->value == 0) {
            append_to_list(&result, list1->value / list2->value);
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    return result;
}

void print_list(List* list) {
    while (list != NULL) {
        printf("%d -> ", list->value);
        list = list->next;
    }
    printf("NULL\n");
}

void free_list(List* list) {
    while (list != NULL) {
        List* temp = list;
        list = list->next;
        free(temp);
    }
}

int main() {
    List* list1 = NULL;
    append_to_list(&list1, 10);
    append_to_list(&list1, 20);
    append_to_list(&list1, 30);

    List* list2 = NULL;
    append_to_list(&list2, 2);
    append_to_list(&list2, 4);
    append_to_list(&list2, 5);

    List* result = divide_lists(list1, list2);

    printf("Result of division:\n");
    print_list(result);

    free_list(list1);
    free_list(list2);
    free_list(result);

    return 0;
}