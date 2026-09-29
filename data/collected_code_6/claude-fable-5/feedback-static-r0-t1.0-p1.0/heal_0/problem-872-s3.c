#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum { ITEM_INT, ITEM_LIST } ItemType;

typedef struct List List;
typedef struct Item Item;

struct Item {
    ItemType type;
    int value;
    List *sublist;
    Item *next;
};

struct List {
    Item *head;
    Item *tail;
};

static List *list_create(void)
{
    List *l = malloc(sizeof(List));
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL;
    return l;
}

static void list_free(List *l)
{
    Item *cur;
    Item *next;

    if (l == NULL) {
        return;
    }
    cur = l->head;
    while (cur != NULL) {
        next = cur->next;
        if (cur->type == ITEM_LIST) {
            list_free(cur->sublist);
        }
        free(cur);
        cur = next;
    }
    free(l);
}

static bool list_append_int(List *l, int v)
{
    Item *it;

    if (l == NULL) {
        return false;
    }
    it = malloc(sizeof(Item));
    if (it == NULL) {
        return false;
    }
    it->type = ITEM_INT;
    it->value = v;
    it->sublist = NULL;
    it->next = NULL;
    if (l->tail == NULL) {
        l->head = it;
    } else {
        l->tail->next = it;
    }
    l->tail = it;
    return true;
}

static bool list_append_list(List *l, List *sub)
{
    Item *it;

    if (l == NULL || sub == NULL) {
        list_free(sub);
        return false;
    }
    it = malloc(sizeof(Item));
    if (it == NULL) {
        list_free(sub);
        return false;
    }
    it->type = ITEM_LIST;
    it->value = 0;
    it->sublist = sub;
    it->next = NULL;
    if (l->tail == NULL) {
        l->head = it;
    } else {
        l->tail->next = it;
    }
    l->tail = it;
    return true;
}

static bool lists_equal(const List *a, const List *b);

static bool items_equal(const Item *a, const Item *b)
{
    if (a == NULL || b == NULL) {
        return false;
    }
    if (a->type != b->type) {
        return false;
    }
    if (a->type == ITEM_INT) {
        return a->value == b->value;
    }
    return lists_equal(a->sublist, b->sublist);
}

static bool lists_equal(const List *a, const List *b)
{
    const Item *ia;
    const Item *ib;

    if (a == NULL || b == NULL) {
        return a == b;
    }
    ia = a->head;
    ib = b->head;
    while (ia != NULL && ib != NULL) {
        if (!items_equal(ia, ib)) {
            return false;
        }
        ia = ia->next;
        ib = ib->next;
    }
    return ia == NULL && ib == NULL;
}

static bool list_contains(const List *super, const Item *it)
{
    const Item *cur;

    if (super == NULL || it == NULL) {
        return false;
    }
    cur = super->head;
    while (cur != NULL) {
        if (items_equal(cur, it)) {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

static bool is_subset(const List *sub, const List *super)
{
    const Item *cur;

    if (sub == NULL) {
        return true;
    }
    if (super == NULL) {
        return sub->head == NULL;
    }
    cur = sub->head;
    while (cur != NULL) {
        if (!list_contains(super, cur)) {
            return false;
        }
        cur = cur->next;
    }
    return true;
}

int main(void)
{
    List *super = NULL;
    List *sub = NULL;
    List *notsub = NULL;
    List *inner1 = NULL;
    List *inner2 = NULL;
    List *inner3 = NULL;
    int status = EXIT_FAILURE;

    super = list_create();
    sub = list_create();
    notsub = list_create();
    inner1 = list_create();
    inner2 = list_create();
    inner3 = list_create();

    if (super == NULL || sub == NULL || notsub == NULL ||
        inner1 == NULL || inner2 == NULL || inner3 == NULL) {
        fprintf(stderr, "Allocation failure\n");
        goto cleanup;
    }

    if (!list_append_int(super, 1)) { goto cleanup; }
    if (!list_append_int(super, 2)) { goto cleanup; }
    if (!list_append_int(inner1, 3)) { goto cleanup; }
    if (!list_append_int(inner1, 4)) { goto cleanup; }
    if (!list_append_list(super, inner1)) { inner1 = NULL; goto cleanup; }
    inner1 = NULL;
    if (!list_append_int(super, 5)) { goto cleanup; }

    if (!list_append_int(sub, 2)) { goto cleanup; }
    if (!list_append_int(inner2, 3)) { goto cleanup; }
    if (!list_append_int(inner2, 4)) { goto cleanup; }
    if (!list_append_list(sub, inner2)) { inner2 = NULL; goto cleanup; }
    inner2 = NULL;

    if (!list_append_int(inner3, 3)) { goto cleanup; }
    if (!list_append_int(inner3, 9)) { goto cleanup; }
    if (!list_append_list(notsub, inner3)) { inner3 = NULL; goto cleanup; }
    inner3 = NULL;

    printf("sub is subset of super: %s\n",
           is_subset(sub, super) ? "true" : "false");
    printf("notsub is subset of super: %s\n",
           is_subset(notsub, super) ? "true" : "false");

    status = EXIT_SUCCESS;

cleanup:
    list_free(super);
    list_free(sub);
    list_free(notsub);
    list_free(inner1);
    list_free(inner2);
    list_free(inner3);
    return status;
}