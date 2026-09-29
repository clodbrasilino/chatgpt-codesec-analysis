#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int is_even;
    union {
        int value;
        struct List *list;
    };
} Element;

typedef struct List {
    Element data;
    struct List *next;
} List;

List* create_element(int value, int is_even) {
    List *new = (List*)malloc(sizeof(List));
    new->data.is_even = is_even;
    new->data.value = value;
    new->next = NULL;
    return new;
}

List* create_list() {
    return NULL;
}

void push_front(List **head, int value, int is_even) {
    List *new = create_element(value, is_even);
    new->next = *head;
    *head = new;
}

void free_list(List **head) {
    List *current = *head;
    while (current != NULL) {
        List *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

List* extract_even_elements(List *input) {
    List *output = create_list();
    if (input == NULL) {
        return output;
    }

    List *current = input;
    while (current != NULL) {
        if (current->data.is_even && !current->data.list) {
            push_front(&output, current->data.value, 1);
        } else if (current->data.list) {
            List *sublist = extract_even_elements(current->data.list);
            if (sublist != NULL) {
                while (sublist != NULL) {
                    push_front(&output, sublist->data.value, 1);
                    List *temp = sublist;
                    sublist = sublist->next;
                    free(temp);
                }
            }
        }
        current = current->next;
    }
    return output;
}

void print_list(List *head) {
    List *current = head;
    while (current != NULL) {
        printf("%d ", current->data.value);
        current = current->next;
    }
    printf("\n");
}

int main() {
    List *mixed_tuple = create_list();

    push_front(&mixed_tuple, 2, 1); // Even
    push_front(&mixed_tuple, 3, 0); // Odd
    List *nested_list = create_list();
    push_front(&nested_list, 1, 0); // Odd
    push_front(&nested_list, 4, 1); // Even
    List *nested_element = create_element(0, 0);
    nested_element->data.list = nested_list;
    mixed_tuple->next = nested_element;

    push_front(&mixed_tuple, 5, 0); // Odd

    printf("Original List: ");
    print_list(mixed_tuple);

    List *even_elements = extract_even_elements(mixed_tuple);
    printf("Even Elements: ");
    print_list(even_elements);

    free_list(&mixed_tuple);
    free_list(&even_elements);
    return 0;
}