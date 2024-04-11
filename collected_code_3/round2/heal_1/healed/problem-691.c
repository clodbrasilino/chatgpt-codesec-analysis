#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int key;
    int *values;
    int count;
    int size;
} Group;

Group* groupBySecond(Tuple* tuples, int size, int* groupSize) {
    Group* groups = malloc(size * sizeof(Group));

    if(groups == NULL) {
        return NULL;
    }

    *groupSize = 0;

    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < *groupSize; j++) {
            if (groups[j].key == tuples[i].second) {
                if (groups[j].count == groups[j].size) {
                    groups[j].size *= 2;
                    groups[j].values = realloc(groups[j].values, groups[j].size * sizeof(int));

                    if(groups[j].values == NULL) {
                        return NULL;
                    }
                }
                groups[j].values[groups[j].count++] = tuples[i].first;
                found = 1;
                break;
            }
        }
        if (!found) {
            groups[*groupSize].key = tuples[i].second;
            groups[*groupSize].count = 1;
            groups[*groupSize].size = 2;
            groups[*groupSize].values = malloc(2 * sizeof(int));

            if(groups[*groupSize].values == NULL) {
                return NULL;
            }

            groups[*groupSize].values[0] = tuples[i].first;
            (*groupSize)++;
        }
    }

    return groups;
}

int main() {
    Tuple tuples[] = {{1, 2}, {2, 3}, {3, 2}, {4, 5}, {5, 3}};
    int size = sizeof(tuples) / sizeof(Tuple);
    int groupSize;

    Group* groups = groupBySecond(tuples, size, &groupSize);

    if(groups == NULL) {
        return 1;
    }

    for (int i = 0; i < groupSize; i++) {
        printf("Group %d: ", groups[i].key);
        for (int j = 0; j < groups[i].count; j++) {
            printf("%d ", groups[i].values[j]);
        }
        printf("\n");
    }

    for (int i = 0; i < groupSize; i++) {
        free(groups[i].values);
    }
    free(groups);

    return 0;
}