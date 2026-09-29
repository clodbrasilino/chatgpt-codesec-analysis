#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int is_list;
    union {
        int value;
        struct {
            struct Node* head;
            struct Node* tail;
        } list;
    } data;
} Node;

typedef struct {
    int* items;
    int count;
    int capacity;
} FlatArray;

FlatArray* flat_array_create() {
    FlatArray* arr = malloc(sizeof(FlatArray));
    if (!arr) return NULL;
    arr->capacity = 16;
    arr->count = 0;
    arr->items = malloc(arr->capacity * sizeof(int));
    if (!arr->items) {
        free(arr);
        return NULL;
    }
    return arr;
}

int flat_array_append(FlatArray* arr, int value) {
    if (arr->count == arr->capacity) {
        int new_capacity = arr->capacity * 2;
        int* new_items = realloc(arr->items, new_capacity * sizeof(int));
        if (!new_items) return -1;
        arr->items = new_items;
        arr->capacity = new_capacity;
    }
    arr->items[arr->count++] = value;
    return 0;
}

void flat_array_free(FlatArray* arr) {
    if (arr) {
        free(arr->items);
        free(arr);
    }
}

Node* make_int(int value) {
    Node* n = malloc(sizeof(Node));
    if (!n) return NULL;
    n->is_list = 0;
    n->data.value = value;
    return n;
}

Node* make_list(Node* head, Node* tail) {
    Node* n = malloc(sizeof(Node));
    if (!n) return NULL;
    n->is_list = 1;
    n->data.list.head = head;
    n->data.list.tail = tail;
    return n;
}

int flatten(Node* node, FlatArray* arr) {
    if (!node) return 0;
    if (!node->is_list) {
        return flat_array_append(arr, node->data.value);
    }
    if (flatten(node->data.list.head, arr) != 0) return -1;
    if (flatten(node->data.list.tail, arr) != 0) return -1;
    return 0;
}

void free_tree(Node* node) {
    if (!node) return;
    if (node->is_list) {
        free_tree(node->data.list.head);
        free_tree(node->data.list.tail);
    }
    free(node);
}

int main() {
    Node* n1 = make_int(1);
    Node* n2 = make_int(2);
    Node* n3 = make_int(3);
    Node* n4 = make_int(4);
    Node* n5 = make_int(5);
    
    if (!n1 || !n2 || !n3 || !n4 || !n5) {
        free_tree(n1);
        free_tree(n2);
        free_tree(n3);
        free_tree(n4);
        free_tree(n5);
        return 1;
    }

    Node* l1 = make_list(n2, n3);
    if (!l1) {
        free_tree(n1); free_tree(n2); free_tree(n3); free_tree(n4); free_tree(n5);
        return 1;
    }

    Node* l2 = make_list(n4, n5);
    if (!l2) {
        free_tree(n1); free_tree(l1); free_tree(n4); free_tree(n5);
        return 1;
    }

    Node* root = make_list(n1, make_list(l1, l2));
    if (!root) {
        free_tree(n1); free_tree(l1); free_tree(l2);
        return 1;
    }

    FlatArray* arr = flat_array_create();
    if (!arr) {
        free_tree(root);
        return 1;
    }

    if (flatten(root, arr) != 0) {
        flat_array_free(arr);
        free_tree(root);
        return 1;
    }

    for (int i = 0; i < arr->count; i++) {
        printf("%d ", arr->items[i]);
    }
    printf("\n");

    flat_array_free(arr);
    free_tree(root);

    return 0;
}