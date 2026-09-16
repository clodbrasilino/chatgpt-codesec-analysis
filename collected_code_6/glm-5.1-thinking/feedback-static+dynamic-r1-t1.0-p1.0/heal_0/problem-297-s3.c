#include <stdio.h>
#include <stdlib.h>

typedef enum { NODE_INT, NODE_LIST } NodeType;

typedef struct Node {
    NodeType type;
    union {
        int value;
        struct {
            struct Node *items;
            size_t count;
        } list;
    };
} Node;

typedef struct {
    int *items;
    size_t count;
} FlatResult;

size_t count_ints(const Node *root) {
    if (root == NULL) return 0;
    if (root->type == NODE_INT) return 1;
    if (root->list.items == NULL) return 0;
    size_t total = 0;
    for (size_t i = 0; i < root->list.count; i++) {
        total += count_ints(&root->list.items[i]);
    }
    return total;
}

void fill_ints(const Node *root, int *arr, size_t *idx) {
    if (root == NULL) return;
    if (root->type == NODE_INT) {
        arr[*idx] = root->value;
        (*idx)++;
        return;
    }
    if (root->list.items == NULL) return;
    for (size_t i = 0; i < root->list.count; i++) {
        fill_ints(&root->list.items[i], arr, idx);
    }
}

FlatResult flatten(const Node *root) {
    FlatResult result = {NULL, 0};
    if (root == NULL) return result;
    size_t count = count_ints(root);
    if (count == 0) return result;
    int *arr = (int *)malloc(count * sizeof(int));
    if (arr == NULL) return result;
    size_t idx = 0;
    fill_ints(root, arr, &idx);
    result.items = arr;
    result.count = count;
    return result;
}

Node make_int(int val) {
    Node n;
    n.type = NODE_INT;
    n.value = val;
    return n;
}

Node make_list(Node *items, size_t count) {
    Node n;
    n.type = NODE_LIST;
    n.list.items = items;
    n.list.count = count;
    return n;
}

void free_node(Node *root) {
    if (root == NULL) return;
    if (root->type == NODE_LIST) {
        if (root->list.items != NULL) {
            for (size_t i = 0; i < root->list.count; i++) {
                free_node(&root->list.items[i]);
            }
            free(root->list.items);
        }
    }
}

int main(void) {
    Node *inner_list = (Node *)malloc(2 * sizeof(Node));
    if (inner_list == NULL) return EXIT_FAILURE;
    inner_list[0] = make_int(5);
    inner_list[1] = make_int(6);

    Node *mid_list = (Node *)malloc(2 * sizeof(Node));
    if (mid_list == NULL) {
        free(inner_list);
        return EXIT_FAILURE;
    }
    mid_list[0] = make_int(4);
    mid_list[1] = make_list(inner_list, 2);

    Node *another_list = (Node *)malloc(2 * sizeof(Node));
    if (another_list == NULL) {
        free(mid_list);
        free(inner_list);
        return EXIT_FAILURE;
    }
    another_list[0] = make_int(2);
    another_list[1] = make_int(3);

    Node *outer_list = (Node *)malloc(3 * sizeof(Node));
    if (outer_list == NULL) {
        free(another_list);
        free(mid_list);
        free(inner_list);
        return EXIT_FAILURE;
    }
    outer_list[0] = make_int(1);
    outer_list[1] = make_list(mid_list, 2);
    outer_list[2] = make_list(another_list, 2);

    Node root = make_list(outer_list, 3);

    FlatResult flat = flatten(&root);

    for (size_t i = 0; i < flat.count; i++) {
        printf("%d ", flat.items[i]);
    }
    printf("\n");

    free(flat.items);
    free_node(&root);

    return EXIT_SUCCESS;
}