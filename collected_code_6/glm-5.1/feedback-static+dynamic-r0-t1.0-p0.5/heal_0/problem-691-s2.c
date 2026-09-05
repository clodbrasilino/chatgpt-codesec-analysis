#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int key;
    int *values;
    int count;
    int capacity;
} Group;

typedef struct {
    Group *groups;
    int count;
    int capacity;
} GroupList;

void init_group(Group *g, int key) {
    g->key = key;
    g->capacity = 4;
    g->values = (int *)malloc(g->capacity * sizeof(int));
    g->count = 0;
}

void init_group_list(GroupList *gl) {
    gl->capacity = 4;
    gl->groups = (Group *)malloc(gl->capacity * sizeof(Group));
    gl->count = 0;
}

void add_value_to_group(Group *g, int value) {
    if (g->count == g->capacity) {
        g->capacity *= 2;
        g->values = (int *)realloc(g->values, g->capacity * sizeof(int));
    }
    g->values[g->count++] = value;
}

Group *find_group(GroupList *gl, int key) {
    for (int i = 0; i < gl->count; i++) {
        if (gl->groups[i].key == key) {
            return &gl->groups[i];
        }
    }
    return NULL;
}

void add_to_group_list(GroupList *gl, int key, int value) {
    Group *existing = find_group(gl, key);
    if (existing != NULL) {
        add_value_to_group(existing, value);
    } else {
        if (gl->count == gl->capacity) {
            gl->capacity *= 2;
            gl->groups = (Group *)realloc(gl->groups, gl->capacity * sizeof(Group));
        }
        Group new_group;
        init_group(&new_group, key);
        add_value_to_group(&new_group, value);
        gl->groups[gl->count++] = new_group;
    }
}

void free_group_list(GroupList *gl) {
    for (int i = 0; i < gl->count; i++) {
        free(gl->groups[i].values);
    }
    free(gl->groups);
    gl->count = 0;
    gl->capacity = 0;
}

GroupList group_tuples(Tuple *tuples, int size) {
    GroupList gl;
    init_group_list(&gl);
    for (int i = 0; i < size; i++) {
        add_to_group_list(&gl, tuples[i].second, tuples[i].first);
    }
    return gl;
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 2}, {4, 5}, {6, 5}, {7, 8}};
    int size = sizeof(tuples) / sizeof(tuples[0]);

    GroupList gl = group_tuples(tuples, size);

    for (int i = 0; i < gl.count; i++) {
        printf("%d: [", gl.groups[i].key);
        for (int j = 0; j < gl.groups[i].count; j++) {
            printf("%d", gl.groups[i].values[j]);
            if (j < gl.groups[i].count - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }

    free_group_list(&gl);

    return 0;
}