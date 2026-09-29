#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int key;
    int* values;
    int count;
    int capacity;
} Group;

typedef struct {
    Group* groups;
    int count;
    int capacity;
} GroupList;

GroupList* group_tuples(Tuple* tuples, int count) {
    GroupList* gl = malloc(sizeof(GroupList));
    if (!gl) {
        return NULL;
    }
    
    gl->capacity = 10;
    gl->count = 0;
    gl->groups = malloc(gl->capacity * sizeof(Group));
    if (!gl->groups) {
        free(gl);
        return NULL;
    }
    
    for (int i = 0; i < count; i++) {
        int found = 0;
        int group_idx = -1;
        for (int j = 0; j < gl->count; j++) {
            if (gl->groups[j].key == tuples[i].second) {
                found = 1;
                group_idx = j;
                break;
            }
        }
        
        if (found) {
            Group* g = &gl->groups[group_idx];
            if (g->count >= g->capacity) {
                g->capacity = g->capacity * 2;
                int* new_values = realloc(g->values, g->capacity * sizeof(int));
                if (!new_values) {
                    for (int k = 0; k < gl->count; k++) {
                        free(gl->groups[k].values);
                    }
                    free(gl->groups);
                    free(gl);
                    return NULL;
                }
                g->values = new_values;
            }
            g->values[g->count++] = tuples[i].first;
        } else {
            if (gl->count >= gl->capacity) {
                gl->capacity *= 2;
                Group* new_groups = realloc(gl->groups, gl->capacity * sizeof(Group));
                if (!new_groups) {
                    for (int k = 0; k < gl->count; k++) {
                        free(gl->groups[k].values);
                    }
                    free(gl->groups);
                    free(gl);
                    return NULL;
                }
                gl->groups = new_groups;
            }
            
            Group* g = &gl->groups[gl->count];
            g->key = tuples[i].second;
            g->capacity = 2;
            g->count = 1;
            g->values = malloc(g->capacity * sizeof(int));
            if (!g->values) {
                for (int k = 0; k < gl->count; k++) {
                    free(gl->groups[k].values);
                }
                free(gl->groups);
                free(gl);
                return NULL;
            }
            g->values[0] = tuples[i].first;
            gl->count++;
        }
    }
    
    return gl;
}

void free_group_list(GroupList* gl) {
    if (!gl) {
        return;
    }
    for (int i = 0; i < gl->count; i++) {
        free(gl->groups[i].values);
    }
    free(gl->groups);
    free(gl);
}

int main(void) {
    Tuple tuples[] = {
        {1, 10},
        {2, 20},
        {3, 10},
        {4, 30},
        {5, 20}
    };
    int count = sizeof(tuples) / sizeof(tuples[0]);
    
    GroupList* gl = group_tuples(tuples, count);
    if (!gl) {
        return 1;
    }
    
    for (int i = 0; i < gl->count; i++) {
        printf("Key %d: ", gl->groups[i].key);
        for (int j = 0; j < gl->groups[i].count; j++) {
            printf("%d ", gl->groups[i].values[j]);
        }
        printf("\n");
    }
    
    free_group_list(gl);
    
    return 0;
}