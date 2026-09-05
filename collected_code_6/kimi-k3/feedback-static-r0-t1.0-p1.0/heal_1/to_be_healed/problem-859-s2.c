#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} IntList;

int list_init(IntList *list, size_t capacity) {
    if (list == NULL) {
        return 0;
    }
    list->size = 0;
    list->capacity = capacity;
    if (capacity > 0) {
        list->data = (int *)malloc(capacity * sizeof(int));
        if (list->data == NULL) {
            list->capacity = 0;
            return 0;
        }
    } else {
        list->data = NULL;
    }
    return 1;
}

void list_free(IntList *list) {
    if (list == NULL) {
        return;
    }
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

int list_push(IntList *list, int value) {
    int *new_data;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;

    if (list == NULL) {
        return 0;
    }
    if (list->size >= list->capacity) {
        new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;
        new_data = (int *)realloc(list->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            return 0;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size] = value;
    list->size++;
    return 1;
}

void print_list(const IntList *list) {
    size_t i;

    if (list == NULL) {
        return;
    }
    printf("[");
    for (i = 0; i < list->size; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", list->data[i]);
    }
    printf("]\n");
}

int generate_sublists_recursive(const IntList *input, size_t index, IntList *current) {
    /* Possible weaknesses found:
     *  Unused variable: i [unusedVariable]
     */
    size_t i;

    if (input == NULL || current == NULL) {
        return 0;
    }
    if (index == input->size) {
        print_list(current);
        return 1;
    }
    if (!list_push(current, input->data[index])) {
        return 0;
    }
    if (!generate_sublists_recursive(input, index + 1, current)) {
        return 0;
    }
    current->size--;
    if (!generate_sublists_recursive(input, index + 1, current)) {
        return 0;
    }
    return 1;
}

int generate_sublists(const IntList *input) {
    IntList current;
    int result;

    if (input == NULL) {
        return 0;
    }
    if (!list_init(&current, input->size > 0 ? input->size : 1)) {
        return 0;
    }
    result = generate_sublists_recursive(input, 0, &current);
    list_free(&current);
    return result;
}

int main(void) {
    IntList list;
    int values[] = {1, 2, 3};
    size_t i;
    int status = EXIT_SUCCESS;

    if (!list_init(&list, 4)) {
        fprintf(stderr, "Failed to initialize list\n");
        return EXIT_FAILURE;
    }
    for (i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        if (!list_push(&list, values[i])) {
            fprintf(stderr, "Failed to add element to list\n");
            list_free(&list);
            return EXIT_FAILURE;
        }
    }
    if (!generate_sublists(&list)) {
        fprintf(stderr, "Failed to generate sublists\n");
        status = EXIT_FAILURE;
    }
    list_free(&list);
    return status;
}