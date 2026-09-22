#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int value;
    struct List *next;
} List;

List* create_node(int value) {
    List *new_node = (List*)malloc(sizeof(List));
    if (new_node == NULL) exit(EXIT_FAILURE);
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

List* add_lists(List *list1, List *list2) {
    List *result = NULL;
    List *current = NULL;

    while (list1 != NULL || list2 != NULL) {
        int val1 = (list1 != NULL) ? list1->value : 0;
        int val2 = (list2 != NULL) ? list2->value : 0;
        int sum = val1 + val2;

        List *new_node = create_node(sum);

        if (result == NULL) {
            result = new_node;
            current = new_node;
        } else {
            current->next = new_node;
            current = new_node;
        }

        if (list1 != NULL) list1 = list1->next;
        if (list2 != NULL) list2 = list2->next;
    }

    return result;
}

void print_list(List *head) {
    while (head != NULL) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    List *l1 = create_node(1);
    l1->next = create_node(2);
    l1->next->next = create_node(3);

    List *l2 = create_node(4);
    l2->next = create_node(5);
    l2->next->next = create_node(6);

    List *result = add_lists(l1, l2);

    print_list(result);

    while (l1 != NULL) {
        List *temp = l1;
        l1 = l1->next;
        free(temp);
    }

    while (l2 != NULL) {
        List *temp = l2;
        l2 = l2->next;
        free(temp);
    }

    while (result != NULL) {
        List *temp = result;
        result = result->next;
        free(temp);
    }

    return 0;
}