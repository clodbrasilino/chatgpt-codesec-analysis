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

GroupList *create_group_list(void) {
    GroupList *gl = (GroupList *)malloc(sizeof(GroupList));
    if (!gl) {
        return NULL;
    }
    gl->groups = NULL;
    gl->count = 0;
    gl->capacity = 0;
    return gl;
}

void free_group_list(GroupList *gl) {
    if (!gl) {
        return;
    }
    for (size_t i = 0; i < gl->count; i++) {
        free(gl->groups[i].values);
    }
    free(gl->groups);
    free(gl);
}

int add_to_group(GroupList *gl, int key, int value) {
    Group *target_group = NULL;
    for (size_t i = 0; i < gl->count; i++) {
        if (gl->groups[i].key == key) {
            target_group = &gl->groups[i];
            break;
        }
    }

    if (!target_group) {
        if (gl->count == gl->capacity) {
            size_t new_cap = gl->capacity == 0 ? 4 : gl->capacity * 2;
            Group *new_groups = (Group *)realloc(gl->groups, new_cap * sizeof(Group));
            if (!new_groups) {
                return 0;
            }
            gl->groups = new_groups;
            gl->capacity = new_cap;
        }
        target_group = &gl->groups[gl->count];
        target_group->key = key;
        target_group->values = NULL;
        target_group->count = 0;
        target_group->capacity = 0;
        gl->count++;
    }

    if (target_group->count == target_group->capacity) {
        size_t new_cap = target_group->capacity == 0 ? 4 : target_group->capacity * 2;
        int *new_values = (int *)realloc(target_group->values, new_cap * sizeof(int));
        if (!new_values) {
            return 0;
        }
        target_group->values = new_values;
        target_group->capacity = new_cap;
    }

    target_group->values[target_group->count++] = value;
    return 1;
}

GroupList *group_tuples(const Tuple *tuples, size_t tuple_count) {
    if (!tuples) {
        return NULL;
    }
    
    GroupList *gl = create_group_list();
    if (!gl) {
        return NULL;
    }

    for (size_t i = 0; i < tuple_count; i++) {
        if (!add_to_group(gl, tuples[i].second, tuples[i].first)) {
            free_group_list(gl);
            return NULL;
        }
    }
    
    return gl;
}

void print_group_list(const GroupList *gl) {
    if (!gl) {
        return;
    }
    for (size_t i = 0; i < gl->count; i++) {
        printf("Key %d: [", gl->groups[i].key);
        for (size_t j = 0; j < gl->groups[i].count; j++) {
            printf("%d%s", gl->groups[i].values[j], j + 1 < gl->groups[i].count ? ", " : "");
        }
        printf("]\n");
    }
}

int main(void) {
    Tuple tuples[] = {
        {10, 1},
        {20, 2},
        {30, 1},
        {40, 3},
        {50, 2}
    };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    GroupList *grouped = group_tuples(tuples, tuple_count);
    if (!grouped) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    print_group_list(grouped);
    free_group_list(grouped);

    return EXIT_SUCCESS;
}