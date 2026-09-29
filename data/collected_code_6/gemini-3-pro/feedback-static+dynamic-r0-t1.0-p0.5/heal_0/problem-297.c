#include <stdio.h>
#include <stdlib.h>

typedef struct NestedList {
    int is_integer;
    int value;
    struct NestedList** list;
    size_t list_size;
} NestedList;

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} FlatList;

void init_flat_list(FlatList* fl) {
    fl->head = NULL;
    fl->tail = NULL;
}

int append_flat_list(FlatList* fl, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        return 0;
    }
    new_node->value = value;
    new_node->next = NULL;

    if (!fl->head) {
        fl->head = new_node;
        fl->tail = new_node;
    } else {
        fl->tail->next = new_node;
        fl->tail = new_node;
    }
    return 1;
}

void free_flat_list(FlatList* fl) {
    Node* current = fl->head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    fl->head = NULL;
    fl->tail = NULL;
}

int flatten_helper(NestedList* nested, FlatList* fl) {
    if (!nested) {
        return 1;
    }

    if (nested->is_integer) {
        return append_flat_list(fl, nested->value);
    } else {
        for (size_t i = 0; i < nested->list_size; ++i) {
            if (!flatten_helper(nested->list[i], fl)) {
                return 0;
            }
        }
    }
    return 1;
}

FlatList* flatten(NestedList* nested) {
    if (!nested) {
        return NULL;
    }

    FlatList* fl = (FlatList*)malloc(sizeof(FlatList));
    if (!fl) {
        return NULL;
    }
    init_flat_list(fl);

    if (!flatten_helper(nested, fl)) {
        free_flat_list(fl);
        free(fl);
        return NULL;
    }

    return fl;
}

void print_flat_list(FlatList* fl) {
    if (!fl) return;
    Node* current = fl->head;
    printf("[");
    while (current) {
        printf("%d", current->value);
        if (current->next) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

void free_nested_list(NestedList* nested) {
    if (!nested) return;
    if (!nested->is_integer) {
        for (size_t i = 0; i < nested->list_size; ++i) {
            free_nested_list(nested->list[i]);
        }
        free(nested->list);
    }
    free(nested);
}

NestedList* create_integer(int value) {
    NestedList* nl = (NestedList*)malloc(sizeof(NestedList));
    if (!nl) return NULL;
    nl->is_integer = 1;
    nl->value = value;
    nl->list = NULL;
    nl->list_size = 0;
    return nl;
}

NestedList* create_list(NestedList** elements, size_t size) {
    NestedList* nl = (NestedList*)malloc(sizeof(NestedList));
    if (!nl) return NULL;
    nl->is_integer = 0;
    nl->value = 0;
    nl->list = elements;
    nl->list_size = size;
    return nl;
}

int main(void) {
    NestedList* elem1 = create_integer(1);
    NestedList* elem2 = create_integer(2);
    NestedList** sublist1_elems = (NestedList**)malloc(2 * sizeof(NestedList*));
    if (!sublist1_elems) {
        free_nested_list(elem1);
        free_nested_list(elem2);
        return 1;
    }
    sublist1_elems[0] = elem1;
    sublist1_elems[1] = elem2;
    NestedList* sublist1 = create_list(sublist1_elems, 2);

    NestedList* elem3 = create_integer(3);

    NestedList* elem4 = create_integer(4);
    NestedList* elem5 = create_integer(5);
    NestedList** sublist2_elems = (NestedList**)malloc(2 * sizeof(NestedList*));
    if (!sublist2_elems) {
        free_nested_list(sublist1);
        free_nested_list(elem3);
        free_nested_list(elem4);
        free_nested_list(elem5);
        return 1;
    }
    sublist2_elems[0] = elem4;
    sublist2_elems[1] = elem5;
    NestedList* sublist2 = create_list(sublist2_elems, 2);

    NestedList** root_elems = (NestedList**)malloc(3 * sizeof(NestedList*));
    if (!root_elems) {
        free_nested_list(sublist1);
        free_nested_list(elem3);
        free_nested_list(sublist2);
        return 1;
    }
    root_elems[0] = sublist1;
    root_elems[1] = elem3;
    root_elems[2] = sublist2;
    NestedList* root = create_list(root_elems, 3);

    FlatList* flat = flatten(root);
    if (flat) {
        print_flat_list(flat);
        free_flat_list(flat);
        free(flat);
    }

    free_nested_list(root);

    return 0;
}