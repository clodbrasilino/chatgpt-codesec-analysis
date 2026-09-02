#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Element {
    bool is_tuple;
    int value;
    struct Element *next;
} Element;

int count_until_tuple(Element *head) {
    int count = 0;
    Element *current = head;
    while (current != NULL && !current->is_tuple) {
        count++;
        current = current->next;
    }
    return count;
}

Element *create_element(int value, bool is_tuple) {
    Element *element = (Element *)malloc(sizeof(Element));
    if (element == NULL) {
        exit(EXIT_FAILURE);
    }
    element->value = value;
    element->is_tuple = is_tuple;
    element->next = NULL;
    return element;
}

void free_list(Element *head) {
    Element *current = head;
    while (current != NULL) {
        Element *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Element *head = create_element(1, false);
    head->next = create_element(2, false);
    head->next->next = create_element(3, false);
    head->next->next->next = create_element(4, true);
    head->next->next->next->next = create_element(5, false);

    int result = count_until_tuple(head);
    printf("%d\n", result);

    free_list(head);
    return 0;
}