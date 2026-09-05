#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NestedList {
    int isInteger;
    int value;
    struct NestedList **children;
    int numChildren;
} NestedList;

NestedList *createInteger(int value) {
    NestedList *node = (NestedList *)malloc(sizeof(NestedList));
    if (node == NULL) {
        return NULL;
    }
    node->isInteger = 1;
    node->value = value;
    node->children = NULL;
    node->numChildren = 0;
    return node;
}

NestedList *createList(void) {
    NestedList *node = (NestedList *)malloc(sizeof(NestedList));
    if (node == NULL) {
        return NULL;
    }
    node->isInteger = 0;
    node->value = 0;
    node->children = NULL;
    node->numChildren = 0;
    return node;
}

int addChild(NestedList *parent, NestedList *child) {
    if (parent == NULL || child == NULL || parent->isInteger) {
        return 0;
    }
    NestedList **newChildren = (NestedList **)realloc(parent->children,
        (size_t)(parent->numChildren + 1) * sizeof(NestedList *));
    if (newChildren == NULL) {
        return 0;
    }
    parent->children = newChildren;
    parent->children[parent->numChildren] = child;
    parent->numChildren++;
    return 1;
}

int isEqual(NestedList *a, NestedList *b) {
    if (a == NULL || b == NULL) {
        return (a == b);
    }
    if (a->isInteger != b->isInteger) {
        return 0;
    }
    if (a->isInteger) {
        return (a->value == b->value);
    }
    if (a->numChildren != b->numChildren) {
        return 0;
    }
    for (int i = 0; i < a->numChildren; i++) {
        if (!isEqual(a->children[i], b->children[i])) {
            return 0;
        }
    }
    return 1;
}

int isSubset(NestedList *sub, NestedList *super) {
    if (sub == NULL || super == NULL) {
        return 0;
    }
    if (sub->isInteger) {
        if (super->isInteger) {
            return (sub->value == super->value);
        }
        for (int i = 0; i < super->numChildren; i++) {
            if (isSubset(sub, super->children[i])) {
                return 1;
            }
        }
        return 0;
    }
    if (super->isInteger) {
        return 0;
    }
    for (int i = 0; i < sub->numChildren; i++) {
        int found = 0;
        for (int j = 0; j < super->numChildren; j++) {
            if (isEqual(sub->children[i], super->children[j])) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
    }
    return 1;
}

void freeNestedList(NestedList *node) {
    if (node == NULL) {
        return;
    }
    if (!node->isInteger && node->children != NULL) {
        for (int i = 0; i < node->numChildren; i++) {
            freeNestedList(node->children[i]);
        }
        free(node->children);
    }
    free(node);
}

int main(void) {
    NestedList *list1 = createList();
    NestedList *list2 = createList();
    NestedList *sub1 = createList();
    NestedList *sub2 = createList();

    if (list1 == NULL || list2 == NULL || sub1 == NULL || sub2 == NULL) {
        freeNestedList(list1);
        freeNestedList(list2);
        freeNestedList(sub1);
        freeNestedList(sub2);
        return 1;
    }

    NestedList *a = createInteger(1);
    NestedList *b = createInteger(2);
    NestedList *c = createInteger(3);
    NestedList *d = createInteger(4);

    if (a == NULL || b == NULL || c == NULL || d == NULL) {
        freeNestedList(a);
        freeNestedList(b);
        freeNestedList(c);
        freeNestedList(d);
        freeNestedList(list1);
        freeNestedList(list2);
        freeNestedList(sub1);
        freeNestedList(sub2);
        return 1;
    }

    if (!addChild(sub1, a) || !addChild(sub1, b)) {
        freeNestedList(list1);
        freeNestedList(list2);
        freeNestedList(sub1);
        freeNestedList(sub2);
        return 1;
    }

    if (!addChild(sub2, c) || !addChild(sub2, d)) {
        freeNestedList(list1);
        freeNestedList(list2);
        freeNestedList(sub1);
        freeNestedList(sub2);
        return 1;
    }

    if (!addChild(list1, sub1) || !addChild(list1, sub2)) {
        freeNestedList(list1);
        freeNestedList(list2);
        return 1;
    }

    NestedList *e = createInteger(1);
    NestedList *f = createInteger(2);

    if (e == NULL || f == NULL) {
        freeNestedList(e);
        freeNestedList(f);
        freeNestedList(list1);
        freeNestedList(list2);
        return 1;
    }

    if (!addChild(list2, e) || !addChild(list2, f)) {
        freeNestedList(list1);
        freeNestedList(list2);
        return 1;
    }

    if (isSubset(list2, list1)) {
        printf("list2 is a subset of list1\n");
    } else {
        printf("list2 is NOT a subset of list1\n");
    }

    if (isSubset(list1, list2)) {
        printf("list1 is a subset of list2\n");
    } else {
        printf("list1 is NOT a subset of list2\n");
    }

    freeNestedList(list1);
    freeNestedList(list2);

    return 0;
}