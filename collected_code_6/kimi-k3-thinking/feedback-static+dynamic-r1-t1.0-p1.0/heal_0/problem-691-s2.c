#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *first;
    const char *second;
} Tuple;

typedef struct {
    char *key;
    char **members;
    size_t count;
    size_t capacity;
} Group;

typedef struct {
    Group *items;
    size_t count;
    size_t capacity;
} GroupList;

static char *copy_string(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = strlen(s) + 1;
    copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, len);
    return copy;
}

static void group_init(Group *g)
{
    g->key = NULL;
    g->members = NULL;
    g->count = 0;
    g->capacity = 0;
}

static void group_destroy(Group *g)
{
    size_t i;

    if (g == NULL) {
        return;
    }
    for (i = 0; i < g->count; i++) {
        free(g->members[i]);
    }
    free(g->members);
    free(g->key);
    group_init(g);
}

static int group_add_member(Group *g, const char *value)
{
    char **new_members;
    char *member_copy;
    size_t new_capacity;

    if (g == NULL || value == NULL) {
        return -1;
    }
    member_copy = copy_string(value);
    if (member_copy == NULL) {
        return -1;
    }
    if (g->count == g->capacity) {
        new_capacity = (g->capacity == 0) ? 4 : g->capacity * 2;
        new_members = realloc(g->members, new_capacity * sizeof(*new_members));
        if (new_members == NULL) {
            free(member_copy);
            return -1;
        }
        g->members = new_members;
        g->capacity = new_capacity;
    }
    g->members[g->count] = member_copy;
    g->count++;
    return 0;
}

static void group_list_init(GroupList *list)
{
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

static void group_list_destroy(GroupList *list)
{
    size_t i;

    if (list == NULL) {
        return;
    }
    for (i = 0; i < list->count; i++) {
        group_destroy(&list->items[i]);
    }
    free(list->items);
    group_list_init(list);
}

static Group *group_list_find(GroupList *list, const char *key)
{
    size_t i;

    for (i = 0; i < list->count; i++) {
        if (strcmp(list->items[i].key, key) == 0) {
            return &list->items[i];
        }
    }
    return NULL;
}

static Group *group_list_add(GroupList *list, const char *key)
{
    Group *new_items;
    Group *g;
    size_t new_capacity;

    if (list->count == list->capacity) {
        new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;
        new_items = realloc(list->items, new_capacity * sizeof(*new_items));
        if (new_items == NULL) {
            return NULL;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    g = &list->items[list->count];
    group_init(g);
    g->key = copy_string(key);
    if (g->key == NULL) {
        return NULL;
    }
    list->count++;
    return g;
}

int group_tuples(const Tuple *tuples, size_t n, GroupList *result)
{
    size_t i;
    Group *g;

    if (result == NULL) {
        return -1;
    }
    group_list_init(result);
    if (tuples == NULL && n > 0) {
        return -1;
    }
    for (i = 0; i < n; i++) {
        if (tuples[i].first == NULL || tuples[i].second == NULL) {
            group_list_destroy(result);
            return -1;
        }
        g = group_list_find(result, tuples[i].second);
        if (g == NULL) {
            g = group_list_add(result, tuples[i].second);
            if (g == NULL) {
                group_list_destroy(result);
                return -1;
            }
        }
        if (group_add_member(g, tuples[i].first) != 0) {
            group_list_destroy(result);
            return -1;
        }
    }
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {"apple", "fruit"},
        {"carrot", "vegetable"},
        {"banana", "fruit"},
        {"broccoli", "vegetable"},
        {"cherry", "fruit"},
        {"salmon", "fish"},
        {"spinach", "vegetable"},
        {"tuna", "fish"}
    };
    GroupList result;
    size_t n;
    size_t i;
    size_t j;

    n = sizeof(tuples) / sizeof(tuples[0]);
    if (group_tuples(tuples, n, &result) != 0) {
        fprintf(stderr, "Error: failed to group tuples\n");
        return EXIT_FAILURE;
    }
    for (i = 0; i < result.count; i++) {
        printf("%s: ", result.items[i].key);
        for (j = 0; j < result.items[i].count; j++) {
            printf("%s%s", result.items[i].members[j],
                   (j + 1 < result.items[i].count) ? ", " : "");
        }
        printf("\n");
    }
    group_list_destroy(&result);
    return EXIT_SUCCESS;
}