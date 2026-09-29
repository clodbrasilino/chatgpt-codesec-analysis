#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int key;
    int *values;
    size_t count;
    size_t capacity;
} Group;

typedef struct {
    Group *groups;
    size_t count;
    size_t capacity;
} GroupList;

static int group_list_init(GroupList *gl)
{
    gl->count = 0;
    gl->capacity = 4;
    gl->groups = malloc(gl->capacity * sizeof(Group));
    if (gl->groups == NULL) {
        return -1;
    }
    return 0;
}

static void group_list_free(GroupList *gl)
{
    size_t i;

    if (gl == NULL || gl->groups == NULL) {
        return;
    }
    for (i = 0; i < gl->count; i++) {
        free(gl->groups[i].values);
        gl->groups[i].values = NULL;
    }
    free(gl->groups);
    gl->groups = NULL;
    gl->count = 0;
    gl->capacity = 0;
}

static Group *find_group(GroupList *gl, int key)
{
    size_t i;

    for (i = 0; i < gl->count; i++) {
        if (gl->groups[i].key == key) {
            return &gl->groups[i];
        }
    }
    return NULL;
}

static int add_group(GroupList *gl, int key, Group **out)
{
    Group *g;

    if (gl->count == gl->capacity) {
        size_t new_capacity = gl->capacity * 2;
        Group *tmp = realloc(gl->groups, new_capacity * sizeof(Group));
        if (tmp == NULL) {
            return -1;
        }
        gl->groups = tmp;
        gl->capacity = new_capacity;
    }
    g = &gl->groups[gl->count];
    g->key = key;
    g->count = 0;
    g->capacity = 4;
    g->values = malloc(g->capacity * sizeof(int));
    if (g->values == NULL) {
        return -1;
    }
    gl->count++;
    *out = g;
    return 0;
}

static int group_add_value(Group *g, int value)
{
    if (g->count == g->capacity) {
        size_t new_capacity = g->capacity * 2;
        int *tmp = realloc(g->values, new_capacity * sizeof(int));
        if (tmp == NULL) {
            return -1;
        }
        g->values = tmp;
        g->capacity = new_capacity;
    }
    g->values[g->count] = value;
    g->count++;
    return 0;
}

int group_tuples(const Tuple *tuples, size_t n, GroupList *gl)
{
    size_t i;

    if (tuples == NULL || gl == NULL) {
        return -1;
    }
    if (group_list_init(gl) != 0) {
        return -1;
    }
    for (i = 0; i < n; i++) {
        Group *g = find_group(gl, tuples[i].second);
        if (g == NULL) {
            if (add_group(gl, tuples[i].second, &g) != 0) {
                group_list_free(gl);
                return -1;
            }
        }
        if (group_add_value(g, tuples[i].first) != 0) {
            group_list_free(gl);
            return -1;
        }
    }
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {1, 5}, {7, 5}, {3, 7}, {8, 7}, {2, 5}, {9, 3}
    };
    size_t n = sizeof(tuples) / sizeof(tuples[0]);
    GroupList gl;
    size_t i;
    size_t j;

    if (group_tuples(tuples, n, &gl) != 0) {
        fprintf(stderr, "Failed to group tuples\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < gl.count; i++) {
        printf("%d: [", gl.groups[i].key);
        for (j = 0; j < gl.groups[i].count; j++) {
            if (j > 0) {
                printf(", ");
            }
            printf("%d", gl.groups[i].values[j]);
        }
        printf("]\n");
    }

    group_list_free(&gl);
    return EXIT_SUCCESS;
}