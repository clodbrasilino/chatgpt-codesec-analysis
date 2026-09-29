#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} List;

List *list_create(size_t size) {
    List *l = malloc(sizeof(List));
    if (l == NULL) {
        return NULL;
    }
    l->data = malloc(size * sizeof(int));
    if (l->data == NULL) {
        free(l);
        return NULL;
    }
    l->size = size;
    return l;
}

void list_free(List *l) {
    if (l != NULL) {
        free(l->data);
        free(l);
    }
}

List *subtract_lists(const List *a, const List *b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
    if (a->size != b->size) {
        return NULL;
    }
    List *result = list_create(a->size);
    if (result == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < a->size; i++) {
        result->data[i] = a->data[i] - b->data[i];
    }
    return result;
}

int main(void) {
    size_t size = 5;
    List *a = list_create(size);
    if (a == NULL) {
        return EXIT_FAILURE;
    }
    List *b = list_create(size);
    if (b == NULL) {
        list_free(a);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < size; i++) {
        a->data[i] = (int)(i * 10);
        b->data[i] = (int)i;
    }
    List *c = subtract_lists(a, b);
    if (c == NULL) {
        list_free(a);
        list_free(b);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < c->size; i++) {
        printf("%d ", c->data[i]);
    }
    printf("\n");
    list_free(a);
    list_free(b);
    list_free(c);
    return EXIT_SUCCESS;
}