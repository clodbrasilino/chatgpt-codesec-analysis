#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char *name;
} Tuple;

void rearrange_tuples(Tuple* tuples, int tuples_count, const int* order, int order_count, Tuple** rearranged_tuples, int* rearranged_count) {
    if (tuples == NULL || order == NULL || rearranged_tuples == NULL || rearranged_count == NULL) {
        return;
    }

    *rearranged_tuples = (Tuple*)malloc(order_count * sizeof(Tuple));
    if (*rearranged_tuples == NULL) {
        return;
    }

    *rearranged_count = 0;

    for (int i = 0; i < order_count; ++i) {
        for (int j = 0; j < tuples_count; ++j) {
            if (tuples[j].id == order[i]) {
                (*rearranged_tuples)[*rearranged_count].id = tuples[j].id;
                size_t name_len = strlen(tuples[j].name);
                (*rearranged_tuples)[*rearranged_count].name = (char*)malloc(name_len + 1);
                if ((*rearranged_tuples)[*rearranged_count].name != NULL) {
                    strncpy((*rearranged_tuples)[*rearranged_count].name, tuples[j].name, name_len + 1);
                }
                (*rearranged_count)++;
                break;
            }
        }
    }
}

int main(void) {
    Tuple tuples[4];
    const char* names[] = {"Charlie", "Alice", "Dave", "Bob"};
    int ids[] = {3, 1, 4, 2};
    int tuples_count = 4;

    for (int i = 0; i < tuples_count; ++i) {
        tuples[i].id = ids[i];
        size_t len = strlen(names[i]);
        tuples[i].name = (char*)malloc(len + 1);
        if (tuples[i].name != NULL) {
            strncpy(tuples[i].name, names[i], len + 1);
        }
    }

    int order[] = {2, 1, 4, 3};
    int order_count = sizeof(order) / sizeof(order[0]);

    Tuple* rearranged = NULL;
    int rearranged_count = 0;

    rearrange_tuples(tuples, tuples_count, order, order_count, &rearranged, &rearranged_count);

    if (rearranged != NULL) {
        for (int i = 0; i < rearranged_count; ++i) {
            printf("{%d, \"%s\"}\n", rearranged[i].id, rearranged[i].name);
            free(rearranged[i].name);
        }
        free(rearranged);
    }

    for (int i = 0; i < tuples_count; ++i) {
        free(tuples[i].name);
    }

    return 0;
}