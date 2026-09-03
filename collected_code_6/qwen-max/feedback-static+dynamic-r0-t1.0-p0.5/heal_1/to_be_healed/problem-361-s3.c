#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    size_t size;
    struct List *next;
} List;

List* create_list() {
    return (List*)calloc(1, sizeof(List));
}

void free_list(List *list) {
    if (list) {
        free(list->data);
        free_list(list->next);
        free(list);
    }
}

/* Possible weaknesses found:
 *  Parameter 'elements' can be declared as pointer to const [constParameterPointer]
 */
List* append_to_list(List *head, int *elements, size_t num_elements) {
    List *new_node = (List*)malloc(sizeof(List));
    new_node->data = (int*)malloc(num_elements * sizeof(int));
    for (size_t i = 0; i < num_elements; ++i) {
        new_node->data[i] = elements[i];
    }
    new_node->size = num_elements;
    new_node->next = NULL;

    if (head == NULL) {
        return new_node;
    }

    List *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return head;
}

List* remove_empty_lists(List *head) {
    List *dummy = (List*)malloc(sizeof(List));
    dummy->next = head;
    List *prev = dummy;
    List *current = head;

    while (current != NULL) {
        if (current->size == 0) {
            prev->next = current->next;
            free(current->data);
            free(current);
            current = prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }

    List *new_head = dummy->next;
    free(dummy);
    return new_head;
}

void print_list(List *head) {
    while (head != NULL) {
        printf("[");
        for (size_t i = 0; i < head->size; ++i) {
            printf("%d", head->data[i]);
            if (i < head->size - 1) {
                printf(", ");
            }
        }
        printf("]");
        if (head->next != NULL) {
            printf(" -> ");
        }
        head = head->next;
    }
    printf("\n");
}

int main() {
    List *head = create_list();

    int elements1[] = {1, 2, 3};
    head = append_to_list(head, elements1, 3);

    int elements2[] = {};
    head = append_to_list(head, elements2, 0);

    int elements3[] = {4, 5};
    head = append_to_list(head, elements3, 2);

    int elements4[] = {};
    head = append_to_list(head, elements4, 0);

    int elements5[] = {6};
    head = append_to_list(head, elements5, 1);

    printf("Original list: \n");
    print_list(head);

    head = remove_empty_lists(head);

    printf("List after removing empty lists: \n");
    print_list(head);

    free_list(head);
    return 0;
}