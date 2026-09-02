#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int *list;
    size_t list_len;
} Tuple;

Tuple* create_tuple(const char *input_str, const int *input_list, size_t list_length) {
    if (input_str == NULL || input_list == NULL || list_length == 0) {
        return NULL;
    }

    Tuple *new_tuple = malloc(sizeof(Tuple));
    if (new_tuple == NULL) {
        return NULL;
    }

    new_tuple->str = strdup(input_str);
    if (new_tuple->str == NULL) {
        free(new_tuple);
        return NULL;
    }

    new_tuple->list = malloc(list_length * sizeof(int));
    if (new_tuple->list == NULL) {
        free(new_tuple->str);
        free(new_tuple);
        return NULL;
    }

    for (size_t i = 0; i < list_length; ++i) {
        new_tuple->list[i] = input_list[i];
    }
    new_tuple->list_len = list_length;

    return new_tuple;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->str);
        free(t->list);
        free(t);
    }
}

int main() {
    const char *str = "example";
    const int list[] = {1, 2, 3};
    size_t list_length = sizeof(list) / sizeof(list[0]);

    Tuple *tuple = create_tuple(str, list, list_length);

    if (tuple == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    printf("String: %s\n", tuple->str);
    printf("List: ");
    for (size_t i = 0; i < tuple->list_len; ++i) {
        printf("%d ", tuple->list[i]);
    }
    printf("\n");

    free_tuple(tuple);
    return EXIT_SUCCESS;
}