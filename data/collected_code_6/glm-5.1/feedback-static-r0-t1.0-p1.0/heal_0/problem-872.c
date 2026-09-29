#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    enum { INTEGER, LIST } type;
    union {
        int integer;
        struct {
            struct Node* items;
            int count;
        } list;
    } data;
} Node;

Node create_integer(int value) {
    Node n;
    n.type = INTEGER;
    n.data.integer = value;
    return n;
}

Node create_list(Node* items, int count) {
    Node n;
    n.type = LIST;
    n.data.list.items = items;
    n.data.list.count = count;
    return n;
}

bool is_equal(Node a, Node b) {
    if (a.type != b.type) {
        return false;
    }
    if (a.type == INTEGER) {
        return a.data.integer == b.data.integer;
    }
    if (a.type == LIST) {
        if (a.data.list.count != b.data.list.count) {
            return false;
        }
        for (int i = 0; i < a.data.list.count; i++) {
            if (!is_equal(a.data.list.items[i], b.data.list.items[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool is_subset(Node subset, Node superset) {
    if (subset.type == INTEGER) {
        return is_equal(subset, superset);
    }
    if (superset.type != LIST) {
        return false;
    }
    if (subset.data.list.count > superset.data.list.count) {
        return false;
    }
    bool* used = (bool*)calloc(superset.data.list.count, sizeof(bool));
    if (used == NULL) {
        return false;
    }
    bool result = true;
    for (int i = 0; i < subset.data.list.count; i++) {
        bool found = false;
        for (int j = 0; j < superset.data.list.count; j++) {
            if (!used[j] && is_equal(subset.data.list.items[i], superset.data.list.items[j])) {
                used[j] = true;
                found = true;
                break;
            }
        }
        if (!found) {
            result = false;
            break;
        }
    }
    free(used);
    return result;
}

void free_node(Node n) {
    if (n.type == LIST) {
        for (int i = 0; i < n.data.list.count; i++) {
            free_node(n.data.list.items[i]);
        }
        free(n.data.list.items);
    }
}

int main() {
    Node a1 = create_integer(1);
    Node a2 = create_integer(2);
    Node a3 = create_integer(3);
    Node sub_arr1[] = {a1, a2};
    Node sub1 = create_list(sub_arr1, 2);
    Node sup_arr1[] = {a2, a3, a1};
    Node sup1 = create_list(sup_arr1, 3);
    bool res1 = is_subset(sub1, sup1);
    printf("%d\n", res1);

    Node b1 = create_integer(5);
    Node b2 = create_integer(6);
    Node nested_sub_arr[] = {a1, b1};
    Node nested_sub = create_list(nested_sub_arr, 2);
    Node nested_sup_arr[] = {a1, b2, a2};
    Node nested_sup = create_list(nested_sup_arr, 3);
    bool res2 = is_subset(nested_sub, nested_sup);
    printf("%d\n", res2);

    Node deep_sub_arr[] = {sub1, a3};
    Node deep_sub = create_list(deep_sub_arr, 2);
    Node deep_sup_arr[] = {a3, sup1};
    Node deep_sup = create_list(deep_sup_arr, 2);
    bool res3 = is_subset(deep_sub, deep_sup);
    printf("%d\n", res3);

    free_node(deep_sub);
    free_node(deep_sup);
    free_node(nested_sub);
    free_node(nested_sup);
    free_node(sub1);
    free_node(sup1);

    return 0;
}