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
    g->count = 0;
    g->values = (int *)malloc(g->capacity * sizeof(int));
    if (g->values == NULL) {
        exit(EXIT_FAILURE);
    }
}

void add_value_to_group(Group *g, int value) {
    if (g->count == g->capacity) {
        g->capacity *= 2;
        int *new_values = (int *)realloc(g->values, g->capacity * sizeof(int));
        if (new_values == NULL) {
            free(g->values);
            exit(EXIT_FAILURE);
        }
        g->values = new_values;
    }
    g->values[g->count++] = value;
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
    gl.capacity = 4;
    gl.count = 0;
    gl.groups = (Group *)malloc(gl.capacity * sizeof(Group));
    if (gl.groups == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < gl.count; j++) {
            if (gl.groups[j].key == tuples[i].second) {
                add_value_to_group(&gl.groups[j], tuples[i].first);
                found = 1;
                break;
            }
        }
        if (!found) {
            if (gl.count == gl.capacity) {
                gl.capacity *= 2;
                Group *new_groups = (Group *)realloc(gl.groups, gl.capacity * sizeof(Group));
                if (new_groups == NULL) {
                    free_group_list(&gl);
                    exit(EXIT_FAILURE);
                }
                gl.groups = new_groups;
            }
            init_group(&gl.groups[gl.count], tuples[i].second);
            add_value_to_group(&gl.groups[gl.count], tuples[i].first);
            gl.count++;
        }
    }
    return gl;
}

int main() {
    Tuple tuples[] = {
        {1, 2},
        {3, 2},
        {5, 4},
        {7, 4},
        {9, 6}
    };
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