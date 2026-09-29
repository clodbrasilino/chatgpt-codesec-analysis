#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ELEM_INT,
    ELEM_TUPLE
} ElemType;

typedef struct Element Element;

struct Element {
    ElemType type;
    int value;
    Element **children;
    size_t count;
};

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} IntList;

static Element *make_int(int value)
{
    Element *e = malloc(sizeof(Element));
    if (e == NULL) {
        return NULL;
    }
    e->type = ELEM_INT;
    e->value = value;
    e->children = NULL;
    e->count = 0;
    return e;
}

static Element *make_tuple(size_t count)
{
    Element *e = malloc(sizeof(Element));
    if (e == NULL) {
        return NULL;
    }
    e->type = ELEM_TUPLE;
    e->value = 0;
    e->count = count;
    if (count > 0) {
        e->children = calloc(count, sizeof(Element *));
        if (e->children == NULL) {
            free(e);
            return NULL;
        }
    } else {
        e->children = NULL;
    }
    return e;
}

static void free_element(Element *e)
{
    if (e == NULL) {
        return;
    }
    if (e->type == ELEM_TUPLE && e->children != NULL) {
        for (size_t i = 0; i < e->count; i++) {
            free_element(e->children[i]);
        }
        free(e->children);
    }
    free(e);
}

static int list_init(IntList *list)
{
    list->size = 0;
    list->capacity = 8;
    list->data = malloc(list->capacity * sizeof(int));
    if (list->data == NULL) {
        list->capacity = 0;
        return -1;
    }
    return 0;
}

static int list_append(IntList *list, int value)
{
    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        int *tmp = realloc(list->data, new_capacity * sizeof(int));
        if (tmp == NULL) {
            return -1;
        }
        list->data = tmp;
        list->capacity = new_capacity;
    }
    list->data[list->size] = value;
    list->size++;
    return 0;
}

static void list_free(IntList *list)
{
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

static int extract_even(const Element *e, IntList *result)
{
    if (e == NULL) {
        return 0;
    }
    if (e->type == ELEM_INT) {
        if (e->value % 2 == 0) {
            return list_append(result, e->value);
        }
        return 0;
    }
    for (size_t i = 0; i < e->count; i++) {
        if (extract_even(e->children[i], result) != 0) {
            return -1;
        }
    }
    return 0;
}

int main(void)
{
    Element *root = make_tuple(4);
    if (root == NULL) {
        fprintf(stderr, "allocation failure\n");
        return EXIT_FAILURE;
    }

    root->children[0] = make_int(4);
    root->children[1] = make_int(5);

    Element *inner = make_tuple(2);
    if (inner == NULL) {
        free_element(root);
        fprintf(stderr, "allocation failure\n");
        return EXIT_FAILURE;
    }
    inner->children[0] = make_int(7);
    inner->children[1] = make_int(6);
    root->children[2] = inner;

    Element *deep = make_tuple(2);
    if (deep == NULL) {
        free_element(root);
        fprintf(stderr, "allocation failure\n");
        return EXIT_FAILURE;
    }
    deep->children[0] = make_int(1);

    Element *deeper = make_tuple(2);
    if (deeper == NULL) {
        free_element(deep);
        free_element(root);
        fprintf(stderr, "allocation failure\n");
        return EXIT_FAILURE;
    }
    deeper->children[0] = make_int(2);
    deeper->children[1] = make_int(3);
    deep->children[1] = deeper;
    root->children[3] = deep;

    for (size_t i = 0; i < root->count; i++) {
        if (root->children[i] == NULL) {
            free_element(root);
            fprintf(stderr, "allocation failure\n");
            return EXIT_FAILURE;
        }
    }

    IntList result;
    if (list_init(&result) != 0) {
        free_element(root);
        fprintf(stderr, "allocation failure\n");
        return EXIT_FAILURE;
    }

    if (extract_even(root, &result) != 0) {
        list_free(&result);
        free_element(root);
        fprintf(stderr, "extraction failure\n");
        return EXIT_FAILURE;
    }

    printf("Even elements: ");
    for (size_t i = 0; i < result.size; i++) {
        printf("%d ", result.data[i]);
    }
    printf("\n");

    list_free(&result);
    free_element(root);
    return EXIT_SUCCESS;
}